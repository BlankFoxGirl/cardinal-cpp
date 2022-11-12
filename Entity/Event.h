#include "AbstractEntity.h"
#include <string>
using namespace std;

namespace Cardinal {
    namespace Entity {
        class Event: public AbstractEntity {
            public:
            std::string key = "";
            std::string payload = "";
        };
    }
}