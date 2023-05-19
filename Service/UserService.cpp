#include "UserService.hpp"
#include "../Entity/UserEntity.hpp"

using Cardinal::Service::UserService;

UserService::UserService() {};

Cardinal::Entity::UserEntity UserService::SetUser(Cardinal::Entity::UserEntity User) {
    this->User = User;
    return this->User;
}

Cardinal::Entity::UserEntity UserService::GetUser() {
    return this->User;
}
