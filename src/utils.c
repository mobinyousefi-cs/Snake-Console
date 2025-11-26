/*
===========================================================
 Project:    Snake Game in Console
 File:       utils.c
 Author:     Mobin Yousefi (GitHub: github.com/mobinyousefi-cs)
 Created:    2025-11-26
 Updated:    2025-11-26
 License:    MIT License (see LICENSE file for details)
===========================================================

 Description:
    Cross-platform console utilities:
      - raw terminal configuration (POSIX)
      - non-blocking input
      - clear screen
      - millisecond sleep
===========================================================
*/

#include "utils.h"

#include <stdio.h>

#ifdef _WIN32

#  include <conio.h>
#  include <windows.h>

int utils_terminal_init(void)
{
    return 1;
}

void utils_terminal_restore(void)
{
}

void utils_clear_screen(void)
{
    system("cls");
}

void utils_sleep_ms(int ms)
{
    Sleep((DWORD)ms);
}

int utils_kbhit(void)
{
    return _kbhit();
}

int utils_getch(void)
{
    return _getch();
}

#else /* POSIX */

#  include <termios.h>
#  include <unistd.h>
#  include <sys/select.h>
#  include <time.h>

static struct termios g_orig_termios;
static int            g_terminal_configured = 0;

int utils_terminal_init(void)
{
    if (g_terminal_configured) {
        return 1;
    }

    if (tcgetattr(STDIN_FILENO, &g_orig_termios) == -1) {
        perror("tcgetattr");
        return 0;
    }

    struct termios raw = g_orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN]  = 0;
    raw.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) == -1) {
        perror("tcsetattr");
        return 0;
    }

    g_terminal_configured = 1;
    return 1;
}

void utils_terminal_restore(void)
{
    if (!g_terminal_configured) {
        return;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &g_orig_termios);
    g_terminal_configured = 0;
}

void utils_clear_screen(void)
{
    const char *clear_seq = "\033[2J\033[H";
    write(STDOUT_FILENO, clear_seq, 7);
}

void utils_sleep_ms(int ms)
{
    struct timespec ts;
    ts.tv_sec  = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000L;
    nanosleep(&ts, NULL);
}

int utils_kbhit(void)
{
    struct timeval tv;
    fd_set         fds;

    tv.tv_sec  = 0;
    tv.tv_usec = 0;

    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    int ret = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return (ret > 0) && FD_ISSET(STDIN_FILENO, &fds);
}

int utils_getch(void)
{
    unsigned char ch;
    ssize_t       n = read(STDIN_FILENO, &ch, 1);
    if (n <= 0) {
        return -1;
    }
    return (int)ch;
}

#endif /* _WIN32 */
