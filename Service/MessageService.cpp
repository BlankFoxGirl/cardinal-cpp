#include <string>
#include "../Exception/Exceptions.h"
#include "MessageService.h"
#include "LogService.h"

using namespace std;
using namespace Cardinal::Service;

MessageService::MessageService () {}
MessageService::MessageService (string raw) {
    LogService logService = LogService();
    logService.Log("MessageService", raw, LOG_LEVEL::Debug);
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
    LogService logService = LogService();
    logService.Log("MessageService::Decode", "Called", LOG_LEVEL::Debug);
    if (this->event.empty() || this->message.empty()) {
        logService.Log("MessageService::Decode", "EMPTY", LOG_LEVEL::Debug);
        throw Cardinal::Exception::InvalidMessage();
    }

    logService.Log("MessageService::Decode", "Complete", LOG_LEVEL::Debug);
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
    LogService logService = LogService();
    logService.Log("MessageService::Decompile", "Called", LOG_LEVEL::Debug);
    if (!this->event.empty() && !this->message.empty()) {
        logService.Log("MessageService::Decompile", "Already Parsed", LOG_LEVEL::Debug);
        return;
    }

    if (this->raw.empty()) {
        logService.Log("MessageService::Decompile", "RAW EMPTY", LOG_LEVEL::Debug);
        throw Cardinal::Exception::InvalidMessage();
    }

    string raw = this->raw;
    string delimiter = "|";

    // IF missing terminator, then append terminator.
    if (raw.at(raw.length() - 1) != '|') {
        raw += "|";
    }

    size_t pos = raw.find(delimiter);
    string token;
    int i = 0;

    while (pos != -1) {
        logService.Log("MessageService::Decompile:87", "Iteration " + i, LOG_LEVEL::Debug);
        token = raw.substr(0, pos);
        logService.Log("MessageService::Decompile:89", "Token " + token, LOG_LEVEL::Debug);

        if (i == 0) {
            this->event = token;
            logService.Log("MessageService::Decompile:92", "Set event to " + token, LOG_LEVEL::Debug);

        } else if (i == 1) {
            this->message = token;
            logService.Log("MessageService::Decompile:95", "Set message to " + token, LOG_LEVEL::Debug);
        }

        raw.erase(0, pos + delimiter.length());
        pos = raw.find(delimiter);
        i++;
    }

    logService.Log("MessageService::Decompile", "Completed", LOG_LEVEL::Debug);
}