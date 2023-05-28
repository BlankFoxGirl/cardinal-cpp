#include <string>
#include <iostream>
#include "Log/LogClient.hpp"

#ifndef LS_H
#define LS_H
namespace Cardinal::Service {
    enum class LOG_LEVEL {
        Error,
        Warning,
        Info,
        Debug,
        Verbose
    };

    class LogServiceInterface {
    public:
        virtual ~LogServiceInterface() noexcept = default;
        virtual void SetMinimumLogLevel(LOG_LEVEL level) = 0;
        virtual void SetEnvironment(std::string environment) = 0;

        virtual bool Log(std::string message, std::string payload = "", LOG_LEVEL level = LOG_LEVEL::Info) = 0;
        virtual void Error(std::string message, std::string payload = "") = 0;
        virtual void Warning(std::string message, std::string payload = "") = 0;
        virtual void Info(std::string message, std::string payload = "") = 0;
        virtual void Debug(std::string message, std::string payload = "") = 0;
        virtual void Verbose(std::string message, std::string payload = "") = 0;
    };
}

#endif