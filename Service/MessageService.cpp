#include <string>
#include "../Exception/Exceptions.h"
#include "MessageService.h"

using namespace std;
using namespace Cardinal::Service;

MessageService::MessageService () {}
MessageService::MessageService (string raw) {
    this->raw = raw;
}

MessageService::MessageService (string event, string message) {
    this->event = event;
    this->message = message;
}

string MessageService::getEvent () {
    return this->event;
}

void MessageService::setEvent (string event) {
    this->event = event;
}

void MessageService::setMessage (string message) {
    this->message = message;
}

void MessageService::appendMessage(string message) {
    this->message += message;
}

string MessageService::getRaw() {
    if (this->raw.empty()) {
        this->Compile();
    }
    return this->raw;
}

tuple<string,string> MessageService::Decode() {
    if (this->event.empty() || this->message.empty()) {
        throw Cardinal::Exception::InvalidMessage();
    }

    return make_tuple(this->event, this->message);
}


void MessageService::Compile () {
    if (this->event.empty() || this->message.empty()) {
        throw Cardinal::Exception::InvalidMessage();
    }

    string compiledMessage = this->event + "|" + this->message;
    this->raw = compiledMessage;
}
