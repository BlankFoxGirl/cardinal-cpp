#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <vector>
#include <sys/poll.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <fstream>
#include <string>
#include <cstring>
#include <signal.h>
#include <arpa/inet.h>
#include "EndUserClientConnection.hpp"
#include "Cardinal/Entity/Message.hpp"
#include "Cardinal/Exception/InvalidMessage.h"

using namespace Cardinal::Component::Connection;

/**
 * ToDo: This could be done much better. I think that the
 * inbound and outbound handling of communication should
 * occur within the CommunicationService.
 * Whereas the business logic on what to do with a received
 * message, and what to send back should be handled by this
 * component.
 * For now, this just unblocks first-line communication.
*/
void EndUserClientConnection::AcceptConnection(void *args)
{
    this->logService_.Verbose("[Called] Cardinal::Component::Connection::EndUserClientConnection::AcceptConnection");
    Cardinal::Service::req sock = *((Cardinal::Service::req *)args);

    std::vector<char> buf(32); // you are using C++ not C
    int n = 1;

    struct pollfd fds[200];
    memset(fds, 0 , sizeof(fds));

    /*************************************************************/
    /* Set up the initial listening socket                       */
    /*************************************************************/
    fds[0].fd = sock.des;
    fds[0].events = POLLIN;

    // Message template: !#<message>$
    n = write(sock.des, "!#BEGIN$", 8);
    std::string fullMessage = "";

    while (n >= 0)
    {
        n = poll(fds, 1, 500);
        if (n > 0)
        {
            // Flush buffer.
            std::fill(buf.begin(), buf.end(), '\0');

            n = read(sock.des, buf.data(), buf.size());

            if (buf.size() != 0) {
                std::string data = this->HandleReadingFromClient(buf);

                this->logService_.Debug("Received data:", data);
                fullMessage += data; // Append data to full message.
            }

            if (fullMessage.find("$") != std::string::npos) {
                this->logService_.Debug("Received message terminator.");

                if (fullMessage.find("!#END$") != std::string::npos) {
                    this->logService_.Debug("Received END command.");
                    n = write(sock.des, "!#CEND$", 7);
                    break;
                }

                this->InboundMessageHandler(fullMessage);
                fullMessage = ""; // Reset message.
            }
        }
    }

    this->logService_.Verbose("--Cardinal::Component::Connection::EndUserClientConnection::AcceptConnection Closing Socket.");
    close(sock.des);
    this->logService_.Verbose("--Cardinal::Component::Connection::EndUserClientConnection::AcceptConnection Socket Closed.");
    // ToDo: Add OnClose callback.
    // this->CallCallbackByName("OnClose", args);
    this->logService_.Verbose("[Closed] Cardinal::Component::Connection::EndUserClientConnection::AcceptConnection");
}

std::string EndUserClientConnection::HandleReadingFromClient(std::vector<char>& buffer) {
    this->logService_.Verbose("[Called] EndUserClientConnection::HandleReadingFromClient");

    this->logService_.Verbose("Received " + std::to_string(buffer.size()) + " bytes from client.");
    std::string data;

    std::transform(buffer.begin(), buffer.end(), std::back_inserter(data),
    [](char c)
    {
        return c;
    });

    this->logService_.Debug("Received data: " + data);
    // ToDo: Process the received data from the end user.

    this->logService_.Verbose("[Closed] EndUserClientConnection::HandleReadingFromClient");
    return data;
}

void EndUserClientConnection::InboundMessageHandler(std::string message) {
    this->logService_.Verbose("[Called] EndUserClientConnection::InboundMessageHandler");
    // ToDo: Add DTO Translation layer.
    if (message.find("!#") == std::string::npos) {
        this->logService_.Warning("Received invalid data from client.", message);
        return;
    }

    try {
        this->logService_.Verbose("--EndUserClientConnection::InboundMessageHandler Trimming message boundaries from message", message);
        message = message.substr(2, message.size() - 4); // Remove message boundaries.
        this->logService_.Verbose("--EndUserClientConnection::InboundMessageHandler Message boundaries trimmed from message", message);

        this->logService_.Verbose("--EndUserClientConnection::InboundMessageHandler Creating message object from raw message", message);
        Cardinal::Entity::Message inboundMessage = Cardinal::Entity::Message(message);
        this->logService_.Verbose("--EndUserClientConnection::InboundMessageHandler Dispatching message to message service.", inboundMessage.getKey() + " " + inboundMessage.getPayload());
        this->messageService_.Dispatch(inboundMessage);
    } catch (Cardinal::Exception::InvalidMessage& e) {
        this->logService_.Error("EndUserClientConnection::InboundMessageHandler Invalid message received from end user.", e.what());
        return;
    }

    this->logService_.Verbose("[Closed] EndUserClientConnection::InboundMessageHandler");
}

void EndUserClientConnection::HandleWritingToClient() {
    // Do nothing.
}

bool EndUserClientConnection::IsNeedingToSendData() {
    return false;
}
