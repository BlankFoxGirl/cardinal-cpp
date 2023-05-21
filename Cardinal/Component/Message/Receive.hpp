#ifndef CARDINAL_COMPONENT_MESSAGE_RECEIVE_H
#define CARDINAL_COMPONENT_MESSAGE_RECEIVE_H
#include <string>
#include "../../Entity/Message.hpp"

namespace Cardinal::Component::Message {
    class Receive {
        public:
            explicit Receive(
                Cardinal::Service::LogServiceInterface& s,
                Cardinal::Service::MessageServiceInterface& s1
            ) : logService(s), messageService(s1) {}

            Cardinal::Entity::Message SetMessageContext(Cardinal::Entity::Message message);
            Cardinal::Entity::Message SetMessageContext(std::string message);
            int invoke(void* args);

        private:
            Cardinal::Service::LogServiceInterface& logService;
            Cardinal::Service::MessageServiceInterface& messageService;
            Cardinal::Entity::Message message;
    };
}

#endif