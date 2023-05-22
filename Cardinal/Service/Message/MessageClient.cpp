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
    auto subscriber = MessageClient::redis.subscriber();
    subscriber.subscribe(queue.Name);
    subscriber.on_message([queue](std::string channel, std::string message) {
        Cardinal::Entity::Message msg = Cardinal::Entity::Message(message);
        queue.Callback(msg);
    });

    // ToDo: Still need to resolve the issue of subscribers being killed when this method ends.
    MessageClient::subscribers.push_back(&subscriber);
}

void MessageClient::SubscribeAndConsume(Cardinal::Service::Queue queue) {
    // Connect to consumer, subscribe to queue, callback triggers when new message arrives.
    this->Consume(queue);
}

void MessageClient::Connect(std::string ConnectUrl) {
    // Connect to message server.
    MessageClient::redis = sw::redis::Redis(ConnectUrl);
}

sw::redis::Redis MessageClient::redis = sw::redis::Redis();
std::vector<sw::redis::Subscriber*> MessageClient::subscribers = std::vector<sw::redis::Subscriber*>();