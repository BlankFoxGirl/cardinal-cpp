#include <exception>
using namespace std;

namespace Cardinal {
    namespace Exception {
        class AccountNotFound: public AbstractException {
            public:
            AccountNotFound() : AbstractException("The account could not be found.") {};
        };
    }
}