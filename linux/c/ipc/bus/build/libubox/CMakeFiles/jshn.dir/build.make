# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/local/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tangshishan/tmp/misc/linux/c/ipc/bus

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tangshishan/tmp/misc/linux/c/ipc/bus/build

# Include any dependencies generated for this target.
include libubox/CMakeFiles/jshn.dir/depend.make

# Include the progress variables for this target.
include libubox/CMakeFiles/jshn.dir/progress.make

# Include the compile flags for this target's objects.
include libubox/CMakeFiles/jshn.dir/flags.make

libubox/CMakeFiles/jshn.dir/jshn.c.o: libubox/CMakeFiles/jshn.dir/flags.make
libubox/CMakeFiles/jshn.dir/jshn.c.o: ../libubox/jshn.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tangshishan/tmp/misc/linux/c/ipc/bus/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object libubox/CMakeFiles/jshn.dir/jshn.c.o"
	cd /home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox && /home/tangshishan/arm-himix200-linux/bin/arm-himix200-linux-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/jshn.dir/jshn.c.o   -c /home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/jshn.c

libubox/CMakeFiles/jshn.dir/jshn.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/jshn.dir/jshn.c.i"
	cd /home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox && /home/tangshishan/arm-himix200-linux/bin/arm-himix200-linux-gcc  $(C_DEFINES) $(C_FLAGS) -E /home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/jshn.c > CMakeFiles/jshn.dir/jshn.c.i

libubox/CMakeFiles/jshn.dir/jshn.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/jshn.dir/jshn.c.s"
	cd /home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox && /home/tangshishan/arm-himix200-linux/bin/arm-himix200-linux-gcc  $(C_DEFINES) $(C_FLAGS) -S /home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/jshn.c -o CMakeFiles/jshn.dir/jshn.c.s

libubox/CMakeFiles/jshn.dir/jshn.c.o.requires:
.PHONY : libubox/CMakeFiles/jshn.dir/jshn.c.o.requires

libubox/CMakeFiles/jshn.dir/jshn.c.o.provides: libubox/CMakeFiles/jshn.dir/jshn.c.o.requires
	$(MAKE) -f libubox/CMakeFiles/jshn.dir/build.make libubox/CMakeFiles/jshn.dir/jshn.c.o.provides.build
.PHONY : libubox/CMakeFiles/jshn.dir/jshn.c.o.provides

libubox/CMakeFiles/jshn.dir/jshn.c.o.provides.build: libubox/CMakeFiles/jshn.dir/jshn.c.o

# Object files for target jshn
jshn_OBJECTS = \
"CMakeFiles/jshn.dir/jshn.c.o"

# External object files for target jshn
jshn_EXTERNAL_OBJECTS =

libubox/jshn: libubox/CMakeFiles/jshn.dir/jshn.c.o
libubox/jshn: libubox/CMakeFiles/jshn.dir/build.make
libubox/jshn: libubox/json/libjson-c.so
libubox/jshn: libubox/CMakeFiles/jshn.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable jshn"
	cd /home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jshn.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libubox/CMakeFiles/jshn.dir/build: libubox/jshn
.PHONY : libubox/CMakeFiles/jshn.dir/build

libubox/CMakeFiles/jshn.dir/requires: libubox/CMakeFiles/jshn.dir/jshn.c.o.requires
.PHONY : libubox/CMakeFiles/jshn.dir/requires

libubox/CMakeFiles/jshn.dir/clean:
	cd /home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox && $(CMAKE_COMMAND) -P CMakeFiles/jshn.dir/cmake_clean.cmake
.PHONY : libubox/CMakeFiles/jshn.dir/clean

libubox/CMakeFiles/jshn.dir/depend:
	cd /home/tangshishan/tmp/misc/linux/c/ipc/bus/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tangshishan/tmp/misc/linux/c/ipc/bus /home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox /home/tangshishan/tmp/misc/linux/c/ipc/bus/build /home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox /home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox/CMakeFiles/jshn.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libubox/CMakeFiles/jshn.dir/depend

