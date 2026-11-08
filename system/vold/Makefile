CC ?= clang
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Wpedantic
CPPFLAGS += -Iinclude

TARGET := build/mylinux-vold
SOURCES := main.c VolumeManager.c

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCES) include/mylinux_vold.h
mkdir -p build
$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES) -o $@

run: $(TARGET)
./$(TARGET) --help

clean:
rm -f $(TARGET)
