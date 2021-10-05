cmake_minimum_required(VERSION 3.0)

project(Test)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set (SOURCES Test.cpp Plotter.cpp)
set (HEADER_FILES Plotter.h GlobalTypes.h FileHandler.h)
include_directories(${PROJECT_SOURCE_DIR}/sciplot)


add_executable(${PROJECT_NAME} Test.cpp Plotter.cpp)
