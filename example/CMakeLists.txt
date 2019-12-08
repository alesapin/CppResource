cmake_minimum_required(VERSION 3.3)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
set (CMAKE_CXX_STANDARD 17)

project(cpp_test)

# Add subdirectory wit hdifferent binary dir
# because we add parent directory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR}/cpp_resource)

set(TEST_SRCS main.cpp)
add_executable(test_resource ${TEST_SRCS})

target_include_directories(test_resource PRIVATE ${CPP_RESOURCE_INCLUDE_DIR})

add_resource(test_resource "f3" "${CMAKE_CURRENT_SOURCE_DIR}/textfiles/f3.txt")
add_resource(test_resource "f1" "${CMAKE_CURRENT_SOURCE_DIR}/textfiles/f1.txt")
add_resource(test_resource "f2" "${CMAKE_CURRENT_SOURCE_DIR}/textfiles/f2.txt")
add_resource(test_resource "f4" "${CMAKE_CURRENT_SOURCE_DIR}/textfiles/f4.txt")
