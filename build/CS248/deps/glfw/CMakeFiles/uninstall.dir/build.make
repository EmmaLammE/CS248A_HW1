# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build

# Utility rule file for uninstall.

# Include any custom commands dependencies for this target.
include CS248/deps/glfw/CMakeFiles/uninstall.dir/compiler_depend.make

# Include the progress variables for this target.
include CS248/deps/glfw/CMakeFiles/uninstall.dir/progress.make

CS248/deps/glfw/CMakeFiles/uninstall:
	cd /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CS248/deps/glfw && /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake -P /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CS248/deps/glfw/cmake_uninstall.cmake

uninstall: CS248/deps/glfw/CMakeFiles/uninstall
uninstall: CS248/deps/glfw/CMakeFiles/uninstall.dir/build.make
.PHONY : uninstall

# Rule to build all files generated by this target.
CS248/deps/glfw/CMakeFiles/uninstall.dir/build: uninstall
.PHONY : CS248/deps/glfw/CMakeFiles/uninstall.dir/build

CS248/deps/glfw/CMakeFiles/uninstall.dir/clean:
	cd /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CS248/deps/glfw && $(CMAKE_COMMAND) -P CMakeFiles/uninstall.dir/cmake_clean.cmake
.PHONY : CS248/deps/glfw/CMakeFiles/uninstall.dir/clean

CS248/deps/glfw/CMakeFiles/uninstall.dir/depend:
	cd /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/CS248/deps/glfw /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CS248/deps/glfw /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CS248/deps/glfw/CMakeFiles/uninstall.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CS248/deps/glfw/CMakeFiles/uninstall.dir/depend

