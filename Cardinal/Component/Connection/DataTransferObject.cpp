#include "DataTransferObject.hpp"

using namespace Cardinal::Component::Connection;

DataTransferObject::DataTransferObject()
{
    // Initial Connection.
    this->SetHeader(0x00, "BEGIN");

    // Authentication
    this->SetHeader(0x01, "SETKEY");
    this->SetHeader(0x02, "LOGIN");

    // Character
    this->SetHeader(0x03, "SHOWCHARS");
    this->SetHeader(0x04, "CREATECHAR");
    this->SetHeader(0x05, "DELETECHAR");
    this->SetHeader(0x06, "SELECTCHAR");

    // Movement
    this->SetHeader(0x04, "PMOVE");
    this->SetHeader(0x05, "PCAST");
    this->SetHeader(0x06, "PATTACK");

    // Chat
    this->SetHeader(0x07, "PCHAT");

    // Player
    this->SetHeader(0x08, "PINFO");
    this->SetHeader(0x09, "PSTATS");
    this->SetHeader(0x0A, "PINV");

    // Equipment
    this->SetHeader(0x0B, "PITEM");
    this->SetHeader(0x0C, "PUSE");
    this->SetHeader(0x0D, "PEQUIP");
    this->SetHeader(0x0E, "PUNEQUIP");

    // Market
    this->SetHeader(0x0F, "PBUY");
    this->SetHeader(0x10, "PSELL");

    // Trade
    this->SetHeader(0x11, "PTRADE");
    this->SetHeader(0x12, "PTRADEACCEPT");
    this->SetHeader(0x13, "PTRADECANCEL");
    this->SetHeader(0x14, "PTRADECONFIRM");
    this->SetHeader(0x15, "PTRADEDECLINE");

    // Party
    this->SetHeader(0x16, "PCPARTY"); // Create Party
    this->SetHeader(0x16, "PJPARTY"); // Join Party
    this->SetHeader(0x16, "PLPARTY"); // Leave Party
    this->SetHeader(0x16, "PIPARTY"); // Invite To Party
}

void DataTransferObject::SetHeader(std::byte byte, std::string value)
{
    this->bytesToHeaders.insert(std::pair<std::byte, std::string>(byte, value));
    this->headersToBytes.insert(std::pair<std::string, std::byte>(value, byte));
}

void DataTransferObject::SetHeader(int byte, std::string value)
{
    this->bytesToHeaders.insert(std::pair<std::byte, std::string>((std::byte)byte, value));
    this->headersToBytes.insert(std::pair<std::string, std::byte>(value, (std::byte)byte));
}

Cardinal::Entity::Message DataTransferObject::Decode(char *value)
{
    std::string asString = (std::string)value;
    // Message template: !#<message>$
    // IF first byte of message portion is a header, then we use it to derive the message type.
    this->message = Cardinal::Entity::Message(asString);

    // Read DTO Headers using byte at index 2.
    if (this->bytesToHeaders.find((std::byte)value[2]) != this->bytesToHeaders.end())
    {
        this->message.setKey(this->bytesToHeaders[(std::byte)value[2]]);

        this->message.setPayload(asString.substr(1, asString.length()));
    }

    return this->message;
}

const char *DataTransferObject::Encode()
{
    std::string message = this->message.Compile();
    if (this->headersToBytes.find(this->message.getKey()) != this->headersToBytes.end())
    {
        auto replaceValue = (char *)this->headersToBytes[this->message.getKey()];

        message = message.replace(
            (int)message.find(
                this->message.getKey()),
            this->message.getKey().length(),
            (std::string)replaceValue);
    }

    auto response = new char[message.length() + 1];
    strcpy(response, message.c_str());

    return response;
}

void DataTransferObject::SetValue(std::string value)
{
    this->message = Cardinal::Entity::Message(value);
}

void DataTransferObject::SetValue(char *value)
{
    this->message = this->Decode(value);
}

void DataTransferObject::SetValue(Cardinal::Entity::Message message)
{
    this->message = message;
}
