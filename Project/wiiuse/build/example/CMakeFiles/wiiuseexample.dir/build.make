# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse/build

# Include any dependencies generated for this target.
include example/CMakeFiles/wiiuseexample.dir/depend.make

# Include the progress variables for this target.
include example/CMakeFiles/wiiuseexample.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/wiiuseexample.dir/flags.make

example/CMakeFiles/wiiuseexample.dir/example.c.o: example/CMakeFiles/wiiuseexample.dir/flags.make
example/CMakeFiles/wiiuseexample.dir/example.c.o: ../example/example.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object example/CMakeFiles/wiiuseexample.dir/example.c.o"
	cd /Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse/build/example && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wiiuseexample.dir/example.c.o   -c /Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse/example/example.c

example/CMakeFiles/wiiuseexample.dir/example.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wiiuseexample.dir/example.c.i"
	cd /Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse/build/example && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse/example/example.c > CMakeFiles/wiiuseexample.dir/example.c.i

example/CMakeFiles/wiiuseexample.dir/example.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wiiuseexample.dir/example.c.s"
	cd /Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse/build/example && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse/example/example.c -o CMakeFiles/wiiuseexample.dir/example.c.s

example/CMakeFiles/wiiuseexample.dir/example.c.o.requires:

.PHONY : example/CMakeFiles/wiiuseexample.dir/example.c.o.requires

example/CMakeFiles/wiiuseexample.dir/example.c.o.provides: example/CMakeFiles/wiiuseexample.dir/example.c.o.requires
	$(MAKE) -f example/CMakeFiles/wiiuseexample.dir/build.make example/CMakeFiles/wiiuseexample.dir/example.c.o.provides.build
.PHONY : example/CMakeFiles/wiiuseexample.dir/example.c.o.provides

example/CMakeFiles/wiiuseexample.dir/example.c.o.provides.build: example/CMakeFiles/wiiuseexample.dir/example.c.o


# Object files for target wiiuseexample
wiiuseexample_OBJECTS = \
"CMakeFiles/wiiuseexample.dir/example.c.o"

# External object files for target wiiuseexample
wiiuseexample_EXTERNAL_OBJECTS =

example/wiiuseexample: example/CMakeFiles/wiiuseexample.dir/example.c.o
example/wiiuseexample: example/CMakeFiles/wiiuseexample.dir/build.make
example/wiiuseexample: src/libwiiuse.dylib
example/wiiuseexample: example/CMakeFiles/wiiuseexample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable wiiuseexample"
	cd /Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse/build/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wiiuseexample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/wiiuseexample.dir/build: example/wiiuseexample

.PHONY : example/CMakeFiles/wiiuseexample.dir/build

example/CMakeFiles/wiiuseexample.dir/requires: example/CMakeFiles/wiiuseexample.dir/example.c.o.requires

.PHONY : example/CMakeFiles/wiiuseexample.dir/requires

example/CMakeFiles/wiiuseexample.dir/clean:
	cd /Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse/build/example && $(CMAKE_COMMAND) -P CMakeFiles/wiiuseexample.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/wiiuseexample.dir/clean

example/CMakeFiles/wiiuseexample.dir/depend:
	cd /Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse /Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse/example /Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse/build /Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse/build/example /Users/Tim/Downloads/Shiro-Bougyo/Project/wiiuse/build/example/CMakeFiles/wiiuseexample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/wiiuseexample.dir/depend
