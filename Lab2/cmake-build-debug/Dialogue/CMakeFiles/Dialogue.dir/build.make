# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/rasul/CLionProjects/OOP/Lab2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug

# Include any dependencies generated for this target.
include Dialogue/CMakeFiles/Dialogue.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Dialogue/CMakeFiles/Dialogue.dir/compiler_depend.make

# Include the progress variables for this target.
include Dialogue/CMakeFiles/Dialogue.dir/progress.make

# Include the compile flags for this target's objects.
include Dialogue/CMakeFiles/Dialogue.dir/flags.make

Dialogue/CMakeFiles/Dialogue.dir/source/main.cpp.o: Dialogue/CMakeFiles/Dialogue.dir/flags.make
Dialogue/CMakeFiles/Dialogue.dir/source/main.cpp.o: ../Dialogue/source/main.cpp
Dialogue/CMakeFiles/Dialogue.dir/source/main.cpp.o: Dialogue/CMakeFiles/Dialogue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Dialogue/CMakeFiles/Dialogue.dir/source/main.cpp.o"
	cd /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Dialogue && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Dialogue/CMakeFiles/Dialogue.dir/source/main.cpp.o -MF CMakeFiles/Dialogue.dir/source/main.cpp.o.d -o CMakeFiles/Dialogue.dir/source/main.cpp.o -c /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/Dialogue/source/main.cpp

Dialogue/CMakeFiles/Dialogue.dir/source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Dialogue.dir/source/main.cpp.i"
	cd /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Dialogue && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/Dialogue/source/main.cpp > CMakeFiles/Dialogue.dir/source/main.cpp.i

Dialogue/CMakeFiles/Dialogue.dir/source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Dialogue.dir/source/main.cpp.s"
	cd /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Dialogue && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/Dialogue/source/main.cpp -o CMakeFiles/Dialogue.dir/source/main.cpp.s

# Object files for target Dialogue
Dialogue_OBJECTS = \
"CMakeFiles/Dialogue.dir/source/main.cpp.o"

# External object files for target Dialogue
Dialogue_EXTERNAL_OBJECTS =

Dialogue/Dialogue: Dialogue/CMakeFiles/Dialogue.dir/source/main.cpp.o
Dialogue/Dialogue: Dialogue/CMakeFiles/Dialogue.dir/build.make
Dialogue/Dialogue: WeatherReport/libWeatherReport.a
Dialogue/Dialogue: Dialogue/CMakeFiles/Dialogue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Dialogue"
	cd /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Dialogue && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Dialogue.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Dialogue/CMakeFiles/Dialogue.dir/build: Dialogue/Dialogue
.PHONY : Dialogue/CMakeFiles/Dialogue.dir/build

Dialogue/CMakeFiles/Dialogue.dir/clean:
	cd /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Dialogue && $(CMAKE_COMMAND) -P CMakeFiles/Dialogue.dir/cmake_clean.cmake
.PHONY : Dialogue/CMakeFiles/Dialogue.dir/clean

Dialogue/CMakeFiles/Dialogue.dir/depend:
	cd /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/rasul/CLionProjects/OOP/Lab2 /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/Dialogue /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Dialogue /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Dialogue/CMakeFiles/Dialogue.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Dialogue/CMakeFiles/Dialogue.dir/depend

