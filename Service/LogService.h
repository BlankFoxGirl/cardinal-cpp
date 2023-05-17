#include <string>
#include <iostream>

#ifndef LS_H
#define LS_H
using namespace std;
// using namespace Cardinal::Service;

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
        virtual void SetEnvironment(string environment) = 0;

        virtual bool Log(string message, string payload = "", LOG_LEVEL level = LOG_LEVEL::Info) = 0;
        virtual void Error(string message, string payload = "") = 0;
        virtual void Warning(string message, string payload = "") = 0;
        virtual void Info(string message, string payload = "") = 0;
        virtual void Debug(string message, string payload = "") = 0;
        virtual void Verbose(string message, string payload = "") = 0;

    };

    class LogService: public Cardinal::Service::LogServiceInterface {
        public:
            LogService();

            void SetMinimumLogLevel(LOG_LEVEL level);
            void SetEnvironment(string environment);

            bool Log(string message, string payload = "", LOG_LEVEL level = LOG_LEVEL::Info);
            void Error(string message, string payload);
            void Warning(string message, string payload);
            void Info(string message, string payload);
            void Debug(string message, string payload);
            void Verbose(string message, string payload);

        private:
            static LOG_LEVEL MinimumLogLevel;
            static string Environment;
            bool isLogLevelGreaterOrEqualToMinimum(LOG_LEVEL level);
            void WriteToCout(string message, string colour = "\033[0m");
            void WriteToFile();
            void WriteToDatabase();
            void WriteToRedis();
            void ErrorLog(string message, string payload);
            void WarningLog(string message, string payload);
            void InfoLog(string message, string payload);
            void DebugLog(string message, string payload);
            void VerboseLog(string message, string payload);
            string SetColour(string colour);
            string ClearColour();
            string GetTimeStampUTC();
            string GetEnvironment();
    };
}

#endif