#include "Redis.hpp"
#include "RedisClient.h"
#include <string>
#include "../Exception/NoRedisConfigException.h"
#include "../Entity/Event.h"

using namespace Cardinal::Exception;
using namespace std;

using namespace Cardinal::Service;
using RedisInstance = AbstractRedis;
void RedisClient::Connect(std::string Hostname, std::string Port, std::string Protocol)
{
    this->redis = RedisInstance(Protocol + "://" + Hostname + ":" + Port);
}

void RedisClient::Set(string Key, string Val)
{
    this->redis.set(Key, Val);
}

sw::redis::OptionalString RedisClient::set(string Key)
{
    return (sw::redis::OptionalString)this->redis.get(Key);
}

void RedisClient::SubscribeEvent(string Channel)
{
    this->logService_.Verbose("RedisClient::Subscribe Subscribing to channel: " + Channel);

    this->subscriber = this->redis.subscriber();
    this->subscriber.subscribe(Channel);

    this->logService_.Verbose("RedisClient::Subscribe Binding OnMessage Handler ");

    this->subscriber.on_message([this](std::string channel, std::string message) {
        this->logService_.Verbose("Called Subscriber on_message");
        this->InvokeEventMapService(channel, message);
    });
}

Subscriber RedisClient::GetSubscriber()
{
    return this->redis.subscriber();
}

void RedisClient::InvokeEventMapService(string channel, string message)
{
    this->logService_.Verbose("Called RedisClient::InvokeEventMapService");
    this->logService_.Debug("RedisClient::InvokeEventMapService received", message);
    this->logService_.Verbose("RedisClient::InvokeEventMapService invoking eventMapService_.Invoke");
    this->eventMapService_.Invoke(channel, message);
}

void RedisClient::Write(Cardinal::Entity::Event Event)
{
    this->redis.publish(Event.key, Event.payload);
}

void RedisClient::Consume()
{
    return this->subscriber.consume();
}

