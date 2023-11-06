cmake_minimum_required(VERSION 3.27.0)
project(search VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR})

set(SOURCE
  ${CMAKE_SOURCE_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE})

# Google Test setup
set(TEST_PROJECT_NAME test_${PROJECT_NAME})
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/googletest)

set(TEST_FILES
  ${CMAKE_SOURCE_DIR}/test/test_avl.cpp
)
add_executable(${TEST_PROJECT_NAME} ${TEST_FILES})
target_link_libraries(${TEST_PROJECT_NAME} gtest gtest_main)

# Enable testing
enable_testing()
add_test(NAME test_avl COMMAND ${TEST_PROJECT_NAME} --gtest_filter=AVLTreeTest.*)
