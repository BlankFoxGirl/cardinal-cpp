#ifndef ABSTE_H
#define ABSTE_H
#include "Cardinal/Entity/Extension/SerializableObject.hpp"
#include <string>
using namespace Cardinal::Entity::Extension;

namespace Cardinal {
    namespace Entity {
        class AbstractEntity: public SerializableObject {
            public:
            AbstractEntity();

            void setPoly(std::string polyValue);

            bool hasPoly();

            bool hasUUID();

            std::string getUUID();

            std::string getPoly();

            void overrideUUID(std::string UUID);

            private:
                std::string poly = "";
                std::string UUID = "";

                std::string setUUID(std::string UUID);
                std::string generateUUID();
        };
    }
}
#endif