cmake_minimum_required(VERSION 3.10)

add_compile_definitions(NOT_ROOT_USE=true)

add_library(CoincMatch STATIC CoincMatch.cpp)

target_include_directories(CoincMatch PUBLIC
                           "${CMAKE_CURRENT_SOURCE_DIR}"
                           "${CMAKE_CURRENT_SOURCE_DIR}/Filter/Source/"
                           )

target_link_libraries(CoincMatch Hist Filter GenLib INI_File)

install(TARGETS CoincMatch
LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/lib/
ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/lib/)