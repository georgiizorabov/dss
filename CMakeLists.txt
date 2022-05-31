cmake_minimum_required(VERSION 3.22)
project(shdProj)

set(CMAKE_CXX_STANDARD 17)

add_executable(shdProj main.cpp kvs.cpp SSTable.cpp fileHandler.cpp)
