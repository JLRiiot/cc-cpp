cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project("Basic Library")

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STABDARD_REQUIRED ON)

add_library(utils utils.h utils.cc)

add_executable(runme main.cc)
target_link_libraries(runme utils)
