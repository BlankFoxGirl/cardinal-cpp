#include "AbstractEntity.h"
#include "PlayerEntity.hpp"
#include "UserEntity.hpp"

using Cardinal::Entity::UserEntity;
Cardinal::Entity::UserEntity::UserEntity() {
    this->player = PlayerEntity();
}

void UserEntity::Write(std::string response, bool error) {
    UserWriteBufferObject writeBufferObject;
    writeBufferObject.response = response;
    writeBufferObject.error = error;
    this->writeBuffer.push(writeBufferObject);
}

string UserEntity::Read() {
    if (this->readBuffer.size() > 0) {
        UserReadBufferObject readBufferObject = this->readBuffer.front();
        this->readBuffer.pop();
        return readBufferObject.request;
    }

    return "";
}

Cardinal::Entity::PlayerEntity UserEntity::GetPlayer() {
    return this->player;
}

Cardinal::Entity::PlayerEntity UserEntity::SetPlayer(PlayerEntity player) {
    this->player = player;
    return this->player;
}