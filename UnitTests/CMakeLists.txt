project(test_cardinal)

cmake_minimum_required(VERSION 3.1)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

SET(CARDINAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../)
SET(BASEPATH ${CARDINAL_DIR})
find_package(UnitTest++ REQUIRED)
include_directories(${UTPP_INCLUDE_DIRS})

find_library(CARDINAL_LIB Cardinal ${CMAKE_CURRENT_SOURCE_DIR}/../build/lib)
find_library(UNIT_TEST_LIB UnitTest++ ${UTPP_INCLUDE_DIRS})

enable_testing()

file(GLOB_RECURSE TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    Tests/**/*.cpp
    ../vendor/eranpeer/FakeIt/single_header/standalone/fakeit.hpp
    main.cpp
)

# file(GLOB_RECURSE TEST_SRCS
#     **/*Test.cpp
#     main.cpp
# )

message(TEST_SRCS, ${TEST_SRCS})
message(CMAKE_CURRENT_SOURCE_DIR, ${CMAKE_CURRENT_SOURCE_DIR})
message(CARDINAL_DIR, ${CARDINAL_DIR})
message(CARDINAL_LIB, ${CARDINAL_LIB})
message(UNIT_TEST_LIB, ${UNIT_TEST_LIB})
message(BASEPATH, ${BASEPATH})
message(UTPP_INCLUDE_DIRS, ${UTPP_INCLUDE_DIRS})

# source_group( "" FILES ${TEST_SRCS})
add_executable(TEST_Runner ${TEST_SRCS})

target_link_libraries(TEST_Runner ${CARDINAL_LIB})

target_include_directories(TEST_Runner PUBLIC ${CARDINAL_DIR})
target_include_directories(TEST_Runner PUBLIC ${UTPP_INCLUDE_DIRS})

target_link_libraries(TEST_Runner ${UNIT_TEST_LIB})

set_target_properties(TEST_Runner PROPERTIES LINKER_LANGUAGE CXX)

# #Run through each source
# foreach(testSrc ${TEST_SRCS})
#     #Extract the filename without an extension (NAME_WE)
#     get_filename_component(testName ${testSrc} NAME_WE)

#     #Add compile target
#     add_executable(${testName} ${testSrc})

#     target_link_libraries(${testName} ${CARDINAL_LIB})

#     # target_link_libraries(${testName} UnitTest++)

#     #I like to move testing binaries into a testBin directory
#     set_target_properties(${testName} PROPERTIES
#         RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/testBin)

#     set_target_properties(${testName} PROPERTIES LINKER_LANGUAGE CXX)
#     #Finally add it to test execution -
#     #Notice the WORKING_DIRECTORY and COMMAND
#     add_test(NAME ${testName}
#                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin
#                 COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )

# endforeach(testSrc)