#include <string>
#include <iostream>
#include "AbstractEvent.h"
using namespace std;

namespace Cardinal::Event {
    class TestEvent: public Cardinal::Event::AbstractEvent {
        public:
        bool invoke(std::string Payload) {
            cout << "Executed on TestEvent " << Payload << endl;
            return true;
        }
    };
}