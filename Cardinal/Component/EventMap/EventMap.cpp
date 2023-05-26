#include <string>
#include <map>
#include <typeinfo>
#include "Cardinal/Exception/Exceptions.h"
#include "Cardinal/Event/AbstractEvent.hpp"

#include "EventMap.hpp"
#include "Cardinal/Service/LogService.hpp"
#include "Cardinal/Entity/Message.hpp"

using namespace Cardinal::Component::EventMap;


void EventMap::Invoke (Cardinal::Entity::Message message) {
    this->logService_.Verbose("[Called] Cardinal::Component::EventMap::Invoke");
    try {
        this->logService_.Verbose("--Cardinal::Component::EventMap::Invoke Retrieving and Invoking Event Object");
        this->RetrieveAndInvokeEventObject(message.getKey(), message.getPayload());
        this->logService_.Verbose("--Cardinal::Component::EventMap::Invoke Completed!");
    } catch (Cardinal::Exception::InvalidOrMissingEvent& e) {
        this->logService_.Warning(
            "--Cardinal::Component::EventMap::Invoke",
            "Invalid or missing event " + message.getPayload() + " Channel: " + message.getKey()
        );

        this->logService_.Debug(
            "--Could it be that the event you're calling hasn't been registered? Event: " + message.getKey(),
            std::to_string(EventMap::events.size())
        );
    } catch (Cardinal::Exception::InvalidMessage& e) {
        this->logService_.Warning(
            "--Cardinal::Component::EventMap::Invoke",
            "Invalid message " + message.getPayload() + " Channel: " + message.getKey()
        );
    }
    this->logService_.Verbose("[Closed] Cardinal::Component::EventMap::Invoke");
}

void EventMap::RetrieveAndInvokeEventObject(std::string EventName, std::string Payload) {
    this->logService_.Verbose("[Called] Cardinal::Component::EventMap::RetrieveAndInvokeEventObject");
    try {
        this->logService_.Verbose("--Cardinal::Component::EventMap::RetrieveAndInvokeEventObject retrieving event from registered events.");
        auto factory = events.at(EventName)();
        this->logService_.Verbose("--Cardinal::Component::EventMap::RetrieveAndInvokeEventObject cloning event into scope...");
        auto receivedEventObject = factory->Clone(this->logService_);

        this->logService_.Verbose("--Cardinal::Component::EventMap::RetrieveAndInvokeEventObject invoking event...");
        receivedEventObject->invoke(Payload);
        this->logService_.Verbose("--Cardinal::Component::EventMap::RetrieveAndInvokeEventObject event invoked.");

    } catch (std::exception& e) {
        this->logService_.Error("--Cardinal::Component::EventMap::RetrieveAndInvokeEventObject", "Failed to execute event.");
        throw Cardinal::Exception::InvalidOrMissingEvent();
    }
    // Factory and Event both deleted here.
    this->logService_.Verbose("[Closed] Cardinal::Component::EventMap::RetrieveAndInvokeEventObject");
}

eventObject EventMap::events;
