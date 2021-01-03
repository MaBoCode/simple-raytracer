#include "plane.h"

#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

#include "shape.h"

bool plane_intersect(const void *object, const struct ray *ray, float *t0, float *t1) {
    assert(object);
    assert(ray);

    const struct shape *shape = object;
    const struct plane *plane = &shape->object.p;

    struct vec3 n = plane_normal(NULL, NULL);
    float denominator = vec3_dot(&n, &ray->direction);
    if (abs(denominator) > 1e-4) {
        struct vec3 tmp = vec3_sub(&plane->center, &ray->origin);
        float t = vec3_dot(&tmp, &n) / denominator;
        return t >= 0;
    }

    return false;
}

struct vec3 plane_normal(const void *object, const struct vec3 *hit) {
    struct vec3 normal = { 0, 1, 0};
    return normal;
}