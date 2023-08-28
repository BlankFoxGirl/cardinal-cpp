
#include "Cardinal/Service/Services.hpp"
#include "Cardinal/Service/Log/LogClient.hpp"
#include "Cardinal/Service/Message/RedisMessageClient.hpp"
#include "Cardinal/Service/Communication/TCPClient.hpp"
#include "Cardinal/Service/Memory/RedisCacheClient.hpp"
#include "Cardinal/Service/Storage/MySQLStorageClient.hpp"
#include "vendor/boost/di.hpp"
#include "DI.hpp"
#include "Cardinal/Core.hpp"

using namespace Cardinal::Service;

Cardinal::Global::DI::DI()
{
    this->Init<Cardinal::Core>();
};

template <typename T>
void Cardinal::Global::DI::Init()
{
    auto injector = boost::di::make_injector(
        boost::di::bind<Cardinal::Service::LogServiceInterface>().to<Cardinal::Service::Log::LogClient>(),
        boost::di::bind<Cardinal::Service::CommunicationServiceInterface>().to<Cardinal::Service::Communication::TCPClient>(),
        boost::di::bind<Cardinal::Service::MemoryServiceInterface>().to<Cardinal::Service::Memory::RedisCacheClient>(),
        boost::di::bind<Cardinal::Service::MessageServiceInterface>().to<Cardinal::Service::Message::RedisMessageClient>(),
        boost::di::bind<Cardinal::Service::StorageServiceInterface>().to<Cardinal::Service::Storage::MySQLStorageClient>()
    );

    auto cardinal = injector.create<T>();
}
