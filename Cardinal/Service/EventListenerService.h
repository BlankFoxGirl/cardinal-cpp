#ifndef ELS_H
#define ELS_H
#include <string>

using namespace std;

namespace Cardinal::Service {
    class EventListenerService {
        //   Sets up the redis connection, subscribes, and handles inbound events. On event receipt, triggers the event's invocation.
        public:
        EventListenerService(string topic) {
            Cardinal::Service::RedisClient c = Cardinal::Service::RedisClient("localhost", "6379");
            c.subscribe(topic, this);
            c.publish("ACK");
        }
        void callbackHandler(string channel, string message) {
            cout << channel + ":" + message << endl;
        }
        static void callbackHandler(Cardinal::Service::EventListenerService *service, string channel, string message) {
            service->callbackHandler(channel, message);
        }
    };
}
#endif