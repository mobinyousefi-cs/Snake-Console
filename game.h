/*
===========================================================
 Project:    Snake Game in Console
 File:       game.h
 Author:     Mobin Yousefi (GitHub: github.com/mobinyousefi-cs)
 Created:    2025-11-26
 Updated:    2025-11-26
 License:    MIT License (see LICENSE file for details)
===========================================================

 Description:
    Public interface for the core game state and logic.
    Encapsulates the snake, board, score, and game status.
===========================================================
*/

#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "snake.h"

typedef enum GameStatus {
    GAME_RUNNING = 0,
    GAME_OVER_QUIT,
    GAME_OVER_COLLISION
} GameStatus;

typedef struct Game {
    Board      *board;
    Snake      *snake;
    int         score;
    GameStatus  status;
} Game;

Game *game_create(void);
void  game_destroy(Game *game);

void  game_update(Game *game);
void  game_change_direction(Game *game, Direction dir);
void  game_render(const Game *game);

#endif /* GAME_H */
