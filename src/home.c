/* SPDX-License-Identifier: MIT */

#include <curses.h>
#include "screens.h"
#include "version.h"

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
    wclrtoeol(screen->win); /* clear rest of line to prevent longer inputs from sticking around */
    mvwprintw(screen->win, 11, 1, "Git hash: %s", GIT_HASH);
    mvwprintw(screen->win, 12, 1, "Git tag: %s", GIT_TAG);
    mvwprintw(screen->win, 13, 1, "CC version: %s", CC_VERSION);
    mvwprintw(screen->win, 14, 1, "Build date: %s", BUILD_DATE);
    box(screen->win, 0, 0);
}
