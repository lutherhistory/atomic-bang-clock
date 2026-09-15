# --- Compile Info ---
CC      = gcc
CFLAGS  = -g -Wall -Wextra -O2 -I./inc $(shell pkg-config --cflags gtk4 gstreamer-1.0)
LIBS    = $(shell pkg-config --libs gtk4 gstreamer-1.0)

# --- Sources ---
TARGET  = build/atomic-bang-clock
SRC     = $(wildcard src/*.c)
OBJ     = $(patsubst src/%.c, build/%.o, $(SRC))

# --- Resources ---
RESOURCE_XML = resources/atomic-bang-clock.gresources.xml
RESOURCE_C   = build/resources.c
RESOURCE_O   = build/resources.o

# --- Targets ---
.PHONY: all clean run

all: $(TARGET)

# --- Linking ---
$(TARGET): $(OBJ) $(RESOURCE_O)
	$(CC) $(OBJ) $(RESOURCE_O) -o $@ $(LIBS)

# --- Compiling ---
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# --- Compile GResource ---
$(RESOURCE_C): $(RESOURCE_XML) $(shell find resources -type f) | build
	glib-compile-resources $(RESOURCE_XML) \
		--generate-source \
		--target=$@

# --- Compile generated resource ---
$(RESOURCE_O): $(RESOURCE_C)
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
