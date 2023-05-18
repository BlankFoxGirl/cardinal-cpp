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
#include <arpa/inet.h>
#include "LogService.h"
#include "../Exception/Exceptions.h"

using namespace std;

namespace Cardinal::Service
{
    class TCPListenerServiceInterface {
        public:
            virtual ~TCPListenerServiceInterface() noexcept = default;
            virtual void Start() = 0;
            virtual void Accept() = 0;
            virtual void Bind(string port, char *address) = 0;
            virtual void Bind(string port, string address) = 0;
    };

    class TCPListenerService: public TCPListenerServiceInterface
    {
    public:
        explicit TCPListenerService(Cardinal::Service::LogServiceInterface& s): logService_(s) {
            this->logService_.Verbose("Starting TCPListenerService");
        }

        void Bind(string port, char *address);
        void Bind(string port, string address);
        void Start();
        void Accept();

        static void sig_handler(int signo)
        {
            /* signal handler */
            if (signo == SIGINT)
            {
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
        static void *Connection(void *args);
        void *LocalConnection(void *args);
        void CreateSocketStream();
        sockaddr_in ConfigureServerAddress();
        void SetSocketData(sockaddr_in &clientaddr, socklen_t &addrlen);
        void SetSignalHandlers();
        void StoreServerAddressInMemory(sockaddr_in serverAddress);
        void BindServerAddressAndPort(sockaddr_in serverAddress);
        void ListenForConnections();
    };
}
