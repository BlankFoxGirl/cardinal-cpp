#include "UnitTest++/UnitTest++.h"
#include "Cardinal/Entity/EventEntity.hpp"

SUITE(EventEntityTest)
{
   TEST(CanCreateEventEntity)
   {
      auto entity = Cardinal::Entity::EventEntity("", "", "", "");
      CHECK(true);
   }

   TEST(EventEntityHasUUID)
   {
      auto entity = Cardinal::Entity::EventEntity("", "", "", "");
      CHECK(entity.getUUID() != "");
   }

   TEST(EventEntityCanBeConvertedToString)
   {
      auto entity = Cardinal::Entity::EventEntity("Name", "Payload", "", "");
      CHECK_EQUAL("Name|Payload,", entity.ToString());
   }

   TEST(EventCanBeSerialised)
   {
      auto entity = Cardinal::Entity::EventEntity("Name", "Payload", "", "");
      auto serializedEvent = entity.Serialize();
      CHECK_EQUAL("Name", serializedEvent[0].second);
   }

   TEST(EventCanBeSerialised2)
   {
      auto entity = Cardinal::Entity::EventEntity("Name", "Payload", "", "");
      auto serializedEvent = entity.Serialize();
      CHECK_EQUAL("Payload", serializedEvent[1].second);
   }

   TEST(EventCanBeSerialised3)
   {
      auto entity = Cardinal::Entity::EventEntity("Name", "Payload", "Origin", "");
      auto serializedEvent = entity.Serialize();
      CHECK_EQUAL("Origin", serializedEvent[2].second);
   }

   TEST(EventCanBeSerialised4)
   {
      auto entity = Cardinal::Entity::EventEntity("Name", "Payload", "", "Locked");
      auto serializedEvent = entity.Serialize();
      CHECK_EQUAL("Locked", serializedEvent[3].second);
   }

   TEST(EventCanBeInstantiatedFromSerialised)
   {
      auto entity = Cardinal::Entity::EventEntity("Name", "Payload", "", "");
      auto serializedEvent = entity.Serialize();
      auto entity2 = Cardinal::Entity::EventEntity(serializedEvent);
      CHECK_EQUAL(entity.ToString(), entity2.ToString());
   }

   TEST(CanGetEventQueue)
   {
      auto entity = Cardinal::Entity::EventEntity("", "", "", "");
      CHECK_EQUAL("event:123", entity.GetQueue("123"));
   }
}