cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project("C++ Quickstart")

SET(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hello main.cc)