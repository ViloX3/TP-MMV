# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hippo/Documents/4as/MMV/mmv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hippo/Documents/4as/MMV/mmv

# Utility rule file for mmv_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/mmv_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mmv_autogen.dir/progress.make

CMakeFiles/mmv_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/hippo/Documents/4as/MMV/mmv/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target mmv"
	/opt/homebrew/Cellar/cmake/3.25.1/bin/cmake -E cmake_autogen /Users/hippo/Documents/4as/MMV/mmv/CMakeFiles/mmv_autogen.dir/AutogenInfo.json ""

mmv_autogen: CMakeFiles/mmv_autogen
mmv_autogen: CMakeFiles/mmv_autogen.dir/build.make
.PHONY : mmv_autogen

# Rule to build all files generated by this target.
CMakeFiles/mmv_autogen.dir/build: mmv_autogen
.PHONY : CMakeFiles/mmv_autogen.dir/build

CMakeFiles/mmv_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mmv_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mmv_autogen.dir/clean

CMakeFiles/mmv_autogen.dir/depend:
	cd /Users/hippo/Documents/4as/MMV/mmv && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hippo/Documents/4as/MMV/mmv /Users/hippo/Documents/4as/MMV/mmv /Users/hippo/Documents/4as/MMV/mmv /Users/hippo/Documents/4as/MMV/mmv /Users/hippo/Documents/4as/MMV/mmv/CMakeFiles/mmv_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mmv_autogen.dir/depend
