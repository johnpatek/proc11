
cmake_minimum_required(VERSION 3.0)

project(proc11)

if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(PTHREAD "")
    set(DL "")
else()
    set(CMAKE_CXX_FLAGS  "-std=c++14 -Werror -Wall -Wextra -O3")
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)    
    set(PTHREAD Threads::Threads)
    set(DL dl)
    #add_subdirectory(examples)
endif(WIN32)

set(PROC11_INCLUDE ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

add_subdirectory(extern)

add_subdirectory(test)
