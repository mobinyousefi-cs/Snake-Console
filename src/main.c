/*
===========================================================
 Project:    Snake Game in Console
 File:       main.c
 Author:     Mobin Yousefi (GitHub: github.com/mobinyousefi-cs)
 Created:    2025-11-26
 Updated:    2025-11-26
 License:    MIT License (see LICENSE file for details)
===========================================================

 Description:
    Entry point for the console-based Snake Game.
    Initializes the game, configures the terminal, and runs
    the main game loop until the player quits or the game ends.

 Usage:
    make
    ./snake_game

 Notes:
    - Uses a simple game loop with a fixed tick duration.
    - Input is polled in non-blocking mode so the snake
      continues moving even when no key is pressed.
===========================================================
*/

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "game.h"
#include "input.h"
#include "utils.h"

int main(void)
{
    if (!utils_terminal_init()) {
        fprintf(stderr, "[ERROR] Failed to initialize terminal.\n");
        return EXIT_FAILURE;
    }

    atexit(utils_terminal_restore);

    Game *game = game_create();
    if (!game) {
        fprintf(stderr, "[ERROR] Failed to create game.\n");
        return EXIT_FAILURE;
    }

    utils_clear_screen();

    while (game->status == GAME_RUNNING) {
        InputAction action = input_poll();

        switch (action) {
        case INPUT_TURN_UP:
            game_change_direction(game, DIR_UP);
            break;
        case INPUT_TURN_DOWN:
            game_change_direction(game, DIR_DOWN);
            break;
        case INPUT_TURN_LEFT:
            game_change_direction(game, DIR_LEFT);
            break;
        case INPUT_TURN_RIGHT:
            game_change_direction(game, DIR_RIGHT);
            break;
        case INPUT_QUIT:
            game->status = GAME_OVER_QUIT;
            break;
        case INPUT_NONE:
        default:
            break;
        }

        game_update(game);
        game_render(game);

        utils_sleep_ms(GAME_TICK_MS);
    }

    utils_clear_screen();

    if (game->status == GAME_OVER_COLLISION) {
        printf("Game Over! Final score: %d\n", game->score);
    } else if (game->status == GAME_OVER_QUIT) {
        printf("You quit the game. Final score: %d\n", game->score);
    }

    game_destroy(game);
    return EXIT_SUCCESS;
}
