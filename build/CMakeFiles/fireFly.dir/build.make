# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /home/ugurcan/.local/lib/python3.8/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/ugurcan/.local/lib/python3.8/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ugurcan/Desktop/pythonScripts/fireFly

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ugurcan/Desktop/pythonScripts/fireFly/build

# Include any dependencies generated for this target.
include CMakeFiles/fireFly.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/fireFly.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/fireFly.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fireFly.dir/flags.make

CMakeFiles/fireFly.dir/main.cpp.o: CMakeFiles/fireFly.dir/flags.make
CMakeFiles/fireFly.dir/main.cpp.o: /home/ugurcan/Desktop/pythonScripts/fireFly/main.cpp
CMakeFiles/fireFly.dir/main.cpp.o: CMakeFiles/fireFly.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ugurcan/Desktop/pythonScripts/fireFly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fireFly.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/fireFly.dir/main.cpp.o -MF CMakeFiles/fireFly.dir/main.cpp.o.d -o CMakeFiles/fireFly.dir/main.cpp.o -c /home/ugurcan/Desktop/pythonScripts/fireFly/main.cpp

CMakeFiles/fireFly.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fireFly.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ugurcan/Desktop/pythonScripts/fireFly/main.cpp > CMakeFiles/fireFly.dir/main.cpp.i

CMakeFiles/fireFly.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fireFly.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ugurcan/Desktop/pythonScripts/fireFly/main.cpp -o CMakeFiles/fireFly.dir/main.cpp.s

# Object files for target fireFly
fireFly_OBJECTS = \
"CMakeFiles/fireFly.dir/main.cpp.o"

# External object files for target fireFly
fireFly_EXTERNAL_OBJECTS =

fireFly: CMakeFiles/fireFly.dir/main.cpp.o
fireFly: CMakeFiles/fireFly.dir/build.make
fireFly: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.5.1
fireFly: /usr/lib/x86_64-linux-gnu/libsfml-audio.so.2.5.1
fireFly: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.5.1
fireFly: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.5.1
fireFly: /home/ugurcan/Downloads/Box2D_v2.3.0/Box2D/Build/Box2D/libBox2D.a
fireFly: CMakeFiles/fireFly.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ugurcan/Desktop/pythonScripts/fireFly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable fireFly"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fireFly.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fireFly.dir/build: fireFly
.PHONY : CMakeFiles/fireFly.dir/build

CMakeFiles/fireFly.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fireFly.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fireFly.dir/clean

CMakeFiles/fireFly.dir/depend:
	cd /home/ugurcan/Desktop/pythonScripts/fireFly/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ugurcan/Desktop/pythonScripts/fireFly /home/ugurcan/Desktop/pythonScripts/fireFly /home/ugurcan/Desktop/pythonScripts/fireFly/build /home/ugurcan/Desktop/pythonScripts/fireFly/build /home/ugurcan/Desktop/pythonScripts/fireFly/build/CMakeFiles/fireFly.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/fireFly.dir/depend

