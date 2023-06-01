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

void UserEntity::AddToSendBuffer(std::string response) {
    UserWriteBufferObject sendBufferObject;
    sendBufferObject.response = response;
    this->writeBuffer.push(sendBufferObject);
}

void UserEntity::AddToSendBuffer(std::queue<std::string> messages) {
    while (messages.size() > 0) {
        UserWriteBufferObject sendBufferObject;
        sendBufferObject.response = messages.front();
        this->writeBuffer.push(sendBufferObject);
        messages.pop();
    }
}

bool UserEntity::hasMessagesToBeSent() {
    return this->writeBuffer.empty() == false;
}

std::string UserEntity::GetMessageToSend() {
    if (this->writeBuffer.size() > 0) {
        UserWriteBufferObject writeBufferObject = this->writeBuffer.front();
        this->writeBuffer.pop();
        return writeBufferObject.response;
    }

    return "";
}

std::string UserEntity::Read() {
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