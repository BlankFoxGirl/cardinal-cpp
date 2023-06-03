#include "AbstractException.h"

#ifndef CNFE_H
#define CNFE_H
using namespace std;

namespace Cardinal
{
    namespace Exception
    {
        class CharacterNotFound : public AbstractException
        {
        public:
            CharacterNotFound() : AbstractException("The character could not be found."){};
        };
    }
}
#endif