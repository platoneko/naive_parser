# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cyx/cfiles/naive_parser

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cyx/cfiles/naive_parser/build

# Include any dependencies generated for this target.
include CMakeFiles/naive_parser.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/naive_parser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/naive_parser.dir/flags.make

CMakeFiles/naive_parser.dir/src/array_parser.o: CMakeFiles/naive_parser.dir/flags.make
CMakeFiles/naive_parser.dir/src/array_parser.o: ../src/array_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyx/cfiles/naive_parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/naive_parser.dir/src/array_parser.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_parser.dir/src/array_parser.o -c /home/cyx/cfiles/naive_parser/src/array_parser.cpp

CMakeFiles/naive_parser.dir/src/array_parser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_parser.dir/src/array_parser.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyx/cfiles/naive_parser/src/array_parser.cpp > CMakeFiles/naive_parser.dir/src/array_parser.i

CMakeFiles/naive_parser.dir/src/array_parser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_parser.dir/src/array_parser.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyx/cfiles/naive_parser/src/array_parser.cpp -o CMakeFiles/naive_parser.dir/src/array_parser.s

CMakeFiles/naive_parser.dir/src/branch_recurrent_parser.o: CMakeFiles/naive_parser.dir/flags.make
CMakeFiles/naive_parser.dir/src/branch_recurrent_parser.o: ../src/branch_recurrent_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyx/cfiles/naive_parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/naive_parser.dir/src/branch_recurrent_parser.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_parser.dir/src/branch_recurrent_parser.o -c /home/cyx/cfiles/naive_parser/src/branch_recurrent_parser.cpp

CMakeFiles/naive_parser.dir/src/branch_recurrent_parser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_parser.dir/src/branch_recurrent_parser.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyx/cfiles/naive_parser/src/branch_recurrent_parser.cpp > CMakeFiles/naive_parser.dir/src/branch_recurrent_parser.i

CMakeFiles/naive_parser.dir/src/branch_recurrent_parser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_parser.dir/src/branch_recurrent_parser.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyx/cfiles/naive_parser/src/branch_recurrent_parser.cpp -o CMakeFiles/naive_parser.dir/src/branch_recurrent_parser.s

CMakeFiles/naive_parser.dir/src/codeblock_parser.o: CMakeFiles/naive_parser.dir/flags.make
CMakeFiles/naive_parser.dir/src/codeblock_parser.o: ../src/codeblock_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyx/cfiles/naive_parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/naive_parser.dir/src/codeblock_parser.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_parser.dir/src/codeblock_parser.o -c /home/cyx/cfiles/naive_parser/src/codeblock_parser.cpp

CMakeFiles/naive_parser.dir/src/codeblock_parser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_parser.dir/src/codeblock_parser.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyx/cfiles/naive_parser/src/codeblock_parser.cpp > CMakeFiles/naive_parser.dir/src/codeblock_parser.i

CMakeFiles/naive_parser.dir/src/codeblock_parser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_parser.dir/src/codeblock_parser.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyx/cfiles/naive_parser/src/codeblock_parser.cpp -o CMakeFiles/naive_parser.dir/src/codeblock_parser.s

CMakeFiles/naive_parser.dir/src/expression_parser.o: CMakeFiles/naive_parser.dir/flags.make
CMakeFiles/naive_parser.dir/src/expression_parser.o: ../src/expression_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyx/cfiles/naive_parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/naive_parser.dir/src/expression_parser.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_parser.dir/src/expression_parser.o -c /home/cyx/cfiles/naive_parser/src/expression_parser.cpp

CMakeFiles/naive_parser.dir/src/expression_parser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_parser.dir/src/expression_parser.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyx/cfiles/naive_parser/src/expression_parser.cpp > CMakeFiles/naive_parser.dir/src/expression_parser.i

CMakeFiles/naive_parser.dir/src/expression_parser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_parser.dir/src/expression_parser.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyx/cfiles/naive_parser/src/expression_parser.cpp -o CMakeFiles/naive_parser.dir/src/expression_parser.s

CMakeFiles/naive_parser.dir/src/function_parser.o: CMakeFiles/naive_parser.dir/flags.make
CMakeFiles/naive_parser.dir/src/function_parser.o: ../src/function_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyx/cfiles/naive_parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/naive_parser.dir/src/function_parser.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_parser.dir/src/function_parser.o -c /home/cyx/cfiles/naive_parser/src/function_parser.cpp

