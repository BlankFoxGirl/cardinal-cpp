
#include "Exception/Exceptions.h"
#include "Service/LogService.hpp"
#include "Core.hpp"
// #include "Service/MemoryService.hpp"
#include "Component/Message/Receive.hpp"
#include "Component/EventMap/EventMap.hpp"
#include "Component/Connection/EndUserClientConnection.hpp"

#include "Global/Queue.hpp"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace Cardinal;

void Core::Init()
{
    this->SetVerboseMode();
    this->LoadEnvironment();
    this->SetLogEnvironment();
    this->logService_.Info("Starting Cardinal Core");
    this->LoadEnvironmentVariables();
    this->StartMessageService();
    this->StartMemoryService();

    if (this->is_listener)
    {
        this->StartListener();
        this->StartLoop();
        return;
    }
    else
    {
        this->StartWorker();
    }

    this->StartLoop();
}

void Core::SetDebugMode()
{
    this->logService_.Info("Setting debug mode...");
    this->logService_.SetMinimumLogLevel(Cardinal::Service::LOG_LEVEL::Debug);
    this->logService_.Debug("Debug mode enabled.");
}

void Core::SetVerboseMode()
{
    this->logService_.Info("Setting verbose mode...");
    this->logService_.SetMinimumLogLevel(Cardinal::Service::LOG_LEVEL::Verbose);
    this->logService_.Verbose("Verbose mode enabled.");
}

void Core::SetLogEnvironment()
{
    this->logService_.Debug("Setting log environment...");
    this->logService_.SetEnvironment(this->ENVIRONMENT);
    this->logService_.Verbose("Log environment set to", this->ENVIRONMENT);
}

void Core::LoadEnvironmentVariables()
{
    this->logService_.Verbose("Running LoadEnvironmentVariables");
    this->LoadListenerToggle();
    this->LoadRedisConfig();
}

void Core::LoadEnvironment()
{
    this->logService_.Verbose("Running LoadEnvironment");
    this->logService_.Debug("Loading environment...");
    this->ENVIRONMENT = this->LoadEnvironmentVariable("ENVIRONMENT", "local");
    this->logService_.Debug("Environment set to", this->ENVIRONMENT);
}

void Core::LoadRedisConfig()
{
    this->logService_.Verbose("[Called] LoadRedisConfig");
    this->logService_.Debug("Loading Redis config...");
    this->REDIS_HOST = this->LoadEnvironmentVariable("REDIS_HOST", "localhost");
    this->REDIS_PORT = this->LoadEnvironmentVariable("REDIS_PORT", "6379");
    this->logService_.Verbose("[Closed] LoadRedisConfig");
}

void Core::LoadListenerConfig()
{
    this->logService_.Verbose("[Called] LoadListenerConfig");
    this->logService_.Debug("Loading listener config...");
    string port = this->LoadEnvironmentVariable("PORT", "7777");
    string bindIp = this->LoadEnvironmentVariable("BIND_IP", "0.0.0.0");
    this->communicationService_.Bind(port, bindIp);
    this->RegisterListenerCallback();
    this->logService_.Debug("Listener config loaded!");
    this->logService_.Verbose("[Closed] LoadListenerConfig");
}

void Core::RegisterListenerCallback()
{
    this->logService_.Verbose("[Called] RegisterListenerCallback");
    this->logService_.Debug("Registering listener callback...");
    this->communicationService_.RegisterCallback("OnConnection", [this](void *args)
                                                 {
        this->logService_.Verbose("[Called] OnConnection Callback");

        Cardinal::Component::Connection::EndUserClientConnection userConnection(
            this->logService_,
            this->communicationService_,
            this->messageService_,
            this->memoryService_
        );

        userConnection.AcceptConnection(args);
        this->logService_.Verbose("[Closed] OnConnection Callback"); });

    this->logService_.Debug("Listener callback registered!");
    this->logService_.Verbose("[Closed] RegisterListenerCallback");
}

void Core::LoadListenerToggle()
{
    this->logService_.Verbose("Running LoadListenerToggle");
    this->logService_.Debug("Loading listener toggle...");
    std::string is_listener = this->LoadEnvironmentVariable("IS_LISTENER", this->IS_LISTENER_DEFAULT_VALUE);

    this->is_listener = is_listener.compare("TRUE") == 0;
    this->logService_.Debug("this->is_listener set to", (this->is_listener ? "true" : "false"));
}

string Core::LoadEnvironmentVariable(string key, string default_value)
{
    this->logService_.Verbose("Running LoadEnvironmentVariable with Params", key + ", " + default_value);
    this->logService_.Debug("Loading environment variable", key);
    string value = default_value;

    try
    {
        this->logService_.Verbose("Attempting to load environment variable", key);
        value = std::getenv(key.c_str()) ? std::getenv(key.c_str()) : default_value;
        this->logService_.Verbose("Loaded environment variable", key);
    }
    catch (std::exception &e)
    {
        this->logService_.Verbose("Could not load environment variable", key);
        this->logService_.Error("Error occurred when attempting to load environment variable " + key, e.what());
    }

    this->logService_.Info(key, "set to " + value);
    return value;
}

