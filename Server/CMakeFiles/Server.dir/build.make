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
include CMakeFiles/Server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Server.dir/flags.make

CMakeFiles/Server.dir/src/simple_server_main.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/src/simple_server_main.cpp.o: src/simple_server_main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/lampp/htdocs/fr/Server/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Server.dir/src/simple_server_main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/src/simple_server_main.cpp.o -c /opt/lampp/htdocs/fr/Server/src/simple_server_main.cpp

CMakeFiles/Server.dir/src/simple_server_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/src/simple_server_main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /opt/lampp/htdocs/fr/Server/src/simple_server_main.cpp > CMakeFiles/Server.dir/src/simple_server_main.cpp.i

CMakeFiles/Server.dir/src/simple_server_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/src/simple_server_main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /opt/lampp/htdocs/fr/Server/src/simple_server_main.cpp -o CMakeFiles/Server.dir/src/simple_server_main.cpp.s

CMakeFiles/Server.dir/src/simple_server_main.cpp.o.requires:
.PHONY : CMakeFiles/Server.dir/src/simple_server_main.cpp.o.requires

CMakeFiles/Server.dir/src/simple_server_main.cpp.o.provides: CMakeFiles/Server.dir/src/simple_server_main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/src/simple_server_main.cpp.o.provides.build
.PHONY : CMakeFiles/Server.dir/src/simple_server_main.cpp.o.provides

CMakeFiles/Server.dir/src/simple_server_main.cpp.o.provides.build: CMakeFiles/Server.dir/src/simple_server_main.cpp.o

# Object files for target Server
Server_OBJECTS = \
"CMakeFiles/Server.dir/src/simple_server_main.cpp.o"

# External object files for target Server
Server_EXTERNAL_OBJECTS =

Server: CMakeFiles/Server.dir/src/simple_server_main.cpp.o
Server: CMakeFiles/Server.dir/build.make
Server: libServerSocket.a
Server: /usr/lib/libopencv_videostab.so.2.4.13
Server: /usr/lib/libopencv_video.so.2.4.13
Server: /usr/lib/libopencv_ts.a
Server: /usr/lib/libopencv_superres.so.2.4.13
Server: /usr/lib/libopencv_stitching.so.2.4.13
Server: /usr/lib/libopencv_photo.so.2.4.13
Server: /usr/lib/libopencv_ocl.so.2.4.13
Server: /usr/lib/libopencv_objdetect.so.2.4.13
Server: /usr/lib/libopencv_nonfree.so.2.4.13
Server: /usr/lib/libopencv_ml.so.2.4.13
Server: /usr/lib/libopencv_legacy.so.2.4.13
Server: /usr/lib/libopencv_imgproc.so.2.4.13
Server: /usr/lib/libopencv_highgui.so.2.4.13
Server: /usr/lib/libopencv_gpu.so.2.4.13
Server: /usr/lib/libopencv_flann.so.2.4.13
Server: /usr/lib/libopencv_features2d.so.2.4.13
Server: /usr/lib/libopencv_core.so.2.4.13
Server: /usr/lib/libopencv_contrib.so.2.4.13
Server: /usr/lib/libopencv_calib3d.so.2.4.13
Server: libDetectObject.a
Server: libRecognition.a
Server: libPreprocessFace.a
Server: libSocket.a
Server: libDetectObject.a
Server: /usr/lib/libopencv_videostab.so.2.4.13
Server: /usr/lib/libopencv_ts.a
Server: /usr/lib/libopencv_superres.so.2.4.13
Server: /usr/lib/libopencv_stitching.so.2.4.13
Server: /usr/lib/libopencv_contrib.so.2.4.13
Server: /usr/lib/libopencv_nonfree.so.2.4.13
Server: /usr/lib/libopencv_ocl.so.2.4.13
Server: /usr/lib/libopencv_gpu.so.2.4.13
Server: /usr/lib/libopencv_photo.so.2.4.13
Server: /usr/lib/libopencv_objdetect.so.2.4.13
Server: /usr/lib/libopencv_legacy.so.2.4.13
Server: /usr/lib/libopencv_video.so.2.4.13
Server: /usr/lib/libopencv_ml.so.2.4.13
Server: /usr/lib/libopencv_calib3d.so.2.4.13
Server: /usr/lib/libopencv_features2d.so.2.4.13
Server: /usr/lib/libopencv_highgui.so.2.4.13
Server: /usr/lib/libopencv_imgproc.so.2.4.13
Server: /usr/lib/libopencv_flann.so.2.4.13
Server: /usr/lib/libopencv_core.so.2.4.13
Server: CMakeFiles/Server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Server.dir/build: Server
.PHONY : CMakeFiles/Server.dir/build

CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/src/simple_server_main.cpp.o.requires
.PHONY : CMakeFiles/Server.dir/requires

CMakeFiles/Server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Server.dir/clean

CMakeFiles/Server.dir/depend:
	cd /opt/lampp/htdocs/fr/Server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/lampp/htdocs/fr/Server /opt/lampp/htdocs/fr/Server /opt/lampp/htdocs/fr/Server /opt/lampp/htdocs/fr/Server /opt/lampp/htdocs/fr/Server/CMakeFiles/Server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Server.dir/depend
