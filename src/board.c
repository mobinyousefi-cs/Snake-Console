/*
===========================================================
 Project:    Snake Game in Console
 File:       board.c
 Author:     Mobin Yousefi (GitHub: github.com/mobinyousefi-cs)
 Created:    2025-11-26
 Updated:    2025-11-26
 License:    MIT License (see LICENSE file for details)
===========================================================

 Description:
    Implementation of board operations, including creation,
    destruction, boundary checks, and random food placement.
===========================================================
*/

#include "board.h"

#include <stdlib.h>

Board *board_create(int width, int height)
{
    if (width <= 0 || height <= 0) {
        return NULL;
    }

    Board *board = (Board *)malloc(sizeof(Board));
    if (!board) {
        return NULL;
    }

    board->width  = width;
    board->height = height;
    board->food.x = width / 2;
    board->food.y = height / 2;

    return board;
}

void board_destroy(Board *board)
{
    if (!board) {
        return;
    }
    free(board);
}

int board_is_inside(const Board *board, int x, int y)
{
    if (!board) {
        return 0;
    }

    return (x >= 0 && x < board->width && y >= 0 && y < board->height);
}

void board_place_food(Board *board, const Snake *snake)
{
    if (!board) {
        return;
    }

    int x, y;

    do {
        x = rand() % board->width;
        y = rand() % board->height;
    } while (snake && snake_occupies(snake, x, y));

    board->food.x = x;
    board->food.y = y;
}
