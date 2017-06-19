cmake_minimum_required(VERSION 3.7)
project(udpStockClient)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(udpStockClient ${SOURCE_FILES})