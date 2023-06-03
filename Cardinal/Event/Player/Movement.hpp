#ifndef CARDINAL_EVENT_PLAYER_MOVEMENT_HPP
#define CARDINAL_EVENT_PLAYER_MOVEMENT_HPP

#include "Cardinal/Event/AbstractEvent.hpp"
#include "Cardinal/Service/LogService.hpp"
#include "Cardinal/Service/MessageService.hpp"
#include "Cardinal/Service/MemoryService.hpp"
#include "Cardinal/Global/Physics.hpp"

using namespace Cardinal::Global::Physics;

namespace Cardinal::Event::Player
{
    struct MovementPacket
    {
        Vector3 position;
        Quaternion rotation;
        int mapId;
        int instanceId;
        std::string connectionUUID;

        std::string PositionToString()
        {
            return this->position.ToString();
        }

        std::string RotationToString()
        {
            return this->rotation.ToEulerString();
        }

        std::string MapIdToString()
        {
            return std::to_string(this->mapId);
        }

        std::string InstanceIdToString()
        {
            return std::to_string(this->instanceId);
        }
    };

    class Movement : public AbstractEvent
    {
    public:
        Movement(
            Cardinal::Service::LogServiceInterface &s,
            Cardinal::Service::MessageServiceInterface &s1,
            Cardinal::Service::MemoryServiceInterface &s2) : logService_(s), messageService_(s1), memoryService_(s2) {}

        ~Movement() = default;

        bool invoke(std::string Payload) override
        {
            // Do something.
            this->UpdatePlayerLocation(Payload);
            return true;
        };

        virtual std::unique_ptr<AbstractEvent> Clone(
            Cardinal::Service::LogServiceInterface &s,
            Cardinal::Service::MessageServiceInterface &s1,
            Cardinal::Service::MemoryServiceInterface &s2) override
        {
            return std::make_unique<Movement>(s, s1, s2);
        }

        static std::unique_ptr<AbstractEvent> Create(
            Cardinal::Service::LogServiceInterface &s,
            Cardinal::Service::MessageServiceInterface &s1,
            Cardinal::Service::MemoryServiceInterface &s2)
        {
            return std::make_unique<Movement>(s, s1, s2);
        }

        static std::string GetEventKey()
        {
            return "PMOVE";
        }

    private:
        Cardinal::Service::LogServiceInterface &logService_;
        Cardinal::Service::MessageServiceInterface &messageService_;
        Cardinal::Service::MemoryServiceInterface &memoryService_;
        const int MOVE_PACKET_SIZE = 9;
        const std::string MOVE_PACKET_DELIMITER = ",";
        void UpdatePlayerLocation(std::string Payload);
        std::vector<std::string> GetPlayerLocation(std::string Payload);
        MovementPacket DecodePlayerLocation(std::vector<std::string> Payload);
        bool PlayerCanMoveToLocation(MovementPacket packet);
        void SendMovementFailureMessage(std::string connectionUUID);
        void SendMovementSuccessMessage(std::string connectionUUID);
        void BroadcastLocationUpdate(std::string uuid, std::string Payload);
    };
}

#endif