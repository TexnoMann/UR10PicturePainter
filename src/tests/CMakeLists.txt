cmake_minimum_required(VERSION 3.1)

project(tests_program CXX)

add_executable(test_json_writer test_json_writer.cpp)
target_link_libraries(test_json_writer jsoncpp)

add_executable(test_ctrl test_ctrl.cpp)
target_link_libraries(test_ctrl PUBLIC ur_rtde::rtde)

add_executable(test_cart test_ctrl_C.cpp)
target_link_libraries(test_cart PUBLIC ur_rtde::rtde)
