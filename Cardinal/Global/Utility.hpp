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

        static std::string Join(const std::vector<std::string> &str, std::string delimiter)
        {
            if (str.empty())
            {
                return "";
            }

            std::string result;

            for (auto &s : str)
            {
                result += s + delimiter;
            }

            return result.substr(0, result.length() - delimiter.length());
        }

        static std::string Escape(const std::string &str)
        {
            std::string result;

            for (auto &c : str)
            {
                switch (c)
                {
                case '\\':
                    result += "\\\\";
                    break;
                case '\n':
                    result += "\\n";
                    break;
                case '\r':
                    result += "\\r";
                    break;
                case '\t':
                    result += "\\t";
                    break;
                case '\b':
                    result += "\\b";
                    break;
                case '\f':
                    result += "\\f";
                    break;
                case '\"':
                    result += "\\\"";
                    break;
                case '@':
                    result += "\\@";
                    break;
                case '.':
                    result += "\\.";
                    break;
                case '\'':
                    result += "\\\'";
                    break;
                default:
                    result += c;
                    break;
                }
            }

            return result;
        }
    };
}

#endif