CMakeFiles/naive_parser.dir/src/function_parser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_parser.dir/src/function_parser.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyx/cfiles/naive_parser/src/function_parser.cpp > CMakeFiles/naive_parser.dir/src/function_parser.i

CMakeFiles/naive_parser.dir/src/function_parser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_parser.dir/src/function_parser.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyx/cfiles/naive_parser/src/function_parser.cpp -o CMakeFiles/naive_parser.dir/src/function_parser.s

CMakeFiles/naive_parser.dir/src/global_parser.o: CMakeFiles/naive_parser.dir/flags.make
CMakeFiles/naive_parser.dir/src/global_parser.o: ../src/global_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyx/cfiles/naive_parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/naive_parser.dir/src/global_parser.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_parser.dir/src/global_parser.o -c /home/cyx/cfiles/naive_parser/src/global_parser.cpp

CMakeFiles/naive_parser.dir/src/global_parser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_parser.dir/src/global_parser.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyx/cfiles/naive_parser/src/global_parser.cpp > CMakeFiles/naive_parser.dir/src/global_parser.i

CMakeFiles/naive_parser.dir/src/global_parser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_parser.dir/src/global_parser.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyx/cfiles/naive_parser/src/global_parser.cpp -o CMakeFiles/naive_parser.dir/src/global_parser.s

CMakeFiles/naive_parser.dir/src/indent_format.o: CMakeFiles/naive_parser.dir/flags.make
CMakeFiles/naive_parser.dir/src/indent_format.o: ../src/indent_format.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyx/cfiles/naive_parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/naive_parser.dir/src/indent_format.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_parser.dir/src/indent_format.o -c /home/cyx/cfiles/naive_parser/src/indent_format.cpp

CMakeFiles/naive_parser.dir/src/indent_format.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_parser.dir/src/indent_format.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyx/cfiles/naive_parser/src/indent_format.cpp > CMakeFiles/naive_parser.dir/src/indent_format.i

CMakeFiles/naive_parser.dir/src/indent_format.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_parser.dir/src/indent_format.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyx/cfiles/naive_parser/src/indent_format.cpp -o CMakeFiles/naive_parser.dir/src/indent_format.s

CMakeFiles/naive_parser.dir/src/local_parser.o: CMakeFiles/naive_parser.dir/flags.make
CMakeFiles/naive_parser.dir/src/local_parser.o: ../src/local_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyx/cfiles/naive_parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/naive_parser.dir/src/local_parser.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_parser.dir/src/local_parser.o -c /home/cyx/cfiles/naive_parser/src/local_parser.cpp

CMakeFiles/naive_parser.dir/src/local_parser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_parser.dir/src/local_parser.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyx/cfiles/naive_parser/src/local_parser.cpp > CMakeFiles/naive_parser.dir/src/local_parser.i

CMakeFiles/naive_parser.dir/src/local_parser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_parser.dir/src/local_parser.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyx/cfiles/naive_parser/src/local_parser.cpp -o CMakeFiles/naive_parser.dir/src/local_parser.s

CMakeFiles/naive_parser.dir/src/naive_parser.o: CMakeFiles/naive_parser.dir/flags.make
CMakeFiles/naive_parser.dir/src/naive_parser.o: ../src/naive_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyx/cfiles/naive_parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/naive_parser.dir/src/naive_parser.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_parser.dir/src/naive_parser.o -c /home/cyx/cfiles/naive_parser/src/naive_parser.cpp

CMakeFiles/naive_parser.dir/src/naive_parser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_parser.dir/src/naive_parser.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyx/cfiles/naive_parser/src/naive_parser.cpp > CMakeFiles/naive_parser.dir/src/naive_parser.i

CMakeFiles/naive_parser.dir/src/naive_parser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_parser.dir/src/naive_parser.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyx/cfiles/naive_parser/src/naive_parser.cpp -o CMakeFiles/naive_parser.dir/src/naive_parser.s

