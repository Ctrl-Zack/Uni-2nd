SRC_DIR = source
INC_DIR = include
BIN_DIR = bin

TARGET = $(BIN_DIR)/main

SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

CC = gcc
CFLAGS = -I$(INC_DIR) -Wall -Wextra -O2

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
#	@mkdir -p $(BIN_DIR) for linux
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
#	rm -rf $(BIN_DIR)/*.o $(TARGET) for linux
	del /q bin\*.o bin\main.exe

run:
	$(BIN_DIR)/main.exe

.PHONY: all clean run
