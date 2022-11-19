#include <string>
#include "../Service/Services.h"

using namespace std;

namespace Cardinal {
    namespace Entity {
        class AbstractEntity {
            public:
            AbstractEntity(){
                if (!this->hasUUID()) {
                    Cardinal::Service::ObjectIdentityService identity;
                    this->setUUID(identity.generateUUID());
                }
            }

            void setPoly(std::string polyValue) {
                this->poly = polyValue;
            }

            bool hasPoly() {
                return (this->poly != "");
            }

            bool hasUUID() {
                return (this->UUID != "");
            }

            std::string getUUID() {
                return this->UUID;
            }

            std::string getPoly() {
                return this->poly;
            }

            private:
            std::string poly = "";
            std::string UUID = "";

            std::string setUUID(std::string UUID) {
                this->UUID = UUID;

                return this->getUUID();
            }
        };
    }
}
