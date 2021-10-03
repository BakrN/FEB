cmake_minimum_required(VERSION 3.0)

project(Test)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(${PROJECT_SOURCE_DIR}/sciplot)


add_executable(${PROJECT_NAME} Test.cpp Plotter.cpp)
