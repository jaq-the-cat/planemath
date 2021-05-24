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

// area

double get_frontal_area(PhysicsObject *obj, double angle);

double get_wing_area(PhysicsObject *obj, double angle);

// drag

double get_drag_coeff(PhysicsObject *obj, double angle);

double drag(PhysicsObject *obj, double u, double A, double angle);

// lift

double get_lift_coeff(PhysicsObject *obj);

double lift(PhysicsObject *obj, double v, double A);

// angles

double get_prograde(PhysicsObject *obj);

double get_aot(PhysicsObject *obj);

// util

double gravity(PhysicsObject *obj);

double get_horizontal_thrust(PhysicsObject *obj);

double get_vertical_thrust(PhysicsObject *obj);

double to_ms(double mass, double force);

#endif
