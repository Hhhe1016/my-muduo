# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mycoder/myProjects/muduo-core

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mycoder/myProjects/muduo-core/build

# Include any dependencies generated for this target.
include example/CMakeFiles/testserver.dir/depend.make

# Include the progress variables for this target.
include example/CMakeFiles/testserver.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/testserver.dir/flags.make

example/CMakeFiles/testserver.dir/testserver.cc.o: example/CMakeFiles/testserver.dir/flags.make
example/CMakeFiles/testserver.dir/testserver.cc.o: ../example/testserver.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mycoder/myProjects/muduo-core/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/testserver.dir/testserver.cc.o"
	cd /home/mycoder/myProjects/muduo-core/build/example && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testserver.dir/testserver.cc.o -c /home/mycoder/myProjects/muduo-core/example/testserver.cc

example/CMakeFiles/testserver.dir/testserver.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testserver.dir/testserver.cc.i"
	cd /home/mycoder/myProjects/muduo-core/build/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mycoder/myProjects/muduo-core/example/testserver.cc > CMakeFiles/testserver.dir/testserver.cc.i

example/CMakeFiles/testserver.dir/testserver.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testserver.dir/testserver.cc.s"
	cd /home/mycoder/myProjects/muduo-core/build/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mycoder/myProjects/muduo-core/example/testserver.cc -o CMakeFiles/testserver.dir/testserver.cc.s

# Object files for target testserver
testserver_OBJECTS = \
"CMakeFiles/testserver.dir/testserver.cc.o"

# External object files for target testserver
testserver_EXTERNAL_OBJECTS =

../example/testserver: example/CMakeFiles/testserver.dir/testserver.cc.o
../example/testserver: example/CMakeFiles/testserver.dir/build.make
../example/testserver: ../lib/libmuduo_core.so
../example/testserver: example/CMakeFiles/testserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mycoder/myProjects/muduo-core/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../example/testserver"
	cd /home/mycoder/myProjects/muduo-core/build/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/testserver.dir/build: ../example/testserver

.PHONY : example/CMakeFiles/testserver.dir/build

example/CMakeFiles/testserver.dir/clean:
	cd /home/mycoder/myProjects/muduo-core/build/example && $(CMAKE_COMMAND) -P CMakeFiles/testserver.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/testserver.dir/clean

example/CMakeFiles/testserver.dir/depend:
	cd /home/mycoder/myProjects/muduo-core/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mycoder/myProjects/muduo-core /home/mycoder/myProjects/muduo-core/example /home/mycoder/myProjects/muduo-core/build /home/mycoder/myProjects/muduo-core/build/example /home/mycoder/myProjects/muduo-core/build/example/CMakeFiles/testserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/testserver.dir/depend

