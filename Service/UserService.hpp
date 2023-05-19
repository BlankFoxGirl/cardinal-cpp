#ifndef US_H
#define US_H
#include "../Entity/UserEntity.hpp"

namespace Cardinal::Service {
    class UserServiceInterface {
        public:
            ~UserServiceInterface() = default;
            virtual Cardinal::Entity::UserEntity SetUser(Cardinal::Entity::UserEntity User) = 0;
            virtual Cardinal::Entity::UserEntity GetUser() = 0;
    };

    class UserService: public UserServiceInterface {
        public:
            UserService();
            Cardinal::Entity::UserEntity SetUser(Cardinal::Entity::UserEntity User);
            Cardinal::Entity::UserEntity GetUser();
        private:
            Cardinal::Entity::UserEntity User;
    };
}
#endif