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
        0, // initial angle (degrees)
        4500, // mass (kg)
        (26.5)*1000, // thrust (N)
        0.2, // lift constant
        0.2, // drag coefficient at 0°
        0.9, // drag coefficient at 90°
        3, // frontal area at 0°
        24, // frontal area at 90°
        20, // wing area
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
        mvprintw(0, 0, "Angle        %f", mig15.angle);
        mvprintw(1, 0, "Thrust       %f", mig15.thrust);
        mvprintw(2, 0, "Drag         %f", drag(&mig15));
        mvprintw(3, 0, "Lift         %f", lift(&mig15) * mig15.lift_const);
        mvprintw(4, 0, "H Velocity   %f", mig15.velocity);
        mvprintw(5, 0, "V Velocity   %f", to_ms(mig15.mass, lift(&mig15) - gravity(&mig15)));
        mig15.velocity += to_ms(mig15.mass, mig15.thrust - drag(&mig15));
        position += mig15.velocity;

        refresh();
    }

    endwin();

    return EXIT_SUCCESS;
}
