#include <exception>
#include "AbstractException.h"
#ifndef TCPSCE_H
#define TCPSCE_H
using namespace std;

namespace Cardinal
{
    namespace Exception
    {
        class TCPSocketCreationException : public AbstractException
        {
        public:
            TCPSocketCreationException() : AbstractException("Socket creation failed."){};
        };
    }
}
#endif