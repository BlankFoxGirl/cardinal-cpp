#include <string>
#include "MessageClient.hpp"
#include "Cardinal/Entity/Message.hpp"
#include <iostream>

using namespace Cardinal::Service::Message;

void MessageClient::Dispatch(Cardinal::Entity::Message message) {
    // Send payload to producer.
    std::string payload = message.Compile();
    MessageClient::redis.publish(message.getKey(), payload);
}

void MessageClient::Subscribe(Cardinal::Service::Queue queue) {
    // Connect to consumer, subscribe to queue, callback triggers when new message arrives.
    ::MessageSubscribers = this->redis.subscriber();

    this->subscriber.reset(&::MessageSubscribers);
    this->subscriber->subscribe(queue.Name);

    this->subscriber->on_message([queue](std::string channel, std::string message) {
        queue.Callback(message);
    });

    return;
}

void* MessageClient::Consume(Cardinal::Service::Queue queue) {
    this->Subscribe(queue);
    // ToDo: Still need to resolve the issue of subscribers being killed when this method ends.
    return &this->subscriber;
}

void* MessageClient::SubscribeAndConsume(Cardinal::Service::Queue queue) {
    // Connect to consumer, subscribe to queue, callback triggers when new message arrives.
    return this->Consume(queue);
}

void MessageClient::Connect(std::string ConnectUrl) {
    // Connect to message server.
    this->redis = sw::redis::Redis(ConnectUrl);
}

void MessageClient::Connect(std::string Hostname, std::string Port, std::string Protocol) {
    // Connect to message server.
    this->redis = sw::redis::Redis(Protocol + "://" + Hostname + ":" + Port);
}

void MessageClient::ConsumeAllLoop() {
    this->logService->Verbose("[Called] Cardinal::Service::Message::MessageClient::ConsumeAllLoop");

    // ToDo: Use non-blocking.
    this->subscriber->consume();
    this->logService->Verbose("[Closed] Cardinal::Service::Message::MessageClient::ConsumeAllLoop");
}

void MessageClient::ConsumeAllLoop(void* &subscribers) {
    this->logService->Verbose("[Called] Cardinal::Service::Message::MessageClient::ConsumeAllLoop with Params");
    this->logService->Verbose("Casting params to subscriber vector");
    auto subscribersVector = static_cast<std::vector<sw::redis::Subscriber*>*>(subscribers);
    this->logService->Verbose("Done!");
    // Loop through each subscriber and consume messages.
    this->logService->Verbose("Loop through each subscriber and consume messages.");
    for (sw::redis::Subscriber* subscriber : *subscribersVector) {
        try {
            this->logService->Verbose("Calling consume on subscriber.");
            subscriber->consume(); // Segmentation Fault.
            this->logService->Verbose("Done!");
        } catch (const std::exception& e) {
            this->logService->Error("Failed to successfully call consume on subscriber", e.what());
        }
    }

    delete subscribersVector;
}

std::vector<sw::redis::Subscriber*> MessageClient::subscribers = std::vector<sw::redis::Subscriber*>();

sw::redis::Subscriber MessageSubscribers = sw::redis::Subscriber();
