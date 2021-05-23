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
        0,
        4500, // 5000kg
        (26.5)*1000, // 26.5kN
        3 // 3m
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
