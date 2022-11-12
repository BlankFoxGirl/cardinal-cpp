#include "AbstractException.h"

using namespace std;

namespace Cardinal {
    namespace Exception {
        class EntityPropertyNotWritable: public AbstractException {
            public:
            EntityPropertyNotWritable() : AbstractException("The entity property is not writable.") {};
        };
    }
}