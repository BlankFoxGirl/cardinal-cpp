#ifndef EventMapS_H
#define EventMapS_H
#include <string>
#include <map>
#include <iostream>
#include "../Exception/Exceptions.h"
#include "../Event/AbstractEvent.h"

using namespace std;
using namespace Cardinal::Event;
using namespace Cardinal::Exception;
// using namespace Cardinal::Global;

namespace Cardinal::Service {
    typedef map<string, Cardinal::Event::AbstractEvent*> eventObject;
    class EventMapServiceInterface {
    public:
        virtual ~EventMapServiceInterface() noexcept = default;
        virtual void Invoke (string channel, string message) = 0;
        virtual void Register (string eventName, Cardinal::Event::AbstractEvent *eventObject) = 0;
    };

    class EventMapService: public EventMapServiceInterface {
        public:
            EventMapService() {
                events = {};
            }
            void Invoke (string channel, string message);

            void Register (string eventName, Cardinal::Event::AbstractEvent *eventObject);

        private:
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

// Cardinal::Service::eventObject Cardinal::Service::EventMapService::events = {};
#endif