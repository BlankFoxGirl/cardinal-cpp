#include "AbstractEntity.h"
#include "PlayerEntity.hpp"
#include "UserEntity.hpp"
// #include "../Service/TCPListenerService.h"

using Cardinal::Entity::UserEntity;
Cardinal::Entity::UserEntity::UserEntity() {
    this->player = PlayerEntity();
}

// Cardinal::Entity::UserEntity::UserEntity(Cardinal::Service::req req) {
//     this->req = req;
//     this->player = PlayerEntity();
// }

void UserEntity::Write(std::string response, bool error) {
    UserWriteBufferObject writeBufferObject;
    writeBufferObject.response = response;
    writeBufferObject.error = error;
    this->writeBuffer.push(writeBufferObject);
}

void UserEntity::AddToReadBuffer(std::string response) {
    UserReadBufferObject readBufferObject;
    readBufferObject.request = response;
    this->readBuffer.push(readBufferObject);
}

bool UserEntity::hasMessagesToBeSent() {
    return this->writeBuffer.empty() == false;
}

string UserEntity::GetMessageToSend() {
    if (this->writeBuffer.size() > 0) {
        UserWriteBufferObject writeBufferObject = this->writeBuffer.front();
        this->writeBuffer.pop();
        return writeBufferObject.response;
    }

    return "";
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