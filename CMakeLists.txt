cmake_minimum_required(VERSION 2.8)
project(CFPMM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE SOURCE_FILES
    "src/*.hpp"
    "src/*.h"
    "src/*.cpp"
    "src/*.c"
)

add_executable(CFPMM ${SOURCE_FILES})

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

target_link_libraries(CFPMM)
