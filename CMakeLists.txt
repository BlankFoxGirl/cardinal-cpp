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
file(GLOB_RECURSE LIBRARY_SOURCES
    Cardinal/**/*.hpp
    Cardinal/Exception/*.h
    Cardinal/Core.hpp
    Cardinal/Core.cpp
    Cardinal/**/*.cpp
)

file(GLOB_RECURSE SOURCES
    application.cpp
)


project(Cardinal)
add_library(cardinal SHARED ${LIBRARY_SOURCES})

add_executable(cardinal-server ${SOURCES})

target_link_libraries (cardinal)

target_link_libraries (cardinal-server)

# <------------ add cardinal framework link --------------->
target_link_libraries (cardinal-server cardinal)

# <------------ add hiredis dependency here --------------->
find_path(HIREDIS_HEADER hiredis)
target_include_directories(cardinal PUBLIC ${HIREDIS_HEADER})

find_library(HIREDIS_LIB hiredis)
target_link_libraries(cardinal ${HIREDIS_LIB})

# <------------ add redis-plus-plus dependency here -------------->
find_path(REDIS_PLUS_PLUS_HEADER sw)      # NOTE: this should be *sw* NOT *redis++*
target_include_directories(cardinal PUBLIC ${REDIS_PLUS_PLUS_HEADER})

find_library(REDIS_PLUS_PLUS_LIB redis++)
target_link_libraries(cardinal ${REDIS_PLUS_PLUS_LIB})