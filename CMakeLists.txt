cmake_minimum_required(VERSION 3.15)
project("Basic Library")

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STABDARD_REQUIRED ON)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ZLIB)
find_package(GTest)

message("Building with CMake version: ${CMAKE_VERSION}")

add_library(utils src/utils.h src/utils.cc)
target_link_libraries(utils ZLIB::ZLIB gtest::gtest)

add_executable(runme src/main.cc)
target_link_libraries(runme utils)

enable_testing()
add_executable(
  # Test suite
  tests
  src/main_tests.cc
)
target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)