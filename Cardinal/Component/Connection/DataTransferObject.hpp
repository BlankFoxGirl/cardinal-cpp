#ifndef CARDINAL_COMPONENT_CONNECTION_DATATRANSFEROBJECT_HPP
#define CARDINAL_COMPONENT_CONNECTION_DATATRANSFEROBJECT_HPP
#include <string>
#include <map>
#include "Cardinal/Entity/Message.hpp"

namespace Cardinal::Component::Connection {
    class DataTransferObject {
        public:
            DataTransferObject();
            ~DataTransferObject() = default;
            virtual const char* Encode();
            virtual Cardinal::Entity::Message Decode(char* value);

            virtual void SetValue(std::string value);
            virtual void SetValue(Cardinal::Entity::Message message);
            virtual void SetValue(char* value);

        private:
            Cardinal::Entity::Message message;
            std::map<std::byte, std::string> bytesToHeaders;
            std::map<std::string, std::byte> headersToBytes;
            void SetHeader(std::byte byte, std::string value);
            void SetHeader(int byte, std::string value);
    };
}

#endif