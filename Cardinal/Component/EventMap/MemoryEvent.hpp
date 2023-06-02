#ifndef CARDINAL_COMPONENT_EVENTMAP_MEMORYEVENT_HPP
#define CARDINAL_COMPONENT_EVENTMAP_MEMORYEVENT_HPP

#include <string>
#include "Cardinal/Entity/Message.hpp"
#include "Cardinal/Service/Services.hpp"
#include "Cardinal/Entity/EventEntity.hpp"
#include "Cardinal/Global/Queue.hpp"

namespace Cardinal::Component::EventMap {
    class MemoryEvent {
        public:
            MemoryEvent() = default;
            ~MemoryEvent() = default;

            static void SendOptimisedMessage(
                std::string connectionUUID,
                Cardinal::Entity::Message& message,
                Service::MemoryServiceInterface& memoryService,
                Service::MessageServiceInterface& messageService,
                std::string Queue = Cardinal::Global::Queue::DEFAULT
            );
    };
}
#endif