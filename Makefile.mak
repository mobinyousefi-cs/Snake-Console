# ==========================================================
#  Project:    Snake Game in Console
#  File:       Makefile
#  Author:     Mobin Yousefi (GitHub: github.com/mobinyousefi-cs)
#  Created:    2025-11-26
#  Updated:    2025-11-26
#  License:    MIT License (see LICENSE file for details)
# ==========================================================

CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -pedantic -O2
INCLUDE := -I./

SRC := \
    src/main.c \
    src/game.c \
    src/snake.c \
    src/board.c \
    src/input.c \
    src/utils.c

OBJ    := $(SRC:.c=.o)
TARGET := snake_game

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
