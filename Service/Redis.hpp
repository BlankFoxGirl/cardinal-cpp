#include <sw/redis++/redis++.h>
#include <string>

#ifndef AR_H
#define AR_H
using namespace std;
using namespace sw::redis;

namespace Cardinal::Service {
    class AbstractRedis: public Redis {
        public:
            AbstractRedis() = default;
            explicit AbstractRedis(const std::string &uri) : Redis(uri) {};

        private:
            ConnectionOptions c;
    };
}
#endif