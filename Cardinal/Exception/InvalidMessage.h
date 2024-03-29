#ifndef CARDINAL_EXCEPTION_INVALIDMESSAGE_H
#define CARDINAL_EXCEPTION_INVALIDMESSAGE_H
#include <exception>
#include "AbstractException.h"

namespace Cardinal::Exception
{
    class InvalidMessage : public AbstractException
    {
    public:
        InvalidMessage() : AbstractException("The message provided was invalid."){};
    };
}
#endif