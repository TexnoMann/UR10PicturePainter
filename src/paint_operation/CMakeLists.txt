cmake_minimum_required(VERSION 3.1D)

PROJECT(paint_operation CXX)

cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -lstdc++fs -Wall")
set(CMAKE_CXX_STANDARD 17)


include_directories(util/fast-cpp-csv-parser)

ADD_EXECUTABLE(draw_csv draw_csv.cpp)
set_property(TARGET draw_csv PROPERTY CXX_STANDARD 17)
target_link_libraries(draw_csv spdlog ur_rtde::rtde stdc++fs)
