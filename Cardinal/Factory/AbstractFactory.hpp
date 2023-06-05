#ifndef CARDINAL_FACTORY_ABSTRACTFACTORY_HPP
#define CARDINAL_FACTORY_ABSTRACTFACTORY_HPP
#include "Cardinal/Service/Services.hpp"

namespace Cardinal::Factory
{
    class AbstractFactory
    {
    public:
        explicit AbstractFactory(
            Cardinal::Service::LogServiceInterface &logService,
            Cardinal::Service::MessageServiceInterface &messageService,
            Cardinal::Service::MemoryServiceInterface &memoryService) : logService_(logService), messageService_(messageService), memoryService_(memoryService){};

        virtual ~AbstractFactory() = default;
        virtual AbstractFactory *Clone() { return nullptr; };

        template <class T>
        T *Create()
        {
            return new T(this->logService_, this->messageService_, this->memoryService_);
        }

    protected:
        Cardinal::Service::LogServiceInterface &logService_;
        Cardinal::Service::MessageServiceInterface &messageService_;
        Cardinal::Service::MemoryServiceInterface &memoryService_;
    };
}

#endif