#include "Send.hpp"
#include "../../Exception/Exceptions.h"
#include "../../Service/LogService.hpp"
#include "../../Service/MessageService.hpp"
#include "../../Entity/Message.hpp"

using namespace Cardinal::Component::Message;

int Send::invoke(void* args) {
    this->logService.Verbose("[Called] Cardinal::Component::Message::Send::invoke");
    Cardinal::Entity::Message* message = (Cardinal::Entity::Message*) args;
    this->logService.Debug("Sending message: " + message->Compile());
    this->messageService.Dispatch(*message);
    this->logService.Debug("Message sent!");
    this->logService.Verbose("[Closed] Cardinal::Component::Message::Send::invoke");
    return 0;
};