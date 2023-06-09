#ifndef CARDINAL_SERVICE_STORAGE_REDISSTACKSTORAGE_HPP
#define CARDINAL_SERVICE_STORAGE_REDISSTACKSTORAGE_HPP
#include "Cardinal/Service/StorageService.hpp"
#include <sw/redis++/redis++.h>

namespace Cardinal::Service::Storage
{
    class RedisStackStorage: public StorageServiceInterface
    {
    public:
        // RedisStackStorage();
        ~RedisStackStorage() = default;

        void Connect(std::string ConnectionURL) override;
        void Connect(std::string Hostname, std::string Port, std::string Protocol = "tcp") override;

        StoredObject Get(const std::string& primary, const std::string& table) override;
        StoredObjectCollection Find(StoredObject& parameter, const std::string& table) override;
        StoredObject Save(StoredObject& object, const std::string& table) override;

    private:
        sw::redis::Redis redisStack;
        std::string ConstructFindCommand(std::string table, StoredObject parameters);
        void CreateIndexes();
    };
}
#endif