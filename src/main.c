#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ncurses.h>

#include "physics.h"

typedef struct {
    char *str;
    double value;
} ConsoleData;

void printdata(ConsoleData data[], int length) {
    for (int i=0; i<length; i++)
        mvprintw(i, 0, data[i].str, data[i].value);
}

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
        25, // frontal area at 90°
        23, // wing area
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

        mig15.horizontal += to_ms(mig15.mass,
            get_horizontal_thrust(&mig15)
            + lift(&mig15, mig15.horizontal, get_wing_area(&mig15, 90.)));

        mig15.vertical += to_ms(mig15.mass,
            get_vertical_thrust(&mig15)
            + lift(&mig15, mig15.vertical, get_wing_area(&mig15, 0.))
            * mig15.lift_const
            - gravity(&mig15));

        ConsoleData data[] = {
            "Angle            %lf Degrees", mig15.angle,
            "Angle of Attack  %lf Degrees", get_aot(&mig15),
            "H Thrust         %lf N", get_horizontal_thrust(&mig15),
            "V Thrust         %lf N", get_vertical_thrust(&mig15),
            "H Velocity       %lf m/s", mig15.horizontal,
            "V Velocity       %lf m/s", mig15.vertical,
            "H Drag           %lf N", drag(&mig15, mig15.horizontal, get_frontal_area(&mig15, 0.)),
            "V Drag           %lf N", drag(&mig15, mig15.vertical, get_frontal_area(&mig15, 90.)),
            "H Lift           %lf N", lift(&mig15, mig15.horizontal, get_wing_area(&mig15, 90.)),
            "V Lift           %lf N", lift(&mig15, mig15.vertical, get_wing_area(&mig15, 0.))
        };
        printdata(data, 10);

        refresh();
    }

    endwin();

    return EXIT_SUCCESS;
}
