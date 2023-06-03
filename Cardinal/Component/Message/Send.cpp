#include "Send.hpp"
#include "Cardinal/Exception/Exceptions.h"
#include "Cardinal/Service/LogService.hpp"
#include "Cardinal/Service/MessageService.hpp"
#include "Cardinal/Entity/Message.hpp"

using namespace Cardinal::Component::Message;

int Send::invoke(void *args)
{
    this->logService.Verbose("[Called] Cardinal::Component::Message::Send::invoke");
    Cardinal::Entity::Message *message = (Cardinal::Entity::Message *)args;
    this->logService.Debug("Sending message: " + message->Compile());
    this->messageService.Dispatch(*message);
    this->logService.Debug("Message sent!");
    this->logService.Verbose("[Closed] Cardinal::Component::Message::Send::invoke");
    delete message;
    return 0;
};