// Only supports 1 worker per channel presently. This will likely need to change.
void Core::StartWorker()
{
    this->logService_.Verbose("Called StartWorker");
    this->logService_.Info("Initiating Worker");

    Cardinal::Service::Queue q;
    q.Name = LoadEnvironmentVariable("QUEUE", Cardinal::Global::Queue::DEFAULT);
    this->logService_.Debug("Subscribing to Redis channel ", q.Name);

    q.Callback = [this](std::string raw)
    {
        this->logService_.Verbose("[Called] WorkerCallback");
        this->logService_.Debug("--Received raw message", raw);

        if (raw.empty())
        {
            this->logService_.Debug("--Raw message is empty, exiting callback");
            this->logService_.Verbose("[Closed] WorkerCallback");
            return;
        }

        try
        {
            Cardinal::Entity::Message message = Cardinal::Entity::Message(raw);
            this->logService_.Debug("--Received message", message.getPayload());
            this->logService_.Verbose("--Instantiating Message Component...");
            auto r = Cardinal::Component::Message::Receive(this->logService_, this->messageService_, this->memoryService_);
            this->logService_.Verbose("--Message component instantiated successfully!");
            this->logService_.Verbose("--Call Message Component Invoker with", message.getUUID() + ": " + message.getKey() + "->" + message.getPayload());
            r(message); // Invoke the message component with the received message.
        }
        catch (Cardinal::Exception::InvalidMessage &e)
        {
            this->logService_.Error("Invalid message received", e.what());
        }
        catch (std::exception &e)
        {
            this->logService_.Error("Error occurred when attempting to process message in worker.", e.what());
        }

        this->logService_.Verbose("[Closed] WorkerCallback");
    };

    this->messageService_.SubscribeAndConsume(q);
    this->logService_.Debug("Subscribed to channel", q.Name);
}

void Core::StartListener()
{
    this->logService_.Verbose("Called StartListener");
    this->logService_.Info("Initiating Communication Service Listener");
    this->LoadListenerConfig();
    this->logService_.Info("Starting Communication Service...");
    this->communicationService_.Start();
    this->logService_.Info("Communication Service started!");
}

void Core::StartLoop()
{
    this->logService_.Verbose("Called StartLoop");
    this->Active = true;
    if (this->dryRun)
    {
        this->logService_.Warning("Dry run enabled. Exiting.");
        this->logService_.Verbose("Exiting in StartLoap due to DryRun");
        exit(0);
    }

    while (this->Active && !this->dryRun)
    {
        usleep(1);
        this->Loop();
    }
}

void Core::StartLoop(void *&params)
{
    this->logService_.Verbose("Called StartLoop with Params");
    this->Active = true;
    if (this->dryRun)
    {
        this->logService_.Warning("Dry run enabled. Exiting.");
        this->logService_.Verbose("Exiting in StartLoap due to DryRun");
        exit(0);
    }

    this->logService_.Verbose("StartLoop is calling Loop");
    while (this->Active && !this->dryRun)
    {
        usleep(1);
        this->Loop(params);
    }

    this->logService_.Verbose("StartLoop Closed Loop");
}

void Core::StartMessageService()
{
    this->logService_.Verbose("[Called] StartMessageService");
    this->logService_.Info("Starting Message Service...");
    this->messageService_.Connect(this->REDIS_HOST, this->REDIS_PORT);
    this->logService_.Info("Message Service started!");
    this->logService_.Verbose("[Closed] StartMessageService");
}

void Core::StartMemoryService()
{
    this->logService_.Verbose("[Called] StartMemoryService");
    this->logService_.Info("Starting Memory Service...");
    this->memoryService_.Connect(this->REDIS_HOST, this->REDIS_PORT);
    this->logService_.Info("Memory Service started!");
    this->logService_.Verbose("[Closed] StartMemoryService");
}

void Core::Loop()
{
    if (this->is_listener)
    {
        this->ListenerLoop();
    }
    else
    {
        this->WorkerLoop();
    }
}

void Core::Loop(void *&params)
{
    this->logService_.Verbose("Called Loop with Params");
    if (this->is_listener)
    {
        this->ListenerLoop();
    }
    else
    {
        this->logService_.Verbose("Loop is calling WorkerLoop with Params");
        this->WorkerLoop(params);
    }
}

void Core::ListenerLoop()
{
    this->communicationService_.Accept();
}

void Core::WorkerLoop()
{
    this->messageService_.ConsumeAllLoop();
}

void Core::WorkerLoop(void *&params)
{
    this->logService_.Verbose("Called WorkerLoop with Params");
    this->logService_.Verbose("Calling ConsumeAllLoop on Message Service with Params");
    this->messageService_.ConsumeAllLoop(params);
    this->logService_.Verbose("WorkerLoop Closed ConsumeAllLoop");
}