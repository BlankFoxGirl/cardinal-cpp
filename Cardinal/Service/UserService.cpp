#include "UserService.hpp"
#include <map>
#include "../Entity/UserEntity.hpp"
#include "../Entity/Message.hpp"

using Cardinal::Service::UserService;

// void UserService::RegisterConnection(Cardinal::Service::req req) {
//     auto user = Cardinal::Entity::UserEntity();
//     user.getUUID();
//     this->Users.insert(std::pair<std::string, Cardinal::Entity::UserEntity>(user.getUUID(), user));
// }

Cardinal::Entity::UserEntity UserService::RegisterConnection() {
    this->logService_.Verbose("Called UserService::RegisterConnection");
    auto user = Cardinal::Entity::UserEntity();
    this->Users.insert(std::pair<std::string, std::reference_wrapper<Cardinal::Entity::UserEntity>>(user.getUUID(), std::ref(user)));
    this->Subscribe(user.getUUID());
    return user;
}

void UserService::DestroyConnection(std::string userUUID) {
    this->logService_.Verbose("Called UserService::DestroyConnection", userUUID);
    this->Users.erase(userUUID);
}

Subscriber UserService::Subscribe(string userUUID) {
    this->logService_.Verbose("Called UserService::Subscribe");
    auto subscriber = this->redisService_.GetSubscriber();
    subscriber.subscribe(userUUID);
    subscriber.on_message([this](std::string channel, std::string message) {
        this->logService_.Verbose("Called UserService::Subscribe::on_message");
        this->logService_.Debug("User " + channel + " received", message);
        this->SendToUser(channel, message);
        this->logService_.Verbose("UserService::Subscribe::on_message completed.");
    });
    this->logService_.Verbose("User subscribed to channel: " + userUUID);
    this->logService_.Verbose("UserService::Subscribe Completed.");

    // this->redisService_.Consume();

    return subscriber;
}

void UserService::SendToUser(string userUUID, string message) {
    this->logService_.Verbose("Called UserService::SendToUser", userUUID + " " + message);
    this->Users.find(userUUID)->second.get().Write(message);
    this->logService_.Verbose("Called UserService::SendToUser written to user");
}
