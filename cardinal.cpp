// #include "Entity/Event.h"
#include "Exception/Exceptions.h"
#include "Service/LogService.h"
#include "Service/EventMapService.hpp"
#include "Service/RedisClient.h"
#include "Service/TCPListenerService.h"
#include "Service/UserService.hpp"
#include "Event/Events.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "vendor/boost/di.hpp"
namespace di = boost::di;

using namespace std;


// namespace ttest {
//     class Test {
//         public:
//             Test() {
//                 // this->di = DI::getDI();
//             }

//             // static void Connect() {
//             //     Test::client = Cardinal::Service::RedisClient("localhost", "6379");
//             // }
//             void test() {
//                 throw Cardinal::Exception::AccountNotFound();
//             }

//             void test2() {
//                 Test::client.subscribe("test");
//                 Test::client.publish("Test message");
//             }
//             void test3_setup() {
//                 Cardinal::Event::TestEvent *t = new Cardinal::Event::TestEvent();
//                 // di.getEventMapService().Register("TestEvent", t);
//             }

//             static Cardinal::Service::RedisClient client;
//         // private:
//             // DI di;
//     };
// }
// // Config;
// // Cardinal::Event::eventObject Cardinal::Event::EventMap::events = {};
// Cardinal::Service::RedisClient ttest::Test::client = Cardinal::Service::RedisClient("localhost", "6379");

int main() {
    // Cardinal::Global::DI * di = new Cardinal::Global::DI();
    auto injector = di::make_injector(
        di::bind<Cardinal::Service::LogServiceInterface>().to<Cardinal::Service::LogService>(),
        di::bind<Cardinal::Service::EventMapServiceInterface>().to<Cardinal::Service::EventMapService>(),
        di::bind<Cardinal::Service::CacheClientInterface>().to<Cardinal::Service::RedisClient>(),
        di::bind<Cardinal::Service::TCPListenerServiceInterface>().to<Cardinal::Service::TCPListenerService>(),
        di::bind<Cardinal::Service::UserServiceInterface>().to<Cardinal::Service::UserService>()
    );


    injector.create<Cardinal::Core>();
}

