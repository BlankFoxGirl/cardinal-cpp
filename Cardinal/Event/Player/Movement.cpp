#include "Movement.hpp"
#include "Cardinal/Global/Utility.hpp"
#include "Cardinal/Entity/Message.hpp"
#include "Cardinal/Event/AbstractEvent.hpp"
#include "Cardinal/Service/LogService.hpp"
#include "Cardinal/Service/MessageService.hpp"
#include "Cardinal/Service/MemoryService.hpp"
#include "Cardinal/Component/User/Player.hpp"
#include "Cardinal/Component/EventMap/MemoryEvent.hpp"
#include <bits/stdc++.h>

using namespace Cardinal::Event::Player;

void Movement::UpdatePlayerLocation(std::string Payload) {
    this->logService_.Verbose("[Called] Movement::UpdatePlayerLocation", Payload);

    this->logService_.Verbose("--Movement::UpdatePlayerLocation Splitting payload.");
    auto result = Movement::GetPlayerLocation(Payload.substr(6, Payload.size()));
    this->logService_.Verbose("--Movement::UpdatePlayerLocation Splitted payload successfully!");

    if (result.size() != Movement::MOVE_PACKET_SIZE) {
        this->logService_.Verbose("--Movement::UpdatePlayerLocation Invalid payload size.");
        return;
    }

    this->logService_.Verbose("--Movement::UpdatePlayerLocation Decoding payload.");
    auto packet = Movement::DecodePlayerLocation(result);
    this->logService_.Verbose("--Movement::UpdatePlayerLocation Decoded payload successfully!");


    this->logService_.Verbose("--Movement::UpdatePlayerLocation Loading player.");
    auto player = Cardinal::Component::User::Player::LoadPlayer(
        packet.connectionUUID,
        this->memoryService_,
        this->logService_
    );
    this->logService_.Verbose("--Movement::UpdatePlayerLocation Loaded player successfully!");

    if (!PlayerCanMoveToLocation(packet)) {
        this->logService_.Verbose("--Movement::UpdatePlayerLocation Player cannot move to location.");
        // Send to player movement failure message.
        SendMovementFailureMessage(packet.connectionUUID);
        return;
    }

    this->logService_.Verbose("--Movement::UpdatePlayerLocation Update player position and rotation.");
    // Update player entity.
    player.SetActorPosition(packet.position);
    player.SetActorRotation(packet.rotation);

    this->logService_.Verbose("--Movement::UpdatePlayerLocation Save player.");
    // Save Player in memory service.
    Cardinal::Component::User::Player::SavePlayer(
        player,
        this->memoryService_,
        this->logService_
    );
    this->logService_.Verbose("--Movement::UpdatePlayerLocation Saved player successfully!");

    // Send to player success response.
    SendMovementSuccessMessage(packet.connectionUUID);
    BroadcastLocationUpdate(packet.connectionUUID, Payload);
    this->logService_.Verbose("[Closed] Movement::UpdatePlayerLocation");
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
    this->logService_.Verbose("[Called] Movement::GetPlayerLocation", Payload);
    // Expected payload: "x,y,z,rx,ry,rz,mapId,instanceId,connectionUUID"
    return Cardinal::Global::Utility::Split(Payload, Movement::MOVE_PACKET_DELIMITER);
}

MovementPacket Movement::DecodePlayerLocation(std::vector<std::string> Payload) {
    this->logService_.Verbose("[Called] Movement::DecodePlayerLocation");

    MovementPacket packet;
    this->logService_.Verbose("--Movement::DecodePlayerLocation Decoding location.");

    this->logService_.Verbose("--Movement::DecodePlayerLocation Decoding X", Payload[0]);
    float x = std::stof(Payload[0]);
    this->logService_.Verbose("--Movement::DecodePlayerLocation Decoded X", std::to_string(x));

    this->logService_.Verbose("--Movement::DecodePlayerLocation Decoding Y", Payload[1]);
    float y = std::stof(Payload[1]);
    this->logService_.Verbose("--Movement::DecodePlayerLocation Decoded Y", std::to_string(y));

    this->logService_.Verbose("--Movement::DecodePlayerLocation Decoding Z", Payload[2]);
    float z = std::stof(Payload[2]);
    this->logService_.Verbose("--Movement::DecodePlayerLocation Decoded Z", std::to_string(z));

    packet.position = Vector3(x, y, z);

    this->logService_.Verbose("--Movement::DecodePlayerLocation Decoding rotation.");
    packet.rotation = Quaternion::FromEuler(std::stof(Payload[3]), std::stof(Payload[4]), std::stof(Payload[5]));

    this->logService_.Verbose("--Movement::DecodePlayerLocation Decoding mapId, instanceId, and connectionUUID.");
    packet.mapId = std::stoi(Payload[6]);
    packet.instanceId = std::stoi(Payload[7]);
    packet.connectionUUID = Payload[8];

    this->logService_.Verbose("[Closed] Movement::DecodePlayerLocation");
    return packet;
}