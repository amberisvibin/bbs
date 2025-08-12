/* SPDX-License-Identifier: MIT */

#include <curses.h>
#include <string.h>
#include <locale.h>
#include "globals.h"
#include "screens.h"

char error_message[MAX_ERROR_MESSAGE_SIZE];

unsigned int terminal_width;
unsigned int terminal_height;
unsigned int old_terminal_width = 0;
unsigned int old_terminal_height = 0;

enum Status status = STATUS_NEED_REFRESH; /* refresh screens[active_screen].window on first loop */
char input = ' ';

unsigned int screen_before_error = HOME;
enum ActiveScreen active_screen = HOME;

static void draw_screen (struct Screen *screen, char *input) {
    screen->draw_screen(screen, input);
    wattron(screen->win, A_STANDOUT);
    mvwprintw(screen->win, 0, 1, " %s ", screen->name);
    wattroff(screen->win, A_STANDOUT);
}

static void resize_active_screen() {
    wclear(screens[active_screen].win);
    wresize(screens[active_screen].win, terminal_height, terminal_width);
    mvwin(screens[active_screen].win, 0, 0);
    wrefresh(screens[active_screen].win);
    old_terminal_width = terminal_width;
    old_terminal_height = terminal_height;

    if (terminal_width < 80 || terminal_height < 24) {
        if (active_screen != ERROR) {
            strcpy(error_message, "This program expects at least 80 rows by 24 columns.");
            screen_before_error = active_screen;
        };
        active_screen = ERROR;
    } else if (active_screen != screen_before_error) {
        active_screen = screen_before_error;
    };
    status = STATUS_NEED_REFRESH;
}

int main() {

    initscr();                   /* start ncurses */
    noecho();                    /* hide keyboard input */
    curs_set(0);                 /* disable cursor */
    keypad(stdscr, TRUE);        /* enable extra keys */
    timeout(GETCH_TIMEOUT);      /* set timeout for getch() */
    setlocale(LC_CTYPE, "");     /* set locale to current locale */

    strcpy(error_message, "");

    getmaxyx(stdscr, terminal_height, terminal_width);



    /* could be it's own init func within the screen's file. */
    screens[HOME].win = newwin(terminal_height, terminal_width, 0, 0);
    screens[ERROR].win = newwin(terminal_height, terminal_width, 0, 0);

    /* main event loop */
    while (status != STATUS_QUIT) {
        if ((input = getch())) { /* if any input was read */
            /* TODO: factor out input to another function */
            if (input == 'q') {
                status = STATUS_QUIT;
            } else {
                status = STATUS_NEED_REFRESH;
            };
        };

        getmaxyx(stdscr, terminal_height, terminal_width);
        if (old_terminal_width != terminal_width || old_terminal_height != terminal_height) {
            resize_active_screen();
        };

        /* refresh active screen's window */
        if (status == STATUS_NEED_REFRESH) {
            draw_screen(&screens[active_screen], &input);
            wrefresh(screens[active_screen].win);
            status = STATUS_WAITING;
        }

    };

    /* clean up */
    delwin(screens[0].win); /* could be in a destructor function in the screen's file */
    delwin(screens[1].win);
    nocbreak();
    endwin();   /* ends curses mode */
    curs_set(1);
    echo();
    return 0;
}
