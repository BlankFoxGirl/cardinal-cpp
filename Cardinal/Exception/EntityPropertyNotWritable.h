#include "AbstractException.h"

#ifndef EPNWE_H
#define EPNWE_H
using namespace std;

namespace Cardinal {
    namespace Exception {
        class EntityPropertyNotWritable: public AbstractException {
            public:
            EntityPropertyNotWritable() : AbstractException("The entity property is not writable.") {};
        };
    }
}
#endif