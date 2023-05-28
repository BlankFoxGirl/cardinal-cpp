cmake_minimum_required(VERSION 3.00)

SET(BASEPATH "${CMAKE_SOURCE_DIR}")
INCLUDE_DIRECTORIES("${BASEPATH}")

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native  -pthread")
add_compile_options(-pthread)
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# This will be simplified. Due to refactoring only the refactored areas are included.
file(GLOB_RECURSE SOURCES
    # Cardinal/**/*.hpp
    Cardinal/Entity/*.hpp
    Cardinal/Entity/*.cpp
    Cardinal/Event/*.hpp
    Cardinal/Event/*.cpp
    Cardinal/Exception/*.h
    Cardinal/Exception/*.cpp
    Cardinal/Service/Memory/*.hpp
    Cardinal/Service/Memory/*.cpp
    Cardinal/Service/LogService.hpp
    Cardinal/Service/Log/*.hpp
    Cardinal/Service/Log/*.cpp
    Cardinal/Service/MessageService.hpp
    Cardinal/Service/Message/*.cpp
    Cardinal/Service/Message/*.hpp
    Cardinal/Service/CommunicationService.hpp
    Cardinal/Service/Communication/*.cpp
    Cardinal/Service/Communication/*.hpp
    Cardinal/Service/Services.hpp
    Cardinal/Component/Message/*.hpp
    Cardinal/Component/Message/*.cpp
    Cardinal/Component/EventMap/*.hpp
    Cardinal/Component/EventMap/*.cpp
    Cardinal/Component/Connection/*.hpp
    Cardinal/Component/Connection/*.cpp
    Cardinal/Global/DI.hpp
    Cardinal/Global/DI.cpp
    Cardinal/Core.hpp
    Cardinal/Core.cpp
    # Cardinal/**/*.cpp
    application.cpp
)


project(Cardinal)

add_executable(cardinal-server ${SOURCES})

target_link_libraries (cardinal-server)
# <------------ add hiredis dependency here --------------->
find_path(HIREDIS_HEADER hiredis)
target_include_directories(cardinal-server PUBLIC ${HIREDIS_HEADER})

find_library(HIREDIS_LIB hiredis)
target_link_libraries(cardinal-server ${HIREDIS_LIB})

# <------------ add redis-plus-plus dependency here -------------->
find_path(REDIS_PLUS_PLUS_HEADER sw)      # NOTE: this should be *sw* NOT *redis++*
target_include_directories(cardinal-server PUBLIC ${REDIS_PLUS_PLUS_HEADER})

find_library(REDIS_PLUS_PLUS_LIB redis++)
target_link_libraries(cardinal-server ${REDIS_PLUS_PLUS_LIB})