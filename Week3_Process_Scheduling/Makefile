
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
INCLUDES = -Iinclude

SRC = src/main.c src/haneena.c src/ayman.c src/vishnu.c
TARGET = scheduler.exe

.PHONY: all run clean test

all: $(TARGET)

$(TARGET): $(SRC) include/scheduler.h
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

test:
	$(CC) $(CFLAGS) $(INCLUDES) src/haneena.c tests/test_haneena.c -o test_haneena.exe
	./test_haneena.exe
	$(CC) $(CFLAGS) $(INCLUDES) src/ayman.c tests/test_ayman.c -o test_ayman.exe
	./test_ayman.exe
	$(CC) $(CFLAGS) $(INCLUDES) src/vishnu.c tests/test_vishnu.c -o test_vishnu.exe
	./test_vishnu.exe

clean:
	rm -f $(TARGET) test_haneena.exe test_ayman.exe test_vishnu.exe
