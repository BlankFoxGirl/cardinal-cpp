#ifndef CARDINAL_GLOBAL_UTILITY_HPP
#define CARDINAL_GLOBAL_UTILITY_HPP
#include <vector>
#include <string>

namespace Cardinal::Global
{
    class Utility
    {
    public:
        static std::vector<std::string> Split(const std::string &str, std::string delimiter)
        {
            if (str.empty())
            {
                return {};
            }

            std::vector<std::string> result;

            std::string::size_type pos = 0;
            std::string::size_type idx = 0;

            while (true)
            {
                pos = str.find(delimiter, idx);

                if (pos == std::string::npos)
                {
                    result.push_back(str.substr(idx));
                    break;
                }

                result.push_back(str.substr(idx, pos - idx));
                idx = pos + 1;
            }

            return result;
        }

        static std::string CharToString(char value)
        {
            std::string asString = "";
            asString += value;
            return asString;
        }

        static int CharToInt(char value)
        {
            return std::stoi(CharToString(value));
        }
    };
}

#endif