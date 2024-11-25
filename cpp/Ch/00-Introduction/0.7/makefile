# the compiler CC: gcc for C programs, define as g++ for c++
CC = g++

# compiler flags CFLAGS:
#  -ggdb				- Includes debugging info in the executable,
#  						  allowing you to use tools like GDB (GNU Debugger)
#
#  -std=c++23			- Specifies the C++ language standard to be C++23
#
#  -pedantic			- Generates additional warning and errors to enforce
#  						  strict adherence to the C++ standard. It helps ensure
#  						  portability and compliance with language specifications
#
#  -Wall 				- Enables set of common warnings.
#  						  It stands for "all warnings"
#
#  -Weffc++				- Warns about violations of Effective C++ coding
#  						  standards. This set of guidelines aims to improve
#  						  C++ code quality and maintainability
#
#  -Wextra				- Enables additional warning messages not covered by -Wall
#
#  -Wconversion			- Warns about implicit type conversions that may
#  						  result in loss of data
#
#  -Wsign-conversion	- Warns about sign-conversion issues when converting
#  						  between signed and unsigned integers
#
#  -Werror				- Treats all warning messages as errors, making the
#  						  compilation fail if there are any warnings. Used to
#  						  enforce a strict policy on code quality
#
CFLAGS = -ggdb -std=c++23 -pedantic -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror

# The build target. Change HelloWorld depending on the file
TARGET = HelloWorld

# The default target 'all' specifies that when you run 'make' without any target
# it should build the target specified in its dependency list, which is $(TARGET)
all: $(TARGET)

# The rule to build the target $(TARGET). It depends on $(TARGET).cpp
# meaning if $(TARGET).cpp is modified, this rule will be executed to rebuild the target
$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp
#	$(CC): Compiler command (g++)
#	$(CFLAGS): Compiler flags, including debugging info, C++ standard, warnings, etc
#	-o $(TARGET): Specifies the output file name
#	$(TARGET).cpp: Input source file

# The 'clean' target, which is used to remove generated files and start fresh
# Runnings 'make clean' will remove the executable
clean:
	$(RM) $(TARGET)
#	$(RM): Remove command
#	$(TARGET): The target file to be removed
