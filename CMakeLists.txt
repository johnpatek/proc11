
cmake_minimum_required(VERSION 3.0)

project(proc11)

if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(PTHREAD "")
    set(DL "")
else()
    set(CMAKE_CXX_FLAGS  "-std=c++14")
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)    
    set(PTHREAD Threads::Threads)
    set(DL dl)
endif(WIN32)

set(PROC11_INCLUDE ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

#add_subdirectory(examples)

add_subdirectory(extern)

add_subdirectory(test)
