# Sets default compiler
CC = g++

# Sets flags
CFLAGS = -Wall -Wextra -pedantic
CVERSION = -std=c++17

# Main
all: clean assembler

assembler:
	# Compiles the assembler
	$(CC) $(CVERSION) $(CFLAGS) -o assembler.o assembler.cpp

clean:
	# Deletes binary files
	-rm $(objects) *.o