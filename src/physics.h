#pragma once
#include <math.h>

typedef struct {
    float velocity;
    float angle;
    float mass;
    float thrust;
    float lift_const;
    float cd_min;
    float cd_max;
    float area_min;
    float area_max;
} PhysicsObject;

float equiv(float minv, float maxv, float angle) {
    float a = (maxv - minv) / 90;
    return angle * a + minv;
}

float get_lift_coeff(PhysicsObject *obj) {
    float angle = obj->angle;
    float lift = 0;
    while (angle >= 180)
        angle -= 180;
    if (angle >= 0 && angle < 15) lift = equiv(0, 1.4, angle);
    if (angle >= 15 && angle < 50) lift = equiv(1.4, 1, angle);
    if (angle >= 50 && angle < 100) lift = equiv(1, 0, angle);
    if (angle >= 100 && angle < 150) lift = equiv(0, -1, angle);
    if (angle >= 150 && angle < 180) lift = equiv(-1, 0, angle);
    return lift;
}

float get_drag_coeff(PhysicsObject *obj) {
    float angle = obj->angle;
    while (angle >= 90)
        angle -= 90;
    return equiv(obj->cd_min, obj->cd_max, angle);
}

float get_frontal_area(PhysicsObject *obj) {
    float angle = obj->angle;
    while (angle >= 90)
        angle -= 90;
    return equiv(obj->area_min, obj->area_max, angle);
}

float drag(PhysicsObject *obj) {
    float p = 1.2; // density of air
    float u = obj->velocity;
    float cd = get_drag_coeff(obj);
    float A = get_frontal_area(obj);

    return 0.5 * p * pow(u, 2) * cd * A;
}

float acc(PhysicsObject *obj) {
    // v = F/m
    return (obj->thrust - drag(obj)) / obj->mass;
}
