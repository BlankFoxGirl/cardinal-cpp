#include "TCPClient.hpp"
#include "../Exception/TCPSocketCreationException.h"
#include "../Exception/TCPSocketBindException.h"
#include "../Exception/TCPSocketListenException.h"
#include "../Entity/UserEntity.hpp"
#include <iostream>
#include <vector>
#include <sys/poll.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <fstream>
#include <string>
#include <cstring>
#include <signal.h>
#include <arpa/inet.h>

using namespace std;

using namespace Cardinal::Service;

typedef void *(*THREADFUNCPTR)(void *);
pthread_t thread_tcp[100], thread_file[10];
int threadno_tcp = 0;

/* message type that will be sent by the client through TCP connection */
struct msg
{
    char filename[100];
    char file[2048];
};

void TCPListenerService::Bind(string port, char *address)
{
    this->logService_.Verbose("Called TCPListenerService::Bind");
    // Specified Port!
    this->Port = stoi(port);

    // Specified Address!
    this->Address = inet_pton(AF_INET, address, NULL);
}

void TCPListenerService::Bind(string port, string address)
{
    this->logService_.Verbose("Called TCPListenerService::Bind");
    // Specified Port!
    this->logService_.Verbose("TCPListenerService::Bind Set Port");
    this->Port = stoi(port);

    // Specified Address!
    this->logService_.Verbose("TCPListenerService::Bind Convert Str to Const Char*");
    const char* addressChar = address.c_str();
    
    this->logService_.Verbose("TCPListenerService::Bind Set Address");
    inet_pton(AF_INET, addressChar, &this->Address);
    this->logService_.Verbose("TCPListenerService::Bind Complete");
}

void TCPListenerService::Start()
{
    this->logService_.Verbose("Called TCPListenerService::Start");
    sockaddr_in clientaddr; // client address
    sockaddr_in serverAddress = ConfigureServerAddress();
    socklen_t addrlen = sizeof(clientaddr);
    this->mistfd = 0;

    CreateSocketStream();
    StoreServerAddressInMemory(serverAddress);
    BindServerAddressAndPort(serverAddress);
    ListenForConnections();
    SetSignalHandlers();

    this->logService_.Info("Server is listening on port ", to_string(this->Port));
    SetSocketData(clientaddr, addrlen);
}

void TCPListenerService::ListenForConnections()
{
    this->logService_.Verbose("Called TCPListenerService::ListenForConnections");
    if ((listen(this->mistfd, 5)) != 0)
    {
        throw Cardinal::Exception::TCPSocketListenException();
    }
}

