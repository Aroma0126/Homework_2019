# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\ClionProjects\Homework_2019\OS_homeworks\myworks

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\ClionProjects\Homework_2019\OS_homeworks\myworks\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/myworks.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/myworks.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/myworks.dir/flags.make

CMakeFiles/myworks.dir/main.c.obj: CMakeFiles/myworks.dir/flags.make
CMakeFiles/myworks.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\ClionProjects\Homework_2019\OS_homeworks\myworks\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/myworks.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\myworks.dir\main.c.obj   -c C:\ClionProjects\Homework_2019\OS_homeworks\myworks\main.c

CMakeFiles/myworks.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/myworks.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\ClionProjects\Homework_2019\OS_homeworks\myworks\main.c > CMakeFiles\myworks.dir\main.c.i

CMakeFiles/myworks.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/myworks.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\ClionProjects\Homework_2019\OS_homeworks\myworks\main.c -o CMakeFiles\myworks.dir\main.c.s

# Object files for target myworks
myworks_OBJECTS = \
"CMakeFiles/myworks.dir/main.c.obj"

# External object files for target myworks
myworks_EXTERNAL_OBJECTS =

myworks.exe: CMakeFiles/myworks.dir/main.c.obj
myworks.exe: CMakeFiles/myworks.dir/build.make
myworks.exe: CMakeFiles/myworks.dir/linklibs.rsp
myworks.exe: CMakeFiles/myworks.dir/objects1.rsp
myworks.exe: CMakeFiles/myworks.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\ClionProjects\Homework_2019\OS_homeworks\myworks\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable myworks.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\myworks.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/myworks.dir/build: myworks.exe

.PHONY : CMakeFiles/myworks.dir/build

CMakeFiles/myworks.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\myworks.dir\cmake_clean.cmake
.PHONY : CMakeFiles/myworks.dir/clean

CMakeFiles/myworks.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\ClionProjects\Homework_2019\OS_homeworks\myworks C:\ClionProjects\Homework_2019\OS_homeworks\myworks C:\ClionProjects\Homework_2019\OS_homeworks\myworks\cmake-build-debug C:\ClionProjects\Homework_2019\OS_homeworks\myworks\cmake-build-debug C:\ClionProjects\Homework_2019\OS_homeworks\myworks\cmake-build-debug\CMakeFiles\myworks.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/myworks.dir/depend
