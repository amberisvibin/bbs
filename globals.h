/* SPDX-License-Identifier: MIT */

#define MAX_SCREENS 2 /* size of screens array */

#ifndef GLOBALS_H /* header guard */
#define GLOBALS_H

enum Status {
    STATUS_QUIT,
    STATUS_WAITING,
    STATUS_NEED_REFRESH
};

enum ActiveScreen {
    HOME,
    ERROR
};

struct Screen {
    char name[20];
    WINDOW *win;
    void (*draw_screen)(struct Screen *, char *input); /* GETCH_TIMEOUT determines how often this is run, in ms */
};

struct Screen screens[MAX_SCREENS];

#endif
