#ifndef CARDINAL_GLOBAL_DI_H
#define CARDINAL_GLOBAL_DI_H
#include "../../vendor/boost/di.hpp"

namespace Cardinal::Global {
    class DI {
        public:
            DI();
            // template <typename T>
            // DI(T BindingClass);

            // static const DI& getDI() {
            //     assert(instance);
            //     return *instance;
            // }

        private:
            // static DI* instance;
            void Init();
    };
}

#endif