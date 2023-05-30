#ifndef CARDINAL_SERVICE_COMMUNICATIONSERVICE_H
#define CARDINAL_SERVICE_COMMUNICATIONSERVICE_H
#include <string>
#include <utility>
#include <netinet/in.h>
#include <sys/types.h>
#include <functional>

namespace Cardinal::Service {
    struct req
    {
        int des;
        socklen_t addlen;
        sockaddr_in clientaddr;
    };

    class CommunicationServiceInterface {
        public:
            virtual ~CommunicationServiceInterface() noexcept = default;
            virtual void Bind(std::string port, char *address) = 0;
            virtual void Bind(std::string port, std::string address) = 0;
            virtual void Start() = 0;
            virtual void Accept() = 0;
            virtual void RegisterCallback(std::string name, std::function<void(void *args)> callback) = 0;
    };
}
#endif