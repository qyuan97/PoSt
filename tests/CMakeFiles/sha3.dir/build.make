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
CMAKE_BINARY_DIR = /Users/xieqingyuan/code/PoSt

# Include any dependencies generated for this target.
include tests/CMakeFiles/sha3.dir/depend.make
# Include the progress variables for this target.
include tests/CMakeFiles/sha3.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/sha3.dir/flags.make

tests/CMakeFiles/sha3.dir/sha3.cpp.o: tests/CMakeFiles/sha3.dir/flags.make
tests/CMakeFiles/sha3.dir/sha3.cpp.o: tests/sha3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/xieqingyuan/code/PoSt/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/sha3.dir/sha3.cpp.o"
	cd /Users/xieqingyuan/code/PoSt/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sha3.dir/sha3.cpp.o -c /Users/xieqingyuan/code/PoSt/tests/sha3.cpp

tests/CMakeFiles/sha3.dir/sha3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sha3.dir/sha3.cpp.i"
	cd /Users/xieqingyuan/code/PoSt/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/xieqingyuan/code/PoSt/tests/sha3.cpp > CMakeFiles/sha3.dir/sha3.cpp.i

tests/CMakeFiles/sha3.dir/sha3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sha3.dir/sha3.cpp.s"
	cd /Users/xieqingyuan/code/PoSt/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/xieqingyuan/code/PoSt/tests/sha3.cpp -o CMakeFiles/sha3.dir/sha3.cpp.s

# Object files for target sha3
sha3_OBJECTS = \
"CMakeFiles/sha3.dir/sha3.cpp.o"

# External object files for target sha3
sha3_EXTERNAL_OBJECTS =

tests/sha3: tests/CMakeFiles/sha3.dir/sha3.cpp.o
tests/sha3: tests/CMakeFiles/sha3.dir/build.make
tests/sha3: tests/CMakeFiles/sha3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/xieqingyuan/code/PoSt/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sha3"
	cd /Users/xieqingyuan/code/PoSt/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sha3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/sha3.dir/build: tests/sha3
.PHONY : tests/CMakeFiles/sha3.dir/build

tests/CMakeFiles/sha3.dir/clean:
	cd /Users/xieqingyuan/code/PoSt/tests && $(CMAKE_COMMAND) -P CMakeFiles/sha3.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/sha3.dir/clean

tests/CMakeFiles/sha3.dir/depend:
	cd /Users/xieqingyuan/code/PoSt && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/xieqingyuan/code/PoSt /Users/xieqingyuan/code/PoSt/tests /Users/xieqingyuan/code/PoSt /Users/xieqingyuan/code/PoSt/tests /Users/xieqingyuan/code/PoSt/tests/CMakeFiles/sha3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/sha3.dir/depend

