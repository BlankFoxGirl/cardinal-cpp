#include "Cardinal/Entity/AbstractEntity.h"
#include "Cardinal/Entity/PlayerEntity.hpp"
#include "Cardinal/Global/Physics.hpp"

using Cardinal::Entity::PlayerEntity;
PlayerEntity::PlayerEntity() {
    this->actor.name = "Player";
    this->actor.position = Cardinal::Global::Physics::Vector3();
    this->actor.rotation = Cardinal::Global::Physics::Quaternion();
}

std::string PlayerEntity::GetActorName() {
    return this->actor.name;
}

std::string PlayerEntity::SetActorName(std::string name) {
    this->actor.name = name;
    return this->actor.name;
}

Cardinal::Entity::PlayerActor PlayerEntity::GetActor() {
    return this->actor;
}

Cardinal::Global::Physics::Vector3 PlayerEntity::GetActorPosition() {
    return actor.position;
}

Cardinal::Global::Physics::Vector3 PlayerEntity::SetActorPosition(Cardinal::Global::Physics::Vector3 position) {
    actor.position = position;
    return actor.position;
}

Cardinal::Global::Physics::Quaternion PlayerEntity::GetActorRotation() {
    return actor.rotation;
}

Cardinal::Global::Physics::Quaternion PlayerEntity::SetActorRotation(Cardinal::Global::Physics::Quaternion rotation) {
    actor.rotation = rotation;
    return actor.rotation;
}
