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
CMAKE_COMMAND = /snap/clion/61/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/61/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tootoot/CLionProjects/garbageCollector

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tootoot/CLionProjects/garbageCollector/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/garbageCollector.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/garbageCollector.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/garbageCollector.dir/flags.make

CMakeFiles/garbageCollector.dir/TestIterator.cpp.o: CMakeFiles/garbageCollector.dir/flags.make
CMakeFiles/garbageCollector.dir/TestIterator.cpp.o: ../TestIterator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tootoot/CLionProjects/garbageCollector/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/garbageCollector.dir/TestIterator.cpp.o"
	/usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/garbageCollector.dir/TestIterator.cpp.o -c /home/tootoot/CLionProjects/garbageCollector/TestIterator.cpp

CMakeFiles/garbageCollector.dir/TestIterator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/garbageCollector.dir/TestIterator.cpp.i"
	/usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tootoot/CLionProjects/garbageCollector/TestIterator.cpp > CMakeFiles/garbageCollector.dir/TestIterator.cpp.i

CMakeFiles/garbageCollector.dir/TestIterator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/garbageCollector.dir/TestIterator.cpp.s"
	/usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tootoot/CLionProjects/garbageCollector/TestIterator.cpp -o CMakeFiles/garbageCollector.dir/TestIterator.cpp.s

# Object files for target garbageCollector
garbageCollector_OBJECTS = \
"CMakeFiles/garbageCollector.dir/TestIterator.cpp.o"

# External object files for target garbageCollector
garbageCollector_EXTERNAL_OBJECTS =

garbageCollector: CMakeFiles/garbageCollector.dir/TestIterator.cpp.o
garbageCollector: CMakeFiles/garbageCollector.dir/build.make
garbageCollector: CMakeFiles/garbageCollector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tootoot/CLionProjects/garbageCollector/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable garbageCollector"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/garbageCollector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/garbageCollector.dir/build: garbageCollector

.PHONY : CMakeFiles/garbageCollector.dir/build

CMakeFiles/garbageCollector.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/garbageCollector.dir/cmake_clean.cmake
.PHONY : CMakeFiles/garbageCollector.dir/clean

CMakeFiles/garbageCollector.dir/depend:
	cd /home/tootoot/CLionProjects/garbageCollector/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tootoot/CLionProjects/garbageCollector /home/tootoot/CLionProjects/garbageCollector /home/tootoot/CLionProjects/garbageCollector/cmake-build-debug /home/tootoot/CLionProjects/garbageCollector/cmake-build-debug /home/tootoot/CLionProjects/garbageCollector/cmake-build-debug/CMakeFiles/garbageCollector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/garbageCollector.dir/depend

