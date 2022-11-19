#include "Entity/Event.h"
#include "Exception/Exceptions.h"
#include "Service/Services.h"
#include "Event/Events.h"
#include <unistd.h>

using namespace std;
namespace ttest {
    class Test {
        public:
        void test() {
            throw Cardinal::Exception::AccountNotFound();
        }

        void test2() {
            Test::client.subscribe("test");
            Test::client.publish("Test message");
        }
        void test3_setup() {
            Cardinal::Event::TestEvent *t = new Cardinal::Event::TestEvent();
            Cardinal::Event::EventMap::Register("test", t);
        }

        static Cardinal::Service::RedisClient client;
    };
}
// Config;
Cardinal::Event::eventObject Cardinal::Event::EventMap::events = {};
Cardinal::Service::RedisClient ttest::Test::client = Cardinal::Service::RedisClient("localhost", "6379");

int main() {
    Cardinal::Entity::Event entity;

    cout << entity.getUUID() << endl;
    try {
        ttest::Test t;
        // t.test2();
        t.test3_setup();
        t.test2();
    } catch (Cardinal::Exception::AccountNotFound& e) {
        cout << e.what() << endl;
    } catch (Cardinal::Exception::InvalidOrMissingEvent& e) {
        cout << e.what() << endl;
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }
    while (true) {
        usleep(1);
        ttest::Test::client.consume();
    }
}

