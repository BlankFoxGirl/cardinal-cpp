#include <string>
#include "../Exception/Exceptions.h"
#include "MessageService.h"
#include "LogService.h"

using namespace std;
using namespace Cardinal::Service;

MessageService::MessageService () {}
MessageService::MessageService (string raw) {
    // TODO: Convert to DI.
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

void MessageService::setRaw (string raw) {
    this->raw = raw;
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
    // DI::getDI().getLogService().Debug("MessageService::Decode", "Called");
    if (this->event.empty() || this->message.empty()) {
        // DI::getDI().getLogService().Debug("MessageService::Decode", "EMPTY");
        throw Cardinal::Exception::InvalidMessage();
    }

    // DI::getDI().getLogService().Debug("MessageService::Decode", "Complete");
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
    // LogService logService = DI::getDI().getLogService();
    // logService.Debug("MessageService::Decompile", "Called");
    if (!this->event.empty() && !this->message.empty()) {
        // logService.Debug("MessageService::Decompile", "Already Parsed");
        return;
    }

    if (this->raw.empty()) {
        // logService.Debug("MessageService::Decompile", "RAW EMPTY");
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
        // logService.Debug("MessageService::Decompile:87", "Iteration " + i);
        token = raw.substr(0, pos);
        // logService.Debug("MessageService::Decompile:89", "Token " + token);

        if (i == 0) {
            this->event = token;
            // logService.Debug("MessageService::Decompile:92", "Set event to " + token);

        } else if (i == 1) {
            this->message = token;
            // logService.Debug("MessageService::Decompile:95", "Set message to " + token);
        }

        raw.erase(0, pos + delimiter.length());
        pos = raw.find(delimiter);
        i++;
    }

    // logService.Debug("MessageService::Decompile", "Completed");
}