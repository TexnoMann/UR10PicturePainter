cmake_minimum_required(VERSION 3.1D)

PROJECT(tests_program CXX)

  ADD_EXECUTABLE(test_json_writer test_json_writer.cpp)
  target_link_libraries(test_json_writer jsoncpp)
