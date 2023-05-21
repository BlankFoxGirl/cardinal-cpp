#include "AbstractException.h"

#ifndef EPNFE_H
#define EPNFE_H
using namespace std;

namespace Cardinal {
    namespace Exception {
        class EntityPropertyNotFound: public AbstractException {
            public:
            EntityPropertyNotFound() : AbstractException("The EntityProperty could not be found.") {};
        };
    }
}
#endif