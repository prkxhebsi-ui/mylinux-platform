CC ?= clang
CFLAGS := -std=c11 -D_POSIX_C_SOURCE=200809L -D_DEFAULT_SOURCE \
          -Wall -Wextra -Wpedantic -O2 -Iinclude

SOURCES := src/core/main.c \
           src/core/unit.c \
           src/core/manager.c \
           src/android/compat.c

TARGET := out/systemd

.PHONY: all clean check

all: $(TARGET)

$(TARGET): $(SOURCES) include/systemd.h
mkdir -p out
$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

check: $(TARGET)
./$(TARGET) --version
./$(TARGET) --check units

clean:
rm -f $(TARGET)
