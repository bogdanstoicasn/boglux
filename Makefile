# Compiler
CC = gcc
OUT = boglux

# Directories

LIB_DIR = lib
SRC_DIR = src

# Flags for warnings and include directories

CFLAGS = -Wall -Wextra -std=c99 -I$(SRC_DIR)
LDFLAGS = 

# Source files

SRC = $(SRC_DIR)/boglux.c $(SRC_DIR)/command_parsing.c

# Object files created at build

OBJ = $(SRC:.c=.o)

# Build program
build: $(OBJ)
	$(CC) $(OBJ) -o $(out) $(LDFLAGS)

# Each source file separately
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run
run: build
	./$(OUT)

# Clean
clean:
	rm -f $(OBJ) $(OUT)

# Pack
pack:
	zip -FSr file.zip README Makefile $(SRC) $(LIB_DIR)/*.h

.PHONY: pack clean