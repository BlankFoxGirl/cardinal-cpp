#ifndef AbstractEvent_H
#define AbstractEvent_H
#include <string>
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

            virtual AbstractEvent* Clone(Cardinal::Service::LogServiceInterface& logService) {
                return new AbstractEvent();
            }

            template <typename... Args>
            static AbstractEvent* Create(Args... args) {
                return new AbstractEvent();
            }

            static std::string GetEventKey() {
                return "AbstractEvent";
            };
            // std::string SetEventKey(std::string eventKey);
    };
}
#endif