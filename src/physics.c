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

double get_drag_coeff(PhysicsObject *obj) {
    double angle = get_aot(obj);
    while (angle >= 90)
        angle -= 90;
    return equiv(obj->cd_min, obj->cd_max, angle, 90);
}

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

double lift(PhysicsObject *obj)  {
    double cl = get_lift_coeff(obj);
    double p = 1.2;  // density of air
    double v = pow(obj->vertical, 2) + pow(obj->horizontal, 2);
    double A = get_wing_area(obj);
    return cl * (p * v / 2) * A;
}

double drag(PhysicsObject *obj) {
    double p = 1.2; // density of air
    double u = pow(obj->vertical, 2) + pow(obj->horizontal, 2);
    double cd = get_drag_coeff(obj);
    double A = get_frontal_area(obj);

    return 0.5 * p * u * cd * A;
}

double get_prograde(PhysicsObject *obj) {
    return atan(obj->vertical / obj->horizontal) * (180/3.141);
}

double get_aot(PhysicsObject *obj) {
    return obj->angle - get_prograde(obj);
}

double gravity(PhysicsObject *obj) {
    return obj->mass * 9.8;
}

double fabs(double v) {
    if (v < 0) return -v;
    return v;
}

double get_horizontal_force(PhysicsObject *obj) {
    return (fabs(200./180. * obj->angle - 200.) - 100.) / 100 * obj->thrust;
}

double get_vertical_force(PhysicsObject *obj) {
    return (-fabs(100./90. * obj->angle - 100.) + 100.) / 100 * obj->thrust;
}

double to_ms(double mass, double force) {
    return force / mass;
}

double acc(PhysicsObject *obj) {
    // v = F/m
    return (obj->thrust - drag(obj)) / obj->mass;
}
