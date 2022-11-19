#include <string>
#include <map>
#include <iostream>

using namespace std;

namespace Cardinal::Event {
    typedef map<string, Cardinal::Event::AbstractEvent*> eventObject;
    class EventMap {
        public:
            static void Invoke (string eventName, string payload) {
                auto receivedEventObject = events.at(eventName);
                try {
                    receivedEventObject->invoke(payload);
                } catch (std::exception& e) {
                    throw Cardinal::Exception::InvalidOrMissingEvent();
                }
                receivedEventObject->invoke(payload);
                cout << "Ran:" << eventName << endl;
            }

            static void Register (string eventName, Cardinal::Event::AbstractEvent *eventObject) {
                events.insert(pair<string, std::map<std::string, Cardinal::Event::AbstractEvent *>::mapped_type>(eventName, eventObject));
            }

            static eventObject events;
    };
}

Cardinal::Event::eventObject Cardinal::Event::EventMap::events = {};