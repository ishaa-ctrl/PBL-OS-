
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

TARGET = deadlock.exe

SOURCES = src/main.c \
          src/banker.c \
          src/detection.c \
          src/gui.c \
          src/rag.c

all: $(TARGET)

$(TARGET): $(SOURCES) include/deadlock.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	del /Q $(TARGET) 2>NUL

.PHONY: all run clean

