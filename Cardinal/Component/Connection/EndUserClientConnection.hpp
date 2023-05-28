#ifndef CARDINAL_COMPONENT_CONNECTION_ENDUSERCLIENTCONNECTION_HPP
#define CARDINAL_COMPONENT_CONNECTION_ENDUSERCLIENTCONNECTION_HPP
#include "Cardinal/Service/CommunicationService.hpp"
#include "Cardinal/Service/LogService.hpp"
#include "Cardinal/Service/MessageService.hpp"
#include <vector>

namespace Cardinal::Component::Connection {
    class EndUserClientConnection {
        public:
            EndUserClientConnection(
                Cardinal::Service::LogServiceInterface& s,
                Cardinal::Service::CommunicationServiceInterface& s1,
                Cardinal::Service::MessageServiceInterface& s2
            ): logService_(s), communicationService_(s1), messageService_(s2)
            {};

            ~EndUserClientConnection() = default;

            void AcceptConnection(void *args);

        private:
            Cardinal::Service::LogServiceInterface& logService_;
            Cardinal::Service::CommunicationServiceInterface& communicationService_;
            Cardinal::Service::MessageServiceInterface& messageService_;
            Cardinal::Service::req socket;
            std::vector<char> buffer;
            int SocketStatus = 1;
            std::string HandleReadingFromClient(std::vector<char>& buffer);
            void HandleWritingToClient();
            bool IsNeedingToSendData();
            void InboundMessageHandler(std::string message);
    };
}
#endif