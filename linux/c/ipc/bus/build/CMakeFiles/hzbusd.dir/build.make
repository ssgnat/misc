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
include CMakeFiles/hzbusd.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hzbusd.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hzbusd.dir/flags.make

CMakeFiles/hzbusd.dir/ubusd.c.o: CMakeFiles/hzbusd.dir/flags.make
CMakeFiles/hzbusd.dir/ubusd.c.o: ../ubusd.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tangss/tmp/misc/linux/c/ipc/bus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/hzbusd.dir/ubusd.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hzbusd.dir/ubusd.c.o   -c /home/tangss/tmp/misc/linux/c/ipc/bus/ubusd.c

CMakeFiles/hzbusd.dir/ubusd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hzbusd.dir/ubusd.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tangss/tmp/misc/linux/c/ipc/bus/ubusd.c > CMakeFiles/hzbusd.dir/ubusd.c.i

CMakeFiles/hzbusd.dir/ubusd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hzbusd.dir/ubusd.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tangss/tmp/misc/linux/c/ipc/bus/ubusd.c -o CMakeFiles/hzbusd.dir/ubusd.c.s

CMakeFiles/hzbusd.dir/ubusd.c.o.requires:

.PHONY : CMakeFiles/hzbusd.dir/ubusd.c.o.requires

CMakeFiles/hzbusd.dir/ubusd.c.o.provides: CMakeFiles/hzbusd.dir/ubusd.c.o.requires
	$(MAKE) -f CMakeFiles/hzbusd.dir/build.make CMakeFiles/hzbusd.dir/ubusd.c.o.provides.build
.PHONY : CMakeFiles/hzbusd.dir/ubusd.c.o.provides

CMakeFiles/hzbusd.dir/ubusd.c.o.provides.build: CMakeFiles/hzbusd.dir/ubusd.c.o


CMakeFiles/hzbusd.dir/ubusd_id.c.o: CMakeFiles/hzbusd.dir/flags.make
CMakeFiles/hzbusd.dir/ubusd_id.c.o: ../ubusd_id.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tangss/tmp/misc/linux/c/ipc/bus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/hzbusd.dir/ubusd_id.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hzbusd.dir/ubusd_id.c.o   -c /home/tangss/tmp/misc/linux/c/ipc/bus/ubusd_id.c

CMakeFiles/hzbusd.dir/ubusd_id.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hzbusd.dir/ubusd_id.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tangss/tmp/misc/linux/c/ipc/bus/ubusd_id.c > CMakeFiles/hzbusd.dir/ubusd_id.c.i

CMakeFiles/hzbusd.dir/ubusd_id.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hzbusd.dir/ubusd_id.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tangss/tmp/misc/linux/c/ipc/bus/ubusd_id.c -o CMakeFiles/hzbusd.dir/ubusd_id.c.s

CMakeFiles/hzbusd.dir/ubusd_id.c.o.requires:

.PHONY : CMakeFiles/hzbusd.dir/ubusd_id.c.o.requires

CMakeFiles/hzbusd.dir/ubusd_id.c.o.provides: CMakeFiles/hzbusd.dir/ubusd_id.c.o.requires
	$(MAKE) -f CMakeFiles/hzbusd.dir/build.make CMakeFiles/hzbusd.dir/ubusd_id.c.o.provides.build
.PHONY : CMakeFiles/hzbusd.dir/ubusd_id.c.o.provides

CMakeFiles/hzbusd.dir/ubusd_id.c.o.provides.build: CMakeFiles/hzbusd.dir/ubusd_id.c.o


CMakeFiles/hzbusd.dir/ubusd_obj.c.o: CMakeFiles/hzbusd.dir/flags.make
CMakeFiles/hzbusd.dir/ubusd_obj.c.o: ../ubusd_obj.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tangss/tmp/misc/linux/c/ipc/bus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/hzbusd.dir/ubusd_obj.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hzbusd.dir/ubusd_obj.c.o   -c /home/tangss/tmp/misc/linux/c/ipc/bus/ubusd_obj.c

