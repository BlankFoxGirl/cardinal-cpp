#include <string>
#include <map>
#include <iostream>
#include "../Exception/Exceptions.h"
#include "Events.h"
#include "../Service/MessageService.h"
#include "../Service/LogService.h"
#ifndef EventMap_H
#define EventMap_H
using namespace std;

namespace Cardinal::Event {
    typedef map<string, Cardinal::Event::AbstractEvent*> eventObject;
    class EventMap {
        public:
            static void Invoke (string channel, string message) {
                try {
                    EventMap::RetrieveAndInvokeEventObjectFromMessage(message);
                } catch (Cardinal::Exception::InvalidOrMissingEvent& e) {
                    cout << "Invalid or missing event " << message << " Channel: " << channel << endl;
                } catch (Cardinal::Exception::InvalidMessage& e) {
                    cout << "Invalid message " << message << " Channel: " << channel << endl;
                }
            }

            static void Register (string eventName, Cardinal::Event::AbstractEvent *eventObject) {
                events.insert(pair<string, std::map<std::string, Cardinal::Event::AbstractEvent *>::mapped_type>(eventName, eventObject));
            }

            static eventObject events;
        private:
            static std::__1::tuple<std::__1::string, std::__1::string> RetrieveEventFromMessage (string message) {
                Cardinal::Service::MessageService messageService = Cardinal::Service::MessageService(message);
                return messageService.Decode();
            }

            static void RetrieveAndInvokeEventObjectFromMessage(string Message) {
                Service::LogService logService = Service::LogService();
                logService.Log("EventMap::RetrieveAndInvokeEventObjectFromMessage", "Called", Service::LOG_LEVEL::Debug);
                auto [eventName, payload] = EventMap::RetrieveEventFromMessage(Message);
                logService.Log("EventMap::RetrieveAndInvokeEventObjectFromMessage", "Received " + (string)eventName + " " + (string)payload, Service::LOG_LEVEL::Debug);
                
                EventMap::RetrieveAndInvokeEventObject(eventName, payload);
            }

            static void RetrieveAndInvokeEventObject(string EventName, string Payload) {
                try {
                    auto receivedEventObject = events.at(EventName);
                    receivedEventObject->invoke(Payload);
                } catch (std::exception& e) {
                    throw Cardinal::Exception::InvalidOrMissingEvent();
                }
            }

            static Cardinal::Event::AbstractEvent* GetEventObject (string eventName) {
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