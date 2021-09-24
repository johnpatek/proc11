set(GTEST_INCLUDE ${CMAKE_SOURCE_DIR}/extern/googletest/googletest/include)
set(GTEST_LIB gtest)
set(GTEST_MAIN_LIB gtest_main)

file(GLOB SOURCES *.cpp)

add_executable(unittest ${SOURCES})
target_include_directories(unittest PRIVATE ${GTEST_INCLUDE} ${PROC11_INCLUDE})
target_link_libraries(unittest proc11 ${GTEST_LIB} ${GTEST_MAIN_LIB} ${PTHREAD} ${DL})