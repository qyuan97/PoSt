# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/xieqingyuan/code/PoSt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/xieqingyuan/code/PoSt/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/sha3.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/sha3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sha3.dir/flags.make

CMakeFiles/sha3.dir/sha3.cpp.o: CMakeFiles/sha3.dir/flags.make
CMakeFiles/sha3.dir/sha3.cpp.o: ../sha3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/xieqingyuan/code/PoSt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sha3.dir/sha3.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sha3.dir/sha3.cpp.o -c /Users/xieqingyuan/code/PoSt/sha3.cpp

CMakeFiles/sha3.dir/sha3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sha3.dir/sha3.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/xieqingyuan/code/PoSt/sha3.cpp > CMakeFiles/sha3.dir/sha3.cpp.i

CMakeFiles/sha3.dir/sha3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sha3.dir/sha3.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/xieqingyuan/code/PoSt/sha3.cpp -o CMakeFiles/sha3.dir/sha3.cpp.s

# Object files for target sha3
sha3_OBJECTS = \
"CMakeFiles/sha3.dir/sha3.cpp.o"

# External object files for target sha3
sha3_EXTERNAL_OBJECTS =

sha3: CMakeFiles/sha3.dir/sha3.cpp.o
sha3: CMakeFiles/sha3.dir/build.make
sha3: CMakeFiles/sha3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/xieqingyuan/code/PoSt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sha3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sha3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sha3.dir/build: sha3
.PHONY : CMakeFiles/sha3.dir/build

CMakeFiles/sha3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sha3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sha3.dir/clean

CMakeFiles/sha3.dir/depend:
	cd /Users/xieqingyuan/code/PoSt/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/xieqingyuan/code/PoSt /Users/xieqingyuan/code/PoSt /Users/xieqingyuan/code/PoSt/cmake-build-debug /Users/xieqingyuan/code/PoSt/cmake-build-debug /Users/xieqingyuan/code/PoSt/cmake-build-debug/CMakeFiles/sha3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sha3.dir/depend

