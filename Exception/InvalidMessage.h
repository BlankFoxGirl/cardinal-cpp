#include <exception>
using namespace std;

namespace Cardinal {
    namespace Exception {
        class InvalidMessage: public AbstractException {
            public:
            InvalidMessage() : AbstractException("The message provided was invalid.") {};
        };
    }
}