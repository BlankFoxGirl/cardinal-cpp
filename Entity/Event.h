#include "AbstractEntity.h"
#include <string>
#ifndef EVENTENT_H
#define EVENTENT_H
using namespace std;

namespace Cardinal::Entity {
    class Event: public AbstractEntity {
        public:
        std::string key = "";
        std::string payload = "";
    };
}
#endif