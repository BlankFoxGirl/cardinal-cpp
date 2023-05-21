#ifndef CARDINAL_SERVICE_MESSAGESERVICE_H
#define CARDINAL_SERVICE_MESSAGESERVICE_H

#include "../Entity/Message.hpp"

namespace Cardinal::Service {
    struct Queue {
        std::string Name;
        std::function <void(Cardinal::Entity::Message)> Callback;
    };

    class MessageServiceInterface {
    public:
        virtual ~MessageServiceInterface() noexcept = default;

        virtual void Dispatch(Cardinal::Entity::Message message) = 0;
        virtual void Consume(Queue queue) = 0;
        virtual void Connect(std::string ConnectUrl) = 0;
    };
}
#endif