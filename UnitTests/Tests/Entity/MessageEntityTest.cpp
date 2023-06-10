#include "UnitTest++/UnitTest++.h"
#include "Cardinal/Entity/Message.hpp"

SUITE(MessageEntityTest)
{
   TEST(CanCreateMessageEntity)
   {
      auto entity = Cardinal::Entity::Message();
      CHECK(true);
   }

   TEST(CanCreateMessageEntity2)
   {
      auto entity = Cardinal::Entity::Message("Name", "Payload");
      CHECK_EQUAL("Name", entity.getKey());
   }

   TEST(CanCreateMessageEntity3)
   {
      auto entity = Cardinal::Entity::Message("Name", "Payload");
      CHECK_EQUAL("Payload", entity.getPayload());
   }

   TEST(CanCreateAndDecodeMessageEntity)
   {
      auto entity = Cardinal::Entity::Message("Name|Payload");
      CHECK_EQUAL("Name", entity.getKey());
   }

   TEST(CanCreateAndDecodeMessageEntity2)
   {
      auto entity = Cardinal::Entity::Message("Name|Payload");
      CHECK_EQUAL("Payload", entity.getPayload());
   }

   TEST(CanSetKey)
   {
      auto entity = Cardinal::Entity::Message();
      entity.setKey("NewName");
      CHECK_EQUAL("NewName", entity.getKey());
   }

   TEST(CanSetPayload)
   {
      auto entity = Cardinal::Entity::Message();
      entity.setPayload("NewPayload");
      CHECK_EQUAL("NewPayload", entity.getPayload());
   }

   TEST(CanCompileMessage)
   {
      auto entity = Cardinal::Entity::Message("Name", "Payload");
      CHECK_EQUAL("Name|Payload", entity.Compile());
   }

   TEST(CanSerialiseMessage)
   {
      auto entity = Cardinal::Entity::Message("Name", "Payload");
      auto serialised = entity.Serialize();
      CHECK_EQUAL("Name", serialised[0].second);
   }

   TEST(CanSerialiseMessage2)
   {
      auto entity = Cardinal::Entity::Message("Name", "Payload");
      auto serialised = entity.Serialize();
      CHECK_EQUAL("Payload", serialised[1].second);
   }
}