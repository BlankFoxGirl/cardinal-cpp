#include <string>
#include <map>
#include "../Exception/Exceptions.h"
#include "../Event/AbstractEvent.h"

#include "EventMapService.hpp"
#include "MessageService.h"
#include "LogService.h"

using namespace std;
using namespace Cardinal::Event;
using namespace Cardinal::Exception;
using namespace Cardinal::Service;

void EventMapService::Invoke (string channel, string message) {
    this->logService_.Verbose("Called EventMapService");
    try {
        this->RetrieveAndInvokeEventObjectFromMessage(message);
    } catch (Cardinal::Exception::InvalidOrMissingEvent& e) {
        this->logService_.Info("EventMapService::Invoke", "Invalid or missing event " + message + " Channel: " + channel);
    } catch (Cardinal::Exception::InvalidMessage& e) {
        this->logService_.Warning("EventMapService::Invoke", "Invalid message " + message + " Channel: " + channel);
    }
}

void EventMapService::Register (string eventName, Cardinal::Event::AbstractEvent *eventObject) {
    this->logService_.Debug("EventMapService::Register", "Registered " + eventName);
    events.insert(pair<string, std::map<std::string, Cardinal::Event::AbstractEvent *>::mapped_type>(eventName, eventObject));
}


std::__1::tuple<std::__1::string, std::__1::string> EventMapService::RetrieveEventFromMessage (string message) {
    Cardinal::Service::MessageService messageService = Cardinal::Service::MessageService(message);
    return messageService.Decode();
}

void EventMapService::RetrieveAndInvokeEventObjectFromMessage(string Message) {
    this->logService_.Verbose("EventMapService::RetrieveAndInvokeEventObjectFromMessage", "Called");
    auto [eventName, payload] = this->RetrieveEventFromMessage(Message);

    this->logService_.Debug(
        "EventMapService::RetrieveAndInvokeEventObjectFromMessage",
        "Received " + (string)eventName + " " + (string)payload
    );

    this->RetrieveAndInvokeEventObject(eventName, payload);
}

void EventMapService::RetrieveAndInvokeEventObject(string EventName, string Payload) {
    try {
        auto receivedEventObject = events.at(EventName);
        receivedEventObject->invoke(Payload);
    } catch (std::exception& e) {
        throw Cardinal::Exception::InvalidOrMissingEvent();
    }
}

// static eventObject EventMapService::events;
