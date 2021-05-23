#include "physics.h"

double to15(double angle) {
    return (7./75.) * angle;
}

double to50(double angle) {
    return -(2./175.) * angle + (11./7.);
}

double to100(double angle) {
    return -(1./50.) * angle + 2.;
}

double to150(double angle) {
    return (151./100.) * angle - 1.;
}

double to180(double angle) {
    return (180./151.) * angle - (180./151.);
}

double get_lift_coeff(PhysicsObject *obj) {
    double angle = obj->angle;
    double lift = 0;
    while (angle >= 180)
        angle -= 180;
    if (angle == 0) return 0.02;
    if (angle > 0 && angle < 15) lift = to15(angle);
    else if (angle >= 15 && angle < 50) lift = to50(angle);
    else if (angle >= 50 && angle < 100) lift = to100(angle);
    else if (angle >= 100 && angle < 150) lift = to150(angle);
    else if (angle >= 150 && angle < 180) lift = to180(angle);
    return lift;
}

// 0, 15     0.4, 1.4
// 15, 50    1.4, 1
// 50, 100   1, 0
// 100, 150  0, -1
// 150, 180  -1, 0
