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

            EventEntity(std::vector<std::pair<std::string, std::string>> serializedEvent) {
                this->EventName = serializedEvent[0].second;
                this->Payload = serializedEvent[1].second;
                this->Origin = serializedEvent[2].second;
                this->Locked = serializedEvent[3].second;
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

            std::string ToString() {
                return this->EventName + "|" + this->Payload + "," + this->Origin;
            }

            std::string GetKey() {
                return this->key;
            }

            std::string GetQueue(std::string UUID) {
                return this->GetKey() + UUID;
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