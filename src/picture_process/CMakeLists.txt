cmake_minimum_required(VERSION 3.1)

PROJECT(picture_process CXX)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS})
include_directories( ${OpenCV_INCLUDE_DIRS})

add_library(picture_process SHARED
  image_filter.h
  image_filter.cpp
  layer_parser.cpp
  layer_parser.h
  contour_finder.h
  contour_finder.cpp
  )

target_link_libraries(picture_process ${OpenCV_LIBS} spdlog)

ADD_EXECUTABLE(test_filters tests/test_filters.cpp)
target_link_libraries(test_filters picture_process)
ADD_TEST(NAME test_filters COMMAND test_filters)

ADD_EXECUTABLE(test_layer_parser tests/test_layer_parser.cpp)
target_link_libraries(test_layer_parser picture_process)
ADD_TEST(NAME test_layer_parser COMMAND test_layer_parser)

ADD_EXECUTABLE(test_contours_finder tests/test_contour_finder.cpp)
target_link_libraries(test_contours_finder picture_process)
ADD_TEST(NAME test_contours_finder COMMAND test_contours_finder)
