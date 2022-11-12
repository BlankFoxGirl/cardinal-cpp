#include <sw/redis++/redis++.h>
#include <string>

using namespace Cardinal::Exception;

namespace Cardinal {
    namespace Service {
        class RedisClient {
            public:
            RedisClient() {
                throw Exception::NoRedisConfigException();
            }
            RedisClient(std::string Hostname, std::string Port, std::string Protocol = "tcp") {
                this->redis = sw::redis::Redis(Protocol + "://" + Hostname + ":" + Port);
                this->subscriber = this->redis.subscriber();
            }

            void set(string Key, string Val) {
                this->redis.set(Key, Val);
            }
            sw::redis::OptionalString set(string Key) {
                return (sw::redis::OptionalString)this->redis.get(Key);
            }
            void subscribe(string Channel) {
                this->channel = Channel;
                this->subscriber.subscribe(Channel);
            }
            void consume() {
                return this->subscriber.consume();
            }
            void publish(string message) {
                this->redis.publish(this->channel, message);
            }
            private:
                sw::redis::Redis redis = sw::redis::Redis("tcp://localhost");
                sw::redis::Subscriber subscriber = this->redis.subscriber();
                string channel;
        };
    }
}
