#include <exception>
#include <cstring>
#ifndef AE_H
#define AE_H
using namespace std;

namespace Cardinal
{
    namespace Exception
    {
        class AbstractException : public std::exception
        {
        private:
            const char *message = "An exception has occurred.";

        public:
            AbstractException(const char *message = "")
            {
                if (strcmp(message, "") != 0)
                {
                    this->message = message;
                }
            }
            const char *what() const throw()
            {
                return this->message;
            }
        };
    }
}
#endif