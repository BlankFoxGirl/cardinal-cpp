#include "Redis.hpp"
#include <string>
#include "../Entity/Event.h"
#include "../Exception/Exceptions.h"
#include "EventMapService.hpp"
#include "LogService.h"

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

            virtual void Set(std::string Key, std::string Val) = 0;
            virtual sw::redis::OptionalString set(std::string Key) = 0;
            virtual void SubscribeEvent(std::string Channel) = 0;
            virtual void Consume() = 0;
            virtual void Write(Cardinal::Entity::Event Event) = 0;
            virtual Subscriber GetSubscriber() = 0;
        };

        class RedisClient: public CacheClientInterface {
            public:
                explicit RedisClient(Cardinal::Service::EventMapServiceInterface& s, Cardinal::Service::LogServiceInterface& l): eventMapService_(s), logService_(l) {
                    // this->subscriber = this->redis.subscriber();
                }
                void Connect(std::string Hostname, std::string Port, std::string Protocol = "tcp");

                void Set(std::string Key, std::string Val);
                sw::redis::OptionalString set(std::string Key);
                void SubscribeEvent(std::string Channel);
                void Consume();
                void Write(Cardinal::Entity::Event Event);
                Subscriber GetSubscriber();

            private:
                Cardinal::Service::EventMapServiceInterface& eventMapService_;
                Cardinal::Service::LogServiceInterface& logService_;
                RedisInstance redis;
                Subscriber subscriber;
                void InvokeEventMapService(string channel, string message);
        };
    }
}
#endif