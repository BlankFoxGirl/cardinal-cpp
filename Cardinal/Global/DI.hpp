#ifndef CARDINAL_GLOBAL_DI_H
#define CARDINAL_GLOBAL_DI_H
#include "vendor/boost/di.hpp"

namespace Cardinal::Global {
    class DI {
        public:
            DI();

            template <typename T>
            void Init();
    };
}

#endif