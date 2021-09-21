add_executable(parent_terminate parent_main.cpp)

add_executable(child_terminate child_main.cpp)

target_include_directories(parent_terminate PRIVATE ${PROC11_INCLUDE})

target_link_libraries(parent_terminate proc11)

target_include_directories(child_terminate PRIVATE ${PROC11_INCLUDE})

target_link_libraries(child_terminate proc11)

set_target_properties(parent_terminate PROPERTIES OUTPUT_NAME parent)

set_target_properties(child_terminate PROPERTIES OUTPUT_NAME child)