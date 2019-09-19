# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/tangss/tmp/misc/linux/c/ipc/bus

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tangss/tmp/misc/linux/c/ipc/bus/build

# Include any dependencies generated for this target.
include ubus_conduit/CMakeFiles/conduit_cli.dir/depend.make

# Include the progress variables for this target.
include ubus_conduit/CMakeFiles/conduit_cli.dir/progress.make

# Include the compile flags for this target's objects.
include ubus_conduit/CMakeFiles/conduit_cli.dir/flags.make

ubus_conduit/CMakeFiles/conduit_cli.dir/conduit_client.c.o: ubus_conduit/CMakeFiles/conduit_cli.dir/flags.make
ubus_conduit/CMakeFiles/conduit_cli.dir/conduit_client.c.o: ../ubus_conduit/conduit_client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tangss/tmp/misc/linux/c/ipc/bus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object ubus_conduit/CMakeFiles/conduit_cli.dir/conduit_client.c.o"
	cd /home/tangss/tmp/misc/linux/c/ipc/bus/build/ubus_conduit && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/conduit_cli.dir/conduit_client.c.o   -c /home/tangss/tmp/misc/linux/c/ipc/bus/ubus_conduit/conduit_client.c

ubus_conduit/CMakeFiles/conduit_cli.dir/conduit_client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/conduit_cli.dir/conduit_client.c.i"
	cd /home/tangss/tmp/misc/linux/c/ipc/bus/build/ubus_conduit && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tangss/tmp/misc/linux/c/ipc/bus/ubus_conduit/conduit_client.c > CMakeFiles/conduit_cli.dir/conduit_client.c.i

ubus_conduit/CMakeFiles/conduit_cli.dir/conduit_client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/conduit_cli.dir/conduit_client.c.s"
	cd /home/tangss/tmp/misc/linux/c/ipc/bus/build/ubus_conduit && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tangss/tmp/misc/linux/c/ipc/bus/ubus_conduit/conduit_client.c -o CMakeFiles/conduit_cli.dir/conduit_client.c.s

ubus_conduit/CMakeFiles/conduit_cli.dir/conduit_client.c.o.requires:

.PHONY : ubus_conduit/CMakeFiles/conduit_cli.dir/conduit_client.c.o.requires

ubus_conduit/CMakeFiles/conduit_cli.dir/conduit_client.c.o.provides: ubus_conduit/CMakeFiles/conduit_cli.dir/conduit_client.c.o.requires
	$(MAKE) -f ubus_conduit/CMakeFiles/conduit_cli.dir/build.make ubus_conduit/CMakeFiles/conduit_cli.dir/conduit_client.c.o.provides.build
.PHONY : ubus_conduit/CMakeFiles/conduit_cli.dir/conduit_client.c.o.provides

ubus_conduit/CMakeFiles/conduit_cli.dir/conduit_client.c.o.provides.build: ubus_conduit/CMakeFiles/conduit_cli.dir/conduit_client.c.o


# Object files for target conduit_cli
conduit_cli_OBJECTS = \
"CMakeFiles/conduit_cli.dir/conduit_client.c.o"

# External object files for target conduit_cli
conduit_cli_EXTERNAL_OBJECTS =

ubus_conduit/libconduit_cli.so: ubus_conduit/CMakeFiles/conduit_cli.dir/conduit_client.c.o
ubus_conduit/libconduit_cli.so: ubus_conduit/CMakeFiles/conduit_cli.dir/build.make
ubus_conduit/libconduit_cli.so: libhzbus.so
ubus_conduit/libconduit_cli.so: libubox/libblobmsg_json.so
ubus_conduit/libconduit_cli.so: libubox/libubox.so
ubus_conduit/libconduit_cli.so: ../bin/lib/libjson-c.so
ubus_conduit/libconduit_cli.so: ubus_conduit/CMakeFiles/conduit_cli.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tangss/tmp/misc/linux/c/ipc/bus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libconduit_cli.so"
	cd /home/tangss/tmp/misc/linux/c/ipc/bus/build/ubus_conduit && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/conduit_cli.dir/link.txt --verbose=$(VERBOSE)
	cd /home/tangss/tmp/misc/linux/c/ipc/bus/build/ubus_conduit && cp /home/tangss/tmp/misc/linux/c/ipc/bus/conduit_client.h /home/tangss/tmp/misc/linux/c/ipc/bus/../bin/lib/include/client/
	cd /home/tangss/tmp/misc/linux/c/ipc/bus/build/ubus_conduit && cp /home/tangss/tmp/misc/linux/c/ipc/bus/conduit_server.h /home/tangss/tmp/misc/linux/c/ipc/bus/../bin/lib/include/server/
	cd /home/tangss/tmp/misc/linux/c/ipc/bus/build/ubus_conduit && cp /home/tangss/tmp/misc/linux/c/ipc/bus/conduit_common.h /home/tangss/tmp/misc/linux/c/ipc/bus/../bin/lib/include/client/
	cd /home/tangss/tmp/misc/linux/c/ipc/bus/build/ubus_conduit && cp /home/tangss/tmp/misc/linux/c/ipc/bus/conduit_common.h /home/tangss/tmp/misc/linux/c/ipc/bus/../bin/lib/include/server/
	cd /home/tangss/tmp/misc/linux/c/ipc/bus/build/ubus_conduit && cp /home/tangss/tmp/misc/linux/c/ipc/bus/build/*.so /home/tangss/tmp/misc/linux/c/ipc/bus/../bin/lib/

# Rule to build all files generated by this target.
ubus_conduit/CMakeFiles/conduit_cli.dir/build: ubus_conduit/libconduit_cli.so

.PHONY : ubus_conduit/CMakeFiles/conduit_cli.dir/build

ubus_conduit/CMakeFiles/conduit_cli.dir/requires: ubus_conduit/CMakeFiles/conduit_cli.dir/conduit_client.c.o.requires

.PHONY : ubus_conduit/CMakeFiles/conduit_cli.dir/requires

ubus_conduit/CMakeFiles/conduit_cli.dir/clean:
	cd /home/tangss/tmp/misc/linux/c/ipc/bus/build/ubus_conduit && $(CMAKE_COMMAND) -P CMakeFiles/conduit_cli.dir/cmake_clean.cmake
.PHONY : ubus_conduit/CMakeFiles/conduit_cli.dir/clean

ubus_conduit/CMakeFiles/conduit_cli.dir/depend:
	cd /home/tangss/tmp/misc/linux/c/ipc/bus/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tangss/tmp/misc/linux/c/ipc/bus /home/tangss/tmp/misc/linux/c/ipc/bus/ubus_conduit /home/tangss/tmp/misc/linux/c/ipc/bus/build /home/tangss/tmp/misc/linux/c/ipc/bus/build/ubus_conduit /home/tangss/tmp/misc/linux/c/ipc/bus/build/ubus_conduit/CMakeFiles/conduit_cli.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ubus_conduit/CMakeFiles/conduit_cli.dir/depend

