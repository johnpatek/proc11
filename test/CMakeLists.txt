set(GTEST_INCLUDE ${CMAKE_SOURCE_DIR}/extern/googletest/googletest/include)
set(GTEST_LIB gtest)
set(GTEST_MAIN_LIB gtest_main)

file(GLOB SOURCES *.cpp)

add_executable(unittest ${SOURCES})
target_include_directories(unittest PRIVATE ${GTEST_INCLUDE} ${PROC11_INCLUDE})
target_link_libraries(unittest proc11 ${GTEST_LIB} ${GTEST_MAIN_LIB} ${PTHREAD} ${DL})

add_executable(signaler children/signaler.cpp)
target_include_directories(signaler PRIVATE ${PROC11_INCLUDE})
target_link_libraries(signaler proc11 ${PTHREAD} ${DL})

add_executable(arg_logger children/arg_logger.cpp)
target_include_directories(arg_logger PRIVATE ${PROC11_INCLUDE})
target_link_libraries(arg_logger proc11 ${PTHREAD} ${DL})