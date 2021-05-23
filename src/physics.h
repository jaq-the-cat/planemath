#ifndef PHYSICS_H
#define PHYSICS_H
#include <math.h>

typedef struct {
    double horizontal;
    double vertical;
    double angle;
    double mass;
    double thrust;
    double lift_const;
    double cd_min;
    double cd_max;
    double area_min;
    double area_max;
    double wing_area;
} PhysicsObject;

double get_lift_coeff(PhysicsObject *obj);

double get_drag_coeff(PhysicsObject *obj);

double get_frontal_area(PhysicsObject *obj);

double get_wing_area(PhysicsObject *obj);

double lift(PhysicsObject *obj);

double drag(PhysicsObject *obj);

double get_prograde(PhysicsObject *obj);

double get_aot(PhysicsObject *obj);

double gravity(PhysicsObject *obj);

double get_horizontal_force(PhysicsObject *obj);

double get_vertical_force(PhysicsObject *obj);

double to_ms(double mass, double force);

double acc(PhysicsObject *obj);

#endif
