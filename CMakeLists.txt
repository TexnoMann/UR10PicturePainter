cmake_minimum_required(VERSION 3.1)

project(picture_painter CXX)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(Eigen3 REQUIRED Core)
include_directories(${EIGEN3_INCLUDE_DIRS})
find_package(Boost 1.54.0 COMPONENTS serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(src/picture_process)
add_subdirectory(src/property_manager)
add_subdirectory(src/trj_planer)
add_subdirectory(src/util/spdlog)
