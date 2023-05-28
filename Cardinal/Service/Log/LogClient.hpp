
#ifndef CARDINAL_LOGCLIENT_H
#define CARDINAL_LOGCLIENT_H
#include <string>
#include <iostream>
#include "Cardinal/Service/LogService.hpp"

namespace Cardinal::Service::Log {
    class LogClient: public Cardinal::Service::LogServiceInterface {
        public:
            LogClient();

            void SetMinimumLogLevel(Cardinal::Service::LOG_LEVEL level);
            void SetEnvironment(std::string environment);

            bool Log(std::string message, std::string payload = "", Cardinal::Service::LOG_LEVEL level = Cardinal::Service::LOG_LEVEL::Info);
            void Error(std::string message, std::string payload);
            void Warning(std::string message, std::string payload);
            void Info(std::string message, std::string payload);
            void Debug(std::string message, std::string payload);
            void Verbose(std::string message, std::string payload);

        private:
            static Cardinal::Service::LOG_LEVEL MinimumLogLevel;
            static std::string Environment;
            bool isLogLevelGreaterOrEqualToMinimum(Cardinal::Service::LOG_LEVEL level);
            void WriteToCout(std::string message, std::string colour = "\033[0m");
            void WriteToFile();
            void WriteToDatabase();
            void WriteToRedis();
            void ErrorLog(std::string message, std::string payload);
            void WarningLog(std::string message, std::string payload);
            void InfoLog(std::string message, std::string payload);
            void DebugLog(std::string message, std::string payload);
            void VerboseLog(std::string message, std::string payload);
            std::string SetColour(std::string colour);
            std::string ClearColour();
            std::string GetTimeStampUTC();
            std::string GetEnvironment();
    };
}

#endif