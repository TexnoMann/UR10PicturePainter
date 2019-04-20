cmake_minimum_required(3.1 REQUIRED)

PROJECT(kinematic_solver CXX)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS})
include_directories( ${OpenCV_INCLUDE_DIRS})

add_library(picture_process SHARED
  image_filter.h
  image_filter.cpp
  )

target_link_libraries(picture_process ${OpenCV_LIBS} spdlog)

ADD_EXECUTABLE(test_filters tests/test_filters.cpp)
target_link_libraries(test_filters picture_process)
ADD_TEST(NAME test_filters COMMAND test_filters)
