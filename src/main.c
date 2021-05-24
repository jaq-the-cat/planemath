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
        0., // initial horizontal velocity (m/s)
        0., // initial vertical velocity (m/s)
        0., // initial angle (degrees)
        4500., // mass (kg)
        (26.5)*1000., // thrust (N)
        0.7, // lift constant
        0.2, // drag coefficient at 0°
        0.9, // drag coefficient at 90°
        3., // frontal area at 0°
        25., // frontal area at 90°
        23., // wing area
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
            + lift(&mig15, mig15.vertical, get_wing_area(&mig15, 90.))
            - drag(&mig15, mig15.horizontal, get_frontal_area(&mig15, 0.), mig15.angle));

        mig15.vertical += to_ms(mig15.mass,
            get_vertical_thrust(&mig15)
            + lift(&mig15, mig15.horizontal, get_wing_area(&mig15, 0.))
            + drag(&mig15, mig15.vertical, get_frontal_area(&mig15, 90.), mig15.angle)
            - gravity(&mig15));

        ConsoleData data[] = {
            "Density of Air  %.2lf", 1.2,
            "V Velocity²     %.2lf", pow(mig15.horizontal, 2.),
            "V Drag Coeff    %.2lf", get_lift_coeff(&mig15),
            "WA at 0°       %.2lfm²", get_wing_area(&mig15, 0.),
            "", 0,
            "Angle            %.2lf°", mig15.angle,
            "Angle of Attack  %.2lf°", get_aot(&mig15),
            "", 0,
            "H Thrust         %.2lf kN", get_horizontal_thrust(&mig15) / 1000,
            "V Thrust         %.2lf kN", get_vertical_thrust(&mig15) / 1000,
            "H Velocity       %.2lf m/s", mig15.horizontal,
            "V Velocity       %.2lf m/s", mig15.vertical,
            "Velocity         %.2lf m/s", sqrt(pow(mig15.horizontal, 2) + pow(mig15.vertical, 2)),
            "", 0,
            "H Drag           %.2lf kN", drag(&mig15, mig15.horizontal, get_frontal_area(&mig15, 0.), mig15.angle) / 1000,
            "FA at 0°        %.2lfm²", get_frontal_area(&mig15, 0.),
            "V Drag           %.2lf kN", drag(&mig15, mig15.vertical, get_frontal_area(&mig15, 90.), mig15.angle) / 1000,
            "FA at 90°       %.2lfm²", get_frontal_area(&mig15, 90.),
            "", 0,
            "H Lift           %.2lf kN", lift(&mig15, mig15.horizontal, get_wing_area(&mig15, 90.)) / 1000,
            "WA at 90°       %.2lfm²", get_wing_area(&mig15, 90.),
            "V Lift           %.2lf kN", lift(&mig15, mig15.vertical, get_wing_area(&mig15, 0.)) / 1000,
            "WA at 0°        %.2lfm²", get_wing_area(&mig15, 0.),
            "", 0,
            "Gravity°        %.2lf kN", gravity(&mig15),
        };
        printdata(data, 25);

        refresh();
    }

    endwin();

    return EXIT_SUCCESS;
}
