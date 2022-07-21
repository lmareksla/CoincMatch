cmake_minimum_required(VERSION 3.10)

add_compile_definitions(NOT_ROOT_USE=true)

add_library(CoincMatch STATIC CoincMatch.cpp Elist.cpp GF.cpp)

target_include_directories(CoincMatch PUBLIC
                           "${CMAKE_CURRENT_SOURCE_DIR}"
                           "${CMAKE_CURRENT_SOURCE_DIR}/Filter/Source/"
                           "${CMAKE_CURRENT_SOURCE_DIR}/Hist/Source/"    
                           "${CMAKE_CURRENT_SOURCE_DIR}/Hist/Source/INI_File/"        
                           "${CMAKE_CURRENT_SOURCE_DIR}/Hist/Source/INI_File/Source/GenLib/"                                                                                                                                                                             
                           )

target_link_libraries(CoincMatch Filter Hist GenLib INI_File)

install(TARGETS CoincMatch
LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/lib/
ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/lib/)