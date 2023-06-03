#ifndef CARDINAL_SERVICE_MEMORY_REDISCACHECLIENT_H
#define CARDINAL_SERVICE_MEMORY_REDISCACHECLIENT_H
#include "Cardinal/Service/MemoryService.hpp"
#include <sw/redis++/redis++.h>
#include <queue>

namespace Cardinal::Service::Memory
{
    class RedisCacheClient : public MemoryServiceInterface
    {
    public:
        RedisCacheClient();
        void Connect(std::string ConnectUrl);
        void Connect(std::string Hostname, std::string Port, std::string Protocol = "tcp");
        void WriteHash(std::string Key, std::string Field, std::string Value, int ttl = DEFAULT_TTL);
        void WriteHash(std::string Key, std::pair<std::string, std::string> Pair, int ttl = DEFAULT_TTL);
        void WriteAllHash(std::string Key, std::vector<std::pair<std::string, std::string>> Hash, int ttl = DEFAULT_TTL);
        void Write(std::string Key, std::string Value, int ttl = DEFAULT_TTL);
        void Add(std::string Key, std::string Value, int ttl = DEFAULT_TTL);
        std::string Fetch(std::string Key);
        long long Length(std::string Key);
        std::string Pop(std::string Key);
        std::queue<std::string> PopRange(std::string Key, int Count);
        std::string Read(std::string Key);
        std::pair<std::string, std::string> ReadHash(std::string Key, std::string Field);
        std::vector<std::pair<std::string, std::string>> ReadAllHash(std::string Key);
        void Delete(std::string Key);
        bool Exists(std::string Key);
        void Persist(std::string Key);

    private:
        static const int DEFAULT_TTL = 60;
        static sw::redis::Redis redis;
        void SetTTL(std::string Key, int ttl);
    };
}
#endif