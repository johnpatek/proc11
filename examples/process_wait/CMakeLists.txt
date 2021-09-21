add_executable(parent parent_main.cpp)

add_executable(child child_main.cpp)

target_include_directories(parent PRIVATE ${PROC11_INCLUDE})

target_link_libraries(parent proc11)