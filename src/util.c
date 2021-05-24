#include "physics.h"
#include "util.h"

double max(double a, double b) {
    return a > b ? a : b;
}

double min(double a, double b) {
    return a < b ? a : b;
}

double equiv(double minv, double maxv, double value, double maxvalue) {
    return (maxv-minv) * value / maxvalue + minv;
}

double gravity(PhysicsObject *obj) {
    return obj->mass * 9.8;
}

double to_ms(double mass, double force) {
    return force / mass;
}
