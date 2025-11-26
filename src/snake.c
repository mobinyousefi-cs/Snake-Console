/*
===========================================================
 Project:    Snake Game in Console
 File:       snake.c
 Author:     Mobin Yousefi (GitHub: github.com/mobinyousefi-cs)
 Created:    2025-11-26
 Updated:    2025-11-26
 License:    MIT License (see LICENSE file for details)
===========================================================

 Description:
    Implementation of snake operations, including creation,
    movement, growth, and occupancy checks.
===========================================================
*/

#include "snake.h"

#include <stdlib.h>

static SnakeNode *allocate_node(int x, int y)
{
    SnakeNode *node = (SnakeNode *)malloc(sizeof(SnakeNode));
    if (!node) {
        return NULL;
    }
    node->pos.x = x;
    node->pos.y = y;
    node->next  = NULL;
    return node;
}

Snake *snake_create(int start_x, int start_y, Direction dir, int initial_length)
{
    if (initial_length <= 0) {
        return NULL;
    }

    Snake *snake = (Snake *)malloc(sizeof(Snake));
    if (!snake) {
        return NULL;
    }

    SnakeNode *head = allocate_node(start_x, start_y);
    if (!head) {
        free(snake);
        return NULL;
    }

    snake->head   = head;
    snake->tail   = head;
    snake->dir    = dir;
    snake->length = 1;

    for (int i = 1; i < initial_length; ++i) {
        int x = start_x - i;
        int y = start_y;

        SnakeNode *node = allocate_node(x, y);
        if (!node) {
            snake_destroy(snake);
            return NULL;
        }

        snake->tail->next = node;
        snake->tail       = node;
        snake->length++;
    }

    return snake;
}

void snake_destroy(Snake *snake)
{
    if (!snake) {
        return;
    }

    SnakeNode *node = snake->head;
    while (node) {
        SnakeNode *next = node->next;
        free(node);
        node = next;
    }

    free(snake);
}

void snake_set_direction(Snake *snake, Direction dir)
{
    if (!snake) {
        return;
    }

    if ((snake->dir == DIR_UP && dir == DIR_DOWN) ||
        (snake->dir == DIR_DOWN && dir == DIR_UP) ||
        (snake->dir == DIR_LEFT && dir == DIR_RIGHT) ||
        (snake->dir == DIR_RIGHT && dir == DIR_LEFT)) {
        return;
    }

    snake->dir = dir;
}

Position snake_next_head_position(const Snake *snake)
{
    Position next = snake->head->pos;

    switch (snake->dir) {
    case DIR_UP:
        next.y -= 1;
        break;
    case DIR_DOWN:
        next.y += 1;
        break;
    case DIR_LEFT:
        next.x -= 1;
        break;
    case DIR_RIGHT:
        next.x += 1;
        break;
    }

    return next;
}

int snake_move(Snake *snake, int grow)
{
    if (!snake) {
        return 0;
    }

    Position next = snake_next_head_position(snake);

    SnakeNode *new_head = allocate_node(next.x, next.y);
    if (!new_head) {
        return 0;
    }

    new_head->next = snake->head;
    snake->head    = new_head;
    snake->length++;

    if (!grow) {
        SnakeNode *prev = NULL;
        SnakeNode *curr = snake->head;

        while (curr->next) {
            prev = curr;
            curr = curr->next;
        }

        if (prev) {
            prev->next = NULL;
            snake->tail = prev;
        } else {
            snake->tail = snake->head;
        }

        free(curr);
        snake->length--;
    }

    return 1;
}

int snake_occupies(const Snake *snake, int x, int y)
{
    if (!snake) {
        return 0;
    }

    const SnakeNode *node = snake->head;
    while (node) {
        if (node->pos.x == x && node->pos.y == y) {
            return 1;
        }
        node = node->next;
    }

    return 0;
}
