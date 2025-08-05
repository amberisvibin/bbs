/* SPDX-License-Identifier: MIT */

#define MAX_ERROR_MESSAGE_SIZE 60 /* size of error_message array */
#define MAX_SCREEN_NAME_SIZE 20   /* size of the screen name array */

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
    char name[MAX_SCREEN_NAME_SIZE];
    WINDOW *win;
    void (*draw_screen)(struct Screen *, char *input); /* GETCH_TIMEOUT determines how often this is run, in ms */
};

/* TODO: put this in a screens.c file and include all screens there, that way the array can be initialized at compile
 * time */
extern struct Screen screens[];

#endif
