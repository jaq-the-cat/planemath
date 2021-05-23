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
        0, // initial velocity (m/s)
        12, // initial angle (degrees)
        4500, // mass (kg)
        (26.5)*1000, // thrust (N)
        1, // lift constant
        0.2, // drag coefficient at 0°
        0.9, // drag coefficient at 90°
        3, // area at 0°
        24, // area at 90°
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
        mvprintw(0, 0, "Thrust:           %f", mig15.thrust);
        mvprintw(1, 0, "Drag:             %f", drag(&mig15));
        mvprintw(2, 0, "Acceleration:     %f", acc(&mig15));
        mvprintw(3, 0, "Velocity:         %f", mig15.velocity);
        mvprintw(4, 0, "Position:         %d", position);
        mvprintw(5, 0, "Angle:            %f", mig15.angle);
        mvprintw(6, 0, "Lift Coefficient: %f", get_lift_coeff(&mig15));
        mig15.velocity += acc(&mig15);
        position += mig15.velocity;

        refresh();
    }

    endwin();

    return EXIT_SUCCESS;
}
