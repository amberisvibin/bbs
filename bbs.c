/* SPDX-License-Identifier: MIT */

#include <curses.h>
#include <string.h>
#include <locale.h>

#define MAX_ERROR_MESSAGE_SIZE 60      /* size of error_message array */
#define MAX_SCREENS 2                  /* size of screens array */

const unsigned int GETCH_TIMEOUT = 10; /* in ms */
const char* LOCALE = "en_US.UTF-8";    /* enable unicode support, set to "ANSI_X3.4-1968" for ascii */

char error_message[MAX_ERROR_MESSAGE_SIZE];

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

static void draw_home(struct Screen *screen, char *input)  {
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

static void draw_error(struct Screen *screen, __attribute__((unused)) char *input)  {
    mvwprintw(screen->win, 1, 2, "%s", error_message);
}

static void draw_screen (struct Screen *screen, char *input) {
    screen->draw_screen(screen, input);
    box(screen->win, 0, 0);
    /* wattron(screen->win, A_STANDOUT); */
    mvwprintw(screen->win, 0, 1, " %s ", screen->name);
    /* wattroff(screen->win, A_STANDOUT); */
}

int main() {

    initscr();                   /* start ncurses */
    noecho();                    /* hide keyboard input */
    curs_set(0);                 /* disable cursor */
    timeout(GETCH_TIMEOUT);      /* set timeout for getch() */
    setlocale(LC_CTYPE, LOCALE); /* set locale, UTF8 support is enabled here */

    unsigned int start_y = 0;
    unsigned int start_x = 0;
    unsigned int terminal_width;
    unsigned int terminal_height;
    unsigned int old_terminal_width = 0;
    unsigned int old_terminal_height = 0;

    struct Screen screens[MAX_SCREENS];

    enum Status status = STATUS_NEED_REFRESH; /* refresh screens[active_screen].window on first loop */
    char input = ' ';

    strcpy(error_message, "");

    getmaxyx(stdscr, terminal_height, terminal_width);

    unsigned int screen_before_error = HOME;

    enum ActiveScreen active_screen = HOME;
    struct Screen home = {
        "home",
        newwin(terminal_height, terminal_width, start_y, start_x),
        draw_home
    };
    screens[HOME] = home;
    struct Screen error = {
        "error",
        newwin(terminal_height, terminal_width, start_y, start_x),
        draw_error
    };
    screens[ERROR] = error;

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

        /* resize active screen's window */
        if (old_terminal_width != terminal_width || old_terminal_height != terminal_height) {
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
        };

        /* refresh active screen's window */
        if (status == STATUS_NEED_REFRESH) {
            draw_screen(&screens[active_screen], &input);
            wrefresh(screens[active_screen].win);
            status = STATUS_WAITING;
        }

    };

    /* clean up */
    delwin(screens[active_screen].win);
    nocbreak();
    endwin();   /* ends curses mode */
    curs_set(1);
    echo();
    return 0;
}
