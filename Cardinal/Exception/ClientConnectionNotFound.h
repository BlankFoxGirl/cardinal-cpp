#include "AbstractException.h"
#ifndef CCNFE_H
#define CCNFE_H
using namespace std;

namespace Cardinal {
    namespace Exception {
        class ClientConnectionNotFound: public AbstractException {
            public:
            ClientConnectionNotFound() : AbstractException("The ClientConnection could not be found.") {};
        };
    }
}
#endif