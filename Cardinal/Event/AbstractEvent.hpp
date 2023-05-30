#ifndef AbstractEvent_H
#define AbstractEvent_H
#include <string>
#include <memory>
#include "Cardinal/Service/LogService.hpp"

namespace Cardinal::Event {
    class AbstractEvent {
        public:
            AbstractEvent() {};

            virtual ~AbstractEvent() = default;

            virtual bool invoke(std::string Payload) {
                // Do nothing. This gets overridden.
                return true;
            }

            virtual std::unique_ptr<AbstractEvent> Clone(Cardinal::Service::LogServiceInterface& logService) {
                return std::make_unique<AbstractEvent>();
                // return new AbstractEvent();
            }

            template <typename... Args>
            static std::unique_ptr<AbstractEvent> Create(Args... args) {
                return std::make_unique<AbstractEvent>();
            }

            static std::string GetEventKey() {
                return "AbstractEvent";
            };
            // std::string SetEventKey(std::string eventKey);
    };
}
#endif