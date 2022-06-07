cmake_minimum_required(VERSION 3.17.3)
project(ShdProj)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp)
add_executable(KVS_run ${SOURCE_FILES})

include_directories(KVS_lib)
add_subdirectory(KVS_lib)

target_link_libraries(KVS_run KVS_lib)

add_subdirectory(Google_tests)
