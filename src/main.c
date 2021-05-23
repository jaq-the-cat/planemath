#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ncurses.h>

#include "physics.h"

int main() {
    int position;
    PhysicsObject mig15 = {
        0, // initial horizontal velocity (m/s)
        0, // initial vertical velocity (m/s)
        0, // initial angle (degrees)
        4500, // mass (kg)
        (26.5)*1000, // thrust (N)
        0.7, // lift constant
        0.2, // drag coefficient at 0°
        0.9, // drag coefficient at 90°
        3, // frontal area at 0°
        24, // frontal area at 90°
        25, // wing area
    };

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    int input;
    while ((input = getch()) != 'q') {
        clear();
        if (input == KEY_UP)
            mig15.angle += 0.5;
        else if (input == KEY_DOWN)
            mig15.angle -= 0.5;
        mvprintw(0, 0, "Angle        %lf Degrees", mig15.angle);
        mvprintw(1, 0, "Thrust       %lf N", mig15.thrust);
        mvprintw(2, 0, "Drag         %lf N", drag(&mig15));
        mvprintw(3, 0, "Lift         %lf N", lift(&mig15) * mig15.lift_const);
        mvprintw(4, 0, "H Force      %lf N", get_horizontal_force(&mig15));
        mvprintw(5, 0, "V Force      %lf N", get_vertical_force(&mig15) - gravity(&mig15));

        refresh();
    }

    endwin();

    return EXIT_SUCCESS;
}
