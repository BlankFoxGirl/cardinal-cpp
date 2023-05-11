#include <string>
#include "../Exception/Exceptions.h"
#include "MessageService.h"

using namespace std;
using namespace Cardinal::Service;

MessageService::MessageService () {}
MessageService::MessageService (string raw) {
    this->raw = raw;
    this->Decompile();
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

void MessageService::Decompile() {
    if (!this->event.empty() && !this->message.empty()) {
        return;
    }

    if (this->raw.empty()) {
        throw Cardinal::Exception::InvalidMessage();
    }

    string raw = this->raw;
    string delimiter = "|";
    size_t pos = raw.find(delimiter);
    string token;
    int i = 0;

    while (pos != -1) {
        token = raw.substr(0, pos);
        if (i == 0) {
            this->event = token;
        } else if (i == 1) {
            this->message = token;
        }
        raw.erase(0, pos + delimiter.length());
        pos = raw.find(delimiter);
        i++;
    }
}