cmake_minimum_required(VERSION 3.22)
project(iio-practice)

file(GLOB SOURCES "*.cpp")
add_library(GnssLibrary ${SOURCES})
include_directories(GnssLibrary PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
