# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/charInputTest"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/charInputTest/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/charInputTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/charInputTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/charInputTest.dir/flags.make

CMakeFiles/charInputTest.dir/main.cpp.o: CMakeFiles/charInputTest.dir/flags.make
CMakeFiles/charInputTest.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/charInputTest/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/charInputTest.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/charInputTest.dir/main.cpp.o -c "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/charInputTest/main.cpp"

CMakeFiles/charInputTest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/charInputTest.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/charInputTest/main.cpp" > CMakeFiles/charInputTest.dir/main.cpp.i

CMakeFiles/charInputTest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/charInputTest.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/charInputTest/main.cpp" -o CMakeFiles/charInputTest.dir/main.cpp.s

# Object files for target charInputTest
charInputTest_OBJECTS = \
"CMakeFiles/charInputTest.dir/main.cpp.o"

# External object files for target charInputTest
charInputTest_EXTERNAL_OBJECTS =

charInputTest: CMakeFiles/charInputTest.dir/main.cpp.o
charInputTest: CMakeFiles/charInputTest.dir/build.make
charInputTest: CMakeFiles/charInputTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/charInputTest/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable charInputTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/charInputTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/charInputTest.dir/build: charInputTest

.PHONY : CMakeFiles/charInputTest.dir/build

CMakeFiles/charInputTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/charInputTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/charInputTest.dir/clean

CMakeFiles/charInputTest.dir/depend:
	cd "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/charInputTest/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/charInputTest" "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/charInputTest" "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/charInputTest/cmake-build-debug" "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/charInputTest/cmake-build-debug" "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/charInputTest/cmake-build-debug/CMakeFiles/charInputTest.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/charInputTest.dir/depend

