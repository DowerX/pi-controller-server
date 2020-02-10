cmake_minimum_required(VERSION 3.12)
project(controller VERSION 1.0.0)

add_executable(controller_server main.cpp)

find_library(wiringPi_LIB wiringPi)
target_link_libraries(controller_server ${wiringPi_LIB})

find_package(Boost REQUIRED COMPONENTS system thread regex)
include_directories(${Boost_INCLUDEDIR})
link_directories(${Boost_LIBRARYDIR})
target_link_libraries(controller_server ${Boost_LIBRARIES})
