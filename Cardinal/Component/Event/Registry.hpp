#ifndef CARDINAL_COMPONENT_EVENT_REGISTRY_H
#define CARDINAL_COMPONENT_EVENT_REGISTRY_H

#include <string>
#include <map>
#include <string>
#include "Cardinal/Event/AbstractEvent.hpp"
#include "Cardinal/Exception/Exceptions.h"

/**
 * Factory Create methods are registered within the Registry which are subsequently queried and returned
 * to support the invocation of an event.
 * The factory method should inherit a super which already has the appropriate references to service interfaces.
 *
 * This will then allow the tail-end events derriving from the AbstractEvent a simplified constructor pattern
 * for easier implementation for Framework users.
*/
namespace Cardinal::Component::Event {
    typedef std::unique_ptr<Cardinal::Event::AbstractEvent> (*FactoryType)();
    typedef map<string, FactoryType> RegistryEntry;

    class Registry {
    public:
        /// @brief Registers the given Event type with the Event Registry.
        /// @tparam T the type identifier of the given event being registered.
        template <typename T>
        static void Register()
        {
            // All Events MUST have a Static Create method.
            events.insert(
                pair<std::string, std::map<std::string, FactoryType>::mapped_type>(
                    (std::string)T::GetEventKey(),
                    (FactoryType)T::Create)); // Creator method for factory.
        }

        /// @brief Query the Event Registry and return with the corresponding entry by Event Key.
        /// @param key Key Identifier of the event being queried.
        /// @return the FactoryType when invoked creates an instance of the event for event invocation.
        /// @throws InvalidOrMissingEvent when event is not found or a registry error occurs.
        static FactoryType Query(std::string key)
        {
            try
            {
                auto receivedEventObject = events.at(key);
                return receivedEventObject;
            }
            catch (std::exception &e)
            {
                throw Cardinal::Exception::InvalidOrMissingEvent();
            }
        }

    private:
        static RegistryEntry events;
    };
}
#endif