cmake_minimum_required(VERSION 3.0)

project(Test)
include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/sciplot ${PROJECT_SOURCE_DIR}/SLAMTest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set (SOURCES Test.cpp Plotter.cpp SLAMTest/SLAMTest.cpp)
set (HEADERS Plotter.h GlobalTypes.h FileHandler.h SLAMTest/SLAMTest.h)



add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
