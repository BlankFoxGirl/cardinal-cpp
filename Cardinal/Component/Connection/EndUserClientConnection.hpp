#ifndef CARDINAL_COMPONENT_CONNECTION_ENDUSERCLIENTCONNECTION_HPP
#define CARDINAL_COMPONENT_CONNECTION_ENDUSERCLIENTCONNECTION_HPP
#include "Cardinal/Service/CommunicationService.hpp"
#include "Cardinal/Service/LogService.hpp"
#include "Cardinal/Service/MemoryService.hpp"
#include "Cardinal/Service/MessageService.hpp"
#include "Cardinal/Entity/UserEntity.hpp"
#include <vector>

namespace Cardinal::Component::Connection {
    class EndUserClientConnection {
        public:
            EndUserClientConnection(
                Cardinal::Service::LogServiceInterface& s,
                Cardinal::Service::CommunicationServiceInterface& s1,
                Cardinal::Service::MessageServiceInterface& s2,
                Cardinal::Service::MemoryServiceInterface& s3
            ): logService_(s), communicationService_(s1), messageService_(s2), memoryService_(s3)
            {};

            ~EndUserClientConnection() = default;

            void AcceptConnection(void *args);

        private:
            Cardinal::Service::LogServiceInterface& logService_;
            Cardinal::Service::CommunicationServiceInterface& communicationService_;
            Cardinal::Service::MemoryServiceInterface& memoryService_;
            Cardinal::Service::MessageServiceInterface& messageService_;

            static const int POLL_TIMEOUT = 100;
            static const int MAX_BUFFER_SIZE = 1024;

            static const int MESSAGE_EXPIRE_TIME = 60;

            std::string ConnectionMemoryKey = "";

            Cardinal::Service::req socket;
            std::vector<char> buffer;
            Cardinal::Entity::UserEntity* userEntity;
            int SocketStatus = 1;
            std::string HandleReadingFromClient(std::vector<char>& buffer);
            std::string GetMessage();
            void HandleWritingToClient();
            bool IsNeedingToSendData();
            void InboundMessageHandler(std::string message);
            void EstablishMemoryQueue();
            void PullMemoryQueue();
            bool HasItemsInMemoryQueue();
    };
}
#endif