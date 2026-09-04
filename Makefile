# Compiler and Flags
CC = gcc
CFLAGS = -g -Wall -Wextra $(shell pkg-config --cflags gtk4)
LDFLAGS = $(shell pkg-config --libs gtk4)

# Directory Paths
BUILD_PATH  = build
SRC_PATH 	= src
OBJ_PATH	= $(BUILD_PATH)/obj

TARGET 		= $(BUILD_PATH)/atomic-clock

# Source and Object files
SRC 		:= $(wildcard $(SRC_PATH)/*.c)
OBJ 		:= $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC))

# Create directories
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

# Default target
all: $(OBJ_PATH) $(TARGET)

# Link object files to executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✅ Build complete! Binary: $(TARGET)"

# Compile source files to object files
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_PATH)
	@echo "🧹 Clean complete!"

# Run the application
run: all
	./$(TARGET)

# Run with valgrind (memory check)
memcheck: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Show debug info
debug:
	@echo "SRC: $(SRC)"
	@echo "OBJ: $(OBJ)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "LDFLAGS: $(LDFLAGS)"

.PHONY: all clean run memcheck debug