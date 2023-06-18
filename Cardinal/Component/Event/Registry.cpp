#include "Registry.hpp"

namespace Cardinal::Component::Event {
    // All Events MUST have a Static Create method.
    template <typename T>
    void Registry::Register()
    {
        Registry::events.insert(
            pair<std::string, std::map<std::string, FactoryType>::mapped_type>(
                (std::string)T::GetEventKey(),
                (FactoryType)T::Create)); // Creator method for factory.
    }

    FactoryType Registry::Query(std::string key)
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

    RegistryEntry Registry::events;
}