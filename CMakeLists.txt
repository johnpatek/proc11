
cmake_minimum_required(VERSION 3.0)

project(proc11)

if(WIN32)
    set(PTHREAD "")
else()
    set(CMAKE_CXX_FLAGS  "-std=c++14")
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)    
    set(PTHREAD Threads::Threads)
endif(WIN32)

set(PROC11_INCLUDE ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

add_subdirectory(examples)