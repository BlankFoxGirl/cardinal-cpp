
#include "Exception/Exceptions.h"
#include "Service/LogService.hpp"
// #include "Service/EventMapService.hpp"
// #include "Service/MemoryService.hpp"
// #include "Service/MessageService.hpp"
// #include "Service/CommunicationService.hpp"
// #include "Service/UserService.hpp"
// #include "Event/Events.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

namespace Cardinal {
    class Core {
        public:
            explicit Core(
                Cardinal::Service::LogServiceInterface& s
                // Cardinal::Service::EventMapServiceInterface& s1,
                // Cardinal::Service::CacheClientInterface& s2,
                // Cardinal::Service::TCPListenerServiceInterface& s3,
                // Cardinal::Service::UserServiceInterface& s4
            ) : logService_(s)
                // eventMapService_(s1),
                // redisService_(s2),
                // tcpListenerService_(s3),
                // userService_(s4)
            {
                this->Init();
            }

        private:
            Cardinal::Service::LogServiceInterface& logService_;
            // Cardinal::Service::EventMapServiceInterface& eventMapService_;
            // Cardinal::Service::CacheClientInterface& redisService_;
            // Cardinal::Service::TCPListenerServiceInterface& tcpListenerService_;
            // Cardinal::Service::UserServiceInterface& userService_;
            bool Active = false;
            bool dryRun = true;
            bool is_listener = false;
            string REDIS_HOST;
            string REDIS_PORT;
            string ENVIRONMENT;
            string IS_LISTENER_DEFAULT_VALUE = "TRUE";

            void Init();

            void SetDebugMode();

            void SetVerboseMode();

            void SetLogEnvironment();

            void LoadEnvironmentVariables();

            void LoadEnvironment();

            void LoadRedisConfig();

            void LoadListenerConfig();

            void LoadListenerToggle();

            string LoadEnvironmentVariable(string key, string default_value = "");

            void StartWorker();

            void StartListener();

            void StartLoop();

            void StartRedis();

            void Loop();

            void ListenerLoop();

            void WorkerLoop();
    };
}