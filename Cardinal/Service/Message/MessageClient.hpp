#ifndef CARDINAL_MESSAGECLIENT_H
#define CARDINAL_MESSAGECLIENT_H
#include <string>
#include "../MessageService.hpp"

namespace Cardinal::Service::Message {
    class MessageClient: public MessageServiceInterface {
        public:
            MessageClient ();

            void Dispatch(Cardinal::Entity::Message message);
            void Consume(Cardinal::Service::Queue queue);
        // private:
            // static reference to the message server?
    };
}

#endif