#include "AbstractEntity.h"
#include "PlayerEntity.hpp"

using Cardinal::Entity::PlayerEntity;
PlayerEntity::PlayerEntity() {
    this->actor.name = "Player";
    this->actor.position = Vector3();
    this->actor.rotation = Quaternion();
}

string PlayerEntity::GetActorName() {
    return this->actor.name;
}

string PlayerEntity::SetActorName(string name) {
    this->actor.name = name;
    return this->actor.name;
}

Cardinal::Entity::PlayerActor PlayerEntity::GetActor() {
    return this->actor;
}

Cardinal::Entity::Vector3 PlayerEntity::GetActorPosition() {
    return actor.position;
}

Cardinal::Entity::Vector3 PlayerEntity::SetActorPosition(Vector3 position) {
    actor.position = position;
    return actor.position;
}

Cardinal::Entity::Quaternion PlayerEntity::GetActorRotation() {
    return actor.rotation;
}

Cardinal::Entity::Quaternion PlayerEntity::SetActorRotation(Quaternion rotation) {
    actor.rotation = rotation;
    return actor.rotation;
}
