#ifndef US_H
#define US_H
#include <map>
#include "../Entity/UserEntity.hpp"
#include "RedisClient.h"
#include "LogService.h"

namespace Cardinal::Service {
    class UserServiceInterface {
        public:
            ~UserServiceInterface() = default;
            // virtual void RegisterConnection(Cardinal::Service::req rec) = 0;
            virtual Cardinal::Entity::UserEntity RegisterConnection() = 0;
            virtual void DestroyConnection(std::string userUUID) = 0;
            virtual void SendToUser(string userUUID, string message) = 0;
    };

    class UserService: public UserServiceInterface {
        public:
            explicit UserService(Cardinal::Service::CacheClientInterface& s, Cardinal::Service::LogServiceInterface& s1): redisService_(s), logService_(s1) {};
            // void RegisterConnection(Cardinal::Service::req rec);
            Cardinal::Entity::UserEntity RegisterConnection();
            void DestroyConnection(std::string userUUID);
            void SendToUser(string userUUID, string message);
        private:
            Cardinal::Service::CacheClientInterface& redisService_;
            Cardinal::Service::LogServiceInterface& logService_;
            std::map<std::string, std::reference_wrapper<Cardinal::Entity::UserEntity>> Users;
            Subscriber Subscribe(string userUUID);
            Subscriber* subscribers;
    };
}
#endif