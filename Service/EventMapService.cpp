#include <string>
#include <map>
#include "../Exception/Exceptions.h"
#include "../Event/AbstractEvent.h"

#include "EventMapService.hpp"
using namespace std;
using namespace Cardinal::Event;
using namespace Cardinal::Exception;
// using namespace Cardinal::Global;
using namespace Cardinal::Service;

// typedef map<string, Cardinal::Event::AbstractEvent*> eventObject;

void EventMapService::Invoke (string channel, string message) {
    try {
        this->RetrieveAndInvokeEventObjectFromMessage(message);
    } catch (Cardinal::Exception::InvalidOrMissingEvent& e) {
        // DI::getDI().getLogService().Info("EventMap::Invoke", "Invalid or missing event " + message + " Channel: " + channel);
    } catch (Cardinal::Exception::InvalidMessage& e) {
        // DI::getDI().getLogService().Warning("EventMap::Invoke", "Invalid message " + message + " Channel: " + channel);
    }
}

void EventMapService::Register (string eventName, Cardinal::Event::AbstractEvent *eventObject) {
    events.insert(pair<string, std::map<std::string, Cardinal::Event::AbstractEvent *>::mapped_type>(eventName, eventObject));
}


// std::__1::tuple<std::__1::string, std::__1::string> EventMapService::RetrieveEventFromMessage (string message) {
//     Cardinal::Service::MessageService messageService = Cardinal::Service::MessageService(message);
//     return messageService.Decode();
// }

void EventMapService::RetrieveAndInvokeEventObjectFromMessage(string Message) {
    // DI::getDI()->getLogService().Debug("EventMap::RetrieveAndInvokeEventObjectFromMessage", "Called");
    // auto [eventName, payload] = this->RetrieveEventFromMessage(Message);

    // DI::getDI()->getLogService().Debug(
    //     "EventMap::RetrieveAndInvokeEventObjectFromMessage",
    //     "Received " + (string)eventName + " " + (string)payload
    // );

    // this->RetrieveAndInvokeEventObject(eventName, payload);
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
