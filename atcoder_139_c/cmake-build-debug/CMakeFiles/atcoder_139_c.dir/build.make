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
CMAKE_SOURCE_DIR = "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/atcoder_139_c"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/atcoder_139_c/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/atcoder_139_c.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/atcoder_139_c.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/atcoder_139_c.dir/flags.make

CMakeFiles/atcoder_139_c.dir/main.cpp.o: CMakeFiles/atcoder_139_c.dir/flags.make
CMakeFiles/atcoder_139_c.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/atcoder_139_c/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/atcoder_139_c.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/atcoder_139_c.dir/main.cpp.o -c "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/atcoder_139_c/main.cpp"

CMakeFiles/atcoder_139_c.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atcoder_139_c.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/atcoder_139_c/main.cpp" > CMakeFiles/atcoder_139_c.dir/main.cpp.i

CMakeFiles/atcoder_139_c.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atcoder_139_c.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/atcoder_139_c/main.cpp" -o CMakeFiles/atcoder_139_c.dir/main.cpp.s

# Object files for target atcoder_139_c
atcoder_139_c_OBJECTS = \
"CMakeFiles/atcoder_139_c.dir/main.cpp.o"

# External object files for target atcoder_139_c
atcoder_139_c_EXTERNAL_OBJECTS =

atcoder_139_c: CMakeFiles/atcoder_139_c.dir/main.cpp.o
atcoder_139_c: CMakeFiles/atcoder_139_c.dir/build.make
atcoder_139_c: CMakeFiles/atcoder_139_c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/atcoder_139_c/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable atcoder_139_c"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/atcoder_139_c.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/atcoder_139_c.dir/build: atcoder_139_c

.PHONY : CMakeFiles/atcoder_139_c.dir/build

CMakeFiles/atcoder_139_c.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/atcoder_139_c.dir/cmake_clean.cmake
.PHONY : CMakeFiles/atcoder_139_c.dir/clean

CMakeFiles/atcoder_139_c.dir/depend:
	cd "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/atcoder_139_c/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/atcoder_139_c" "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/atcoder_139_c" "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/atcoder_139_c/cmake-build-debug" "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/atcoder_139_c/cmake-build-debug" "/Users/son-wonhui/OneDrive - inu.ac.kr/CLionProjects/ProblemSolvings/atcoder_139_c/cmake-build-debug/CMakeFiles/atcoder_139_c.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/atcoder_139_c.dir/depend
