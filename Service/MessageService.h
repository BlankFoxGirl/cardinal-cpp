#include <string>
#include "../Exception/Exceptions.h"

using namespace std;

namespace Cardinal {
    namespace Service {
        class MessageService {
            MessageService () {}
            MessageService (string raw) {
                this->raw = raw;
            }

            MessageService (string event, string message) {
                this->event = event;
                this->message = message;
            }

            string getEvent () {
                return this->event;
            }

            void setEvent (string event) {
                this->event = event;
            }

            void setMessage (string message) {
                this->message = message;
            }

            void appendMessage(string message) {
                this->message += message;
            }

            string getRaw() {
                if (this->raw.empty()) {
                    this->Compile();
                }
                return this->raw;
            }

            tuple<string,string> Decode() {
                if (this->event.empty() || this->message.empty()) {
                    throw Cardinal::Exception::InvalidMessage();
                }

                return make_tuple(this->event, this->message);
            }

            private:
                string raw = "";
                string event = "";
                string message = "";

                void Compile () {
                    if (this->event.empty() || this->message.empty()) {
                        throw Cardinal::Exception::InvalidMessage();
                    }

                    string compiledMessage = this->event + "|" + this->message;
                    this->raw = compiledMessage;
                }
        };
    };
}
