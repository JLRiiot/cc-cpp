cmake_minimum_required(VERSION 3.15)
project("Basic Library")

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STABDARD_REQUIRED ON)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ZLIB)
find_package(GTest)
find_package(cryptopp)
find_package(Boost)

message("Building with CMake version: ${CMAKE_VERSION}")

add_library(utils src/utils.h src/utils.cc)
add_library(cc-md5 src/cc-md5.h src/cc-md5.cc)
target_link_libraries(utils ZLIB::ZLIB gtest::gtest boost::boost)
target_link_libraries(cc-md5 gtest::gtest boost::boost)

add_executable(runme src/main.cc)
target_link_libraries(runme cc-md5)

# Coding challenge 1: https://codingchallenges.fyi/challenges/challenge-wc
add_library(ccwc-lib src/ccwc.h src/ccwc.cc)
target_link_libraries(ccwc-lib gtest::gtest boost::boost)
add_executable(ccwc src/ccwc-main.cc)
target_link_libraries(ccwc ccwc-lib boost::boost)

#tests configuration
enable_testing()
add_executable(
  # Test suite
  tests
  src/utils_tests.cc
)
target_link_libraries(tests utils)
target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)