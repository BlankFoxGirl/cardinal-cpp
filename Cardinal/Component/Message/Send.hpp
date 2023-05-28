#ifndef CARDINAL_COMPONENT_MESSAGE_SEND_H
#define CARDINAL_COMPONENT_MESSAGE_SEND_H
#include "Cardinal/Service/LogService.hpp"
#include "Cardinal/Service/MessageService.hpp"

namespace Cardinal::Component::Message {
    class Send {
        public:
            explicit Send(
                Cardinal::Service::LogServiceInterface& s,
                Cardinal::Service::MessageServiceInterface& s1
            ) : logService(s), messageService(s1) {}
            int invoke(void* args);

        private:
            Cardinal::Service::LogServiceInterface& logService;
            Cardinal::Service::MessageServiceInterface& messageService;
    };
}
#endif