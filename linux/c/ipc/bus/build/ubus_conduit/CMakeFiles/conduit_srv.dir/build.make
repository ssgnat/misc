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
include ubus_conduit/CMakeFiles/conduit_srv.dir/depend.make

# Include the progress variables for this target.
include ubus_conduit/CMakeFiles/conduit_srv.dir/progress.make

# Include the compile flags for this target's objects.
include ubus_conduit/CMakeFiles/conduit_srv.dir/flags.make

ubus_conduit/CMakeFiles/conduit_srv.dir/conduit_server.c.o: ubus_conduit/CMakeFiles/conduit_srv.dir/flags.make
ubus_conduit/CMakeFiles/conduit_srv.dir/conduit_server.c.o: ../ubus_conduit/conduit_server.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tangshishan/tmp/misc/linux/c/ipc/bus/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object ubus_conduit/CMakeFiles/conduit_srv.dir/conduit_server.c.o"
	cd /home/tangshishan/tmp/misc/linux/c/ipc/bus/build/ubus_conduit && /home/tangshishan/arm-himix200-linux/bin/arm-himix200-linux-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/conduit_srv.dir/conduit_server.c.o   -c /home/tangshishan/tmp/misc/linux/c/ipc/bus/ubus_conduit/conduit_server.c

ubus_conduit/CMakeFiles/conduit_srv.dir/conduit_server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/conduit_srv.dir/conduit_server.c.i"
	cd /home/tangshishan/tmp/misc/linux/c/ipc/bus/build/ubus_conduit && /home/tangshishan/arm-himix200-linux/bin/arm-himix200-linux-gcc  $(C_DEFINES) $(C_FLAGS) -E /home/tangshishan/tmp/misc/linux/c/ipc/bus/ubus_conduit/conduit_server.c > CMakeFiles/conduit_srv.dir/conduit_server.c.i

ubus_conduit/CMakeFiles/conduit_srv.dir/conduit_server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/conduit_srv.dir/conduit_server.c.s"
	cd /home/tangshishan/tmp/misc/linux/c/ipc/bus/build/ubus_conduit && /home/tangshishan/arm-himix200-linux/bin/arm-himix200-linux-gcc  $(C_DEFINES) $(C_FLAGS) -S /home/tangshishan/tmp/misc/linux/c/ipc/bus/ubus_conduit/conduit_server.c -o CMakeFiles/conduit_srv.dir/conduit_server.c.s

ubus_conduit/CMakeFiles/conduit_srv.dir/conduit_server.c.o.requires:
.PHONY : ubus_conduit/CMakeFiles/conduit_srv.dir/conduit_server.c.o.requires

ubus_conduit/CMakeFiles/conduit_srv.dir/conduit_server.c.o.provides: ubus_conduit/CMakeFiles/conduit_srv.dir/conduit_server.c.o.requires
	$(MAKE) -f ubus_conduit/CMakeFiles/conduit_srv.dir/build.make ubus_conduit/CMakeFiles/conduit_srv.dir/conduit_server.c.o.provides.build
.PHONY : ubus_conduit/CMakeFiles/conduit_srv.dir/conduit_server.c.o.provides

ubus_conduit/CMakeFiles/conduit_srv.dir/conduit_server.c.o.provides.build: ubus_conduit/CMakeFiles/conduit_srv.dir/conduit_server.c.o

# Object files for target conduit_srv
conduit_srv_OBJECTS = \
"CMakeFiles/conduit_srv.dir/conduit_server.c.o"

# External object files for target conduit_srv
conduit_srv_EXTERNAL_OBJECTS =

ubus_conduit/libconduit_srv.so: ubus_conduit/CMakeFiles/conduit_srv.dir/conduit_server.c.o
ubus_conduit/libconduit_srv.so: ubus_conduit/CMakeFiles/conduit_srv.dir/build.make
ubus_conduit/libconduit_srv.so: libhzbus.so
ubus_conduit/libconduit_srv.so: libubox/libubox.so
ubus_conduit/libconduit_srv.so: libubox/libblobmsg_json.so
ubus_conduit/libconduit_srv.so: libubox/libubox.so
ubus_conduit/libconduit_srv.so: libubox/json/libjson-c.so
ubus_conduit/libconduit_srv.so: ubus_conduit/CMakeFiles/conduit_srv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libconduit_srv.so"
	cd /home/tangshishan/tmp/misc/linux/c/ipc/bus/build/ubus_conduit && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/conduit_srv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ubus_conduit/CMakeFiles/conduit_srv.dir/build: ubus_conduit/libconduit_srv.so
.PHONY : ubus_conduit/CMakeFiles/conduit_srv.dir/build

ubus_conduit/CMakeFiles/conduit_srv.dir/requires: ubus_conduit/CMakeFiles/conduit_srv.dir/conduit_server.c.o.requires
.PHONY : ubus_conduit/CMakeFiles/conduit_srv.dir/requires

ubus_conduit/CMakeFiles/conduit_srv.dir/clean:
	cd /home/tangshishan/tmp/misc/linux/c/ipc/bus/build/ubus_conduit && $(CMAKE_COMMAND) -P CMakeFiles/conduit_srv.dir/cmake_clean.cmake
.PHONY : ubus_conduit/CMakeFiles/conduit_srv.dir/clean

ubus_conduit/CMakeFiles/conduit_srv.dir/depend:
	cd /home/tangshishan/tmp/misc/linux/c/ipc/bus/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tangshishan/tmp/misc/linux/c/ipc/bus /home/tangshishan/tmp/misc/linux/c/ipc/bus/ubus_conduit /home/tangshishan/tmp/misc/linux/c/ipc/bus/build /home/tangshishan/tmp/misc/linux/c/ipc/bus/build/ubus_conduit /home/tangshishan/tmp/misc/linux/c/ipc/bus/build/ubus_conduit/CMakeFiles/conduit_srv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ubus_conduit/CMakeFiles/conduit_srv.dir/depend

