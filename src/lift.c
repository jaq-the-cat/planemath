#include "physics.h"

double to15(double angle) {
    return 0.096 * angle;
}

double to50(double angle) {
    return -0.013 * angle + 1.596;
}

double to100(double angle) {
    return -0.022 * angle + 2.098;
}

double to150(double angle) {
    return -0.021 * angle + 2.197;
}

double to180(double angle) {
    return 0.039 * angle - 6.882;
}

double get_lift_coeff(PhysicsObject *obj) {
    double angle = obj->angle;
    double lift = 0;
    while (angle >= 180)
        angle -= 180;
    if (angle >= 0 && angle < 15) lift = to15(angle);
    else if (angle >= 15 && angle < 50) lift = to50(angle);
    else if (angle >= 50 && angle < 100) lift = to100(angle);
    else if (angle >= 100 && angle < 150) lift = to150(angle);
    else if (angle >= 150 && angle < 180) lift = to180(angle);
    return lift;
}

