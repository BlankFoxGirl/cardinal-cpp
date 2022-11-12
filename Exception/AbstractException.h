using namespace std;
#include <exception>
#include <cstring>

namespace Cardinal {
    namespace Exception {
        class AbstractException: public std::exception {
            private:
            const char * message = "An exception has occurred.";

            public:
            AbstractException(const char * message = "") {
                if (strcmp(message, "") != 0) {
                    this->message = message;
                }
            }
            const char * what () const throw ()
            {
                return this->message;
            }
        };
    }
}