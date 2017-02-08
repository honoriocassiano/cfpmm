cmake_minimum_required(VERSION 2.8)
project(CFPMM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread")

file(GLOB_RECURSE SOURCE_FILES
    "src/*.hpp"
    "src/*.h"
    "src/*.cpp"
    "src/*.c"
)

find_package(Threads REQUIRED)

add_executable(cfpmm ${SOURCE_FILES})

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(PUBLIC my_app "-pthread")
endif()

if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(cfpmm "${CMAKE_THREAD_LIBS_INIT}")
endif()

target_link_libraries(cfpmm)
