#include "UnitTest++/UnitTest++.h"
#include "Cardinal/Component/Event/Registry.hpp"
#include "Cardinal/Event/TestEvent.hpp"
#include <iostream>

SUITE(EventRegistryTest)
{
    TEST(CanRegisterAnEvent)
    {
        try {
            Cardinal::Component::Event::Registry::Register<Cardinal::Event::TestEvent>();
            CHECK(true);
        } catch (std::exception& e) {
            // Throw fail here.
            CHECK(false);
        }
    }

    TEST(CanFindARegisteredEvent)
    {
        Cardinal::Component::Event::Registry::Register<Cardinal::Event::TestEvent>();

        try {
            auto actuallyAnEvent = Cardinal::Component::Event::Registry::Query("TestEvent");
            CHECK(true);
        } catch (std::exception& e) {
            // Throw fail here.
            CHECK(false);
        }
    }

    TEST(CannotFindAnEventThatHasNotBeenRegistered)
    {
        try {
            auto noEvent = Cardinal::Component::Event::Registry::Query("NoEvent");
            CHECK(false);
        } catch (std::exception& e) {
            // Throw fail here.
            CHECK(true);
        }
    }
}
