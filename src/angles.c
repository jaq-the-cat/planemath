#include "physics.h"

double get_prograde(PhysicsObject *obj) {
    return atan(obj->vertical / obj->horizontal) * (180/3.141);
}

double get_aot(PhysicsObject *obj) {
    return obj->angle - get_prograde(obj);
}
