#ifndef EventMapS_H
#define EventMapS_H
#include <string>
#include <map>
#include <iostream>
#include <memory>
#include "Cardinal/Component/Event/Registry.hpp"
#include "Cardinal/Exception/Exceptions.h"
#include "Cardinal/Event/AbstractEvent.hpp"
#include "Cardinal/Service/MessageService.hpp"
#include "Cardinal/Service/MemoryService.hpp"
#include "Cardinal/Service/LogService.hpp"

using namespace std;
using namespace Cardinal::Event;
using namespace Cardinal::Exception;

namespace Cardinal::Component::EventMap
{
    typedef std::unique_ptr<Cardinal::Event::AbstractEvent> (*FactoryType)();
    typedef map<string, FactoryType> eventObject;

    class EventMap
    {
    public:
        explicit EventMap(
            Cardinal::Service::LogServiceInterface &s,
            Cardinal::Service::MessageServiceInterface &s1,
            Cardinal::Service::MemoryServiceInterface &s2) : logService_(s), messageService_(s1), memoryService_(s2)
        {
            this->logService_.Info("[Initialising] Cardinal::Component::EventMap");
        }

        ~EventMap()
        {
            this->logService_.Info("[Destroying] Cardinal::Component::EventMap");
        }

        void Invoke(Cardinal::Entity::Message message);

        /// @deprecated use Cardinal::Component::Event::Registry::Register instead.
        template <typename T>
        static void Register()
        {
            // Alias to new method.
            Cardinal::Component::Event::Registry::Register<T>();
        }

        static std::unique_ptr<EventMap> Create(
            Cardinal::Service::LogServiceInterface &logService,
            Cardinal::Service::MessageServiceInterface &messageService,
            Cardinal::Service::MemoryServiceInterface &memoryService)
        {
            return std::make_unique<EventMap>(logService, messageService, memoryService);
        }

        void Destroy()
        {
            delete this;
        }

    private:
        Cardinal::Service::LogServiceInterface &logService_;
        Cardinal::Service::MessageServiceInterface &messageService_;
        Cardinal::Service::MemoryServiceInterface &memoryService_;
        // Cardinal::Service::StorageServiceInterface& storageService_;

        void RetrieveAndInvokeEventObject(string EventName, string Payload);

        FactoryType GetEventObject(string eventName)
        {
            return Cardinal::Component::Event::Registry::Query(eventName);
        }
    };
}

#endif