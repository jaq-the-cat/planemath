#pragma once
#include <math.h>

typedef struct {
    float velocity;
    float angle;
    float mass;
    float thrust;
    float cd_min;
    float cd_max;
    float area_min;
    float area_max;
} PhysicsObject;

float equiv(float maxv, float minv, float angle) {
    float a = (maxv - minv) / 90;
    return angle * a + minv;
}

float get_drag_coeff(PhysicsObject *obj) {
    return equiv(obj->cd_max, obj->cd_min, obj->angle);
}

float get_frontal_area(PhysicsObject *obj) {
    return equiv(obj->area_max, obj->area_min, obj->angle);
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
