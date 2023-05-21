#include <string>
#include "../Service/ObjectIdentityService.h"
#include "AbstractEntity.h"

using namespace std;
using namespace Cardinal::Entity;


AbstractEntity::AbstractEntity(){
    if (!this->hasUUID()) {
        this->setUUID(
            Cardinal::Service::ObjectIdentityService::generateUUID()
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