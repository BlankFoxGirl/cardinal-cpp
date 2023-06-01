#ifndef CARDINAL_ENTITY_EVENTENTITY_HPP
#define CARDINAL_ENTITY_EVENTENTITY_HPP
#include "Cardinal/Entity/AbstractEntity.h"
#include <string>
#include <vector>

namespace Cardinal::Entity {
    class EventEntity : public AbstractEntity {
        public:
            EventEntity(std::string EventName, std::string Payload, std::string Origin, std::string Locked) {
                this->EventName = EventName;
                this->Payload = Payload;
                this->Origin = Origin;
                this->Locked = Locked;
            }

            ~EventEntity() = default;

            std::vector<std::pair<std::string, std::string>> Serialize() override {
                std::vector<std::pair<std::string, std::string>> serializedEvent;
                serializedEvent.push_back(std::make_pair("EventName", this->EventName));
                serializedEvent.push_back(std::make_pair("Payload", this->Payload));
                serializedEvent.push_back(std::make_pair("Origin", this->Origin));
                serializedEvent.push_back(std::make_pair("Locked", this->Locked));

                return serializedEvent;
            }

            std::string GetKey() {
                return this->key;
            }

            std::string GetQueue(std::string UUID) {
                return "event:" + UUID;
            }

        private:
            std::string key = "event:";
            std::string EventName;
            std::string Payload;
            std::string Origin;
            std::string Locked;
    };
}
#endif