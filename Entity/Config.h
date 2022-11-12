#include "AbstractEntity.h"
#include <string>
using namespace std;

namespace Cardinal {
    namespace Entity {
        class Config: public AbstractEntity {
            public:
            Config() {
                this->IS_LISTENER = true;
            }

            int PORT = 0;
            int REDIS_PORT = 0;
            std::string REDIS_HOST = "";
            std::string IP_ADDRESS = "";
            std::string IDENTIFIER = "";
            std::string QUEUE = "";
            bool IS_LISTENER = false;
        };
    }
}