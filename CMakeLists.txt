cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(cube)

# Libraries.
add_library(cube cube.cc)
add_library(cube_state cube_state.cc)
add_library(instruction instruction.cc)
add_library(util util.cc)

# Testing OpenGL...
add_definitions(-Wno-deprecated-declarations)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
set(INCLUDE_DIRS ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
set(LIBRARIES ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
include_directories(${INCLUDE_DIRS})
add_executable(main main.cc)
target_link_libraries(main ${LIBRARIES})

# Tests.
enable_testing()
add_executable(tests cube_test.cc cube_state_test.cc instruction_test.cc
                     util_test.cc)
find_package(GTest REQUIRED)
include(GoogleTest)
target_link_libraries(
  tests
  GTest::GTest
  GTest::Main
  cube
  cube_state
  instruction
  util)
gtest_discover_tests(tests)
