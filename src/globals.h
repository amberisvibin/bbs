/* SPDX-License-Identifier: MIT */

#define MAX_SCREEN_NAME_SIZE 20   /* size of the screen name array */
#define MAX_ERROR_MESSAGE_SIZE 60 /* size of error_message array */

#ifndef GLOBALS_H /* header guard */
#define GLOBALS_H

#include <curses.h>

extern char error_message[];

struct Screen {
    char name[MAX_SCREEN_NAME_SIZE];
    WINDOW *win;
    void (*draw_screen)(struct Screen *, char *input); /* GETCH_TIMEOUT determines how often this is run, in ms */
};

enum Status {
    STATUS_QUIT,
    STATUS_WAITING,
    STATUS_NEED_REFRESH
};

enum ActiveScreen {
    HOME,
    ERROR
};

#endif
