#include <sw/redis++/redis++.h>
#include "RedisClient.h"
#include <string>
#include "../Exception/NoRedisConfigException.h"

using namespace Cardinal::Exception;
using namespace std;

using namespace Cardinal::Service;

RedisClient::RedisClient() {
    throw Exception::NoRedisConfigException();
}
RedisClient::RedisClient(std::string Hostname, std::string Port, std::string Protocol) {
    this->redis = sw::redis::Redis(Protocol + "://" + Hostname + ":" + Port);
    this->subscriber = this->redis.subscriber();
}

void RedisClient::set(string Key, string Val) {
    this->redis.set(Key, Val);
}
sw::redis::OptionalString RedisClient::set(string Key) {
    return (sw::redis::OptionalString)this->redis.get(Key);
}
void RedisClient::subscribe(string Channel) {
    this->channel = Channel;
    this->subscriber.subscribe(Channel);
    this->subscriber.on_message(Cardinal::Event::EventMap::Invoke);
}
void RedisClient::consume() {
    return this->subscriber.consume();
}
void RedisClient::publish(string message) {
    this->redis.publish(this->channel, message);
}

// sw::redis::Redis RedisClient::redis = sw::redis::Redis("tcp://localhost");
// sw::redis::Subscriber RedisClient::subscriber = this->redis.subscriber();
// string RedisClient::channel;