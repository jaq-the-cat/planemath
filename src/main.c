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
        0.2, // drag coefficient at 0°
        0.9, // drag coefficient at 90°
        3, // area at 0°
        24, // area at 90°
    };

    initscr();
    noecho();

    while (getch() != 'q') {
        clear();
        mvprintw(0, 0, "Thrust:       %f", mig15.thrust);
        mvprintw(1, 0, "Drag:         %f", drag(&mig15));
        mvprintw(2, 0, "Acceleration: %f", acc(&mig15));
        mvprintw(3, 0, "Velocity:     %f", mig15.velocity);
        mvprintw(4, 0, "Position:     %d", position);
        mig15.velocity += acc(&mig15);
        position += mig15.velocity;

        refresh();
    }

    endwin();

    return EXIT_SUCCESS;
}
