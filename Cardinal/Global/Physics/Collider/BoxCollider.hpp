#ifndef CARDINAL_GLOBAL_PHYSICS_COLLIDER_BOXCOLLIDER_HPP
#define CARDINAL_GLOBAL_PHYSICS_COLLIDER_BOXCOLLIDER_HPP

#include "Cardinal/Global/Physics/Collider/AbstractCollider.hpp"
#include "Cardinal/Global/Physics/Vector3.hpp"

using namespace Cardinal::Global::Physics::Collider;
using namespace Cardinal::Global::Physics;

namespace Cardinal::Global::Physics::Collider {
    class BoxCollider : public AbstractCollider {
    public:
        BoxCollider() = default;

        BoxCollider(Vector3 center, Vector3 size) : AbstractCollider(center, size) {}

        bool IsColliding(AbstractCollider* other) override {
            return false;
        }

        bool IsColliding(Vector3 point) override {
            bool response = false;
            if (point.x >= this->center.x && point.x <= this->center.x + this->size.x) {
                if (point.y >= this->center.y && point.y <= this->center.y + this->size.y) {
                    if (point.z >= this->center.z && point.z <= this->center.z + this->size.z) {
                        response = true;
                    }
                }
            }

            return response;
        }

        bool IsColliding(Vector3 point) override {
            return false;
        }
    };
}

#endif