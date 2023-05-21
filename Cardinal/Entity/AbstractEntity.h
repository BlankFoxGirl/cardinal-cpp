#include <string>
#include "../Service/ObjectIdentityService.h"
#ifndef ABSTE_H
#define ABSTE_H
using namespace std;

namespace Cardinal {
    namespace Entity {
        class AbstractEntity {
            public:
            AbstractEntity();

            void setPoly(std::string polyValue);

            bool hasPoly();

            bool hasUUID();

            std::string getUUID();

            std::string getPoly();

            private:
                std::string poly = "";
                std::string UUID = "";

                std::string setUUID(std::string UUID);
                std::string generateUUID();
        };
    }
}
#endif