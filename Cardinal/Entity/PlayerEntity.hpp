#ifndef PE_H
#define PE_H
#include "AbstractEntity.h"
#include <queue>
#include "Cardinal/Global/Physics.hpp"

using namespace Cardinal::Global::Physics;

namespace Cardinal::Entity {
    struct PlayerActor {
        std::string name;
        Vector3 position;
        Quaternion rotation;
        int mapId;
        int instanceId;
        bool inGame;
    };

    //  ToDo: Extract into seperate entity for items.
    enum ItemRarety {
        Common,
        Uncommon,
        Rare,
        Epic,
        Legendary,
        Mythic
    };

    struct InventoryItem {
        int id;
        std::string name;
        ItemRarety rarety;
        int amount;
    };

    class PlayerEntity: public AbstractEntity {
        public:
            PlayerEntity();

            std::string GetActorName();
            std::string SetActorName(std::string name);
            void SetActorInGame(bool inGame);
            Vector3 GetActorPosition();
            Vector3 SetActorPosition(Vector3 position);
            Quaternion GetActorRotation();
            Quaternion SetActorRotation(Quaternion rotation);
            PlayerActor GetActor();

            std::vector<std::pair<std::string, std::string>> Serialize() override {
                std::vector<std::pair<std::string, std::string>> serializedPlayer;
                serializedPlayer.push_back(std::make_pair("name", this->actor.name));

                serializedPlayer.push_back(
                    std::make_pair(
                        "position",
                        this->actor.position.ToString()
                    )
                );

                serializedPlayer.push_back(
                    std::make_pair(
                        "rotation",
                        this->actor.rotation.ToEulerString()
                    )
                );

                return serializedPlayer;
            }

            static PlayerEntity FromMemory(std::vector<std::pair<std::string, std::string>> serializedPlayer) {
                PlayerEntity player;
                std::vector<std::pair<std::string, std::string>>::iterator iter = serializedPlayer.begin();
                for ( ; iter < serializedPlayer.end(); iter++) {
                    std::pair<std::string, std::string> row = *iter;
                    std::string key = row.first;
                    std::string value = row.second;

                    if (key.compare("name") == 0) {
                        player.SetActorName(value);
                    } else if (key.compare("inGame") == 0) {
                        player.SetActorInGame(value.compare("true") == 0);
                    } else if (key.compare("position") == 0) {
                        player.SetActorPosition(Vector3::FromString(value));
                    } else if (key.compare("rotation") == 0) {
                        player.SetActorRotation(Quaternion::FromEulerString(value));
                    }
                }

                return player;
            }

        private:
            PlayerActor actor;
    };
}
#endif