#include "TCPClient.hpp"
#include "Cardinal/Exception/TCPSocketCreationException.h"
#include "Cardinal/Exception/TCPSocketBindException.h"
#include "Cardinal/Exception/TCPSocketListenException.h"
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

using namespace Cardinal::Service::Communication;

typedef void *(*THREADFUNCPTR)(void *);
pthread_t thread_tcp[100], thread_file[10];
int threadno_tcp = 0;

/* message type that will be sent by the client through TCP connection */
struct msg
{
    char filename[100];
    char file[2048];
};

void TCPClient::Bind(string port, char *address)
{
    this->logService_.Verbose("[Called] TCPClient::Bind");
    // Specified Port!
    this->Port = stoi(port);

    // Specified Address!
    this->Address = inet_pton(AF_INET, address, NULL);
    this->logService_.Verbose("[Closed] TCPClient::Bind");
}

void TCPClient::Bind(string port, string address)
{
    this->logService_.Verbose("[Called] TCPClient::Bind");
    // Specified Port!
    this->logService_.Verbose("--TCPClient::Bind Set Port");
    this->Port = stoi(port);

    // Specified Address!
    this->logService_.Verbose("--TCPClient::Bind Convert Str to Const Char*");
    const char* addressChar = address.c_str();
    
    this->logService_.Verbose("--TCPClient::Bind Set Address");
    inet_pton(AF_INET, addressChar, &this->Address);
    this->logService_.Verbose("--TCPClient::Bind Complete");
    this->logService_.Verbose("[Closed] TCPClient::Bind");
}

void TCPClient::Start()
{
    this->logService_.Verbose("[Called] TCPClient::Start");
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
    this->logService_.Verbose("[Closed] TCPClient::Start");
}

void TCPClient::ListenForConnections()
{
    this->logService_.Verbose("[Called] TCPClient::ListenForConnections");
    if ((listen(this->mistfd, 5)) != 0)
    {
        throw Cardinal::Exception::TCPSocketListenException();
    }
    this->logService_.Verbose("[Closed] TCPClient::ListenForConnections");
}

void TCPClient::BindServerAddressAndPort(sockaddr_in serverAddress)
{
    this->logService_.Verbose("[Called] TCPClient::BindServerAddressAndPort");
    if (::bind(this->mistfd, (sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        throw Cardinal::Exception::TCPSocketBindException();
    }
    this->logService_.Verbose("[Closed] TCPClient::BindServerAddressAndPort");
}

void TCPClient::StoreServerAddressInMemory(sockaddr_in serverAddress)
{
    this->logService_.Verbose("[Called] TCPClient::StoreServerAddressInMemory");
    memset((sockaddr *)&serverAddress, 0, sizeof(serverAddress));
    this->logService_.Verbose("[Closed] TCPClient::StoreServerAddressInMemory");
}

void TCPClient::SetSignalHandlers()
{
    this->logService_.Verbose("[Called] TCPClient::SetSignalHandlers");
    signal(SIGINT, TCPClient::sig_handler);
    signal(SIGTSTP, TCPClient::sig_handler);
    this->logService_.Verbose("[Closed] TCPClient::SetSignalHandlers");
}

void TCPClient::SetSocketData(sockaddr_in &clientaddr, socklen_t &addrlen)
{
    this->logService_.Verbose("[Called] TCPClient::SetSocketData");
    this->clientaddr = clientaddr;
    this->addrlen = addrlen;
    this->logService_.Verbose("[Closed] TCPClient::SetSocketData");
}

void TCPClient::Accept()
{
    this->logService_.Verbose("[Called] TCPClient::Accept");
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

    this->logService_.Verbose("[Closed] TCPClient::Accept");
}

void *TCPClient::Connection(void *args)
{
    // Map args to tuple
    std::tuple<TCPClient*, req*> arg = *reinterpret_cast<std::tuple<TCPClient*, req*>*>(args);

    // Extract first element of tuple args
    auto t = std::get<0>(arg);

    // Extract second element of tuple args
    auto c = std::get<1>(arg);
    reinterpret_cast<TCPClient*>(t)->CallCallbackByName("OnConnection", c);

    return c;
}

void TCPClient::CallCallbackByName(std::string CallbackName, void *args)
{
    this->logService_.Verbose("[Called] TCPClient::CallCallbackByName");
    // 1. Get the callback from this->Callbacks
    auto callback = this->Callbacks.find(CallbackName);
    try {
        this->logService_.Verbose("Calling callback: " + CallbackName);
        // 2. Call the callback
        callback->second(args);
    } catch (std::exception &e) {
        this->logService_.Error("Error calling callback: " + CallbackName, e.what());
    }

    this->logService_.Verbose("[Closed] TCPClient::CallCallbackByName");
}

void TCPClient::CreateSocketStream()
{
    this->logService_.Verbose("[Called] TCPClient::CreateSocketStream");
    if ((this->mistfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        this->logService_.Verbose("--TCPClient::mistfd as a socket == -1");
        throw Cardinal::Exception::TCPSocketCreationException();
    }

    // ToDo: This should be non-blocking... But thread dies if it is.
    // fcntl(this->mistfd, F_SETFL, O_NONBLOCK);
    this->logService_.Verbose("[Closed] TCPClient::CreateSocketStream");
}

sockaddr_in TCPClient::ConfigureServerAddress()
{
    this->logService_.Verbose("[Called] TCPClient::ConfigureServerAddress");
    sockaddr_in serverAddress;                            // server address
    serverAddress.sin_family = AF_INET;                   // IPv4 address family
    serverAddress.sin_addr.s_addr = htons(this->Address); // Give the local machine address
    serverAddress.sin_port = htons(this->Port);           // Port at which server listens to the requests
    this->logService_.Verbose("[Closed] TCPClient::ConfigureServerAddress");

    return serverAddress;
}

void TCPClient::RegisterCallback(std::string name, std::function<void(void *args)> callback)
{
    this->logService_.Verbose("[Called] TCPClient::RegisterCallback");
    this->Callbacks.insert(std::pair<std::string, std::function<void(void *args)>>(name, callback));
    this->logService_.Debug("--Callback " + name + " registered.", "Number of callbacks registered: " + std::to_string(this->Callbacks.size()));
    this->logService_.Verbose("[Closed] TCPClient::RegisterCallback");
}