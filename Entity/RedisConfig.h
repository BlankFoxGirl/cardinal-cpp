#include "AbstractEntity.h"
#include <string>
using namespace std;

namespace Cardinal {
    namespace Entity {
        class RedisConfig: public AbstractEntity {
            public:
            std::string EndPoints = "";
            std::string ChannelPrefix = "";
        };
    }
}