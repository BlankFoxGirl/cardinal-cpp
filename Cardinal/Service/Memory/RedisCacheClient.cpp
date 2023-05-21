#include "RedisCacheClient.hpp"
#include <utility>
#include <string>

using namespace Cardinal::Service::Memory;
RedisCacheClient::RedisCacheClient() {};

void RedisCacheClient::WriteHash(std::string Key, std::string Field, std::string Value) {
    RedisCacheClient::redis.hset(Key, std::make_pair(Field, Value));
}

void RedisCacheClient::WriteHash(std::string Key, std::pair<std::string, std::string> Pair) {
    RedisCacheClient::redis.hset(Key, Pair);
}

void RedisCacheClient::Write(std::string Key, std::string Value) {
    RedisCacheClient::redis.set(Key, Value);
}

std::string RedisCacheClient::Read(std::string Key) {
    auto val = RedisCacheClient::redis.get(Key);

    return val.value_or("");
}

std::pair<std::string, std::string> RedisCacheClient::ReadHash(std::string Key, std::string Field) {
    auto val = RedisCacheClient::redis.hget(Key, Field);
    return std::make_pair(Field, val.value_or(""));
}

void RedisCacheClient::Connect(std::string ConnectUrl) {
    RedisCacheClient::redis = sw::redis::Redis(ConnectUrl);
}

sw::redis::Redis RedisCacheClient::redis = sw::redis::Redis();  // static reference to the redis server?