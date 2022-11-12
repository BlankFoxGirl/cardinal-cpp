#include <string>
#include "../vendor/crashoz/uuid_v4/uuid_v4.h"

using namespace std;

namespace Cardinal {
    namespace Service {
        class ObjectIdentityService {
            public:
            std::string generateUUID() {
                UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
                UUIDv4::UUID uuid = uuidGenerator.getUUID();
                return uuid.str();
            }
        };
    }
}
