#include "Cardinal/Component/Connection/DataTransferObject.hpp"
#include "UnitTest++/UnitTest++.h"
#include "Cardinal/Entity/Message.hpp"
#include "Cardinal/Component/Connection/DataTransferObject.hpp"
#include "Cardinal/Global/Utility.hpp"

SUITE(DataTransferObjectTest)
{
    TEST(CanEncodeMovementMessage)
    {
        auto message = Cardinal::Entity::Message();
        // x,y,z,rx,ry,rz,mapId,instanceId,connectionUUID
        // PMOVE|1,1,1,1,1,1,1,1,1 // Valid Basic Payload.
        message.setKey("PMOVE");
        message.setPayload("1,1,1,1,1,1,1,1,1"); // Basic Payload, all 1's.
        auto component = Cardinal::Component::Connection::DataTransferObject();
        // component.SetValue(message);
        component.SetValue("PMOVE|1,1,1,1,1,1,1,1,1");

        auto value = component.Encode();

        // Compare byte at index 2 with expected header byte of 0x04.
        CHECK_EQUAL(4, Cardinal::Global::Utility::CharToInt(value[0]));
    }
}
