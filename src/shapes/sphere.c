#include "sphere.h"

#include <assert.h>
#include <math.h>

#include "shape.h"

bool sphere_intersect(const void *object, const struct ray *r, float *t0, float *t1) {
    assert(object);
    assert(r);

    const struct shape *shape = object;
    const struct sphere *s = &shape->object.s;

    struct vec3 l = vec3_sub(&r->origin, &s->center);
    double a = vec3_dot(&r->direction, &r->direction);
    double b = 2 * vec3_dot(&r->direction, &l);
    double c = vec3_dot(&l, &l) - s->radius * s->radius;

    double delta = b * b - 4 * a * c;

    if (delta < 0) {
        return false;
    }

    *t0 = (-b - sqrt(delta)) / (2 * a);
    *t1 = (-b + sqrt(delta)) / (2 * a);

    return true;
}

struct vec3 sphere_normal(const void *object, const struct vec3 *a) {
    assert(object);
    assert(a);

    const struct shape *shape = object;
    const struct sphere *s = &shape->object.s;

    struct vec3 normal = vec3_sub(a, &s->center);
    //normal = vec3_div_nb(&normal, s->radius);
    return normal;
}