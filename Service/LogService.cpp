#include <string>
#include "LogService.h"
#include <iostream>
#include <time.h>
#include <sstream>

using namespace std;
using namespace Cardinal::Service;

/**
 * // Constructor //
*/
LogService::LogService() {} // New Instance of log service.

/**
 * // Public Methods //
*/
bool LogService::Log(string message, string payload, Service::LOG_LEVEL level)
{
    if (!isLogLevelGreaterOrEqualToMinimum(level)) {
        return false;
    }

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

void LogService::Error(string message, string payload)
{
    this->ErrorLog(message, payload);
}

void LogService::Warning(string message, string payload)
{
    this->WarningLog(message, payload);
}

void LogService::Info(string message, string payload)
{
    this->InfoLog(message, payload);
}

void LogService::Debug(string message, string payload)
{
    this->DebugLog(message, payload);
}

void LogService::Verbose(string message, string payload)
{
    this->VerboseLog(message, payload);
}

void LogService::SetMinimumLogLevel(LOG_LEVEL level)
{
    this->MinimumLogLevel = level;
}

void LogService::SetEnvironment(string environment)
{
    this->Environment = environment;
}

/**
 * // Private Methods //
*/
bool LogService::isLogLevelGreaterOrEqualToMinimum(LOG_LEVEL level)
{
    return (int)level >= (int)this->MinimumLogLevel;
}

void LogService::WriteToCout(string message, string colour)
{
    cout << colour << this->GetTimeStampUTC() << this->GetEnvironment() << message << ClearColour() << std::endl;
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
    WriteToCout("[ERROR] " + message + " " + payload, SetColour("red"));
}

void LogService::WarningLog(string message, string payload)
{
    WriteToCout("[WARNING] " + message + " " + payload, SetColour("yellow"));
}

void LogService::InfoLog(string message, string payload)
{
    WriteToCout("[INFO] " + message + " " + payload, SetColour("white"));
}

void LogService::DebugLog(string message, string payload)
{
    WriteToCout("[DEBUG] " + message + " " + payload, SetColour("blue"));
}

void LogService::VerboseLog(string message, string payload)
{
    WriteToCout("[VERBOSE] " + message + " " + payload);
}

string LogService::SetColour(string colour)
{
    if (colour.compare("white") == 0) {
        return "\033[1;37m"; // White.
    } else if (colour.compare("red") == 0) {
        return "\033[0;31m";
    } else if (colour.compare("blue") == 0) {
        return "\033[0;34m";
    } else if (colour.compare("yellow") == 0) {
        return "\033[1;33m";
    } else if (colour.compare("darkGrey") == 0) {
        return "\033[1;30m";
    }

    return this->ClearColour(); // Normal Colour.
}

string LogService::ClearColour()
{
    return "\033[0m"; // Normal Colour.
}

string LogService::GetEnvironment()
{
    return "[" + this->Environment + "]";
}

string LogService::GetTimeStampUTC()
{
    time_t rawtime;
    struct tm * ptm;
    // Get number of seconds since 00:00 UTC Jan, 1, 1970 and store in rawtime
    time ( &rawtime );
    // UTC struct tm
    ptm = gmtime ( &rawtime );
    char output[80];
    strftime(output, 80, "%Y-%m-%dT%H:%M:%SZ", ptm);
    // print current time in a formatted way
    return "[" + (string)output + "]";
}

LOG_LEVEL LogService::MinimumLogLevel = LOG_LEVEL::Info;
string LogService::Environment = "INIT";