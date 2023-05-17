#include "Redis.hpp"
#include <string>
#include "../Entity/Event.h"
#include "../Exception/Exceptions.h"

using namespace Cardinal::Service;
// using namespace Cardinal::Global;
using RedisInstance = AbstractRedis;

#ifndef RC_H
#define RC_H

namespace Cardinal {
    namespace Service {
        class CacheClientInterface {
        public:
            virtual ~CacheClientInterface() noexcept = default;
            virtual void Connect(std::string Hostname, std::string Port, std::string Protocol = "tcp") = 0;

            virtual void set(std::string Key, std::string Val) = 0;
            virtual sw::redis::OptionalString set(std::string Key) = 0;
            virtual void subscribe(std::string Channel) = 0;
            virtual void consume() = 0;
            virtual void publish(std::string message) = 0;
            virtual void write(Cardinal::Entity::Event Event) = 0;
        };

        class RedisClient: public CacheClientInterface {
            public:
            RedisClient();
            RedisClient(std::string Hostname, std::string Port, std::string Protocol = "tcp");
            void Connect(std::string Hostname, std::string Port, std::string Protocol = "tcp");

            void set(std::string Key, std::string Val);
            sw::redis::OptionalString set(std::string Key);
            void subscribe(std::string Channel);
            void consume();
            void publish(std::string message);
            void write(Cardinal::Entity::Event Event);

            private:
                RedisInstance redis;
                std::string channel;
                void InvokeEventMapService(string channel, string message);
        };
    }
}
#endif