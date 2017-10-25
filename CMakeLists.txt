cmake_minimum_required(VERSION 3.8)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -w -lSDL2 -lSDL2_image ")

set(SOURCE_FILES main.cpp
        Timer.cpp
        Timer.h
        Window.cpp
        Window.h
        Grid.cpp
        Grid.h
        Canvas.cpp
        Canvas.h
        Utils.cpp)
add_executable(GameOfLife ${SOURCE_FILES})