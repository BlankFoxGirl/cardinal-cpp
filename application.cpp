#include "Cardinal/Global/DI.hpp"
#include "Cardinal/Core.hpp"
#include "vendor/boost/di.hpp"
#include "Cardinal/Service/Services.hpp"
#include "Cardinal/Event/TestEvent.hpp"

namespace di = boost::di;

int main() {
    auto di = new Cardinal::Global::DI;

    // Cardinal::Core::RegisterEvent<Cardinal::Event::TestEvent>();
    // Cardinal::Global::DI::Init();
    // auto injector = di::make_injector(
    //     di::bind<Cardinal::Service::LogServiceInterface>().to<Cardinal::Service::LogService>()
    // //     // boost::di::bind<CommunicationServiceInterface>().to<CommunicationService>(),
    // //     // boost::di::bind<MemoryServiceInterface>().to<MemoryService>(),
    // //     // boost::di::bind<MessageServiceInterface>().to<MessageService>(),
    // //     // boost::di::bind<StorageServiceInterface>().to<StorageService>()
    // );

    // injector.create<Cardinal::Core>();
}

