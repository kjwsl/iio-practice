cmake_minimum_required(VERSION 3.22)
project(iio-practice)

include_directories(${PROJECT_SOURCE_DIR}/src/include)

add_subdirectory(src)
add_subdirectory(test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare (
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)

FetchContent_MakeAvailable(googletest)

enable_testing()
