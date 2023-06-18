#include "vendor/eranpeer/FakeIt/single_header/standalone/fakeit.hpp"
#include "UnitTest++/UnitTest++.h"
#include "Cardinal/Service/Services.hpp"
#include "Cardinal/Entity/Message.hpp"
#include "Cardinal/Component/EventMap/EventMap.hpp"
#include "Cardinal/Component/Event/Registry.hpp"
#include "Cardinal/Event/TestEvent.hpp"
#include "Cardinal/Entity/EventEntity.hpp"
#include <iostream>
#include <string>

using namespace fakeit;

SUITE(EventMapTest)
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

    TEST(CanExecuteAValidEvent)
    {
        Mock<Cardinal::Service::MemoryServiceInterface> memoryServiceMock;
        Mock<Cardinal::Service::MessageServiceInterface> messageServiceMock;
        Mock<Cardinal::Service::LogServiceInterface> logServiceMock;

        When(Method(logServiceMock, Verbose)).AlwaysReturn();
        When(Method(logServiceMock, Warning)).AlwaysReturn();
        When(Method(logServiceMock, Error)).AlwaysReturn();
        When(Method(logServiceMock, Info)).AlwaysReturn();
        When(Method(logServiceMock, Debug)).AlwaysReturn();

        std::pair<std::string, std::string> lockedValue = std::make_pair("locked", "0");
        auto eventEntity = Cardinal::Entity::EventEntity("EventName", "Payload", "Origin", "Locked");

        When(Method(memoryServiceMock, ReadHash)).AlwaysReturn(lockedValue);
        When(OverloadedMethod(memoryServiceMock, WriteHash, void(std::string, std::string, std::string, int))).AlwaysReturn(); // str, str, str, int

        When(Method(memoryServiceMock, ReadAllHash)).AlwaysReturn(eventEntity.Serialize());

        auto &memoryService = memoryServiceMock.get();
        auto &messageService = messageServiceMock.get();
        auto &logService = logServiceMock.get();

        // Register TestEvent with the Event Components' Registry.
        Cardinal::Component::Event::Registry::Register<Cardinal::Event::TestEvent>();

        auto messageEntity = Cardinal::Entity::Message("TestEvent", "Payload");
        auto eventMap = Cardinal::Component::EventMap::EventMap(logService, messageService, memoryService);
        eventMap.Invoke(messageEntity);

        CHECK(Verify(Method(logServiceMock, Error)).Never());
        CHECK(Verify(Method(logServiceMock, Warning)).Never());
    }
}