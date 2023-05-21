#ifndef EventMapS_H
#define EventMapS_H
#include <string>
#include <map>
#include <iostream>
#include "../Exception/Exceptions.h"
#include "../Event/AbstractEvent.h"
#include "../../Service/MessageService.hpp"
#include "../../Service/LogService.hpp"

using namespace std;
using namespace Cardinal::Event;
using namespace Cardinal::Exception;
// using namespace Cardinal::Global;

namespace Cardinal::Component::EventMap {
    typedef map<string, Cardinal::Event::AbstractEvent*> eventObject;

    class EventMap {
        public:
            explicit EventMap(Cardinal::Service::LogServiceInterface& s): logService_(s) {
                this->logService_.Info("Starting EventMapService");
            }
            void Invoke (string channel, string message);

            void Register (string eventName, Cardinal::Event::AbstractEvent *eventObject);

        private:
            Cardinal::Service::LogServiceInterface& logService_;
            eventObject events;

            std::__1::tuple<std::__1::string, std::__1::string> RetrieveEventFromMessage (string message);

            void RetrieveAndInvokeEventObjectFromMessage(string Message);

            void RetrieveAndInvokeEventObject(string EventName, string Payload);

            Cardinal::Event::AbstractEvent* GetEventObject (string eventName) {
                try {
                    auto receivedEventObject = events.at(eventName);
                    return receivedEventObject;
                } catch (std::exception& e) {
                    throw Cardinal::Exception::InvalidOrMissingEvent();
                }
            }
    };
}

#endif