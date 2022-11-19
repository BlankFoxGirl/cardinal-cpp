#include <string>
#include "../vendor/crashoz/uuid_v4/uuid_v4.h"

#ifndef OIS_H
#define OIS_H
using namespace std;

namespace Cardinal {
    namespace Service {
        class ObjectIdentityService {
            public:
            std::string generateUUID();
        };
    }
}
#endif