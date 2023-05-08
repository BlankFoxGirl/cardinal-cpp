#include <sw/redis++/redis++.h>
#include <string>
#include "../Entity/Event.h"
#include "../Exception/Exceptions.h"

#ifndef RC_H
#define RC_H

namespace Cardinal {
    namespace Service {
        class RedisClient {
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
                sw::redis::Redis redis = sw::redis::Redis("tcp://localhost");
                sw::redis::Subscriber subscriber = this->redis.subscriber();
                std::string channel;
        };
    }
}
#endif