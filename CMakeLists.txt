set(CMAKE_AUTOMOC ON)
cmake_minimum_required(VERSION 3.8)
project(GameOfLife LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -w -lSDL2 -lSDL2_image")

set(SOURCE_FILES main.cpp
        Timer.cpp
        Timer.h
        Window.cpp
        Window.h
        Grid.cpp
        Grid.h
        Canvas.cpp
        Canvas.h
        Utils.cpp OpenCLCanvas.cpp OpenCLCanvas.h CUDACanvas.cpp CUDACanvas.h CPUCanvas.cpp CPUCanvas.h)
#add_executable(GameOfLife ${SOURCE_FILES})

find_package(CUDA QUIET REQUIRED)
set(CUDA_SEPARABLE_COMPILATION ON)
set(CUDA_PROPAGATE_HOST_FLAGS OFF)

set( CUDA_FILES kernel.cu)
CUDA_COMPILE(CU_O ${CUDA_FILES})

find_package(OpenCL REQUIRED)

cuda_add_executable(GameOfLife ${SOURCE_FILES} ${CU_O})
#add_executable(JuegoDeLaDavi ${SOURCE_FILES})

target_link_libraries (GameOfLife OpenCL::OpenCL)
