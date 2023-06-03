#include <exception>
#include "AbstractException.h"
#ifndef IOMEE_H
#define IOMEE_H
using namespace std;

namespace Cardinal
{
    namespace Exception
    {
        class InvalidOrMissingEvent : public AbstractException
        {
        public:
            InvalidOrMissingEvent() : AbstractException("The event called was either invalid or has not been registered."){};
        };
    }
}
#endif