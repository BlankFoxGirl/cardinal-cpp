#include <string>
#include "vendor/mariusbancila/stduuid/include/uuid.h"
#include "AbstractEntity.h"

using namespace std;
using namespace Cardinal::Entity;
using namespace uuids;


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
    uuid const entityUUID = uuids::uuid_system_generator{}();
    return uuids::to_string(entityUUID);
}