CMakeFiles/naive_parser.dir/src/precompiler_parser.o: CMakeFiles/naive_parser.dir/flags.make
CMakeFiles/naive_parser.dir/src/precompiler_parser.o: ../src/precompiler_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyx/cfiles/naive_parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/naive_parser.dir/src/precompiler_parser.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_parser.dir/src/precompiler_parser.o -c /home/cyx/cfiles/naive_parser/src/precompiler_parser.cpp

CMakeFiles/naive_parser.dir/src/precompiler_parser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_parser.dir/src/precompiler_parser.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyx/cfiles/naive_parser/src/precompiler_parser.cpp > CMakeFiles/naive_parser.dir/src/precompiler_parser.i

CMakeFiles/naive_parser.dir/src/precompiler_parser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_parser.dir/src/precompiler_parser.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyx/cfiles/naive_parser/src/precompiler_parser.cpp -o CMakeFiles/naive_parser.dir/src/precompiler_parser.s

CMakeFiles/naive_parser.dir/src/program_parser.o: CMakeFiles/naive_parser.dir/flags.make
CMakeFiles/naive_parser.dir/src/program_parser.o: ../src/program_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyx/cfiles/naive_parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/naive_parser.dir/src/program_parser.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_parser.dir/src/program_parser.o -c /home/cyx/cfiles/naive_parser/src/program_parser.cpp

CMakeFiles/naive_parser.dir/src/program_parser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_parser.dir/src/program_parser.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyx/cfiles/naive_parser/src/program_parser.cpp > CMakeFiles/naive_parser.dir/src/program_parser.i

CMakeFiles/naive_parser.dir/src/program_parser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_parser.dir/src/program_parser.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyx/cfiles/naive_parser/src/program_parser.cpp -o CMakeFiles/naive_parser.dir/src/program_parser.s

CMakeFiles/naive_parser.dir/src/syntax_parser.o: CMakeFiles/naive_parser.dir/flags.make
CMakeFiles/naive_parser.dir/src/syntax_parser.o: ../src/syntax_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyx/cfiles/naive_parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/naive_parser.dir/src/syntax_parser.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_parser.dir/src/syntax_parser.o -c /home/cyx/cfiles/naive_parser/src/syntax_parser.cpp

CMakeFiles/naive_parser.dir/src/syntax_parser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_parser.dir/src/syntax_parser.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyx/cfiles/naive_parser/src/syntax_parser.cpp > CMakeFiles/naive_parser.dir/src/syntax_parser.i

CMakeFiles/naive_parser.dir/src/syntax_parser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_parser.dir/src/syntax_parser.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyx/cfiles/naive_parser/src/syntax_parser.cpp -o CMakeFiles/naive_parser.dir/src/syntax_parser.s

CMakeFiles/naive_parser.dir/src/token_parser.o: CMakeFiles/naive_parser.dir/flags.make
CMakeFiles/naive_parser.dir/src/token_parser.o: ../src/token_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyx/cfiles/naive_parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/naive_parser.dir/src/token_parser.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_parser.dir/src/token_parser.o -c /home/cyx/cfiles/naive_parser/src/token_parser.cpp

CMakeFiles/naive_parser.dir/src/token_parser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_parser.dir/src/token_parser.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyx/cfiles/naive_parser/src/token_parser.cpp > CMakeFiles/naive_parser.dir/src/token_parser.i

CMakeFiles/naive_parser.dir/src/token_parser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_parser.dir/src/token_parser.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyx/cfiles/naive_parser/src/token_parser.cpp -o CMakeFiles/naive_parser.dir/src/token_parser.s

CMakeFiles/naive_parser.dir/src/token_type.o: CMakeFiles/naive_parser.dir/flags.make
CMakeFiles/naive_parser.dir/src/token_type.o: ../src/token_type.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyx/cfiles/naive_parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/naive_parser.dir/src/token_type.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_parser.dir/src/token_type.o -c /home/cyx/cfiles/naive_parser/src/token_type.cpp

CMakeFiles/naive_parser.dir/src/token_type.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_parser.dir/src/token_type.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyx/cfiles/naive_parser/src/token_type.cpp > CMakeFiles/naive_parser.dir/src/token_type.i

CMakeFiles/naive_parser.dir/src/token_type.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_parser.dir/src/token_type.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyx/cfiles/naive_parser/src/token_type.cpp -o CMakeFiles/naive_parser.dir/src/token_type.s

