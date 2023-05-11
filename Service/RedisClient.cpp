#include <sw/redis++/redis++.h>
#include "RedisClient.h"
#include <string>
#include "../Exception/NoRedisConfigException.h"
#include "../Entity/Event.h"
#include "../Event/EventMap.h"

using namespace Cardinal::Exception;
using namespace std;

using namespace Cardinal::Service;

RedisClient::RedisClient() {}

RedisClient::RedisClient(std::string Hostname, std::string Port, std::string Protocol)
{
    this->redis = sw::redis::Redis(Protocol + "://" + Hostname + ":" + Port);
    this->subscriber = this->redis.subscriber();
}

void RedisClient::Connect(std::string Hostname, std::string Port, std::string Protocol)
{
    this->redis = sw::redis::Redis(Protocol + "://" + Hostname + ":" + Port);
    this->subscriber = this->redis.subscriber();
}

void RedisClient::set(string Key, string Val)
{
    this->redis.set(Key, Val);
}

sw::redis::OptionalString RedisClient::set(string Key)
{
    return (sw::redis::OptionalString)this->redis.get(Key);
}

void RedisClient::subscribe(string Channel)
{
    this->channel = Channel;
    this->subscriber.subscribe(Channel);
    this->subscriber.on_message(Cardinal::Event::EventMap::Invoke);
}

void RedisClient::write(Cardinal::Entity::Event Event)
{
    this->redis.publish(Event.key, Event.payload);
}

void RedisClient::consume()
{
    return this->subscriber.consume();
}

void RedisClient::publish(string message)
{
    this->redis.publish(this->channel, message);
}