void TCPListenerService::BindServerAddressAndPort(sockaddr_in serverAddress)
{
    this->logService_.Verbose("Called TCPListenerService::BindServerAddressAndPort");
    if (::bind(this->mistfd, (sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        throw Cardinal::Exception::TCPSocketBindException();
    }
}

void TCPListenerService::StoreServerAddressInMemory(sockaddr_in serverAddress)
{
    this->logService_.Verbose("Called TCPListenerService::StoreServerAddressInMemory");
    memset((sockaddr *)&serverAddress, 0, sizeof(serverAddress));
}

void TCPListenerService::SetSignalHandlers()
{
    this->logService_.Verbose("Called TCPListenerService::SetSignalHandlers");
    signal(SIGINT, TCPListenerService::sig_handler);
    signal(SIGTSTP, TCPListenerService::sig_handler);
}

void TCPListenerService::SetSocketData(sockaddr_in &clientaddr, socklen_t &addrlen)
{
    this->logService_.Verbose("Called TCPListenerService::SetSocketData");
    this->clientaddr = clientaddr;
    this->addrlen = addrlen;
}

void TCPListenerService::Accept()
{
    int connfd;
    if ((connfd = accept(this->mistfd, (sockaddr *)&this->clientaddr, &this->addrlen)) < 0)
    {
        this->logService_.Error("Server accept failed...", "Client connection declined.");
    }
    else
    {
        this->logService_.Debug("Client connection accepted!");
    }

    /* Filling the parameter values of the threaded function */
    req *r = new req;      // allocate memory
    bzero(r, sizeof(req)); // Clear memory
    r->addlen = addrlen;
    r->clientaddr = clientaddr;
    r->des = connfd;

    auto context = std::make_tuple(this, r);

    pthread_create(&thread_tcp[threadno_tcp++], NULL, Connection, static_cast<void *>(&context));

    if (threadno_tcp == 100)
    {
        threadno_tcp = 0;
    }
}

void *TCPListenerService::Connection(void *args)
{
    // Map args to tuple
    std::tuple<TCPListenerService*, req*> arg = *reinterpret_cast<std::tuple<TCPListenerService*, req*>*>(args);

    // Extract first element of tuple args
    auto t = std::get<0>(arg);

    // Extract second element of tuple args
    auto c = std::get<1>(arg);

    return reinterpret_cast<TCPListenerService*>(t)->LocalConnection(c);
}

void *TCPListenerService::LocalConnection(void *args)
{
    this->logService_.Verbose("Called TCPListenerService::LocalConnection");
    req sock = *((req *)args);
    msg buffer;
    vector<char> buf(32); // you are using C++ not C
    int n = 1;
    // auto User = Cardinal::Entity::UserEntity(sock);
    auto User = this->userService_.RegisterConnection();
    std::string connectionUUID = User.getUUID();
    this->logService_.Debug("Connection assigned to userUUID: " + connectionUUID);
    timeval t;
    t.tv_sec = 2;
    t.tv_usec = 2000;

    struct pollfd fds[200];
    memset(fds, 0 , sizeof(fds));

    /*************************************************************/
    /* Set up the initial listening socket                        */
    /*************************************************************/
    fds[0].fd = sock.des;
    fds[0].events = POLLIN;

    while (n >= 0)
    {
        /* Read the packet sent by the established client */
        // n = read(sock.des, &buffer, sizeof(buffer));
        if (User.hasMessagesToBeSent()) {
            this->logService_.Verbose("User has messages waiting to be sent.");
            string message = User.GetMessageToSend();
            this->logService_.Debug("Sending message " + string(message), " to userUUID: " + connectionUUID);
            n = write(sock.des, &message, sizeof(message));
            this->logService_.Debug("Message sent to userUUID: " + connectionUUID);
        }

        n = poll(fds, 1, 500);
        if (n > 0)
        {
            this->logService_.Verbose("Data available to be read from userUUID: " + connectionUUID);
            n = read(sock.des, buf.data(), buf.size());

            if (buf.size() != 0) {
                string data;
                std::transform(buf.begin(), buf.end(), std::back_inserter(data),
                [](char c)
                {
                    return c;
                });

                this->logService_.Debug(data);
                User.Write(data);
            }
        }
    }

    close(sock.des);
    this->logService_.Verbose("TCPListenerService::LocalConnection Complete");

    return args;
}

void TCPListenerService::CreateSocketStream()
{
    this->logService_.Verbose("Called TCPListenerService::CreateSocketStream");
    if ((this->mistfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        this->logService_.Verbose("TCPListenerService::mistfd as a socket == -1");
        throw Cardinal::Exception::TCPSocketCreationException();
    }

    // fcntl(this->mistfd, F_SETFL, O_NONBLOCK);
}

sockaddr_in TCPListenerService::ConfigureServerAddress()
{
    this->logService_.Verbose("Called TCPListenerService::ConfigureServerAddress");
    sockaddr_in serverAddress;                            // server address
    serverAddress.sin_family = AF_INET;                   // IPv4 address family
    serverAddress.sin_addr.s_addr = htons(this->Address); // Give the local machine address
    serverAddress.sin_port = htons(this->Port);           // Port at which server listens to the requests

    return serverAddress;
}