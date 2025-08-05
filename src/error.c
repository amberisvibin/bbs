/* SPDX-License-Identifier: MIT */

#include <curses.h>
#include "screens.h"

void draw_error(struct Screen *screen, __attribute__((unused)) char *input)  {
    mvwprintw(screen->win, 1, 2, "%s", error_message);
}
