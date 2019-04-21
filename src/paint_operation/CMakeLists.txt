cmake_minimum_required(VERSION 3.1D)

PROJECT(paint_operation CXX)

add_library(paint_operation SHARED
  trj_planer.h
  trj_planer.cpp
  )

  target_link_libraries(paint_operation spdlog Eigen3::Eigen)

  ADD_EXECUTABLE(paint_opration tests/test_trj_planer.cpp)
  target_link_libraries(paint_operation trj_planer)
  ADD_TEST(NAME test_paint_operation COMMAND test_paint_operation)
