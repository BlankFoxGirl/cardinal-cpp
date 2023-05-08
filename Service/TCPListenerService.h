#include <string>
#include <unistd.h>
#include <signal.h>
using namespace std;

namespace Cardinal::Service {
    class TCPListernerService {
        TCPListernerService();
        TCPListernerService(string port);
        TCPListernerService(string port, char* address);
        void* LocalConnection(void* args);
        void Start();
        static void* Connection(void* args) {
            TCPListernerService t = TCPListernerService();
            t.LocalConnection(args);
        }
        static void sig_handler(int signo) {
            /* signal handler */
            if (signo == SIGINT) {
                close (TCPListernerService::mistfd);
                exit (1);
            }
        }

        private:
            u_int32_t Port;
            u_int32_t Address;
            static int mistfd;
    };
}
int Cardinal::Service::TCPListernerService::mistfd = 0;