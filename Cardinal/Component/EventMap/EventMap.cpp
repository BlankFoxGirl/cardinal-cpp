#include <string>
#include <map>
#include <typeinfo>
#include "Cardinal/Exception/Exceptions.h"
#include "Cardinal/Event/AbstractEvent.hpp"

#include "EventMap.hpp"
#include "Cardinal/Service/LogService.hpp"
#include "Cardinal/Entity/Message.hpp"
#include "Cardinal/Entity/EventEntity.hpp"

using namespace Cardinal::Component::EventMap;

void EventMap::Invoke(Cardinal::Entity::Message message)
{
    this->logService_.Verbose("[Called] Cardinal::Component::EventMap::Invoke");
    try
    {
        this->logService_.Verbose("--Cardinal::Component::EventMap::Invoke Retrieving and Invoking Event Object");
        this->RetrieveAndInvokeEventObject(message.getKey(), message.getPayload());
        this->logService_.Verbose("--Cardinal::Component::EventMap::Invoke Completed!");
    }
    catch (Cardinal::Exception::InvalidOrMissingEvent &e)
    {
        this->logService_.Warning(
            "--Cardinal::Component::EventMap::Invoke",
            "Invalid or missing event " + message.getPayload() + " Channel: " + message.getKey());

        this->logService_.Debug(
            "--Could it be that the event you're calling hasn't been registered? Event: " + message.getKey());
    }
    catch (Cardinal::Exception::InvalidMessage &e)
    {
        this->logService_.Warning(
            "--Cardinal::Component::EventMap::Invoke",
            "Invalid message " + message.getPayload() + " Channel: " + message.getKey());
    }
    this->logService_.Verbose("[Closed] Cardinal::Component::EventMap::Invoke");
}

void EventMap::RetrieveAndInvokeEventObject(std::string EventName, std::string Payload)
{
    this->logService_.Verbose("[Called] Cardinal::Component::EventMap::RetrieveAndInvokeEventObject");
    try
    {
        this->logService_.Verbose("--Cardinal::Component::EventMap::RetrieveAndInvokeEventObject retrieving event from registered events.");

        // This is too inefficient.
        // @todo Maintain a single instance of the factory object, and then clone.
        // Presently, this calls the Create static factory method which creates an instance that is then cloned.
        // resulting in two instances of the object being created.
        auto factory = GetEventObject(EventName)();
        this->logService_.Verbose("--Cardinal::Component::EventMap::RetrieveAndInvokeEventObject cloning event into scope...");
        auto receivedEventObject = factory->Clone(this->logService_, this->messageService_, this->memoryService_);
        // Retrieve message from memory reference if not locked. If locked, lock it to self and then retrieve.
        auto lockStatus = this->memoryService_.ReadHash("event:" + Payload, "Locked");

        if (lockStatus.second.compare("1") == 0)
        {
            this->logService_.Verbose("--Cardinal::Component::EventMap::RetrieveAndInvokeEventObject event locked.");
            return;
        }

        this->logService_.Verbose("--Cardinal::Component::EventMap::RetrieveAndInvokeEventObject locking event...");
        this->memoryService_.WriteHash("event:" + Payload, "Locked", "1"); // Lock event.
        this->logService_.Verbose("--Cardinal::Component::EventMap::RetrieveAndInvokeEventObject event locked!");

        this->logService_.Verbose("--Cardinal::Component::EventMap::RetrieveAndInvokeEventObject extracting event payload...");
        auto eventData = this->memoryService_.ReadAllHash("event:" + Payload);
        auto event = Cardinal::Entity::EventEntity(eventData);
        std::string eventPayload = event.ToString();
        this->logService_.Verbose("--Cardinal::Component::EventMap::RetrieveAndInvokeEventObject event payload extracted.", eventPayload);

        this->logService_.Verbose("--Cardinal::Component::EventMap::RetrieveAndInvokeEventObject invoking event...");
        receivedEventObject->invoke(eventPayload);
        this->logService_.Verbose("--Cardinal::Component::EventMap::RetrieveAndInvokeEventObject event invoked.");
    }
    catch (std::exception &e)
    {
        this->logService_.Error("--Cardinal::Component::EventMap::RetrieveAndInvokeEventObject", e.what());
        throw Cardinal::Exception::InvalidOrMissingEvent();
    }
    // Factory and Event both deleted here.
    this->logService_.Verbose("[Closed] Cardinal::Component::EventMap::RetrieveAndInvokeEventObject");
}
