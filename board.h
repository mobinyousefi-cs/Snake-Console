/*
===========================================================
 Project:    Snake Game in Console
 File:       board.h
 Author:     Mobin Yousefi (GitHub: github.com/mobinyousefi-cs)
 Created:    2025-11-26
 Updated:    2025-11-26
 License:    MIT License (see LICENSE file for details)
===========================================================

 Description:
    Board representation and operations, including food
    placement and boundary checks.
===========================================================
*/

#ifndef BOARD_H
#define BOARD_H

#include "snake.h"

typedef struct Board {
    int      width;
    int      height;
    Position food;
} Board;

Board *board_create(int width, int height);
void   board_destroy(Board *board);

int    board_is_inside(const Board *board, int x, int y);
void   board_place_food(Board *board, const Snake *snake);

#endif /* BOARD_H */
