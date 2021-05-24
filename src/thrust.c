#include "physics.h"

double fabs(double v) {
    if (v < 0) return -v;
    return v;
}

double get_horizontal_thrust(PhysicsObject *obj) {
    return (fabs(200./180. * obj->angle - 200.) - 100.) / 100 * obj->thrust;
}

double get_vertical_thrust(PhysicsObject *obj) {
    return (-fabs(100./90. * obj->angle - 100.) + 100.) / 100 * obj->thrust;
}
