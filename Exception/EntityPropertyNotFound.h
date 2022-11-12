#include "AbstractException.h"

using namespace std;

namespace Cardinal {
    namespace Exception {
        class EntityPropertyNotFound: public AbstractException {
            public:
            EntityPropertyNotFound() : AbstractException("The EntityProperty could not be found.") {};
        };
    }
}