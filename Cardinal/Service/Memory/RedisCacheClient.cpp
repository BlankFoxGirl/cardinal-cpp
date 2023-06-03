#include "RedisCacheClient.hpp"
#include <utility>
#include <string>

using namespace Cardinal::Service::Memory;
RedisCacheClient::RedisCacheClient(){};

void RedisCacheClient::WriteHash(std::string Key, std::string Field, std::string Value, int ttl)
{
    this->WriteHash(Key, std::make_pair(Field, Value), ttl);
}

void RedisCacheClient::WriteHash(std::string Key, std::pair<std::string, std::string> Pair, int ttl)
{
    RedisCacheClient::redis.hset(Key, Pair);
    this->SetTTL(Key, ttl);
}

void RedisCacheClient::WriteAllHash(std::string Key, std::vector<std::pair<std::string, std::string>> Hash, int ttl)
{
    RedisCacheClient::redis.hmset(Key, Hash.begin(), Hash.end());
    this->SetTTL(Key, ttl);
}

void RedisCacheClient::Write(std::string Key, std::string Value, int ttl)
{
    RedisCacheClient::redis.set(Key, Value);
    this->SetTTL(Key, ttl);
}

std::string RedisCacheClient::Read(std::string Key)
{
    auto val = RedisCacheClient::redis.get(Key);

    return val.value_or("");
}

std::pair<std::string, std::string> RedisCacheClient::ReadHash(std::string Key, std::string Field)
{
    auto val = RedisCacheClient::redis.hget(Key, Field);
    return std::make_pair(Field, val.value_or(""));
}

std::vector<std::pair<std::string, std::string>> RedisCacheClient::ReadAllHash(std::string Key)
{
    std::vector<std::pair<std::string, std::string>> response;
    RedisCacheClient::redis.hgetall(Key, std::back_inserter(response));
    return response;
}

void RedisCacheClient::Connect(std::string ConnectUrl)
{
    RedisCacheClient::redis = sw::redis::Redis(ConnectUrl);
}

void RedisCacheClient::Connect(std::string Hostname, std::string Port, std::string Protocol)
{
    RedisCacheClient::redis = sw::redis::Redis(Protocol + "://" + Hostname + ":" + Port);
}

void RedisCacheClient::Add(std::string Key, std::string Value, int ttl)
{
    RedisCacheClient::redis.rpush(Key, Value);
    this->SetTTL(Key, ttl);
}

std::string RedisCacheClient::Pop(std::string Key)
{
    auto val = RedisCacheClient::redis.lpop(Key);
    return val.value_or("");
}

std::queue<std::string> RedisCacheClient::PopRange(std::string Key, int Count)
{
    std::vector<std::string> values;
    RedisCacheClient::redis.lrange(Key, 0, (Count - 1), std::back_inserter(values));
    std::queue<std::string> queue;
    for (auto value : values)
    {
        queue.push(value);
        RedisCacheClient::redis.lpop(Key);
    }

    return queue;
}

std::string RedisCacheClient::Fetch(std::string Key)
{
    auto val = RedisCacheClient::redis.lindex(Key, 0);
    return val.value_or("");
}

long long RedisCacheClient::Length(std::string Key)
{
    auto val = RedisCacheClient::redis.llen(Key);
    return val;
}

void RedisCacheClient::SetTTL(std::string Key, int ttl)
{
    if (ttl > 0)
    {
        RedisCacheClient::redis.expire(Key, ttl);
    }
}

void RedisCacheClient::Delete(std::string Key)
{
    RedisCacheClient::redis.unlink(Key);
}

bool RedisCacheClient::Exists(std::string Key)
{
    auto val = RedisCacheClient::redis.exists(Key);
    return val;
}

void RedisCacheClient::Persist(std::string Key)
{
    RedisCacheClient::redis.persist(Key);
}

sw::redis::Redis RedisCacheClient::redis = sw::redis::Redis(); // static reference to the redis server?