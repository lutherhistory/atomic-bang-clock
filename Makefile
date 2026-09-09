# --- Compile Info ---
CC 			= gcc
CFLAGS 		= -g -Wall -Wextra -O2 -I./inc $(shell pkg-config --cflags gtk4 gstreamer-1.0) -DTHIS_PATH=\"$(THIS_PATH)\"
LIBS 		= $(shell pkg-config --libs gtk4 gstreamer-1.0)

THIS_PATH = $(shell pwd)

# --- Sources ---
TARGET 		= build/atomic-bang-clock
SRC 		= $(wildcard src/*.c)
OBJ 		= $(patsubst src/%.c, build/%.o, $(SRC))

# --- Targets ---
.PHONY: all clean run

all: $(TARGET)

# --- Linking ---
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

# --- Compiling ---
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# --- Build Directory ---
build:
	mkdir -p build

# --- Run ---
run: $(TARGET)
	./$(TARGET)

# --- Clean ---
clean:
	rm -rf build
