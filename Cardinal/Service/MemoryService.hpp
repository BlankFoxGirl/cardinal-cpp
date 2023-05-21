#ifndef CARDINAL_SERVICE_MEMORYSERVICE_H
#define CARDINAL_SERVICE_MEMORYSERVICE_H
#include <string>
#include <utility>

namespace Cardinal::Service {
    class MemoryServiceInterface {
        public:
            virtual ~MemoryServiceInterface() noexcept = default;
            virtual void Connect(std::string ConnectUrl) = 0;
            virtual void WriteHash(std::string Key, std::string Field, std::string Value) = 0;
            virtual void WriteHash(std::string Key, std::pair<std::string, std::string> Pair) = 0;
            virtual void Write(std::string Key, std::string Value) = 0;
            virtual std::string Read(std::string Key) = 0;
            virtual std::pair<std::string, std::string> ReadHash(std::string Key, std::string Field) = 0;
    };
}
#endif