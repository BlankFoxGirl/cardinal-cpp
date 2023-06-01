#include <string>
#include "vendor/crashoz/uuid_v4/uuid_v4.h"
#include "AbstractEntity.h"

using namespace std;
using namespace Cardinal::Entity;


AbstractEntity::AbstractEntity(){
    if (!this->hasUUID()) {
        this->setUUID(
            this->generateUUID()
        );
    }
}

void AbstractEntity::setPoly(std::string polyValue) {
    this->poly = polyValue;
}

bool AbstractEntity::hasPoly() {
    return (this->poly != "");
}

bool AbstractEntity::hasUUID() {
    return (this->UUID != "");
}

void AbstractEntity::overrideUUID(std::string UUID) {
    this->setUUID(UUID);
}

std::string AbstractEntity::getUUID() {
    return this->UUID;
}

std::string AbstractEntity::getPoly() {
    return this->poly;
}

std::string AbstractEntity::setUUID(std::string UUID) {
    this->UUID = UUID;

    return this->getUUID();
}

std::string AbstractEntity::generateUUID() {
    UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
    UUIDv4::UUID uuid = uuidGenerator.getUUID();
    return uuid.str();
}