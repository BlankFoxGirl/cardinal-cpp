#include "Cardinal/Global/DI.hpp"
#include "Cardinal/Core.hpp"
#include "vendor/boost/di.hpp"
#include "Cardinal/Service/Services.hpp"
#include "Cardinal/Event/TestEvent.hpp"
#include "Cardinal/Event/Player/Movement.hpp"
#include "Cardinal/Component/Event/Registry.hpp"

int main()
{
    // Register event.
    Cardinal::Component::Event::Registry::Register<Cardinal::Event::TestEvent>();
    Cardinal::Component::Event::Registry::Register<Cardinal::Event::Player::Movement>();

    // Currently, this will auto-start the framework.
    auto di = std::make_shared<Cardinal::Global::DI>();

    // @todo: Starting the framework should be a separate step.
    // Start framework.
    // Cardinal::Core::Start(di);
    // cardinalFramework->Init(); // Start framework.
}
