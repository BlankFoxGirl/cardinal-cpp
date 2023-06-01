#ifndef CARDINAL_ENTITY_EXTENSION_SERIALIZABLEOBJECT_HPP
#define CARDINAL_ENTITY_EXTENSION_SERIALIZABLEOBJECT_HPP
#include <vector>
#include <map>
#include <string>

namespace Cardinal::Entity::Extension {
    class SerializableObject {
        virtual std::vector<std::pair<std::string, std::string>> Serialize() = 0;
    };
}

#endif