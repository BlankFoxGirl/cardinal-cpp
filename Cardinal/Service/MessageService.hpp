#ifndef CARDINAL_SERVICE_MESSAGESERVICE_H
#define CARDINAL_SERVICE_MESSAGESERVICE_H
#include <functional>
#include "Cardinal/Entity/Message.hpp"

namespace Cardinal::Service {
    struct Queue {
        std::string Name;
        std::function <void(std::string)> Callback;
    };

    class MessageServiceInterface {
    public:
        virtual ~MessageServiceInterface() noexcept = default;

        /// @brief Dispatch a Cardinal::Entity::Message to the upstream message service.
        /// @param message The Cardinal::Entity::Message to dispatch.
        virtual void Dispatch(Cardinal::Entity::Message message) = 0;

        /// @brief Subscribe to a queue and consume messages.
        /// @param queue The queue to subscribe to.
        virtual void* SubscribeAndConsume(Queue queue) = 0;

        /// @brief Consume messages from a queue.
        /// @param queue The queue to consume from.
        virtual void* Consume(Queue queue) = 0;

        /// @brief Connect to the upstream message service.
        /// @param ConnectUrl The URL to connect to.
        virtual void Connect(std::string ConnectUrl) = 0;

        /// @brief Connect to the upstream message service.
        /// @param Hostname The hostname to connect to.
        /// @param Port The port to connect to.
        /// @param Protocol The protocol to use (Default TCP).
        virtual void Connect(std::string Hostname, std::string Port, std::string Protocol = "tcp") = 0;

        /// @brief Consume messages from all subscribed queues. Use within a loop.
        virtual void ConsumeAllLoop() = 0;

        /// @brief Consume messages from all subscribed queues. Use within a loop.
        virtual void ConsumeAllLoop(void* &params) = 0;
    };
}
#endif