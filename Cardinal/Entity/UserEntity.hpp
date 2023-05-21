#ifndef UE_H
#define UE_H
#include <queue>
#include "AbstractEntity.h"
#include "PlayerEntity.hpp"
// #include "../Service/TCPListenerService.h"

namespace Cardinal::Entity {
    struct UserWriteBufferObject {
        std::string response;
        bool error;
    };

    struct UserReadBufferObject {
        std::string request;
    };

    class UserEntity: public AbstractEntity {
        public:
            UserEntity();
            // UserEntity(Cardinal::Service::req req);
            void Write(std::string response, bool error = false);
            void AddToReadBuffer(std::string response);
            bool hasMessagesToBeSent();
            string Read();
            string GetMessageToSend();
            PlayerEntity GetPlayer();
            PlayerEntity SetPlayer(PlayerEntity player);

        private:
            std::queue<UserWriteBufferObject> writeBuffer;
            std::queue<UserReadBufferObject> readBuffer;
            PlayerEntity player;
            // Cardinal::Service::req req;
    };
}
#endif