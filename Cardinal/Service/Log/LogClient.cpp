#include <string>
#include "LogClient.hpp"
#include <iostream>
#include <time.h>
#include <sstream>

using namespace std;
using namespace Cardinal::Service::Log;

/**
 * // Constructor //
*/
LogClient::LogClient() {} // New Instance of log service.

/**
 * // Public Methods //
*/
bool LogClient::Log(string message, string payload, Cardinal::Service::LOG_LEVEL level)
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

void LogClient::Error(string message, string payload)
{
    this->ErrorLog(message, payload);
}

void LogClient::Warning(string message, string payload)
{
    this->WarningLog(message, payload);
}

void LogClient::Info(string message, string payload)
{
    this->InfoLog(message, payload);
}

void LogClient::Debug(string message, string payload)
{
    this->DebugLog(message, payload);
}

void LogClient::Verbose(string message, string payload)
{
    this->VerboseLog(message, payload);
}

void LogClient::SetMinimumLogLevel(LOG_LEVEL level)
{
    this->MinimumLogLevel = level;
}

void LogClient::SetEnvironment(string environment)
{
    this->Environment = environment;
}

/**
 * // Private Methods //
*/
bool LogClient::isLogLevelGreaterOrEqualToMinimum(LOG_LEVEL level)
{
    return (int)level >= (int)this->MinimumLogLevel;
}

void LogClient::WriteToCout(string message, string colour)
{
    cout << colour << this->GetTimeStampUTC() << this->GetEnvironment() << message << ClearColour() << std::endl;
}

void LogClient::WriteToFile()
{
    // Do nothing.
}

void LogClient::WriteToDatabase()
{
    // Do nothing.
}

void LogClient::WriteToRedis()
{
    // Do nothing.
}

void LogClient::ErrorLog(string message, string payload)
{
    WriteToCout("[ERROR] " + message + " " + payload, SetColour("red"));
}

void LogClient::WarningLog(string message, string payload)
{
    WriteToCout("[WARNING] " + message + " " + payload, SetColour("yellow"));
}

void LogClient::InfoLog(string message, string payload)
{
    WriteToCout("[INFO] " + message + " " + payload, SetColour("white"));
}

void LogClient::DebugLog(string message, string payload)
{
    WriteToCout("[DEBUG] " + message + " " + payload, SetColour("blue"));
}

void LogClient::VerboseLog(string message, string payload)
{
    WriteToCout("[VERBOSE] " + message + " " + payload);
}

string LogClient::SetColour(string colour)
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

string LogClient::ClearColour()
{
    return "\033[0m"; // Normal Colour.
}

string LogClient::GetEnvironment()
{
    return "[" + this->Environment + "]";
}

string LogClient::GetTimeStampUTC()
{
    time_t rawtime;
    struct tm * ptm;
    // Get number of seconds since 00:00 UTC Jan, 1, 1970 and store in rawtime
    time ( &rawtime );
    // UTC struct tm
    ptm = gmtime ( &rawtime );
    char output[80];
    strftime(output, 80, "%Y-%m-%dT%H:%M:%SZ", ptm);

    // delete ptm;
    // print current time in a formatted way
    return "[" + (string)output + "]";
}

Cardinal::Service::LOG_LEVEL LogClient::MinimumLogLevel = LOG_LEVEL::Info;
string LogClient::Environment = "INIT";