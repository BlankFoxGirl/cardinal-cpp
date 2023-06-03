#include <exception>
#include "AbstractException.h"
#ifndef TCPSLE_H
#define TCPSLE_H
using namespace std;

namespace Cardinal
{
    namespace Exception
    {
        class TCPSocketListenException : public AbstractException
        {
        public:
            TCPSocketListenException() : AbstractException("Socket binding failed."){};
        };
    }
}
#endif