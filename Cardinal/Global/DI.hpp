#ifndef CARDINAL_GLOBAL_DI_H
#define CARDINAL_GLOBAL_DI_H
#include "vendor/boost/di.hpp"
#include "Cardinal/Factory/AbstractFactory.hpp"

namespace Cardinal::Global
{
    class DI
    {
    public:
        DI();

        template <typename T>
        void Init();
        Cardinal::Factory::AbstractFactory* GetFactory();

    private:
        Cardinal::Factory::AbstractFactory* factory = nullptr;
    };
}

#endif