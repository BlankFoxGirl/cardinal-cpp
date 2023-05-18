// #include "Entity/Event.h"
#include "Exception/Exceptions.h"
#include "Service/LogService.h"
#include "Service/EventMapService.hpp"
#include "Service/RedisClient.h"
#include "Service/TCPListenerService.h"
#include "Event/Events.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "vendor/boost/di.hpp"
namespace di = boost::di;

using namespace std;
namespace Cardinal {
    template <class T = class Type, class LogServiceInterface = class LogServiceInterface>
    class Core {
        using type = T;
        public:
            explicit Core(
                Cardinal::Service::LogServiceInterface& s,
                Cardinal::Service::EventMapServiceInterface& s1,
                Cardinal::Service::CacheClientInterface& s2,
                Cardinal::Service::TCPListenerServiceInterface& s3
            ) : logService_(s), eventMapService_(s1), redisService_(s2), tcpListenerService_(s3) {
                this->Init();
            }

        private:
            Cardinal::Service::LogServiceInterface& logService_;
            Cardinal::Service::EventMapServiceInterface& eventMapService_;
            Cardinal::Service::CacheClientInterface& redisService_;
            Cardinal::Service::TCPListenerServiceInterface& tcpListenerService_;
            bool Active = false;
            bool dryRun = false;
            bool is_listener = false;
            string REDIS_HOST;
            string REDIS_PORT;
            string ENVIRONMENT;
            string IS_LISTENER_DEFAULT_VALUE = "TRUE";

            void Init() {
                this->SetVerboseMode();
                this->LoadEnvironment();
                this->SetLogEnvironment();
                this->logService_.Info("Starting Cardinal Core");
                this->LoadEnvironmentVariables();
                this->StartRedis();

                if (this->is_listener) {
                    this->StartListener();
                } else {
                    this->StartWorker();
                }

                this->StartLoop();
            }

            void SetDebugMode() 
            {
                this->logService_.Info("Setting debug mode...");
                this->logService_.SetMinimumLogLevel(Cardinal::Service::LOG_LEVEL::Debug);
                this->logService_.Debug("Debug mode enabled.");
            }

            void SetVerboseMode() 
            {
                this->logService_.Info("Setting verbose mode...");
                this->logService_.SetMinimumLogLevel(Cardinal::Service::LOG_LEVEL::Verbose);
                this->logService_.Verbose("Verbose mode enabled.");
            }

            void SetLogEnvironment() 
            {
                this->logService_.Debug("Setting log environment...");
                this->logService_.SetEnvironment(this->ENVIRONMENT);
                this->logService_.Verbose("Log environment set to", this->ENVIRONMENT);
            }

            void LoadEnvironmentVariables()
            {
                this->logService_.Verbose("Running LoadEnvironmentVariables");
                this->LoadListenerToggle();
                this->LoadRedisConfig();
            }

            void LoadEnvironment()
            {
                this->logService_.Verbose("Running LoadEnvironment");
                this->logService_.Debug("Loading environment...");
                this->ENVIRONMENT = this->LoadEnvironmentVariable("ENVIRONMENT", "local");
                this->logService_.Debug("Environment set to", this->ENVIRONMENT);
            }

            void LoadRedisConfig()
            {
                this->logService_.Verbose("Called LoadRedisConfig");
                this->logService_.Debug("Loading Redis config...");
                this->REDIS_HOST = this->LoadEnvironmentVariable("REDIS_HOST", "localhost");
                this->REDIS_PORT = this->LoadEnvironmentVariable("REDIS_PORT", "6379");
            }

            void LoadListenerConfig()
            {
                this->logService_.Verbose("Called LoadListenerConfig");
                this->logService_.Debug("Loading listener config...");
                string port = this->LoadEnvironmentVariable("PORT", "7777");
                string bindIp = this->LoadEnvironmentVariable("BIND_IP", "0.0.0.0");
                this->tcpListenerService_.Bind(port, bindIp);
                this->logService_.Debug("Listener config loaded!");
            }

            void LoadListenerToggle() {
                this->logService_.Verbose("Running LoadListenerToggle");
                this->logService_.Debug("Loading listener toggle...");
                std::string is_listener = this->LoadEnvironmentVariable("IS_LISTENER", this->IS_LISTENER_DEFAULT_VALUE);

                this->is_listener = is_listener.compare("TRUE") == 0;
                this->logService_.Debug("this->is_listener set to", (this->is_listener ? "true" : "false"));
            }

