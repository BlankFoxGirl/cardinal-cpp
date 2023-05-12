#include <string>
#include "LogService.h"
#include <iostream>

using namespace std;
using namespace Cardinal::Service;

LogService::LogService() {} // New Instance of log service.
bool LogService::Log(string message, string payload, Service::LOG_LEVEL level)
{
    switch (level) {
        case LOG_LEVEL::Verbose:
            this->VerboseLog(message, payload);
            break;
        case LOG_LEVEL::Debug:
            this->DebugLog(message, payload);
            break;
        case LOG_LEVEL::Warning:
            this->WarningLog(message, payload);
            break;
        case LOG_LEVEL::Error:
            this->ErrorLog(message, payload);
            break;
        default:
            this->InfoLog(message, payload);
            break;
    }

    return true;
}

void LogService::WriteToCout(string message)
{
    cout << message << SetColour("") << std::endl;
}

void LogService::WriteToFile()
{
    // Do nothing.
}

void LogService::WriteToDatabase()
{
    // Do nothing.
}

void LogService::WriteToRedis()
{
    // Do nothing.
}

void LogService::ErrorLog(string message, string payload)
{
    WriteToCout(SetColour("red") + "[ERROR] " + message + " " + payload);
}

void LogService::WarningLog(string message, string payload)
{
    WriteToCout(SetColour("yellow") + "[WARNING] " + message + " " + payload);
}

void LogService::InfoLog(string message, string payload)
{
    WriteToCout(SetColour("") + "[INFO] " + message + " " + payload);
}

void LogService::DebugLog(string message, string payload)
{
    WriteToCout(SetColour("grey") + "[DEBUG] " + message + " " + payload);
}

void LogService::VerboseLog(string message, string payload)
{
    WriteToCout(SetColour("darkGrey") + "[VERBOSE] " + message + " " + payload);
}

string LogService::SetColour(string colour)
{
    if (colour.compare("white") == 0) {
        return "\033[1;37m"; // White.
    } else if (colour.compare("red") == 0) {
        return "\033[0;31m";
    } else if (colour.compare("grey") == 0) {
        return "\033[0;37m";
    } else if (colour.compare("yellow") == 0) {
        return "\033[1;33m";
    } else if (colour.compare("darkGrey") == 0) {
        return "\033[1;30m";
    }

    return "\033[0m"; // Normal Colour.
}
