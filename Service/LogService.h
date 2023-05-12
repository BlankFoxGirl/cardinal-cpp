#include <string>
#include <iostream>

#ifndef LS_H
#define LS_H
using namespace std;
namespace Cardinal::Service {
    enum class LOG_LEVEL {
        Error,
        Warning,
        Info,
        Debug,
        Verbose
    };

    class LogService {
        public:
            LogService();

            bool Log(string message, string payload = "", Service::LOG_LEVEL level = Service::LOG_LEVEL::Info);

        private:
            void WriteToCout(string message);
            void WriteToFile();
            void WriteToDatabase();
            void WriteToRedis();
            void ErrorLog(string message, string payload);
            void WarningLog(string message, string payload);
            void InfoLog(string message, string payload);
            void DebugLog(string message, string payload);
            void VerboseLog(string message, string payload);
            string SetColour(string colour);
    };
}

#endif