file(GLOB PROC11_SOURCES "*.cpp")

add_library(proc11 STATIC ${PROC11_SOURCES})

target_include_directories(proc11 PUBLIC ${PROC11_INCLUDE})

target_link_libraries(proc11 ${PTHREAD} dl)