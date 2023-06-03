#ifndef CARDINAL_CORE_H
#define CARDINAL_CORE_H

#include "Exception/Exceptions.h"
#include "Service/LogService.hpp"
#include "Service/MemoryService.hpp"
#include "Service/MessageService.hpp"
#include "Service/CommunicationService.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

namespace Cardinal
{
    class Core
    {
    public:
        explicit Core(
            Cardinal::Service::LogServiceInterface &s,
            Cardinal::Service::MessageServiceInterface &s1,
            Cardinal::Service::MemoryServiceInterface &s2,
            Cardinal::Service::CommunicationServiceInterface &s3) : logService_(s),
                                                                    messageService_(s1),
                                                                    memoryService_(s2),
                                                                    communicationService_(s3)
        // userService_(s4)
        {
            this->Init();
            // Do nothing.
        }

    private:
        void Init();
        Cardinal::Service::LogServiceInterface &logService_;
        Cardinal::Service::MessageServiceInterface &messageService_;
        Cardinal::Service::MemoryServiceInterface &memoryService_;
        Cardinal::Service::CommunicationServiceInterface &communicationService_;

        bool Active = false;
        bool dryRun = false;
        bool is_listener = false;
        string REDIS_HOST;
        string REDIS_PORT;
        string ENVIRONMENT;
        string IS_LISTENER_DEFAULT_VALUE = "TRUE";

        void SetDebugMode();

        void SetVerboseMode();

        void SetLogEnvironment();

        void LoadEnvironmentVariables();

        void LoadEnvironment();

        void LoadRedisConfig();

        void LoadListenerConfig();

        void RegisterListenerCallback();

        void LoadListenerToggle();

        string LoadEnvironmentVariable(string key, string default_value = "");

        void StartWorker();

        void StartListener();

        void StartLoop();

        void StartLoop(void *&params);

        void StartMessageService();

        void StartMemoryService();

        void Loop();

        void Loop(void *&params);

        void ListenerLoop();

        void WorkerLoop();

        void WorkerLoop(void *&params);
    };
}
#endif
