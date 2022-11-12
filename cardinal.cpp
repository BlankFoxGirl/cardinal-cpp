#include "Entity/Event.h"
#include "Exception/Exceptions.h"
#include "Service/RedisClient.h"

using namespace std;
namespace ttest {
    class Test {
        public:
        void test() {
            throw Cardinal::Exception::AccountNotFound();
        }

        void test2() {
            Cardinal::Service::RedisClient c = Cardinal::Service::RedisClient("localhost", "6379");
            c.subscribe("test");
            c.publish("Test message");
        }
    };
}

int main() {
    Cardinal::Entity::Event entity;
    cout << entity.getUUID();
    try {
        ttest::Test t;
        t.test2();
        t.test();
    } catch (Cardinal::Exception::AccountNotFound& e) {
        cout << e.what() << endl;
    } catch (std::exception& e) {

    }
}

