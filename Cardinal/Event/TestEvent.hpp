#ifndef TEE_H
#define TEE_H
#include <string>
#include <iostream>
#include "AbstractEvent.hpp"
#include "Cardinal/Service/LogService.hpp"

namespace Cardinal::Event {
    class TestEvent: public Cardinal::Event::AbstractEvent {
        public:
            TestEvent(Cardinal::Service::LogServiceInterface& s): logService_(s) {}

            ~TestEvent() {
                cout << "[Destroying] Cardinal::Event::TestEvent" << endl;
            };

            bool invoke(std::string Payload) override {
                this->logService_.Debug("Executing on TestEvent!");
                return true;
            }

            virtual TestEvent* Clone(Cardinal::Service::LogServiceInterface& s) override {
                return new TestEvent(s);
            }

            static AbstractEvent* Create(Cardinal::Service::LogServiceInterface& s) {
                return new TestEvent(s);
            }

            static std::string GetEventKey() {
                return "TestEvent";
            }

        private:
            Cardinal::Service::LogServiceInterface &logService_;
    };
}
#endif