#pragma once
#include <math.h>

typedef struct {
    float velocity;
    float mass;
    float thrust;
    float frontal_area;
} PhysicsObject;

float drag(PhysicsObject *obj) {
    float p = 1.2; // density of air
    float u = obj->velocity;
    float cd = 0.2; // drag coefficient
    float A = obj->frontal_area;

    return 0.5 * p * pow(u, 2) * cd * A;
}

float acc(PhysicsObject *obj) {
    // v = F/m
    return (obj->thrust - drag(obj)) / obj->mass;
}
