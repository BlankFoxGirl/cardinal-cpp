#ifndef CARDINAL_SERVICE_MEMORY_REDISCACHECLIENT_H
#define CARDINAL_SERVICE_MEMORY_REDISCACHECLIENT_H
#include "Cardinal/Service/MemoryService.hpp"
#include <sw/redis++/redis++.h>

namespace Cardinal::Service::Memory {
    class RedisCacheClient: public MemoryServiceInterface {
        public:
            RedisCacheClient();
            void Connect(std::string ConnectUrl);
            void WriteHash(std::string Key, std::string Field, std::string Value);
            void WriteHash(std::string Key, std::pair<std::string, std::string> Pair);
            void Write(std::string Key, std::string Value);
            std::string Read(std::string Key);
            std::pair<std::string, std::string> ReadHash(std::string Key, std::string Field);

            private:
                static sw::redis::Redis redis;
    };
}
#endif