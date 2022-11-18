#include "AbstractEntity.h"
#include <string>
#ifndef REDISENT_H
#define REDISENT_H
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
#endif