            string LoadEnvironmentVariable(string key, string default_value = "") {
                this->logService_.Verbose("Running LoadEnvironmentVariable with Params", key + ", " + default_value);
                this->logService_.Debug("Loading environment variable", key);
                string value = default_value;

                try {
                    this->logService_.Verbose("Attempting to load environment variable", key);
                    value = std::getenv(key.c_str()) ? std::getenv(key.c_str()) : default_value;
                    this->logService_.Verbose("Loaded environment variable", key);
                } catch (std::exception& e) {
                    this->logService_.Verbose("Could not load environment variable", key);
                    this->logService_.Error("Error occurred when attempting to load environment variable " + key, e.what());
                }

                this->logService_.Info(key, "set to " + value);
                return value;
            }

            void StartWorker() {
                this->logService_.Verbose("Called StartWorker");
                this->logService_.Info("Initiating Worker");

                this->logService_.Debug("Registering events...");
                Cardinal::Event::TestEvent *t = new Cardinal::Event::TestEvent(this->logService_);
                this->eventMapService_.Register("TestEvent", t);
                this->logService_.Debug("Events registered!");
                this->logService_.Debug("Subscribing to Redis channel 'test'");
                this->redisService_.Subscribe("test");
                this->logService_.Debug("Subscribed to channel 'test'");
            }

            void StartListener() {
                this->logService_.Verbose("Called StartListener");
                this->logService_.Info("Initiating Listener");
                this->LoadListenerConfig();
                this->logService_.Info("Starting TCP Listener Service...");
                this->tcpListenerService_.Start();
                this->logService_.Info("TCP Listener Service started!");
            }

            void StartLoop() {
                this->logService_.Verbose("Called StartLoop");
                this->Active = true;
                if (this->dryRun) {
                    this->logService_.Warning("Dry run enabled. Exiting.");
                    this->logService_.Verbose("Exiting in StartLoap due to DryRun");
                    exit(0);
                }

                while (this->Active && !this->dryRun) {
                    usleep(1);
                    this->Loop();
                }
            }

            void StartRedis() {
                this->logService_.Verbose("Called StartRedis");
                this->logService_.Info("Starting Redis...");
                this->redisService_.Connect(this->REDIS_HOST, this->REDIS_PORT);
                this->logService_.Info("Redis started!");
            }

            void Loop() {
                if (this->is_listener) {
                    this->ListenerLoop();
                } else {
                    this->WorkerLoop();
                }
            }

            void ListenerLoop() {
                this->tcpListenerService_.Accept();
            }

            void WorkerLoop() {
                this->redisService_.Consume();
            }
    };
}

// namespace ttest {
//     class Test {
//         public:
//             Test() {
//                 // this->di = DI::getDI();
//             }

//             // static void Connect() {
//             //     Test::client = Cardinal::Service::RedisClient("localhost", "6379");
//             // }
//             void test() {
//                 throw Cardinal::Exception::AccountNotFound();
//             }

//             void test2() {
//                 Test::client.subscribe("test");
//                 Test::client.publish("Test message");
//             }
//             void test3_setup() {
//                 Cardinal::Event::TestEvent *t = new Cardinal::Event::TestEvent();
//                 // di.getEventMapService().Register("TestEvent", t);
//             }

//             static Cardinal::Service::RedisClient client;
//         // private:
//             // DI di;
//     };
// }
// // Config;
// // Cardinal::Event::eventObject Cardinal::Event::EventMap::events = {};
// Cardinal::Service::RedisClient ttest::Test::client = Cardinal::Service::RedisClient("localhost", "6379");

int main() {
    // Cardinal::Global::DI * di = new Cardinal::Global::DI();
    auto injector = di::make_injector(
        di::bind<Cardinal::Service::LogServiceInterface>().to<Cardinal::Service::LogService>(),
        di::bind<Cardinal::Service::EventMapServiceInterface>().to<Cardinal::Service::EventMapService>(),
        di::bind<Cardinal::Service::CacheClientInterface>().to<Cardinal::Service::RedisClient>(),
        di::bind<Cardinal::Service::TCPListenerServiceInterface>().to<Cardinal::Service::TCPListenerService>()
    );


    injector.create<Cardinal::Core>();
}

