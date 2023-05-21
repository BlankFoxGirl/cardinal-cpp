#include <string>
#include <map>
#include "../../Exception/Exceptions.h"
#include "../../Event/AbstractEvent.h"

#include "EventMap.hpp"
#include "../../Service/MessageService.hpp"
#include "../../Service/LogService.hpp"

using namespace Cardinal::Component::EventMap;

void EventMap::Invoke (std::string channel, std::string message) {
    this->logService_.Verbose("Called EventMap");
    try {
        this->RetrieveAndInvokeEventObjectFromMessage(message);
    } catch (Cardinal::Exception::InvalidOrMissingEvent& e) {
        this->logService_.Info("EventMap::Invoke", "Invalid or missing event " + message + " Channel: " + channel);
    } catch (Cardinal::Exception::InvalidMessage& e) {
        this->logService_.Warning("EventMap::Invoke", "Invalid message " + message + " Channel: " + channel);
    }
}

void EventMap::Register (std::string eventName, Cardinal::Event::AbstractEvent *eventObject) {
    this->logService_.Debug("EventMap::Register", "Registered " + eventName);
    events.insert(pair<std::string, std::map<std::string, Cardinal::Event::AbstractEvent *>::mapped_type>(eventName, eventObject));
}


std::__1::tuple<std::__1::string, std::__1::string> EventMap::RetrieveEventFromMessage (std::string message) {
    // ToDo: Hook up to message service.
    // Cardinal::Service::MessageService messageService = Cardinal::Service::MessageService(message);
    // return messageService.Decode();
    return std::make_tuple("test", "test");
}

void EventMap::RetrieveAndInvokeEventObjectFromMessage(std::string Message) {
    this->logService_.Verbose("EventMap::RetrieveAndInvokeEventObjectFromMessage", "Called");
    auto [eventName, payload] = this->RetrieveEventFromMessage(Message);

    this->logService_.Debug(
        "EventMap::RetrieveAndInvokeEventObjectFromMessage",
        "Received " + (std::string)eventName + " " + (std::string)payload
    );

    this->RetrieveAndInvokeEventObject(eventName, payload);
}

void EventMap::RetrieveAndInvokeEventObject(std::string EventName, std::string Payload) {
    try {
        auto receivedEventObject = events.at(EventName);
        receivedEventObject->invoke(Payload);
    } catch (std::exception& e) {
        throw Cardinal::Exception::InvalidOrMissingEvent();
    }
}

// static eventObject EventMap::events;