CMakeFiles/hzbusd.dir/ubusd_obj.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hzbusd.dir/ubusd_obj.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tangss/tmp/misc/linux/c/ipc/bus/ubusd_obj.c > CMakeFiles/hzbusd.dir/ubusd_obj.c.i

CMakeFiles/hzbusd.dir/ubusd_obj.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hzbusd.dir/ubusd_obj.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tangss/tmp/misc/linux/c/ipc/bus/ubusd_obj.c -o CMakeFiles/hzbusd.dir/ubusd_obj.c.s

CMakeFiles/hzbusd.dir/ubusd_obj.c.o.requires:

.PHONY : CMakeFiles/hzbusd.dir/ubusd_obj.c.o.requires

CMakeFiles/hzbusd.dir/ubusd_obj.c.o.provides: CMakeFiles/hzbusd.dir/ubusd_obj.c.o.requires
	$(MAKE) -f CMakeFiles/hzbusd.dir/build.make CMakeFiles/hzbusd.dir/ubusd_obj.c.o.provides.build
.PHONY : CMakeFiles/hzbusd.dir/ubusd_obj.c.o.provides

CMakeFiles/hzbusd.dir/ubusd_obj.c.o.provides.build: CMakeFiles/hzbusd.dir/ubusd_obj.c.o


CMakeFiles/hzbusd.dir/ubusd_proto.c.o: CMakeFiles/hzbusd.dir/flags.make
CMakeFiles/hzbusd.dir/ubusd_proto.c.o: ../ubusd_proto.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tangss/tmp/misc/linux/c/ipc/bus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/hzbusd.dir/ubusd_proto.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hzbusd.dir/ubusd_proto.c.o   -c /home/tangss/tmp/misc/linux/c/ipc/bus/ubusd_proto.c

CMakeFiles/hzbusd.dir/ubusd_proto.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hzbusd.dir/ubusd_proto.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tangss/tmp/misc/linux/c/ipc/bus/ubusd_proto.c > CMakeFiles/hzbusd.dir/ubusd_proto.c.i

CMakeFiles/hzbusd.dir/ubusd_proto.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hzbusd.dir/ubusd_proto.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tangss/tmp/misc/linux/c/ipc/bus/ubusd_proto.c -o CMakeFiles/hzbusd.dir/ubusd_proto.c.s

CMakeFiles/hzbusd.dir/ubusd_proto.c.o.requires:

.PHONY : CMakeFiles/hzbusd.dir/ubusd_proto.c.o.requires

CMakeFiles/hzbusd.dir/ubusd_proto.c.o.provides: CMakeFiles/hzbusd.dir/ubusd_proto.c.o.requires
	$(MAKE) -f CMakeFiles/hzbusd.dir/build.make CMakeFiles/hzbusd.dir/ubusd_proto.c.o.provides.build
.PHONY : CMakeFiles/hzbusd.dir/ubusd_proto.c.o.provides

CMakeFiles/hzbusd.dir/ubusd_proto.c.o.provides.build: CMakeFiles/hzbusd.dir/ubusd_proto.c.o


CMakeFiles/hzbusd.dir/ubusd_event.c.o: CMakeFiles/hzbusd.dir/flags.make
CMakeFiles/hzbusd.dir/ubusd_event.c.o: ../ubusd_event.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tangss/tmp/misc/linux/c/ipc/bus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/hzbusd.dir/ubusd_event.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hzbusd.dir/ubusd_event.c.o   -c /home/tangss/tmp/misc/linux/c/ipc/bus/ubusd_event.c

CMakeFiles/hzbusd.dir/ubusd_event.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hzbusd.dir/ubusd_event.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tangss/tmp/misc/linux/c/ipc/bus/ubusd_event.c > CMakeFiles/hzbusd.dir/ubusd_event.c.i

