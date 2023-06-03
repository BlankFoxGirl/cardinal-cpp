#ifndef CARDINAL_GLOBAL_PHYSICS_COLLIDER_ABSTRACTCOLLIDER_HPP
#define CARDINAL_GLOBAL_PHYSICS_COLLIDER_ABSTRACTCOLLIDER_HPP

#include "Cardinal/Global/Physics/Vector3.hpp"
using namespace Cardinal::Global::Physics;

namespace Cardinal::Global::Physics::Collider
{
    class AbstractCollider
    {
    public:
        AbstractCollider() = default;

        AbstractCollider(Vector3 center, Vector3 size, bool isEnabled = false, bool isTrigger = false)
        {
            this->center = center;
            this->size = size;
            this->isEnabled = isEnabled;
            this->isTrigger = isTrigger;
        }

        virtual bool IsColliding(AbstractCollider *other) = 0;

        virtual bool IsColliding(Vector3 point) = 0;

    private:
        Vector3 center;
        Vector3 size;
        bool isTrigger = false;
        bool isEnabled = false;
    };
}

#endif