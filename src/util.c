#include "physics.h"

double max(double a, double b) {
    return a > b ? a : b;
}

double min(double a, double b) {
    return a < b ? a : b;
}

double equiv(double minv, double maxv, double angle, double maxangle) {
    return (maxv-minv) * angle / maxangle + minv;
}

double gravity(PhysicsObject *obj) {
    return obj->mass * 9.8;
}

double to_ms(double mass, double force) {
    return force / mass;
}
