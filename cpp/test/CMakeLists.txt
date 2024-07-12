file(GLOB TEST_SOURCES "test_*.cpp")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(MyTests ${TEST_SOURCES})

target_link_libraries(MyTests GnssLibrary gtest gtest_main)

enable_testing()
add_test(NAME MyTests COMMAND MyTests)
