#include <string>
#include <iostream>
using namespace std;

namespace Cardinal::Event {
    class TestEvent: public Cardinal::Event::AbstractEvent {
        public:
        virtual bool invoke(std::string Payload) override {
            cout << "Executed on TestEvent " << Payload << endl;
            return true;
        }
    };
}