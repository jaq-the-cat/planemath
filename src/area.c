#include "physics.h"
#include "util.h"

double get_frontal_area(PhysicsObject *obj) {
    double angle = get_aot(obj);
    while (angle >= 90)
        angle -= 90;
    return equiv(obj->area_min, obj->area_max, angle, 90);
}

double get_wing_area(PhysicsObject *obj) {
    double angle = obj->angle;
    while (angle >= 180)
        angle -= 180;
    if (angle < 90) {
        return equiv(obj->wing_area, 0, angle, 90);
    } else {
        return equiv(0, -obj->wing_area, angle-90, 90);
    }
}
