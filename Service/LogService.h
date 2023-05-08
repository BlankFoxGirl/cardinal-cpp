#include <string>

using namespace std;
namespace Cardinal::Service {
    class LogService {
        LogService();

        bool Log(string message, string payload = "", LogService::LOG_LEVEL level = Info);

        enum LOG_LEVEL{
            Error,
            Warning,
            Info,
            Debug,
            Verbose
        };
        static LOG_LEVEL LOG_LEVEL;
        private:
    };
}