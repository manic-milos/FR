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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /opt/lampp/htdocs/fr/Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /opt/lampp/htdocs/fr/Server

# Include any dependencies generated for this target.
include CMakeFiles/ClientSocket.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ClientSocket.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ClientSocket.dir/flags.make

CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.o: CMakeFiles/ClientSocket.dir/flags.make
CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.o: src/ClientSocket.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/lampp/htdocs/fr/Server/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.o -c /opt/lampp/htdocs/fr/Server/src/ClientSocket.cpp

CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /opt/lampp/htdocs/fr/Server/src/ClientSocket.cpp > CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.i

CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /opt/lampp/htdocs/fr/Server/src/ClientSocket.cpp -o CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.s

CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.o.requires:
.PHONY : CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.o.requires

CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.o.provides: CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.o.requires
	$(MAKE) -f CMakeFiles/ClientSocket.dir/build.make CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.o.provides.build
.PHONY : CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.o.provides

CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.o.provides.build: CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.o

# Object files for target ClientSocket
ClientSocket_OBJECTS = \
"CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.o"

# External object files for target ClientSocket
ClientSocket_EXTERNAL_OBJECTS =

libClientSocket.a: CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.o
libClientSocket.a: CMakeFiles/ClientSocket.dir/build.make
libClientSocket.a: CMakeFiles/ClientSocket.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libClientSocket.a"
	$(CMAKE_COMMAND) -P CMakeFiles/ClientSocket.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ClientSocket.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ClientSocket.dir/build: libClientSocket.a
.PHONY : CMakeFiles/ClientSocket.dir/build

CMakeFiles/ClientSocket.dir/requires: CMakeFiles/ClientSocket.dir/src/ClientSocket.cpp.o.requires
.PHONY : CMakeFiles/ClientSocket.dir/requires

CMakeFiles/ClientSocket.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ClientSocket.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ClientSocket.dir/clean

CMakeFiles/ClientSocket.dir/depend:
	cd /opt/lampp/htdocs/fr/Server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/lampp/htdocs/fr/Server /opt/lampp/htdocs/fr/Server /opt/lampp/htdocs/fr/Server /opt/lampp/htdocs/fr/Server /opt/lampp/htdocs/fr/Server/CMakeFiles/ClientSocket.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ClientSocket.dir/depend

