/*
===========================================================
 Project:    Snake Game in Console
 File:       snake.h
 Author:     Mobin Yousefi (GitHub: github.com/mobinyousefi-cs)
 Created:    2025-11-26
 Updated:    2025-11-26
 License:    MIT License (see LICENSE file for details)
===========================================================

 Description:
    Data structures and operations for the snake entity,
    including movement, growth, and self-collision queries.
===========================================================
*/

#ifndef SNAKE_H
#define SNAKE_H

typedef struct Position {
    int x;
    int y;
} Position;

typedef enum Direction {
    DIR_UP = 0,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

typedef struct SnakeNode {
    Position          pos;
    struct SnakeNode *next;
} SnakeNode;

typedef struct Snake {
    SnakeNode *head;
    SnakeNode *tail;
    Direction  dir;
    int        length;
} Snake;

Snake   *snake_create(int start_x, int start_y, Direction dir, int initial_length);
void     snake_destroy(Snake *snake);

void     snake_set_direction(Snake *snake, Direction dir);
Position snake_next_head_position(const Snake *snake);
int      snake_move(Snake *snake, int grow);
int      snake_occupies(const Snake *snake, int x, int y);

#endif /* SNAKE_H */
