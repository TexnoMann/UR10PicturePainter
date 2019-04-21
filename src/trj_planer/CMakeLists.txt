cmake_minimum_required(VERSION 3.1D)

PROJECT(trj_planer CXX)

add_library(trj_planer SHARED
  trj_planer.h
  trj_planer.cpp
  )

  target_link_libraries(trj_planer spdlog Eigen3::Eigen)

  ADD_EXECUTABLE(test_trj_planer tests/test_trj_planer.cpp)
  target_link_libraries(test_trj_planer trj_planer)
  ADD_TEST(NAME test_trj_planer COMMAND test_trj_planer)
