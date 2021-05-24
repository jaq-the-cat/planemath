#include "physics.h"
#include "util.h"

double get_frontal_area(PhysicsObject *obj, double angle) {
    while (angle >= 90)
        angle -= 90;
    return equiv(obj->area_min, obj->area_max, angle, 90);
}

double get_wing_area(PhysicsObject *obj, double angle) {
    while (angle >= 90)
        angle -= 90;
    return equiv(obj->wing_area, 0, angle, 90);
}
