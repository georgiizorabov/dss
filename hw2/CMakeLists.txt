cmake_minimum_required(VERSION 3.21)
project(hw2)

set(CMAKE_CXX_STANDARD 98)
include_directories(zstd/examples)
add_executable(hw2 zstdCompress.cpp)
add_executable(hw2 lz4Compress.cpp)
target_link_directories(hw2 PUBLIC zstd/lib/compress zstd/lib/decompress zstd/examples)
