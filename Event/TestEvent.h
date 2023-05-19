#ifndef TEE_H
#define TEE_H
#include <string>
#include <iostream>
#include "AbstractEvent.h"
#include "../Service/LogService.h"
using namespace std;

namespace Cardinal::Event {
    class TestEvent: public Cardinal::Event::AbstractEvent {
        public:
            explicit TestEvent(Cardinal::Service::LogServiceInterface& s): logService_(s) {
                this->logService_.Info("Starting TestEvent");
            }
            bool invoke(std::string Payload) {
                this->logService_.Info("Executing on TestEvent!");
                return true;
            }
        private:
            Cardinal::Service::LogServiceInterface &logService_;
    };
}
#endif