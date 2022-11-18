#include <string>
#include "../vendor/crashoz/uuid_v4/uuid_v4.h"
#include "ObjectIdentityService.h"

using namespace std;
using namespace Cardinal::Service;

std::string ObjectIdentityService::generateUUID() {
    UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
    UUIDv4::UUID uuid = uuidGenerator.getUUID();
    return uuid.str();
}
