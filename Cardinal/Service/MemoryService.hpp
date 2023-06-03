#ifndef CARDINAL_SERVICE_MEMORYSERVICE_H
#define CARDINAL_SERVICE_MEMORYSERVICE_H
#include <string>
#include <utility>
#include <queue>

namespace Cardinal::Service
{
    /// @brief The Memory Service is responsible for storing and retrieving data from a transient memory store such as Redis or Memcached.
    class MemoryServiceInterface
    {
    private:
        static const int DEFAULT_TTL = 0;

    public:
        virtual ~MemoryServiceInterface() noexcept = default;

        /// @brief Connect to the memory service
        /// @param ConnectUrl
        virtual void Connect(std::string ConnectUrl) = 0;

        /// @brief Connect to the upstream message service.
        /// @param Hostname The hostname to connect to.
        /// @param Port The port to connect to.
        /// @param Protocol The protocol to use (Default TCP).
        virtual void Connect(std::string Hostname, std::string Port, std::string Protocol = "tcp") = 0;

        /// @brief Write a hash to the memory service
        /// @param Key
        /// @param Field
        /// @param Value
        /// @param ttl
        virtual void WriteHash(std::string Key, std::string Field, std::string Value, int ttl = DEFAULT_TTL) = 0;

        /// @brief Write a hash to the memory service
        /// @param Key
        /// @param Pair
        /// @param ttl
        virtual void WriteHash(std::string Key, std::pair<std::string, std::string> Pair, int ttl = DEFAULT_TTL) = 0;

        /// @brief Write a vector of string pairs to a key using the memory service
        /// @param Key
        /// @param Hash
        /// @param ttl
        virtual void WriteAllHash(std::string Key, std::vector<std::pair<std::string, std::string>> Hash, int ttl = DEFAULT_TTL) = 0;

        /// @brief Write a value to the memory service
        /// @param Key
        /// @param Value
        /// @param ttl
        virtual void Write(std::string Key, std::string Value, int ttl = DEFAULT_TTL) = 0;

        /// @brief Add a value to the memory service
        /// @param Key
        /// @param Value
        /// @param ttl
        virtual void Add(std::string Key, std::string Value, int ttl = DEFAULT_TTL) = 0;

        /// @brief Pop a value from a list in the memory service
        /// @param Key
        /// @return std::string
        virtual std::string Pop(std::string Key) = 0;

        /// @brief Pop a range of values from a list in the memory service
        /// @param Key
        /// @param Count
        /// @return std::queue<std::string>
        virtual std::queue<std::string> PopRange(std::string Key, int Count) = 0;

        /// @brief Fetch a value from a list in the memory service
        /// @param Key
        /// @return std::string
        virtual std::string Fetch(std::string Key) = 0;

        /// @brief Get the length of a list in the memory service
        /// @param Key
        /// @return long long
        virtual long long Length(std::string Key) = 0;

        /// @brief Read a value from the memory service
        /// @param Key
        /// @return std::string
        virtual std::string Read(std::string Key) = 0;

        /// @brief Read a hash from the memory service
        /// @param Key
        /// @param Field
        /// @return std::pair<std::string, std::string>
        virtual std::pair<std::string, std::string> ReadHash(std::string Key, std::string Field) = 0;

        /// @brief Read all hashes from the memory service
        /// @param Key
        /// @return std::vector<std::pair<std::string, std::string>>
        virtual std::vector<std::pair<std::string, std::string>> ReadAllHash(std::string Key) = 0;

        /// @brief Delete a key from the memory service
        /// @param Key
        virtual void Delete(std::string Key) = 0;

        /// @brief Check if a key exists in the memory service
        /// @param Key
        /// @return
        virtual bool Exists(std::string Key) = 0;

        /// @brief Remove the TTL on a key
        /// @param Key
        virtual void Persist(std::string Key) = 0;
    };
}
#endif