#include <string>

#ifndef AbstractEvent_H
#define AbstractEvent_H
using namespace std;

namespace Cardinal::Event {
    class AbstractEvent {
        public:
            AbstractEvent() {}
            virtual bool invoke(std::string Payload) {
                // Do nothing. This gets overridden.
                return true;
            }
    };
}
#endif