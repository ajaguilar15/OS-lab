# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c17

# Executables
TARGETS = generate_file file_mem_map

# Default target
all: $(TARGETS)

# Build generate_file
generate_file: generate_file.c
	$(CC) $(CFLAGS) -o generate_file generate_file.c

# Build file_mem_map
file_mem_map: file_mem_map.c
	$(CC) $(CFLAGS) -o file_mem_map file_mem_map.c

# Clean build files
clean:
	rm -f $(TARGETS)

# Rebuild everything
rebuild: clean all
