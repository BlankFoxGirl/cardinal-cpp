#ifndef CARDINAL_GLOBAL_DI_H
#define CARDINAL_GLOBAL_DI_H
#include "vendor/boost/di.hpp"

// extern Cardinal::Global::DI diContainer;
namespace Cardinal::Global {
    class DI {
        public:
            DI();

        private:
            void Init();
    };
}

#endif