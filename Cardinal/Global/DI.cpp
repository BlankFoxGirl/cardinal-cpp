
#include "../Service/Services.hpp"
#include "../Service/Log/LogClient.hpp"
#include "../../vendor/boost/di.hpp"
#include "DI.hpp"
#include "../Core.hpp"

namespace di = boost::di;
using namespace Cardinal::Service;

// template <typename T>
Cardinal::Global::DI::DI() {
    this->Init();
    // instance = this;
};

// DI::~DI() {};

void Cardinal::Global::DI::Init() {
    auto injector = di::make_injector(
        di::bind<LogServiceInterface>().to<Cardinal::Service::Log::LogClient>()
        // boost::di::bind<CommunicationServiceInterface>().to<CommunicationService>(),
        // boost::di::bind<MemoryServiceInterface>().to<MemoryService>(),
        // boost::di::bind<MessageServiceInterface>().to<MessageService>(),
        // boost::di::bind<StorageServiceInterface>().to<StorageService>()
    );

    injector.create<Cardinal::Core>();
}
