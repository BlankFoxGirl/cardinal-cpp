#ifndef EventMapS_H
#define EventMapS_H
#include <string>
#include <map>
#include <iostream>
#include <memory>
#include "Cardinal/Exception/Exceptions.h"
#include "Cardinal/Event/AbstractEvent.hpp"
#include "Cardinal/Service/MessageService.hpp"
#include "Cardinal/Service/LogService.hpp"

using namespace std;
using namespace Cardinal::Event;
using namespace Cardinal::Exception;



namespace Cardinal::Component::EventMap {
    typedef std::unique_ptr<Cardinal::Event::AbstractEvent> (*FactoryType)();
    typedef map<string, FactoryType> eventObject;

    class EventMap {
        public:
            explicit EventMap(Cardinal::Service::LogServiceInterface& s): logService_(s) {
                this->logService_.Info("[Initialising] Cardinal::Component::EventMap");
            }

            ~EventMap() {
                this->logService_.Info("[Destroying] Cardinal::Component::EventMap");
            }

            void Invoke (Cardinal::Entity::Message message);

            // static void Register (Cardinal::Event::AbstractEvent *eventObject);
            template <typename T> static void Register () {
                EventMap::events.insert(
                    pair<std::string, std::map<std::string, FactoryType>::mapped_type>(
                        (std::string)T::GetEventKey(),
                        (FactoryType)T::Create
                    )
                );
            }

            static std::unique_ptr<EventMap> Create(Cardinal::Service::LogServiceInterface& logService) {
                return std::make_unique<EventMap>(logService);
            }

            void Destroy() {
                delete this;
            }

        private:
            Cardinal::Service::LogServiceInterface& logService_;
            static eventObject events;

            void RetrieveAndInvokeEventObject(string EventName, string Payload);

            FactoryType GetEventObject (string eventName) {
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