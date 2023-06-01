#ifndef CARDINAL_COMPONENT_USER_PLAYER_HPP
#define CARDINAL_COMPONENT_USER_PLAYER_HPP
#include "Cardinal/Entity/PlayerEntity.hpp"
#include "Cardinal/Service/Services.hpp"

#include "Cardinal/Global/Physics.hpp"

namespace Cardinal::Component::User {
    class Player {
        public:
            Player() = default;
            ~Player() = default;
            static Cardinal::Entity::PlayerEntity LoadPlayer(
                std::string UUID,
                Service::MemoryServiceInterface& memoryService,
                Service::LogServiceInterface& logService
            );

            static void SavePlayer(
                Cardinal::Entity::PlayerEntity& player,
                Service::MemoryServiceInterface& memoryService,
                Service::LogServiceInterface& logService
            );
    };
}

#endif