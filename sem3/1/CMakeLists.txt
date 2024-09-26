cmake_minimum_required(VERSION 3.27)
project(lav1_v2)

set(CMAKE_CXX_STANDARD 20)

include_directories(properties)
include_directories(ui)

add_executable(lav1_v2
        properties/properties.cpp
        properties/properties.h
        ui/ui.cpp
        ui/ui.h
        lab1.cpp)
