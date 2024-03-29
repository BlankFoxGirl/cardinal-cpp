#ifndef CARDINAL_COMPONENT_MESSAGE_RECEIVE_H
#define CARDINAL_COMPONENT_MESSAGE_RECEIVE_H
#include <string>
#include "Cardinal/Entity/Message.hpp"
#include "Cardinal/Service/LogService.hpp"
#include "Cardinal/Service/MessageService.hpp"
#include "Cardinal/Service/MemoryService.hpp"

namespace Cardinal::Component::Message
{
    class Receive
    {
    public:
        explicit Receive(
            Cardinal::Service::LogServiceInterface &s,
            Cardinal::Service::MessageServiceInterface &s1,
            Cardinal::Service::MemoryServiceInterface &s2) : logService(s), messageService(s1), memoryService(s2) {}

        ~Receive() = default;

        Cardinal::Entity::Message SetMessageContext(Cardinal::Entity::Message message);
        Cardinal::Entity::Message SetMessageContext(std::string message);
        int operator()(Cardinal::Entity::Message message);

    private:
        Cardinal::Service::LogServiceInterface &logService;
        Cardinal::Service::MessageServiceInterface &messageService;
        Cardinal::Service::MemoryServiceInterface &memoryService;
        Cardinal::Entity::Message message;
        void InvokeEventMap();
    };
}

#endif