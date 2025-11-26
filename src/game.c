/*
===========================================================
 Project:    Snake Game in Console
 File:       game.c
 Author:     Mobin Yousefi (GitHub: github.com/mobinyousefi-cs)
 Created:    2025-11-26
 Updated:    2025-11-26
 License:    MIT License (see LICENSE file for details)
===========================================================

 Description:
    Implements the core game logic: initialization, update,
    collision handling, scoring, and rendering.
===========================================================
*/

#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "utils.h"

Game *game_create(void)
{
    Game *game = (Game *)malloc(sizeof(Game));
    if (!game) {
        return NULL;
    }

    srand((unsigned int)time(NULL));

    game->board = board_create(BOARD_WIDTH, BOARD_HEIGHT);
    if (!game->board) {
        free(game);
        return NULL;
    }

    const int start_x = BOARD_WIDTH / 2;
    const int start_y = BOARD_HEIGHT / 2;

    game->snake = snake_create(start_x, start_y, DIR_RIGHT, 4);
    if (!game->snake) {
        board_destroy(game->board);
        free(game);
        return NULL;
    }

    game->score  = 0;
    game->status = GAME_RUNNING;

    board_place_food(game->board, game->snake);

    return game;
}

void game_destroy(Game *game)
{
    if (!game) {
        return;
    }

    snake_destroy(game->snake);
    board_destroy(game->board);
    free(game);
}

void game_change_direction(Game *game, Direction dir)
{
    if (!game || !game->snake) {
        return;
    }

    snake_set_direction(game->snake, dir);
}

void game_update(Game *game)
{
    if (!game || game->status != GAME_RUNNING) {
        return;
    }

    Position next = snake_next_head_position(game->snake);

    if (!board_is_inside(game->board, next.x, next.y)) {
        game->status = GAME_OVER_COLLISION;
        return;
    }

    if (snake_occupies(game->snake, next.x, next.y)) {
        game->status = GAME_OVER_COLLISION;
        return;
    }

    int grow = 0;
    if (next.x == game->board->food.x && next.y == game->board->food.y) {
        grow = 1;
        game->score += 10;
    }

    if (!snake_move(game->snake, grow)) {
        game->status = GAME_OVER_COLLISION;
        return;
    }

    if (grow) {
        board_place_food(game->board, game->snake);
    }
}

static char cell_symbol(const Game *game, int x, int y)
{
    if (x == game->board->food.x && y == game->board->food.y) {
        return '*';
    }

    const SnakeNode *node = game->snake->head;
    while (node) {
        if (node->pos.x == x && node->pos.y == y) {
            return (node == game->snake->head) ? 'O' : 'o';
        }
        node = node->next;
    }

    return ' ';
}

void game_render(const Game *game)
{
    if (!game) {
        return;
    }

    utils_clear_screen();

    printf("Score: %d\n", game->score);

    putchar('+');
    for (int x = 0; x < game->board->width; ++x) {
        putchar('-');
    }
    putchar('+');
    putchar('\n');

    for (int y = 0; y < game->board->height; ++y) {
        putchar('|');
        for (int x = 0; x < game->board->width; ++x) {
            putchar(cell_symbol(game, x, y));
        }
        putchar('|');
        putchar('\n');
    }

    putchar('+');
    for (int x = 0; x < game->board->width; ++x) {
        putchar('-');
    }
    putchar('+');
    putchar('\n');

    printf("Controls: W/A/S/D to move, Q to quit.\n");
}
