# Compiler and base flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -I.

# Binary name
TARGET = linked-list

# Source and object files
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)

# Ensure build dir exists
$(shell mkdir -p build)

# Default rule: release build
all: release

# Rule to build the binary
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

# Rule to compile each object file
build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Debug build
debug: CFLAGS += -DDEBUG -g
debug: clean $(TARGET)
	./$(TARGET)

# Release build
release: CFLAGS += -O2
release: clean $(TARGET)
	./$(TARGET)

# Run (without forcing rebuild)
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)
