#include "TCPListenerService.h"
#include "../Exception/TCPSocketCreationException.h"
#include "../Exception/TCPSocketBindException.h"
#include "../Exception/TCPSocketListenException.h"
#include <iostream>
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

/* Structure to hold the necessary parameters to pass into the threaded function */
struct req
{
    int des;
    socklen_t addlen;
    sockaddr_in clientaddr;
};

TCPListenerService::TCPListenerService()
{
    // Default values.
    this->Port = stoi("7777");
    this->Address = inet_pton(AF_INET, "0.0.0.0", NULL);
}

TCPListenerService::TCPListenerService(string port)
{
    // Specified Port!
    this->Port = stoi(port);
    this->Address = inet_pton(AF_INET, "0.0.0.0", NULL);
}

TCPListenerService::TCPListenerService(string port, char *address)
{
    // Specified Port!
    this->Port = stoi(port);

    // Specified Address!
    this->Address = inet_pton(AF_INET, address, NULL);
}

void TCPListenerService::Start()
{
    sockaddr_in clientaddr; // client address
    sockaddr_in serverAddress = ConfigureServerAddress();
    socklen_t addrlen = sizeof(clientaddr);

    CreateSocketStream();
    StoreServerAddressInMemory(serverAddress);
    BindServerAddressAndPort(serverAddress);
    ListenForConnections();
    SetSignalHandlers();

    ServerLoop(clientaddr, addrlen);
}

void TCPListenerService::ListenForConnections()
{
    if ((listen(TCPListenerService::mistfd, 5)) != 0)
    {
        throw Cardinal::Exception::TCPSocketListenException();
    }
}

void TCPListenerService::BindServerAddressAndPort(sockaddr_in serverAddress)
{
    if (::bind(TCPListenerService::mistfd, (sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        throw Cardinal::Exception::TCPSocketBindException();
    }
}

void TCPListenerService::StoreServerAddressInMemory(sockaddr_in serverAddress)
{
    memset((sockaddr *)&serverAddress, 0, sizeof(serverAddress));
}

void TCPListenerService::SetSignalHandlers()
{
    signal(SIGINT, TCPListenerService::sig_handler);
    signal(SIGTSTP, TCPListenerService::sig_handler);
}

void TCPListenerService::ServerLoop(sockaddr_in &clientaddr, socklen_t &addrlen)
{
    while (1)
    {
        ServerLoop(clientaddr, addrlen);
    }
}

void TCPListenerService::ServerLoopInnerContent(sockaddr_in &clientaddr, socklen_t &addrlen)
{
    int connfd;
    if ((connfd = accept(TCPListenerService::mistfd, (sockaddr *)&clientaddr, &addrlen)) < 0)
    {
        std::cout << "\n\t Client connection declined..." << '\n';
    }
    else
    {
        std::cout << "\n\t Client connection accepted..." << '\n';
    }

    /* Filling the parameter values of the threaded function */
    req *r = new req;      // allocate memory
    bzero(r, sizeof(req)); // Clear memory
    r->addlen = addrlen;
    r->clientaddr = clientaddr;
    r->des = connfd;

    pthread_create(&thread_tcp[threadno_tcp++], NULL, (THREADFUNCPTR)&TCPListenerService::Connection, (void *)r);

    if (threadno_tcp == 100)
    {
        threadno_tcp = 0;
    }
}

void *TCPListenerService::LocalConnection(void *args)
{
    req sock = *((req *)args);
    msg buffer;

    while (1)
    {
        /* Read the packet sent by the established client */
        read(sock.des, &buffer, sizeof(buffer));

        std::cout << "\n\t File name: " << buffer.filename;
        std::cout << "\n\n"
                  << buffer.file << '\n';
    }
}

void TCPListenerService::CreateSocketStream()
{
    if ((TCPListenerService::mistfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        throw Cardinal::Exception::TCPSocketCreationException();
    }
}

sockaddr_in TCPListenerService::ConfigureServerAddress()
{
    sockaddr_in serverAddress;                            // server address
    serverAddress.sin_family = AF_INET;                   // IPv4 address family
    serverAddress.sin_addr.s_addr = htons(this->Address); // Give the local machine address
    serverAddress.sin_port = htons(this->Port);           // Port at which server listens to the requests

    return serverAddress;
}