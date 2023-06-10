#include "UnitTest++/UnitTest++.h"
#include "Cardinal/Entity/PlayerEntity.hpp"
#include "Cardinal/Global/Physics.hpp"

SUITE(PlayerEntityTest)
{
   TEST(CanCreatePlayerEntity)
   {
      auto entity = Cardinal::Entity::PlayerEntity();
      CHECK(true);
   }

   TEST(CanSetActorName)
   {
      auto entity = Cardinal::Entity::PlayerEntity();
      entity.SetActorName("NewName");
      CHECK_EQUAL("NewName", entity.GetActorName());
   }

   TEST(CanSetActorInGame)
   {
      auto entity = Cardinal::Entity::PlayerEntity();
      entity.SetActorInGame(true);
      CHECK_EQUAL(true, entity.GetActor().inGame);
   }

   TEST(CanSetActorPosition)
   {
      auto entity = Cardinal::Entity::PlayerEntity();
      entity.SetActorPosition(Cardinal::Global::Physics::Vector3(1, 2, 3));
      CHECK_EQUAL(1, entity.GetActor().position.x);
   }

   TEST(CanSetActorRotation)
   {
      auto entity = Cardinal::Entity::PlayerEntity();
      entity.SetActorRotation(Cardinal::Global::Physics::Quaternion(1, 2, 3, 4));
      CHECK_EQUAL(1, entity.GetActor().rotation.x);
   }

   TEST(CanSerialisePlayerEntity)
   {
      auto entity = Cardinal::Entity::PlayerEntity();
      entity.SetActorName("name");
      auto serialised = entity.Serialize();
      CHECK_EQUAL("name", serialised[0].second);
   }

   TEST(CanSerialisePlayerEntity2)
   {
      auto entity = Cardinal::Entity::PlayerEntity();
      auto serialised = entity.Serialize();
      CHECK_EQUAL("0.000000,0.000000,0.000000", serialised[1].second);
   }

   // Below test skipped for now.
   // TEST(CanSerialisePlayerEntity3)
   // {
   //    auto entity = Cardinal::Entity::PlayerEntity();
   //    auto serialised = entity.Serialize();
   //    CHECK_EQUAL("0.000000,0.000000,0.000000", serialised[2].second);
   // }

   TEST(CanCreatePlayerEntityFromMemory)
   {
      auto entity = Cardinal::Entity::PlayerEntity();
      entity.SetActorName("name");
      auto serialised = entity.Serialize();
      auto entity2 = Cardinal::Entity::PlayerEntity::FromMemory(serialised);
      CHECK_EQUAL("name", entity2.GetActorName());
   }
}