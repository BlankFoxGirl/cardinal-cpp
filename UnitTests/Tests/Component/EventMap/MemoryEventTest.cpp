#include "vendor/eranpeer/FakeIt/single_header/standalone/fakeit.hpp"
#include "UnitTest++/UnitTest++.h"
#include "Cardinal/Service/Services.hpp"
#include "Cardinal/Entity/Message.hpp"
#include "Cardinal/Component/EventMap/MemoryEvent.hpp"
#include <iostream>

using namespace fakeit;

SUITE(MemoryEventTest)
{
    TEST(CanMock)
    {
        Mock<Cardinal::Service::MemoryServiceInterface> memoryServiceMock;
        Mock<Cardinal::Service::MessageServiceInterface> messageServiceMock;

        When(Method(memoryServiceMock, WriteAllHash)).AlwaysReturn();

        When(OverloadedMethod(messageServiceMock, Dispatch, void(Cardinal::Entity::Message))).AlwaysReturn();

        auto &memoryService = memoryServiceMock.get();
        auto &messageService = messageServiceMock.get();
        auto messageEntity = Cardinal::Entity::Message("Test", "Payload");

        Cardinal::Component::EventMap::MemoryEvent::SendOptimisedMessage(
            "Test",
            messageEntity,
            memoryService,
            messageService);

        CHECK(Verify(Method(memoryServiceMock, WriteAllHash)).Once());
        CHECK(Verify(OverloadedMethod(messageServiceMock, Dispatch, void(Cardinal::Entity::Message))).Once());
    }
}