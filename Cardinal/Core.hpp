
#include "Exception/Exceptions.h"
#include "Service/LogService.hpp"
// #include "Service/EventMapService.hpp"
// #include "Service/MemoryService.hpp"
#include "Service/MessageService.hpp"
// #include "Service/CommunicationService.hpp"
// #include "Service/UserService.hpp"
// #include "Event/Events.h"
#include "Event/AbstractEvent.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

namespace Cardinal {
    class Core {
        public:
            explicit Core(
                Cardinal::Service::LogServiceInterface& s,
                Cardinal::Service::MessageServiceInterface& s1
                // Cardinal::Service::CacheClientInterface& s2,
                // Cardinal::Service::TCPListenerServiceInterface& s3,
                // Cardinal::Service::UserServiceInterface& s4
            ) : logService_(s),
                messageService_(s1)
                // redisService_(s2),
                // tcpListenerService_(s3),
                // userService_(s4)
            {
                this->Init();
            }

            template <typename T> static void RegisterEvent();

        private:
            Cardinal::Service::LogServiceInterface& logService_;
            Cardinal::Service::MessageServiceInterface& messageService_;
            // Cardinal::Service::CacheClientInterface& redisService_;
            // Cardinal::Service::TCPListenerServiceInterface& tcpListenerService_;
            // Cardinal::Service::UserServiceInterface& userService_;
            bool Active = false;
            bool dryRun = false;
            bool is_listener = false;
            string REDIS_HOST;
            string REDIS_PORT;
            string ENVIRONMENT;
            string IS_LISTENER_DEFAULT_VALUE = "FALSE";

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

            void* StartWorker();

            void StartListener();

            void StartLoop();

            void StartLoop(void* &params);

            void StartRedis();

            void Loop();

            void Loop(void* &params);

            void ListenerLoop();

            void WorkerLoop();

            void WorkerLoop(void* &params);
    };
}