# bbs (working name)

This is a simple bbs program written in c. The way it is meant to work is that a user would ssh into a server, which would auto-launch this program.

## Building

The only dependency is `ncurses`. The makefile asks for `-lncursesw` but unicode is not yet used, so `-lncurses` should be fine. `ncurses` is almost guaranteed preinstalled on your system.

To build, run `make`. It will drop an executable named `bbs` in the current folder.

The makefile has the additional command `make run`, which just launches the program after compilation.

## License

The program is distributed under the MIT license. See the `LICENSE` file.