CMakeFiles/hzbusd.dir/ubusd_event.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hzbusd.dir/ubusd_event.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tangss/tmp/misc/linux/c/ipc/bus/ubusd_event.c -o CMakeFiles/hzbusd.dir/ubusd_event.c.s

CMakeFiles/hzbusd.dir/ubusd_event.c.o.requires:

.PHONY : CMakeFiles/hzbusd.dir/ubusd_event.c.o.requires

CMakeFiles/hzbusd.dir/ubusd_event.c.o.provides: CMakeFiles/hzbusd.dir/ubusd_event.c.o.requires
	$(MAKE) -f CMakeFiles/hzbusd.dir/build.make CMakeFiles/hzbusd.dir/ubusd_event.c.o.provides.build
.PHONY : CMakeFiles/hzbusd.dir/ubusd_event.c.o.provides

CMakeFiles/hzbusd.dir/ubusd_event.c.o.provides.build: CMakeFiles/hzbusd.dir/ubusd_event.c.o


# Object files for target hzbusd
hzbusd_OBJECTS = \
"CMakeFiles/hzbusd.dir/ubusd.c.o" \
"CMakeFiles/hzbusd.dir/ubusd_id.c.o" \
"CMakeFiles/hzbusd.dir/ubusd_obj.c.o" \
"CMakeFiles/hzbusd.dir/ubusd_proto.c.o" \
"CMakeFiles/hzbusd.dir/ubusd_event.c.o"

# External object files for target hzbusd
hzbusd_EXTERNAL_OBJECTS =

hzbusd: CMakeFiles/hzbusd.dir/ubusd.c.o
hzbusd: CMakeFiles/hzbusd.dir/ubusd_id.c.o
hzbusd: CMakeFiles/hzbusd.dir/ubusd_obj.c.o
hzbusd: CMakeFiles/hzbusd.dir/ubusd_proto.c.o
hzbusd: CMakeFiles/hzbusd.dir/ubusd_event.c.o
hzbusd: CMakeFiles/hzbusd.dir/build.make
hzbusd: libubox/libubox.so
hzbusd: CMakeFiles/hzbusd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tangss/tmp/misc/linux/c/ipc/bus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable hzbusd"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hzbusd.dir/link.txt --verbose=$(VERBOSE)
	cp ./hzbusd ../bin/

# Rule to build all files generated by this target.
CMakeFiles/hzbusd.dir/build: hzbusd

.PHONY : CMakeFiles/hzbusd.dir/build

CMakeFiles/hzbusd.dir/requires: CMakeFiles/hzbusd.dir/ubusd.c.o.requires
CMakeFiles/hzbusd.dir/requires: CMakeFiles/hzbusd.dir/ubusd_id.c.o.requires
CMakeFiles/hzbusd.dir/requires: CMakeFiles/hzbusd.dir/ubusd_obj.c.o.requires
CMakeFiles/hzbusd.dir/requires: CMakeFiles/hzbusd.dir/ubusd_proto.c.o.requires
CMakeFiles/hzbusd.dir/requires: CMakeFiles/hzbusd.dir/ubusd_event.c.o.requires

.PHONY : CMakeFiles/hzbusd.dir/requires

CMakeFiles/hzbusd.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hzbusd.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hzbusd.dir/clean

CMakeFiles/hzbusd.dir/depend:
	cd /home/tangss/tmp/misc/linux/c/ipc/bus/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tangss/tmp/misc/linux/c/ipc/bus /home/tangss/tmp/misc/linux/c/ipc/bus /home/tangss/tmp/misc/linux/c/ipc/bus/build /home/tangss/tmp/misc/linux/c/ipc/bus/build /home/tangss/tmp/misc/linux/c/ipc/bus/build/CMakeFiles/hzbusd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hzbusd.dir/depend
