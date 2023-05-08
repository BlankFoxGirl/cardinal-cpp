#include "Entity/Event.h"
#include "Exception/Exceptions.h"
#include "Service/Services.h"
#include "Event/Events.h"
#include <unistd.h>

using namespace std;
namespace Cardinal {
    class Core {
            Core() {
                this->Init();
            }
        private:
            bool Active = false;
            bool dryRun = false;
            bool is_listener = false;

            void Init() {
                if (this->is_listener) {
                    this->StartListner();
                } else {
                    this->StartWorker();
                }

                this->StartLoop();
            }

            void StartWorker() {}
            void StartListner() {}

            void StartLoop() {
                while (this->Active && !this->dryRun) {
                    this->Loop();
                }
            }

            void Loop() {
                if (this->is_listener) {
                    this->ListenerLoop();
                } else {
                    this->WorkerLoop();
                }
            }

            void ListenerLoop() {}
            void WorkerLoop() {}
    };
}

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
Cardinal::Service::RedisClient ttest::Test::client = Cardinal::Service::RedisClient();

int main() {
    Cardinal::Entity::Event entity;
    try {
        ttest::Test::client.Connect("redis", "6379");
    } catch (sw::redis::IoError& e) {
        cout << "Unable to connect to redis server" << endl;
        exit(1);
    }

    cout << "Starting Cardinal Core" << endl;
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

    // Is not a listener, no TCP Connections required.
    std::string is_listener = std::getenv("IS_LISTENER");
    if (is_listener.compare("FALSE") == true) {
        while (true) {
            usleep(1);
            ttest::Test::client.consume();
        }
    }
}

