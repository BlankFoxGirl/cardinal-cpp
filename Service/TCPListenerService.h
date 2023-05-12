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
using namespace std;

namespace Cardinal::Service
{
    class TCPListenerService
    {
        TCPListenerService();
        TCPListenerService(string port);
        TCPListenerService(string port, char *address);
        void *LocalConnection(void *args);
        void Start();
        static void *Connection(void *args)
        {
            TCPListenerService t = TCPListenerService();
            t.LocalConnection(args);
            return args;
        }

        static void sig_handler(int signo)
        {
            /* signal handler */
            if (signo == SIGINT)
            {
                close(TCPListenerService::mistfd);
                exit(1);
            }
        }

    private:
        u_int32_t Port;
        u_int32_t Address;
        static int mistfd;
        void CreateSocketStream();
        sockaddr_in ConfigureServerAddress();
        void ServerLoop(sockaddr_in &clientaddr, socklen_t &addrlen);
        void ServerLoopInnerContent(sockaddr_in &clientaddr, socklen_t &addrlen);
        void SetSignalHandlers();
        void StoreServerAddressInMemory(sockaddr_in serverAddress);
        void BindServerAddressAndPort(sockaddr_in serverAddress);
        void ListenForConnections();
    };
}
int Cardinal::Service::TCPListenerService::mistfd = 0;