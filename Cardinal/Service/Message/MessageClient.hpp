#ifndef CARDINAL_MESSAGECLIENT_H
#define CARDINAL_MESSAGECLIENT_H
#include <string>
#include "../MessageService.hpp"
#include <sw/redis++/redis++.h>
#include "../Memory/Redis.hpp"

namespace Cardinal::Service::Message {
    class MessageClient: public Cardinal::Service::MessageServiceInterface {
        public:
            MessageClient ();

            void Dispatch(Cardinal::Entity::Message message);
            void Consume(Cardinal::Service::Queue queue);
            void Connect(std::string ConnectUrl);
        private:
            // static reference to the message server?
            static sw::redis::Redis redis;
            static sw::redis::Subscriber subscriber;
    };
}

#endif