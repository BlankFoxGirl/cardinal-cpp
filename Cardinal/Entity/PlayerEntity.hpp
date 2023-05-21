#ifndef PE_H
#define PE_H
#include "AbstractEntity.h"
#include <queue>

namespace Cardinal::Entity {
    // ToDo: Extract into physics library.
    struct Vector3 {
        int x;
        int y;
        int z;
    };

    struct Quaternion {
        int x;
        int y;
        int z;
        int w;
    };

    struct PlayerActor {
        std::string name;
        Vector3 position;
        Quaternion rotation;
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
        string name;
        ItemRarety rarety;
        int amount;
    };

    class PlayerEntity: public AbstractEntity {
        public:
            PlayerEntity();

            string GetActorName();
            string SetActorName(string name);
            Vector3 GetActorPosition();
            Vector3 SetActorPosition(Vector3 position);
            Quaternion GetActorRotation();
            Quaternion SetActorRotation(Quaternion rotation);
            PlayerActor GetActor();

        private:
            PlayerActor actor;
    };
}
#endif