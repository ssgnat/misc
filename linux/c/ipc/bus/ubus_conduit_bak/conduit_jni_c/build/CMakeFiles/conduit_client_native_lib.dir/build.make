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
CMAKE_SOURCE_DIR = /home/tangshishan/source/hisi3798_442/nas/device/hisilicon/bigfish/horzon/c/ipc/bus/ubus_conduit/conduit_jni_c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tangshishan/source/hisi3798_442/nas/device/hisilicon/bigfish/horzon/c/ipc/bus/ubus_conduit/conduit_jni_c/build

# Include any dependencies generated for this target.
include CMakeFiles/conduit_client_native_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/conduit_client_native_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/conduit_client_native_lib.dir/flags.make

CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.o: CMakeFiles/conduit_client_native_lib.dir/flags.make
CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.o: ../conduit_client_native_lib.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tangshishan/source/hisi3798_442/nas/device/hisilicon/bigfish/horzon/c/ipc/bus/ubus_conduit/conduit_jni_c/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.o"
	/tmp/my-toolchain/bin/arm-linux-androideabi-gcc  --sysroot=/tmp/my-toolchain//sysroot $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.o   -c /home/tangshishan/source/hisi3798_442/nas/device/hisilicon/bigfish/horzon/c/ipc/bus/ubus_conduit/conduit_jni_c/conduit_client_native_lib.c

CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.i"
	/tmp/my-toolchain/bin/arm-linux-androideabi-gcc  --sysroot=/tmp/my-toolchain//sysroot $(C_DEFINES) $(C_FLAGS) -E /home/tangshishan/source/hisi3798_442/nas/device/hisilicon/bigfish/horzon/c/ipc/bus/ubus_conduit/conduit_jni_c/conduit_client_native_lib.c > CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.i

CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.s"
	/tmp/my-toolchain/bin/arm-linux-androideabi-gcc  --sysroot=/tmp/my-toolchain//sysroot $(C_DEFINES) $(C_FLAGS) -S /home/tangshishan/source/hisi3798_442/nas/device/hisilicon/bigfish/horzon/c/ipc/bus/ubus_conduit/conduit_jni_c/conduit_client_native_lib.c -o CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.s

CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.o.requires:
.PHONY : CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.o.requires

CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.o.provides: CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.o.requires
	$(MAKE) -f CMakeFiles/conduit_client_native_lib.dir/build.make CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.o.provides.build
.PHONY : CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.o.provides

CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.o.provides.build: CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.o

# Object files for target conduit_client_native_lib
conduit_client_native_lib_OBJECTS = \
"CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.o"

# External object files for target conduit_client_native_lib
conduit_client_native_lib_EXTERNAL_OBJECTS =

libconduit_client_native_lib.so: CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.o
libconduit_client_native_lib.so: CMakeFiles/conduit_client_native_lib.dir/build.make
libconduit_client_native_lib.so: ../../libconduit_cli.so
libconduit_client_native_lib.so: CMakeFiles/conduit_client_native_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libconduit_client_native_lib.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/conduit_client_native_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/conduit_client_native_lib.dir/build: libconduit_client_native_lib.so
.PHONY : CMakeFiles/conduit_client_native_lib.dir/build

CMakeFiles/conduit_client_native_lib.dir/requires: CMakeFiles/conduit_client_native_lib.dir/conduit_client_native_lib.c.o.requires
.PHONY : CMakeFiles/conduit_client_native_lib.dir/requires

CMakeFiles/conduit_client_native_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/conduit_client_native_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/conduit_client_native_lib.dir/clean

CMakeFiles/conduit_client_native_lib.dir/depend:
	cd /home/tangshishan/source/hisi3798_442/nas/device/hisilicon/bigfish/horzon/c/ipc/bus/ubus_conduit/conduit_jni_c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tangshishan/source/hisi3798_442/nas/device/hisilicon/bigfish/horzon/c/ipc/bus/ubus_conduit/conduit_jni_c /home/tangshishan/source/hisi3798_442/nas/device/hisilicon/bigfish/horzon/c/ipc/bus/ubus_conduit/conduit_jni_c /home/tangshishan/source/hisi3798_442/nas/device/hisilicon/bigfish/horzon/c/ipc/bus/ubus_conduit/conduit_jni_c/build /home/tangshishan/source/hisi3798_442/nas/device/hisilicon/bigfish/horzon/c/ipc/bus/ubus_conduit/conduit_jni_c/build /home/tangshishan/source/hisi3798_442/nas/device/hisilicon/bigfish/horzon/c/ipc/bus/ubus_conduit/conduit_jni_c/build/CMakeFiles/conduit_client_native_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/conduit_client_native_lib.dir/depend

