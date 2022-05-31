cmake_minimum_required(VERSION 3.17.3)
project(shdProj)

set(CMAKE_CXX_STANDARD 17)

add_executable(shdProj main.cpp kvs.cpp SSTable.cpp Log.cpp)
