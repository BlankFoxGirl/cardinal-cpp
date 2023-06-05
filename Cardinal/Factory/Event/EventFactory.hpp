#ifndef CARDINAL_FACTORY_EVENT_ABSTRACTEVENTFACTORY_HPP
#define CARDINAL_FACTORY_EVENT_ABSTRACTEVENTFACTORY_HPP
#include "Cardinal/Factory/AbstractFactory.hpp"
#include "Cardinal/Event/AbstractEvent.hpp"
#include "Cardinal/Service/Services.hpp"

namespace Cardinal::Factory::Event
{
    class EventFactory : public Cardinal::Factory::AbstractFactory
    {
    public:
        virtual ~EventFactory() = default;
        virtual EventFactory *Clone() = 0;

        template <class T>
        Cardinal::Event::AbstractEvent *Clone()
        {
            return new T(this->logService_, this->messageService_, this->memoryService_);
        }
    };
}
#endif