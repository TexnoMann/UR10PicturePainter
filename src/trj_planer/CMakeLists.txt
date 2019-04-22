cmake_minimum_required(VERSION 3.1)

PROJECT(trj_planer CXX)

add_library(trj_planer SHARED
  trj_planer.h
  trj_planer.cpp
)

target_link_libraries(trj_planer spdlog Eigen3::Eigen property_manager)

add_executable(test_trj_planer tests/test_trj_planer.cpp)
target_link_libraries(test_trj_planer trj_planer)
add_test(NAME test_trj_planer COMMAND test_trj_planer)
