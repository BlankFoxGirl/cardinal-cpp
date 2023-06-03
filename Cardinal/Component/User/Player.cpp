#include "Cardinal/Component/User/Player.hpp"
#include <string>
#include <vector>

using namespace Cardinal::Global::Physics;
using namespace Cardinal::Entity;
using namespace Cardinal::Service;
using namespace Cardinal::Component::User;

Cardinal::Entity::PlayerEntity Player::LoadPlayer(
    std::string UUID,
    Service::MemoryServiceInterface &memoryService,
    Service::LogServiceInterface &logService)
{
    std::vector<std::pair<std::string, std::string>> playerFromMemory = memoryService.ReadAllHash("session:" + UUID + ":player");

    Cardinal::Entity::PlayerEntity player = Cardinal::Entity::PlayerEntity::FromMemory(playerFromMemory);
    player.overrideUUID(UUID);

    return player;
}

void Player::SavePlayer(
    Cardinal::Entity::PlayerEntity &player,
    Service::MemoryServiceInterface &memoryService,
    Service::LogServiceInterface &logService)
{
    memoryService.WriteAllHash("session:" + player.getUUID() + ":player", player.Serialize());
}

std::vector<Cardinal::Entity::PlayerEntity> Player::LoadPlayers(
    int mapId,
    int instanceId,
    Service::MemoryServiceInterface &memoryService,
    Service::LogServiceInterface &logService)
{
    vector<Cardinal::Entity::PlayerEntity> players;
    // Get the list of all connectionIds in the instance:<mapId>:<instanceId> set.
    // std::vector<std::string> connectionIds = memoryService.ReadAllSet("instance:" + std::to_string(mapId) + ":" + std::to_string(instanceId));
    // Load each player from the session:<connectionId>:player hash.
    // Return with the vector collection of each player.

    return players;
}