#ifndef CARDINAL_GLOBAL_QUEUE_HPP
#define CARDINAL_GLOBAL_QUEUE_HPP
#include <string>

namespace Cardinal::Global {
    struct Queue {
        static const std::string DEFAULT;
        static const std::string CRITICAL;
        static const std::string WEATHER;
    };
}

#endif
