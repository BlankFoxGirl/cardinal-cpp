#ifndef TCPS_H
#define TCPS_H
#include <string>
#include <unistd.h>
#include <signal.h>
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
#include <map>
#include <queue>
#include <arpa/inet.h>
#include "Cardinal/Service/LogService.hpp"
#include "Cardinal/Service/CommunicationService.hpp"
#include "Cardinal/Exception/Exceptions.h"

using namespace std;

namespace Cardinal::Service::Communication
{
    class TCPClient: public CommunicationServiceInterface
    {
    public:
        explicit TCPClient(Cardinal::Service::LogServiceInterface& s): logService_(s) {
            this->logService_.Verbose("Starting TCPListenerService");
        }

        void Bind(std::string port, char *address);
        void Bind(std::string port, std::string address);
        void Start();
        void Accept();
        void RegisterCallback(std::string name, std::function<void(void *args)> callback);

        static void sig_handler(int signo)
        {
            /* signal handler */
            if (signo == SIGINT)
            {
                // ToDo: Socket should close when signal is handled.
                // close(Cardinal::Service::TCPListenerService::mistfd);
                exit(1);
            }
        }

    private:
        Cardinal::Service::LogServiceInterface& logService_;
        u_int32_t Port;
        u_int32_t Address;
        sockaddr_in clientaddr;
        socklen_t addrlen;
        int mistfd = 0;
        std::map<std::string, std::function<void(void *args)>> Callbacks;

        // // Messages added to a write queue based on connection id.
        // std::map<std::string, std::queue<void *>> WriteQueue;
        static void *Connection(void *args);
        void CreateSocketStream();
        sockaddr_in ConfigureServerAddress();
        void SetSocketData(sockaddr_in &clientaddr, socklen_t &addrlen);
        void SetSignalHandlers();
        void StoreServerAddressInMemory(sockaddr_in serverAddress);
        void BindServerAddressAndPort(sockaddr_in serverAddress);
        void ListenForConnections();
        void CallCallbackByName(string name, void *args);
    };
}
#endif