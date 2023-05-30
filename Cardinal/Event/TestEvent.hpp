#ifndef TEE_H
#define TEE_H
#include <string>
#include <iostream>
#include "AbstractEvent.hpp"
#include "Cardinal/Service/LogService.hpp"
#include "Cardinal/Service/MessageService.hpp"
#include "Cardinal/Service/MemoryService.hpp"

namespace Cardinal::Event {
    class TestEvent: public Cardinal::Event::AbstractEvent {
        public:
            TestEvent(
                Cardinal::Service::LogServiceInterface& s,
                Cardinal::Service::MessageServiceInterface& s1,
                Cardinal::Service::MemoryServiceInterface& s2
            ): logService_(s), messageService_(s1), memoryService_(s2) {}

            ~TestEvent() = default;

            bool invoke(std::string Payload) override {
                this->logService_.Debug("Executing on TestEvent!");
                return true;
            }

            virtual std::unique_ptr<AbstractEvent> Clone(
                Cardinal::Service::LogServiceInterface& s,
                Cardinal::Service::MessageServiceInterface& s1,
                Cardinal::Service::MemoryServiceInterface& s2
            ) override {
                return std::make_unique<TestEvent>(s, s1, s2);
            }

            static std::unique_ptr<AbstractEvent> Create(
                Cardinal::Service::LogServiceInterface& s,
                Cardinal::Service::MessageServiceInterface& s1,
                Cardinal::Service::MemoryServiceInterface& s2
            ) {
                return std::make_unique<TestEvent>(s, s1, s2);
            }

            static std::string GetEventKey() {
                return "TestEvent";
            }

        private:
            Cardinal::Service::LogServiceInterface &logService_;
            Cardinal::Service::MessageServiceInterface &messageService_;
            Cardinal::Service::MemoryServiceInterface &memoryService_;
    };
}
#endif