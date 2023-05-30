#ifndef UE_H
#define UE_H
#include <queue>
#include "AbstractEntity.h"
#include "PlayerEntity.hpp"

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
            void Write(std::string response, bool error = false);
            void AddToSendBuffer(std::string response);
            void AddToSendBuffer(std::queue<std::string> messages);
            bool hasMessagesToBeSent();
            string Read();
            string GetMessageToSend();
            PlayerEntity GetPlayer();
            PlayerEntity SetPlayer(PlayerEntity player);

        private:
            std::queue<UserWriteBufferObject> writeBuffer;
            std::queue<UserReadBufferObject> readBuffer;
            PlayerEntity player;
    };
}
#endif