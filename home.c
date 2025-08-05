/* SPDX-License-Identifier: MIT */

#include <curses.h>
#include "globals.h"

void draw_home(struct Screen *screen, char *input)  {
    static char* banner = ""
    "                 _                         _                             _   \n"
    "                 | |                       | |                           | |  \n"
    "   __ _ _ __ ___ | |__   ___ _ __ ___ _ __ | | __ _  ___ ___   _ __   ___| |_ \n"
    "  / _` | '_ ` _ \\| '_ \\ / _ \\ '__/ __| '_ \\| |/ _` |/ __/ _ \\ | '_ \\ / _ \\ __|\n"
    " | (_| | | | | | | |_) |  __/ |  \\__ \\ |_) | | (_| | (_|  __/_| | | |  __/ |_ \n"
    "  \\__,_|_| |_| |_|_.__/ \\___|_|  |___/ .__/|_|\\__,_|\\___\\___(_)_| |_|\\___|\\__|\n"
    "                                     | |                                      \n"
    "                                     |_|                                      \n";

    mvwprintw(screen->win, 1, 2, "Thank you for visiting:");
    mvwprintw(screen->win, 2, 1, "%s", banner);
    mvwprintw(screen->win, 10, 1, "Your current input is: %s", input);
}
