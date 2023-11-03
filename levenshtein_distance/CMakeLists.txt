cmake_minimum_required(VERSION 3.27.0)
project(levenshtein VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE
  ${CMAKE_SOURCE_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE})
