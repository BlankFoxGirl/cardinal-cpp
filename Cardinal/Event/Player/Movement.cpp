#include "Movement.hpp"
#include "Cardinal/Global/Utility.hpp"
#include "Cardinal/Entity/Message.hpp"
#include "Cardinal/Event/AbstractEvent.hpp"
#include "Cardinal/Service/LogService.hpp"
#include "Cardinal/Service/MessageService.hpp"
#include "Cardinal/Service/MemoryService.hpp"
#include "Cardinal/Component/User/Player.hpp"
#include "Cardinal/Component/EventMap/MemoryEvent.hpp"

using namespace Cardinal::Event::Player;

void Movement::UpdatePlayerLocation(std::string Payload) {
    auto result = Movement::GetPlayerLocation(Payload);
    if (result.size() != Movement::MOVE_PACKET_SIZE) {
        return;
    }

    auto packet = Movement::DecodePlayerLocation(result);

    auto player = Cardinal::Component::User::Player::LoadPlayer(
        packet.connectionUUID,
        this->memoryService_,
        this->logService_
    );

    if (!PlayerCanMoveToLocation(packet)) {
        // Send to player movement failure message.
        SendMovementFailureMessage(packet.connectionUUID);
        return;
    }

    // Update player entity.
    player.SetActorPosition(packet.position);
    player.SetActorRotation(packet.rotation);

    // Save Player in memory service.
    Cardinal::Component::User::Player::SavePlayer(
        player,
        this->memoryService_,
        this->logService_
    );

    // Send to player success response.
    SendMovementSuccessMessage(packet.connectionUUID);
    BroadcastLocationUpdate(packet.connectionUUID, Payload);
}

bool Movement::PlayerCanMoveToLocation(MovementPacket packet) {
    return true; // Default for now. Need to add collision detection logic.
}

void Movement::SendMovementFailureMessage(std::string connectionUUID) {
    this->memoryService_.Add("queue:" + connectionUUID, "PMOVE|0");
}

void Movement::SendMovementSuccessMessage(std::string connectionUUID) {
    this->memoryService_.Add("queue:" + connectionUUID, "PMOVE|1");
}

void Movement::BroadcastLocationUpdate(std::string uuid, std::string Payload) {
    Cardinal::Entity::Message message = Cardinal::Entity::Message("SENDALL", Payload);

    Cardinal::Component::EventMap::MemoryEvent::SendOptimisedMessage(
        uuid,
        message,
        this->memoryService_,
        this->messageService_
    );
}

std::vector<std::string> Movement::GetPlayerLocation(std::string Payload) {
    // Expected payload: "x,y,z,rx,ry,rz,mapId,instanceId,connectionUUID"
    return Cardinal::Global::Utility::Split(Payload, Movement::MOVE_PACKET_DELIMITER);
}

MovementPacket Movement::DecodePlayerLocation(std::vector<std::string> Payload) {
    MovementPacket packet;
    packet.position = Vector3(std::stof(Payload[0]), std::stof(Payload[1]), std::stof(Payload[2]));
    packet.rotation = Quaternion::FromEuler(std::stof(Payload[3]), std::stof(Payload[4]), std::stof(Payload[5]));
    packet.mapId = std::stoi(Payload[6]);
    packet.instanceId = std::stoi(Payload[7]);
    packet.connectionUUID = Payload[8];

    return packet;
}