#include "Cardinal/Component/User/Player.hpp"
#include <string>

using namespace Cardinal::Global::Physics;
using namespace Cardinal::Entity;
using namespace Cardinal::Service;
using namespace Cardinal::Component::User;

Cardinal::Entity::PlayerEntity Player::LoadPlayer(
    std::string UUID,
    Service::MemoryServiceInterface& memoryService,
    Service::LogServiceInterface& logService
) {
    std::vector<std::pair<std::string, std::string>> playerFromMemory = memoryService.ReadAllHash("session:" + UUID + ":player");

    Cardinal::Entity::PlayerEntity player = Cardinal::Entity::PlayerEntity::FromMemory(playerFromMemory);
    player.overrideUUID(UUID);

    return player;
}

void Player::SavePlayer(
    Cardinal::Entity::PlayerEntity& player,
    Service::MemoryServiceInterface& memoryService,
    Service::LogServiceInterface& logService
) {
    memoryService.WriteAllHash("session:" + player.getUUID() + ":player", player.Serialize());
}
