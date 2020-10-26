cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(cube)

# Libraries.
add_library(instruction instruction.cc)
add_library(util util.cc)
add_library(cube cube.cc)
target_link_libraries(cube util instruction)
add_library(cube_state cube_state.cc)

add_library(renderer renderer.cc)
find_package(PNGwriter REQUIRED)
if(PNGwriter_FOUND)
  target_link_libraries(renderer PRIVATE PNGwriter::PNGwriter cube_state)
endif(PNGwriter_FOUND)

# Main: just for demostrating our libraries.
add_executable(main main.cc)
target_link_libraries(main PRIVATE PNGwriter::PNGwriter cube cube_state
                                   renderer)

# Tests.
enable_testing()
add_executable(tests cube_test.cc cube_state_test.cc instruction_test.cc
                     util_test.cc renderer_test.cc)
find_package(GTest REQUIRED)
include(GoogleTest)
target_link_libraries(
  tests
  GTest::GTest
  GTest::Main
  cube
  cube_state
  instruction
  util
  renderer)
gtest_discover_tests(tests)
