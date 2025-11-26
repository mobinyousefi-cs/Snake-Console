/*
===========================================================
 Project:    Snake Game in Console
 File:       input.h
 Author:     Mobin Yousefi (GitHub: github.com/mobinyousefi-cs)
 Created:    2025-11-26
 Updated:    2025-11-26
 License:    MIT License (see LICENSE file for details)
===========================================================

 Description:
    Input abstraction layer. Polls the keyboard using the
    utilities in utils.c and maps keys to high-level actions.
===========================================================
*/

#ifndef INPUT_H
#define INPUT_H

typedef enum InputAction {
    INPUT_NONE = 0,
    INPUT_TURN_UP,
    INPUT_TURN_DOWN,
    INPUT_TURN_LEFT,
    INPUT_TURN_RIGHT,
    INPUT_QUIT
} InputAction;

InputAction input_poll(void);

#endif /* INPUT_H */
