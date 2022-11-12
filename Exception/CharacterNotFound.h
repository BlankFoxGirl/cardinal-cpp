#include "AbstractException.h"

using namespace std;

namespace Cardinal {
    namespace Exception {
        class CharacterNotFound: public AbstractException {
            public:
            CharacterNotFound() : AbstractException("The character could not be found.") {};
        };
    }
}