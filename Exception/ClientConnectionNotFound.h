#include "AbstractException.h"

using namespace std;

namespace Cardinal {
    namespace Exception {
        class ClientConnectionNotFound: public AbstractException {
            public:
            ClientConnectionNotFound() : AbstractException("The ClientConnection could not be found.") {};
        };
    }
}