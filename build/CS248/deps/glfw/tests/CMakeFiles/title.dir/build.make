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

# Include any dependencies generated for this target.
include CS248/deps/glfw/tests/CMakeFiles/title.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CS248/deps/glfw/tests/CMakeFiles/title.dir/compiler_depend.make

# Include the progress variables for this target.
include CS248/deps/glfw/tests/CMakeFiles/title.dir/progress.make

# Include the compile flags for this target's objects.
include CS248/deps/glfw/tests/CMakeFiles/title.dir/flags.make

CS248/deps/glfw/tests/CMakeFiles/title.dir/title.c.o: CS248/deps/glfw/tests/CMakeFiles/title.dir/flags.make
CS248/deps/glfw/tests/CMakeFiles/title.dir/title.c.o: /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/CS248/deps/glfw/tests/title.c
CS248/deps/glfw/tests/CMakeFiles/title.dir/title.c.o: CS248/deps/glfw/tests/CMakeFiles/title.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CS248/deps/glfw/tests/CMakeFiles/title.dir/title.c.o"
	cd /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CS248/deps/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CS248/deps/glfw/tests/CMakeFiles/title.dir/title.c.o -MF CMakeFiles/title.dir/title.c.o.d -o CMakeFiles/title.dir/title.c.o -c /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/CS248/deps/glfw/tests/title.c

CS248/deps/glfw/tests/CMakeFiles/title.dir/title.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/title.dir/title.c.i"
	cd /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CS248/deps/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/CS248/deps/glfw/tests/title.c > CMakeFiles/title.dir/title.c.i

CS248/deps/glfw/tests/CMakeFiles/title.dir/title.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/title.dir/title.c.s"
	cd /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CS248/deps/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/CS248/deps/glfw/tests/title.c -o CMakeFiles/title.dir/title.c.s

CS248/deps/glfw/tests/CMakeFiles/title.dir/__/deps/glad.c.o: CS248/deps/glfw/tests/CMakeFiles/title.dir/flags.make
CS248/deps/glfw/tests/CMakeFiles/title.dir/__/deps/glad.c.o: /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/CS248/deps/glfw/deps/glad.c
CS248/deps/glfw/tests/CMakeFiles/title.dir/__/deps/glad.c.o: CS248/deps/glfw/tests/CMakeFiles/title.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CS248/deps/glfw/tests/CMakeFiles/title.dir/__/deps/glad.c.o"
	cd /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CS248/deps/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CS248/deps/glfw/tests/CMakeFiles/title.dir/__/deps/glad.c.o -MF CMakeFiles/title.dir/__/deps/glad.c.o.d -o CMakeFiles/title.dir/__/deps/glad.c.o -c /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/CS248/deps/glfw/deps/glad.c

CS248/deps/glfw/tests/CMakeFiles/title.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/title.dir/__/deps/glad.c.i"
	cd /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CS248/deps/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/CS248/deps/glfw/deps/glad.c > CMakeFiles/title.dir/__/deps/glad.c.i

CS248/deps/glfw/tests/CMakeFiles/title.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/title.dir/__/deps/glad.c.s"
	cd /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CS248/deps/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/CS248/deps/glfw/deps/glad.c -o CMakeFiles/title.dir/__/deps/glad.c.s

# Object files for target title
title_OBJECTS = \
"CMakeFiles/title.dir/title.c.o" \
"CMakeFiles/title.dir/__/deps/glad.c.o"

# External object files for target title
title_EXTERNAL_OBJECTS =

CS248/deps/glfw/tests/title.app/Contents/MacOS/title: CS248/deps/glfw/tests/CMakeFiles/title.dir/title.c.o
CS248/deps/glfw/tests/title.app/Contents/MacOS/title: CS248/deps/glfw/tests/CMakeFiles/title.dir/__/deps/glad.c.o
CS248/deps/glfw/tests/title.app/Contents/MacOS/title: CS248/deps/glfw/tests/CMakeFiles/title.dir/build.make
CS248/deps/glfw/tests/title.app/Contents/MacOS/title: CS248/deps/glfw/src/libglfw3.a
CS248/deps/glfw/tests/title.app/Contents/MacOS/title: CS248/deps/glfw/tests/CMakeFiles/title.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable title.app/Contents/MacOS/title"
	cd /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CS248/deps/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/title.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CS248/deps/glfw/tests/CMakeFiles/title.dir/build: CS248/deps/glfw/tests/title.app/Contents/MacOS/title
.PHONY : CS248/deps/glfw/tests/CMakeFiles/title.dir/build

CS248/deps/glfw/tests/CMakeFiles/title.dir/clean:
	cd /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CS248/deps/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/title.dir/cmake_clean.cmake
.PHONY : CS248/deps/glfw/tests/CMakeFiles/title.dir/clean

CS248/deps/glfw/tests/CMakeFiles/title.dir/depend:
	cd /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/CS248/deps/glfw/tests /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CS248/deps/glfw/tests /Users/emmaliu/stanford/courses/cs248A/svg_recompile/draw-svg/build/CS248/deps/glfw/tests/CMakeFiles/title.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CS248/deps/glfw/tests/CMakeFiles/title.dir/depend
