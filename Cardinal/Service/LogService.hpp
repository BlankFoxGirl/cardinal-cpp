#include <string>
#include <iostream>
// #include "Log/LogClient.hpp"

#ifndef LS_H
#define LS_H
namespace Cardinal::Service
{
    /// @brief Enumerable indicating the level of log output for a given message.
    enum class LOG_LEVEL
    {
        Error,
        Warning,
        Info,
        Debug,
        Verbose
    };

    /// @brief The Log Service is responsible for outputting logs to std::out, a log file, and / or an external service.
    class LogServiceInterface
    {
    public:
        virtual ~LogServiceInterface() noexcept = default;

        /// @brief Set the minimum level of application-wide logging. This is used to filter out messages that are not important. (Recommended: Info in production.)
        /// @param level
        virtual void SetMinimumLogLevel(LOG_LEVEL level) = 0;

        /// @brief Set the environment that the application is running in, this is used to differentiate logs that are piped to a combined log file or display.
        /// @param environment
        virtual void SetEnvironment(std::string environment) = 0;

        /// @brief Arbitrary low-level logging function. Default implementation calls Log with level set to Info.
        /// @param message
        /// @param payload
        /// @param level
        /// @return
        virtual bool Log(std::string message, std::string payload = "", LOG_LEVEL level = LOG_LEVEL::Info) = 0;

        /// @brief Output an error log message.
        /// @param message
        /// @param payload
        virtual void Error(std::string message, std::string payload = "") = 0;

        /// @brief Output a warning log message.
        /// @param message
        /// @param payload
        virtual void Warning(std::string message, std::string payload = "") = 0;

        /// @brief Output a standard info log message.
        /// @param message
        /// @param payload
        virtual void Info(std::string message, std::string payload = "") = 0;

        /// @brief Output a debug log message for easier debugging.
        /// @param message
        /// @param payload
        virtual void Debug(std::string message, std::string payload = "") = 0;

        /// @brief Output a verbose log message.
        /// Warning: This will generate a lot of logs and is not recommended on any environment other than local development.
        /// @param message
        /// @param payload
        virtual void Verbose(std::string message, std::string payload = "") = 0;
    };
}

#endif