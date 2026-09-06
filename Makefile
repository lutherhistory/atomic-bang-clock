# --- Compile Info ---
CC 			= gcc
CFLAGS 		= -Wall -Wextra -O2 $(shell pkg-config --cflags gtk4)
LIBS 		= $(shell pkg-config --libs gtk4)

# --- Sources ---
TARGET 		= build/atomic-bang-clock
SRC 		= $(wildcard src/*.c)
OBJ 		= $(patsubst src/%.c, build/%.o, $(SRC))

# --- Targets ---
.PHONY: all clean

all: $(TARGET)

# --- Linking ---
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

# --- Compiling ---
build/%.o: src/%.c | build
	bear -- $(CC) $(CFLAGS) -c $< -o $@

# --- Build Directory ---
build:
	mkdir -p build

# --- Clean ---
clean:
	rm -rf build $(TARGET)
