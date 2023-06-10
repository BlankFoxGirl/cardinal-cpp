#include "UnitTest++/UnitTest++.h"
#include "Cardinal/Entity/UserEntity.hpp"

SUITE(UserEntityTest)
{
    TEST(CanCreateUserEntity)
    {
        auto entity = Cardinal::Entity::UserEntity();
        CHECK(true);
    }

    TEST(CanNotSerialize)
    {
        auto entity = Cardinal::Entity::UserEntity();
        CHECK(entity.Serialize().empty());
    }
}