#ifndef CARDNAL_SERVICE_STORAGESERVICE_HPP
#define CARDNAL_SERVICE_STORAGESERVICE_HPP

#include <string>
#include <vector>

namespace Cardinal::Service
{
    struct StoredObjectRow
    {
        std::string key;
        std::string value;
    };

    struct StoredObject
    {
        std::string table;
        std::vector<StoredObjectRow> rows;
    };

    struct StoredObjectCollection
    {
        std::string table;
        std::vector<StoredObject> objects;
    };

    class StorageServiceInterface
    {
    public:
        virtual ~StorageServiceInterface() noexcept = default;

        /// @brief Connects to the storage service.
        /// @param ConnectionURL The URL to connect to the storage service.
        virtual void Connect(std::string ConnectionURL) = 0;

        /// @brief Connect to the upstream message service.
        /// @param Hostname The hostname to connect to.
        /// @param Port The port to connect to.
        /// @param Protocol The protocol to use (Default TCP).
        virtual void Connect(std::string Hostname, std::string Port, std::string Protocol = "tcp") = 0;

        /// @brief Gets an object from storage by its primary key.
        /// @param primary The primary key of the object to get from storage.
        /// @return Returns a StoredObject.
        virtual StoredObject Get(const std::string& primary, const std::string& table) = 0;

        /// @brief Finds objects in storage that have matching parameters.
        /// @param parameter The parameters of the objects to find in storage.
        /// @return Returns a StoredObjectCollection.
        virtual StoredObjectCollection Find(StoredObject& parameter, const std::string& table) = 0;

        /// @brief Save an object to storage.
        /// @param object The StoredObject to save to storage.
        /// @return StoredObject after it was saved.
        virtual StoredObject Save(StoredObject& object, const std::string& table) = 0;
    };
}

#endif