CMakeFiles/naive_parser.dir/src/var_type.o: CMakeFiles/naive_parser.dir/flags.make
CMakeFiles/naive_parser.dir/src/var_type.o: ../src/var_type.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyx/cfiles/naive_parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/naive_parser.dir/src/var_type.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_parser.dir/src/var_type.o -c /home/cyx/cfiles/naive_parser/src/var_type.cpp

CMakeFiles/naive_parser.dir/src/var_type.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_parser.dir/src/var_type.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyx/cfiles/naive_parser/src/var_type.cpp > CMakeFiles/naive_parser.dir/src/var_type.i

CMakeFiles/naive_parser.dir/src/var_type.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_parser.dir/src/var_type.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyx/cfiles/naive_parser/src/var_type.cpp -o CMakeFiles/naive_parser.dir/src/var_type.s

# Object files for target naive_parser
naive_parser_OBJECTS = \
"CMakeFiles/naive_parser.dir/src/array_parser.o" \
"CMakeFiles/naive_parser.dir/src/branch_recurrent_parser.o" \
"CMakeFiles/naive_parser.dir/src/codeblock_parser.o" \
"CMakeFiles/naive_parser.dir/src/expression_parser.o" \
"CMakeFiles/naive_parser.dir/src/function_parser.o" \
"CMakeFiles/naive_parser.dir/src/global_parser.o" \
"CMakeFiles/naive_parser.dir/src/indent_format.o" \
"CMakeFiles/naive_parser.dir/src/local_parser.o" \
"CMakeFiles/naive_parser.dir/src/naive_parser.o" \
"CMakeFiles/naive_parser.dir/src/precompiler_parser.o" \
"CMakeFiles/naive_parser.dir/src/program_parser.o" \
"CMakeFiles/naive_parser.dir/src/syntax_parser.o" \
"CMakeFiles/naive_parser.dir/src/token_parser.o" \
"CMakeFiles/naive_parser.dir/src/token_type.o" \
"CMakeFiles/naive_parser.dir/src/var_type.o"

# External object files for target naive_parser
naive_parser_EXTERNAL_OBJECTS =

naive_parser: CMakeFiles/naive_parser.dir/src/array_parser.o
naive_parser: CMakeFiles/naive_parser.dir/src/branch_recurrent_parser.o
naive_parser: CMakeFiles/naive_parser.dir/src/codeblock_parser.o
naive_parser: CMakeFiles/naive_parser.dir/src/expression_parser.o
naive_parser: CMakeFiles/naive_parser.dir/src/function_parser.o
naive_parser: CMakeFiles/naive_parser.dir/src/global_parser.o
naive_parser: CMakeFiles/naive_parser.dir/src/indent_format.o
naive_parser: CMakeFiles/naive_parser.dir/src/local_parser.o
naive_parser: CMakeFiles/naive_parser.dir/src/naive_parser.o
naive_parser: CMakeFiles/naive_parser.dir/src/precompiler_parser.o
naive_parser: CMakeFiles/naive_parser.dir/src/program_parser.o
naive_parser: CMakeFiles/naive_parser.dir/src/syntax_parser.o
naive_parser: CMakeFiles/naive_parser.dir/src/token_parser.o
naive_parser: CMakeFiles/naive_parser.dir/src/token_type.o
naive_parser: CMakeFiles/naive_parser.dir/src/var_type.o
naive_parser: CMakeFiles/naive_parser.dir/build.make
naive_parser: CMakeFiles/naive_parser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cyx/cfiles/naive_parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX executable naive_parser"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/naive_parser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/naive_parser.dir/build: naive_parser

.PHONY : CMakeFiles/naive_parser.dir/build

CMakeFiles/naive_parser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/naive_parser.dir/cmake_clean.cmake
.PHONY : CMakeFiles/naive_parser.dir/clean

CMakeFiles/naive_parser.dir/depend:
	cd /home/cyx/cfiles/naive_parser/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cyx/cfiles/naive_parser /home/cyx/cfiles/naive_parser /home/cyx/cfiles/naive_parser/build /home/cyx/cfiles/naive_parser/build /home/cyx/cfiles/naive_parser/build/CMakeFiles/naive_parser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/naive_parser.dir/depend

