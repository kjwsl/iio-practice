file(GLOB TEST_SOURCES "test_gnss_listener.cpp")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(MyTests ${TEST_SOURCES})

include(FetchContent)
FetchContent_Declare (
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)

FetchContent_MakeAvailable(googletest)

target_link_libraries(MyTests GnssLibrary gtest gtest_main)

enable_testing()
add_test(NAME MyTests COMMAND MyTests)
