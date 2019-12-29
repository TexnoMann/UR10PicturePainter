cmake_minimum_required(VERSION 3.1)

project(property_manager CXX)

add_library(${PROJECT_NAME} SHARED
	property_manager.cpp
	property_manager.h)
target_link_libraries(${PROJECT_NAME}
	${Boost_LIBRARIES}
)