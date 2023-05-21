#include "AbstractEntity.h"
#include <string>
#ifndef EVENTENT_H
#define EVENTENT_H
using namespace std;

namespace Cardinal::Entity {
    class Event: public AbstractEntity {
        public:
            Event(string key, string payload) {
                this->key = key;
                this->payload = payload;
            }

            std::string key = "";
            std::string payload = "";
    };
}
#endif