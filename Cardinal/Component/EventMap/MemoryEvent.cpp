#include <string>
#include "Cardinal/Service/Services.hpp"
#include "Cardinal/Entity/EventEntity.hpp"
#include "Cardinal/Entity/Message.hpp"
#include "Cardinal/Component/EventMap/MemoryEvent.hpp"

using namespace Cardinal::Component::EventMap;

void MemoryEvent::SendOptimisedMessage(
    std::string connectionUUID,
    Cardinal::Entity::Message& message,
    Service::MemoryServiceInterface& memoryService,
    Service::MessageServiceInterface& messageService,
    std::string queue
) {
    auto eventEntity = Cardinal::Entity::EventEntity(
            message.getKey(),
            message.getPayload(),
            connectionUUID,
            "0"
        );

    memoryService.WriteAllHash(eventEntity.GetQueue(message.getUUID()), eventEntity.Serialize());

    message.setPayload(message.getUUID()); // Overwite payload with message UUID then publish to workers.

    messageService.Dispatch(message);
}