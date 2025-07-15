#include <curses.h>
#include <string.h>

int terminal_width;
int terminal_height;

char errorMessage[60];

enum Status {
    WAITING,
    NEED_REFRESH
};

enum ActiveScreen {
    HOME,
    ERROR
};

struct Screen {
    char name[20];
    WINDOW *win;
    void (*draw_screen)(struct Screen *);
};

void draw_home(struct Screen *screen)  {
    char* banner = ""
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
}

void draw_error(struct Screen *screen)  {
    mvwprintw(screen->win, 1, 2, "%s", errorMessage);
}

void draw_screen (struct Screen *screen) {
    screen->draw_screen(screen);
    box(screen->win, 0, 0);

    mvwprintw(screen->win, 0, 1, " %s ", screen->name);
}

int main() {

    initscr();   /* start ncurses */
    noecho();    /* hide keyboard input */
    curs_set(0); /* disable cursor */
    timeout(10); /* set timeout for getch() to 10ms */

    int start_y = 0;
    int start_x = 0;
    int old_terminal_width = 0;
    int old_terminal_height = 0;

    struct Screen screens[5];

    enum Status status = NEED_REFRESH; /* refresh screens[active_screen].window on first loop */
    char input = ' ';

    strcpy(errorMessage, "");

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
    while (input != 'q') {
        if ((input = getch())) { /* if any input was read */
            status = NEED_REFRESH;
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
                    strcpy(errorMessage, "This program expects at least 80 rows by 24 columns.");
                    screen_before_error = active_screen;
                };
                active_screen = ERROR;
            } else if (active_screen != screen_before_error) {
                active_screen = screen_before_error;
            };
            status = NEED_REFRESH;
        };

        /* refresh active screen's window */
        if (status == NEED_REFRESH) {
            draw_screen(&screens[active_screen]);
            wrefresh(screens[active_screen].win);
            status = WAITING;
        }

    };

    delwin(screens[active_screen].win);
    nocbreak(); /* cbreak is the not needing to press enter on input, gets set in initscr, not undoing it causes
                   printing errors after exit as this is a setting of the terminal itself */
    endwin();   /* ends curses mode */
    curs_set(1);
    echo();
    return 0;
}
