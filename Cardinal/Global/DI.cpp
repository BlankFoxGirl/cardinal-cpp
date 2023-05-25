
#include "Cardinal/Service/Services.hpp"
#include "Cardinal/Service/Log/LogClient.hpp"
#include "Cardinal/Service/Message/MessageClient.hpp"
#include "vendor/boost/di.hpp"
#include "DI.hpp"
#include "Cardinal/Core.hpp"

namespace di = boost::di;
using namespace Cardinal::Service;

Cardinal::Global::DI::DI() {
    this->Init();
};

void Cardinal::Global::DI::Init() {
    auto injector = di::make_injector(
        di::bind<LogServiceInterface>().to<Cardinal::Service::Log::LogClient>(),
        // boost::di::bind<CommunicationServiceInterface>().to<CommunicationService>(),
        // boost::di::bind<MemoryServiceInterface>().to<MemoryService>(),
        boost::di::bind<MessageServiceInterface>().to<Cardinal::Service::Message::MessageClient>()
        // boost::di::bind<StorageServiceInterface>().to<StorageService>()
    );

    injector.create<Cardinal::Core>();
}
