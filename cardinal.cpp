#include "Entity/Event.h"
#include "Exception/Exceptions.h"
#include "Service/Services.h"
#include "Event/Events.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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
        // static void Connect() {
        //     Test::client = Cardinal::Service::RedisClient("localhost", "6379");
        // }
        void test() {
            throw Cardinal::Exception::AccountNotFound();
        }

        void test2() {
            Test::client.subscribe("test");
            Test::client.publish("Test message");
        }
        void test3_setup() {
            Cardinal::Event::TestEvent *t = new Cardinal::Event::TestEvent();
            Cardinal::Event::EventMap::Register("TestEvent", t);
        }

        static Cardinal::Service::RedisClient client;
    };
}
// Config;
Cardinal::Event::eventObject Cardinal::Event::EventMap::events = {};
Cardinal::Service::RedisClient ttest::Test::client = Cardinal::Service::RedisClient("localhost", "6379");

int main() {
    Cardinal::Entity::Event entity;
    Cardinal::Service::LogService Logger = Cardinal::Service::LogService();
    try {
        // ttest::Test::Connect();
        // ttest::Test::client.Connect("redis", "6379");
    } catch (sw::redis::IoError& e) {
        Logger.Log("Unable to connect to redis server", e.what(), Cardinal::Service::LOG_LEVEL::Error);
        exit(1);
    }

    Logger.Log("Starting Cardinal Core");
    ttest::Test t;
    try {
        t.test2();
        // t.test3_setup();
        // t.test2();
    } catch (Cardinal::Exception::AccountNotFound& e) {
        cout << e.what() << endl;
    } catch (Cardinal::Exception::InvalidOrMissingEvent& e) {
        cout << e.what() << endl;
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }

    // Is not a listener, no TCP Connections required.
    std::string is_listener = "FALSE";
    try {
        is_listener = std::getenv("IS_LISTENER") ? std::getenv("IS_LISTENER") : "FALSE"; // Causing segmentation fault.
        // Do nothing.
    } catch (std::exception& e) {
        Logger.Log("", e.what(), Cardinal::Service::LOG_LEVEL::Error);
    }

    if (is_listener.compare("FALSE") == 0) {
        t.test3_setup();
        while (true) {
            usleep(1);
            ttest::Test::client.consume();
        }
    }
}

