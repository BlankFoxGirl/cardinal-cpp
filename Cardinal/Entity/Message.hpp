#ifndef CARDINAL_ENTITY_MESSAGE_H
#define CARDINAL_ENTITY_MESSAGE_H

#include "AbstractEntity.h"
#include "Cardinal/Exception/InvalidMessage.h"
#include <string>

namespace Cardinal::Entity {
    class Message: public AbstractEntity {
        public:
            Message() {}

            Message(std::string raw) {
                // Decompile inbound message.
                this->Decompile(raw);
            }

            Message(std::string key, std::string payload) {
                this->key = key;
                this->payload = payload;
            }

            std::string getKey() {
                return this->key;
            }

            std::string getPayload() {
                return this->payload;
            }

            std::string setKey(std::string key) {
                this->key = key;
                return this->key;
            }

            std::string setPayload(std::string payload) {
                this->payload = payload;
                return this->payload;
            }

            std::string Compile() {
                if (this->key.empty() || this->payload.empty()) {
                    throw Cardinal::Exception::InvalidMessage();
                }

                std::string compiledMessage = this->key + "|" + this->payload;
                return compiledMessage;
            }

            void Decompile(std::string raw) {
                if (raw.empty()) {
                    throw Cardinal::Exception::InvalidMessage();
                }

                std::string delimiter = "|";

                // IF missing terminator, then append terminator.
                if (raw.at(raw.length() - 1) != '|') {
                    raw += "|";
                }

                size_t pos = raw.find(delimiter);
                std::string token;
                int i = 0;

                while (pos != -1) {
                    token = raw.substr(0, pos);

                    if (i == 0) {
                        this->key = token;

                    } else if (i == 1) {
                        this->payload = token;
                    }

                    raw.erase(0, pos + delimiter.length());
                    pos = raw.find(delimiter);
                    i++;
                }
            }

        private:
            std::string key = "";
            std::string payload = "";
    };
}
#endif