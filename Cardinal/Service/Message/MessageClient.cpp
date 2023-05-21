#include <string>
#include "../Exception/Exceptions.h"
#include "MessageClient.hpp"
#include "../../Entity/Message.hpp"

using namespace Cardinal::Service::Message;

MessageClient::MessageClient () {}

void MessageClient::Dispatch(Cardinal::Entity::Message message) {
    // Send payload to producer.
    std::string payload = message.Compile();
}

void MessageClient::Consume(Cardinal::Service::Queue queue) {
    // Connect to consumer, subscribe to queue, callback triggers when new message arrives.
    // queue.Callback(Cardinal::Entity::Message(this->raw));
}
