#include <string>
#include "MessageClient.hpp"
#include "../../Entity/Message.hpp"

using namespace Cardinal::Service::Message;

MessageClient::MessageClient () {}

void MessageClient::Dispatch(Cardinal::Entity::Message message) {
    // Send payload to producer.
    std::string payload = message.Compile();
    MessageClient::redis.publish(message.getKey(), payload);
}

void MessageClient::Consume(Cardinal::Service::Queue queue) {
    // Connect to consumer, subscribe to queue, callback triggers when new message arrives.
    MessageClient::subscriber = MessageClient::redis.subscriber();
    MessageClient::subscriber.subscribe(queue.Name);
    MessageClient::subscriber.on_message([queue](std::string channel, std::string message) {
        Cardinal::Entity::Message msg = Cardinal::Entity::Message(message);
        queue.Callback(msg);
    });

    MessageClient::subscriber.consume();
}

void MessageClient::Connect(std::string ConnectUrl) {
    // Connect to message server.
    MessageClient::redis = sw::redis::Redis(ConnectUrl);
}

sw::redis::Subscriber MessageClient::subscriber = sw::redis::Subscriber();
sw::redis::Redis MessageClient::redis = sw::redis::Redis();