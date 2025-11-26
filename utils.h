/*
===========================================================
 Project:    Snake Game in Console
 File:       utils.h
 Author:     Mobin Yousefi (GitHub: github.com/mobinyousefi-cs)
 Created:    2025-11-26
 Updated:    2025-11-26
 License:    MIT License (see LICENSE file for details)
===========================================================

 Description:
    Cross-platform console utilities for clearing the screen,
    sleeping, and handling non-blocking keyboard input.
===========================================================
*/

#ifndef UTILS_H
#define UTILS_H

int  utils_terminal_init(void);
void utils_terminal_restore(void);

void utils_clear_screen(void);
void utils_sleep_ms(int ms);
int  utils_kbhit(void);
int  utils_getch(void);

#endif /* UTILS_H */
