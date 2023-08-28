#ifndef CARDINAL_REDIS_MESSAGE_CLIENT_HPP
#define CARDINAL_REDIS_MESSAGE_CLIENT_HPP
#include <string>
#include <memory>
#include "Cardinal/Service/MessageService.hpp"
#include "Cardinal/Service/LogService.hpp"
#include "Cardinal/Global/Queue.hpp"
#include <sw/redis++/redis++.h>
extern sw::redis::Subscriber MessageSubscribers;
namespace Cardinal::Service::Message
{
    class RedisMessageClient : public Cardinal::Service::MessageServiceInterface
    {
    public:
        explicit RedisMessageClient(Cardinal::Service::LogServiceInterface *logService) : logService(logService), subscriber(nullptr){};

        void Dispatch(Cardinal::Entity::Message message);
        void Dispatch(Cardinal::Entity::Message message, std::string queue = Cardinal::Global::Queue::DEFAULT);
        void *SubscribeAndConsume(Cardinal::Service::Queue queue);
        void *Consume(Cardinal::Service::Queue queue);
        void Connect(std::string ConnectUrl);
        void Connect(std::string Hostname, std::string Port, std::string Protocol = "tcp");
        void ConsumeAllLoop();
        void ConsumeAllLoop(void *&subscribers);
        static std::vector<sw::redis::Subscriber *> subscribers;

    private:
        Cardinal::Service::LogServiceInterface *logService;
        void Subscribe(Cardinal::Service::Queue queue);
        // static reference to the message server?
        sw::redis::Redis redis;
        std::unique_ptr<sw::redis::Subscriber> subscriber;
    };
}

#endif