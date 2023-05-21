#include <string>
#include "Receive.hpp"
#include "../../Exception/Exceptions.h"
#include "../../Service/LogService.hpp"
#include "../../Service/MessageService.hpp"

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

int Receive::invoke(void* args) {
    this->logService.Verbose("[Called] Cardinal::Component::Message::Receive::invoke");
    std::string* raw = (std::string*) args;
    this->logService.Debug("Received message: " + *raw);
    Cardinal::Entity::Message* message = new Cardinal::Entity::Message(*raw);
    this->SetMessageContext(*message);
    this->logService.Verbose("[Closed] Cardinal::Component::Message::Receive::invoke");
};
