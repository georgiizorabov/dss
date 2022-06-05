cmake_minimum_required(VERSION 3.17.3)
project(shdProj)

set(CMAKE_CXX_STANDARD 17)


set(SOURCE_FILES main.cpp)
add_executable(run ${SOURCE_FILES})

include_directories(KVS)
add_subdirectory(KVS)

target_link_libraries(run KVS)

add_subdirectory(Google_tests)

