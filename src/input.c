/*
===========================================================
 Project:    Snake Game in Console
 File:       input.c
 Author:     Mobin Yousefi (GitHub: github.com/mobinyousefi-cs)
 Created:    2025-11-26
 Updated:    2025-11-26
 License:    MIT License (see LICENSE file for details)
===========================================================

 Description:
    Maps raw key presses to high-level input actions used
    by the game loop.
===========================================================
*/

#include "input.h"
#include "utils.h"

InputAction input_poll(void)
{
    if (!utils_kbhit()) {
        return INPUT_NONE;
    }

    int ch = utils_getch();
    if (ch == -1) {
        return INPUT_NONE;
    }

    switch (ch) {
    case 'w':
    case 'W':
        return INPUT_TURN_UP;
    case 's':
    case 'S':
        return INPUT_TURN_DOWN;
    case 'a':
    case 'A':
        return INPUT_TURN_LEFT;
    case 'd':
    case 'D':
        return INPUT_TURN_RIGHT;
    case 'q':
    case 'Q':
        return INPUT_QUIT;
    default:
        return INPUT_NONE;
    }
}
