#include <exception>
using namespace std;

namespace Cardinal {
    namespace Exception {
        class InvalidOrMissingEvent: public AbstractException {
            public:
            InvalidOrMissingEvent() : AbstractException("The event called was either invalid or has not been registered.") {};
        };
    }
}