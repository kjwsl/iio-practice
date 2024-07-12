# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ray/code/iio-practice/cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ray/code/iio-practice/cpp/build

# Include any dependencies generated for this target.
include test/CMakeFiles/MyTests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/MyTests.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/MyTests.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/MyTests.dir/flags.make

test/CMakeFiles/MyTests.dir/test_nmea_parser.cpp.o: test/CMakeFiles/MyTests.dir/flags.make
test/CMakeFiles/MyTests.dir/test_nmea_parser.cpp.o: ../test/test_nmea_parser.cpp
test/CMakeFiles/MyTests.dir/test_nmea_parser.cpp.o: test/CMakeFiles/MyTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ray/code/iio-practice/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/MyTests.dir/test_nmea_parser.cpp.o"
	cd /home/ray/code/iio-practice/cpp/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/MyTests.dir/test_nmea_parser.cpp.o -MF CMakeFiles/MyTests.dir/test_nmea_parser.cpp.o.d -o CMakeFiles/MyTests.dir/test_nmea_parser.cpp.o -c /home/ray/code/iio-practice/cpp/test/test_nmea_parser.cpp

test/CMakeFiles/MyTests.dir/test_nmea_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyTests.dir/test_nmea_parser.cpp.i"
	cd /home/ray/code/iio-practice/cpp/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ray/code/iio-practice/cpp/test/test_nmea_parser.cpp > CMakeFiles/MyTests.dir/test_nmea_parser.cpp.i

test/CMakeFiles/MyTests.dir/test_nmea_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyTests.dir/test_nmea_parser.cpp.s"
	cd /home/ray/code/iio-practice/cpp/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ray/code/iio-practice/cpp/test/test_nmea_parser.cpp -o CMakeFiles/MyTests.dir/test_nmea_parser.cpp.s

# Object files for target MyTests
MyTests_OBJECTS = \
"CMakeFiles/MyTests.dir/test_nmea_parser.cpp.o"

# External object files for target MyTests
MyTests_EXTERNAL_OBJECTS =

test/MyTests: test/CMakeFiles/MyTests.dir/test_nmea_parser.cpp.o
test/MyTests: test/CMakeFiles/MyTests.dir/build.make
test/MyTests: libGnssLibrary.a
test/MyTests: lib/libgtest.a
test/MyTests: lib/libgtest_main.a
test/MyTests: lib/libgtest.a
test/MyTests: test/CMakeFiles/MyTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ray/code/iio-practice/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MyTests"
	cd /home/ray/code/iio-practice/cpp/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyTests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/MyTests.dir/build: test/MyTests
.PHONY : test/CMakeFiles/MyTests.dir/build

test/CMakeFiles/MyTests.dir/clean:
	cd /home/ray/code/iio-practice/cpp/build/test && $(CMAKE_COMMAND) -P CMakeFiles/MyTests.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/MyTests.dir/clean

test/CMakeFiles/MyTests.dir/depend:
	cd /home/ray/code/iio-practice/cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ray/code/iio-practice/cpp /home/ray/code/iio-practice/cpp/test /home/ray/code/iio-practice/cpp/build /home/ray/code/iio-practice/cpp/build/test /home/ray/code/iio-practice/cpp/build/test/CMakeFiles/MyTests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/MyTests.dir/depend

