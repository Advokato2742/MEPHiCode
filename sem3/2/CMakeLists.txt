cmake_minimum_required(VERSION 3.27)
project(main)

set(CMAKE_CXX_STANDARD 20)

add_executable(main
        main.cpp
        domino.cpp
        domino.h
        output.cpp
        output.h)