cmake_minimum_required(VERSION 3.10)

project(CoincMatchTemplate)

find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(CoincMatchProc Source/devel.cpp)
    install(TARGETS CoincMatchProc 
        DESTINATION ${PROJECT_SOURCE_DIR}/Devel/)     
elseif(CMAKE_BUILD_TYPE STREQUAL "Releas")
    add_executable(CoincMatchProc Source/main.cpp)
    install(TARGETS CoincMatchProc 
        DESTINATION ${PROJECT_BINARY_DIR}) 
endif()

add_compile_definitions(NOT_ROOT_USE=true)

target_link_libraries(CoincMatchProc CoincMatch Filter Hist GenLib INI_File)
target_link_libraries(CoincMatchProc -static)


target_include_directories(CoincMatchProc PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Source/"                     
                          )

add_subdirectory(Source)
add_subdirectory(Source/ClusterProc/Source)
add_subdirectory(Source/Hist/Source)
add_subdirectory(Source/Hist/Source/INI_File/Source)
add_subdirectory(Source/Hist/Source/INI_File/Source/GenLib/Source)
add_subdirectory(Source/Filter/Source/)
