cmake_minimum_required(VERSION 3.1)

project(tests_program CXX)

add_executable(test_json_writer test_json_writer.cpp)
target_link_libraries(test_json_writer jsoncpp)