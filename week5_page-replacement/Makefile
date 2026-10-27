CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

SOURCES = src/main.c src/fifo.c src/lru.c src/optimal.c src/statistics.c
TARGET = simulator.exe
GUI_TARGET = simulator_gui.exe

.PHONY: all run gui test clean

all: $(TARGET)

$(TARGET): $(SOURCES) include/common.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

gui: $(GUI_TARGET)

$(GUI_TARGET): src/gui.c src/fifo.c src/lru.c src/optimal.c include/common.h
	$(CC) $(CFLAGS) -mwindows src/gui.c src/fifo.c src/lru.c src/optimal.c -o $(GUI_TARGET) -lcomctl32

test: test_fifo.exe test_lru.exe test_optimal.exe
	./test_fifo.exe
	./test_lru.exe
	./test_optimal.exe

test_fifo.exe: tests/test_fifo.c src/fifo.c include/common.h
	$(CC) $(CFLAGS) tests/test_fifo.c src/fifo.c -o test_fifo.exe

test_lru.exe: tests/test_lru.c src/lru.c include/common.h
	$(CC) $(CFLAGS) tests/test_lru.c src/lru.c -o test_lru.exe

test_optimal.exe: tests/test_optimal.c src/optimal.c include/common.h
	$(CC) $(CFLAGS) tests/test_optimal.c src/optimal.c -o test_optimal.exe

clean:
	rm -f $(TARGET) $(GUI_TARGET) test_fifo.exe test_lru.exe test_optimal.exe
