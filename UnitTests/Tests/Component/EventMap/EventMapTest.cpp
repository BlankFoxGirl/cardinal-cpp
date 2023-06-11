#include "vendor/eranpeer/FakeIt/single_header/standalone/fakeit.hpp"
#include "UnitTest++/UnitTest++.h"
#include "Cardinal/Service/Services.hpp"
#include "Cardinal/Entity/Message.hpp"
#include "Cardinal/Component/EventMap/EventMap.hpp"
#include <iostream>

using namespace fakeit;

SUITE(MemoryEventTest)
{
    TEST(CannotExecuteAnInvalidEvent)
    {
        Mock<Cardinal::Service::MemoryServiceInterface> memoryServiceMock;
        Mock<Cardinal::Service::MessageServiceInterface> messageServiceMock;
        Mock<Cardinal::Service::LogServiceInterface> logServiceMock;

        When(Method(logServiceMock, Verbose)).AlwaysReturn();
        When(Method(logServiceMock, Warning)).AlwaysReturn();
        When(Method(logServiceMock, Error)).AlwaysReturn();
        When(Method(logServiceMock, Info)).AlwaysReturn();
        When(Method(logServiceMock, Debug)).AlwaysReturn();

        auto &memoryService = memoryServiceMock.get();
        auto &messageService = messageServiceMock.get();
        auto &logService = logServiceMock.get();

        auto messageEntity = Cardinal::Entity::Message("Test", "Payload");
        auto eventMap = Cardinal::Component::EventMap::EventMap(logService, messageService, memoryService);
        eventMap.Invoke(messageEntity);

        CHECK(Verify(Method(logServiceMock, Error)).Once());
        CHECK(Verify(Method(logServiceMock, Warning)).Once());
    }
}