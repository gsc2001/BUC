cmake_minimum_required(VERSION 3.21)
project(BUC)

set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCE_FILES ${SRC_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
