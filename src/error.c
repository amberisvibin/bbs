/* SPDX-License-Identifier: MIT */

#include <curses.h>
#include "screens.h"

/* char *input is unused */
void draw_error(struct Screen *screen, char *input) {
    box(screen->win, 0, 0);
    mvwprintw(screen->win, 1, 2, "%s", error_message);
}
