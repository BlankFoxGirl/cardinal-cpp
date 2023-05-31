#include <string>
#include "Receive.hpp"
#include "Cardinal/Exception/Exceptions.h"
#include "Cardinal/Service/LogService.hpp"
#include "Cardinal/Service/MessageService.hpp"
#include "Cardinal/Entity/Message.hpp"
#include "Cardinal/Component/EventMap/EventMap.hpp"

using namespace Cardinal::Component::Message;

Cardinal::Entity::Message Receive::SetMessageContext(Cardinal::Entity::Message message) {
    this->logService.Verbose("[Called] Cardinal::Component::Message::Receive::SetMessageContext");
    this->message = message;
    this->logService.Verbose("[Closed] Cardinal::Component::Message::Receive::SetMessageContext");
    return this->message;
}

Cardinal::Entity::Message Receive::SetMessageContext(std::string message) {
    this->logService.Verbose("[Called] Cardinal::Component::Message::Receive::SetMessageContext");
    this->message = Cardinal::Entity::Message(message);
    this->logService.Verbose("[Closed] Cardinal::Component::Message::Receive::SetMessageContext");
    return this->message;
}

int Receive::operator()(Cardinal::Entity::Message message) {
    this->logService.Verbose("[Called] Cardinal::Component::Message::Receive::invoke");
    this->logService.Debug("Received message: " + message.getPayload());
    this->SetMessageContext(message);
    this->InvokeEventMap();
    this->logService.Verbose("[Closed] Cardinal::Component::Message::Receive::invoke");
    return 0;
};

void Receive::InvokeEventMap() {
    this->logService.Verbose("[Called] Cardinal::Component::Message::Receive::InvokeEventMap");

    try {
        this->logService.Verbose("--Cardinal::Component::Message::Receive::InvokeEventMap instantiating event map component.");
        auto eventMap = Cardinal::Component::EventMap::EventMap::Create(this->logService, this->messageService, this->memoryService);
        this->logService.Verbose("--Cardinal::Component::Message::Receive::InvokeEventMap Invoking event map component.");
        eventMap->Invoke(this->message);
        this->logService.Verbose("--Cardinal::Component::Message::Receive::InvokeEventMap done.");
    } catch (std::exception& e) {
        this->logService.Error("--Cardinal::Component::Message::Receive::InvokeEventMap", "Failed to execute event.");
    }

    this->logService.Verbose("[Closed] Cardinal::Component::Message::Receive::InvokeEventMap");
}