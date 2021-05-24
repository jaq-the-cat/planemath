#include "physics.h"
#include "util.h"

double get_drag_coeff(PhysicsObject *obj, double angle) {
    while (angle > 90)
        angle -= 90;
    return equiv(obj->cd_min, obj->cd_max, angle, 90);
}

double drag(PhysicsObject *obj, double u, double A, double angle) {
    double p = 1.2; // density of air
    /*double u = pow(obj->vertical, 2) + pow(obj->horizontal, 2);*/
    double cd = get_drag_coeff(obj, angle);
    /*double A = get_frontal_area(obj);*/

    return 0.5 * p * pow(u, 2) * cd * A;
}
