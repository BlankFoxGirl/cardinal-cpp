#include "Redis.hpp"
#include "RedisClient.h"
#include <string>
#include "../Exception/NoRedisConfigException.h"
#include "../Entity/Event.h"

using namespace Cardinal::Exception;
using namespace std;

using namespace Cardinal::Service;
using RedisInstance = AbstractRedis;
RedisClient::RedisClient()
{
    try {
        // this->redis = RedisInstance();
    } catch (const sw::redis::Error &e) {
        // Do nothing.
    }
}

RedisClient::RedisClient(std::string Hostname, std::string Port, std::string Protocol)
{
    this->redis = RedisInstance(Protocol + "://" + Hostname + ":" + Port);
}

void RedisClient::Connect(std::string Hostname, std::string Port, std::string Protocol)
{
    this->redis = RedisInstance(Protocol + "://" + Hostname + ":" + Port);
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
    this->redis.subscriber().subscribe(Channel);

    this->redis.subscriber().on_message(std::bind(&RedisClient::InvokeEventMapService, this, std::placeholders::_1, std::placeholders::_2));
}

void RedisClient::InvokeEventMapService(string channel, string message)
{
    // this->di->getEventMapService().Invoke(channel, message);
}

void RedisClient::write(Cardinal::Entity::Event Event)
{
    this->redis.publish(Event.key, Event.payload);
}

void RedisClient::consume()
{
    return this->redis.subscriber().consume();
}

void RedisClient::publish(string message)
{
    this->redis.publish(this->channel, message);
}
