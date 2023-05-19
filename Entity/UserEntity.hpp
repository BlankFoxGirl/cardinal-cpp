#ifndef UE_H
#define UE_H
#include "AbstractEntity.h"
#include "PlayerEntity.hpp"
#include <queue>

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
            string Read();
            PlayerEntity GetPlayer();
            PlayerEntity SetPlayer(PlayerEntity player);

        private:
            std::queue<UserWriteBufferObject> writeBuffer;
            std::queue<UserReadBufferObject> readBuffer;
            PlayerEntity player;
    };
}
#endif