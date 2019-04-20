cmake_minimum_required(VERSION 3.1D)

PROJECT(kinematic_solver CXX)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS})
include_directories( ${OpenCV_INCLUDE_DIRS})

add_library(kinematic_solver SHARED
  ur10_kinematic.h
  ur10_kinematic.cpp
  )

#target_link_libraries(kinematic_solver ${OpenCV_LIBS} spdlog Eigen3::Eigen)
