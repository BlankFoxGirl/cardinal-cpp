#include <exception>
#include "AbstractException.h"
#ifndef TCPSBE_H
#define TCPSBE_H
using namespace std;

namespace Cardinal {
    namespace Exception {
        class TCPSocketBindException: public AbstractException {
            public:
            TCPSocketBindException() : AbstractException("Socket binding failed.") {};
        };
    }
}
#endif