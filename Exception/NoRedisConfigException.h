#include <exception>
using namespace std;

namespace Cardinal {
    namespace Exception {
        class NoRedisConfigException: public AbstractException {
            public:
            NoRedisConfigException() : AbstractException("No config provided for redis config.") {};
        };
    }
}