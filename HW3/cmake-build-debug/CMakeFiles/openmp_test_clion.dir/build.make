# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "/Users/brady.bodily/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/202.6948.80/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/brady.bodily/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/202.6948.80/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/brady.bodily/Documents/CS5890_High_Performance_Computing/HW3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/brady.bodily/Documents/CS5890_High_Performance_Computing/HW3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/openmp_test_clion.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/openmp_test_clion.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/openmp_test_clion.dir/flags.make

CMakeFiles/openmp_test_clion.dir/main.cpp.o: CMakeFiles/openmp_test_clion.dir/flags.make
CMakeFiles/openmp_test_clion.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/brady.bodily/Documents/CS5890_High_Performance_Computing/HW3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/openmp_test_clion.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/openmp_test_clion.dir/main.cpp.o -c /Users/brady.bodily/Documents/CS5890_High_Performance_Computing/HW3/main.cpp

CMakeFiles/openmp_test_clion.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/openmp_test_clion.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/brady.bodily/Documents/CS5890_High_Performance_Computing/HW3/main.cpp > CMakeFiles/openmp_test_clion.dir/main.cpp.i

CMakeFiles/openmp_test_clion.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/openmp_test_clion.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/brady.bodily/Documents/CS5890_High_Performance_Computing/HW3/main.cpp -o CMakeFiles/openmp_test_clion.dir/main.cpp.s

# Object files for target openmp_test_clion
openmp_test_clion_OBJECTS = \
"CMakeFiles/openmp_test_clion.dir/main.cpp.o"

# External object files for target openmp_test_clion
openmp_test_clion_EXTERNAL_OBJECTS =

openmp_test_clion: CMakeFiles/openmp_test_clion.dir/main.cpp.o
openmp_test_clion: CMakeFiles/openmp_test_clion.dir/build.make
openmp_test_clion: CMakeFiles/openmp_test_clion.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/brady.bodily/Documents/CS5890_High_Performance_Computing/HW3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable openmp_test_clion"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/openmp_test_clion.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/openmp_test_clion.dir/build: openmp_test_clion

.PHONY : CMakeFiles/openmp_test_clion.dir/build

CMakeFiles/openmp_test_clion.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/openmp_test_clion.dir/cmake_clean.cmake
.PHONY : CMakeFiles/openmp_test_clion.dir/clean

CMakeFiles/openmp_test_clion.dir/depend:
	cd /Users/brady.bodily/Documents/CS5890_High_Performance_Computing/HW3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/brady.bodily/Documents/CS5890_High_Performance_Computing/HW3 /Users/brady.bodily/Documents/CS5890_High_Performance_Computing/HW3 /Users/brady.bodily/Documents/CS5890_High_Performance_Computing/HW3/cmake-build-debug /Users/brady.bodily/Documents/CS5890_High_Performance_Computing/HW3/cmake-build-debug /Users/brady.bodily/Documents/CS5890_High_Performance_Computing/HW3/cmake-build-debug/CMakeFiles/openmp_test_clion.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/openmp_test_clion.dir/depend

