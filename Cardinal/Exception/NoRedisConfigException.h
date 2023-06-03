#include "AbstractException.h"
#ifndef NRCE_H
#define NRCE_H
#include <exception>
using namespace std;

namespace Cardinal
{
    namespace Exception
    {
        class NoRedisConfigException : public AbstractException
        {
        public:
            NoRedisConfigException() : AbstractException("No config provided for redis config."){};
        };
    }
}
#endif