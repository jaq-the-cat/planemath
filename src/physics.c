#include "physics.h"

double max(double a, double b) {
    return a > b ? a : b;
}

double min(double a, double b) {
    return a < b ? a : b;
}

double get_lift_coeff(PhysicsObject *obj);

double equiv(double minv, double maxv, double angle, double maxangle) {
    return (maxv-minv) * angle / maxangle + minv;
}

double get_drag_coeff(PhysicsObject *obj) {
    double angle = obj->angle;
    while (angle >= 90)
        angle -= 90;
    return equiv(obj->cd_min, obj->cd_max, angle, 90);
}

double get_frontal_area(PhysicsObject *obj) {
    double angle = obj->angle;
    while (angle >= 90)
        angle -= 90;
    return equiv(obj->area_min, obj->area_max, angle, 90);
}

double lift(PhysicsObject *obj)  {
    double cl = get_lift_coeff(obj);
    double p = 7.9;  // density of steel
    double v = pow(obj->velocity, 2);
    double A = obj->wing_area;
    return cl * (p * v / 2) * A;
}

double drag(PhysicsObject *obj) {
    double p = 1.2; // density of air
    double u = obj->velocity;
    double cd = get_drag_coeff(obj);
    double A = get_frontal_area(obj);

    return 0.5 * p * pow(u, 2) * cd * A;
}

double gravity(PhysicsObject *obj) {
    return obj->mass * 9.8;
}

double to_ms(double mass, double force) {
    return force / mass;
}

double acc(PhysicsObject *obj) {
    // v = F/m
    return (obj->thrust - drag(obj)) / obj->mass;
}