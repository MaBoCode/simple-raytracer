#ifndef SPHERE_H
#define SPHERE_H

#include <stdbool.h>

#include "vector.h"
#include "ray.h"
#include "material.h"

struct sphere
{
    struct vec3 center;
    float radius;
};

bool sphere_intersect(const void *object, const struct ray *r, float *t0, float *t1);

struct vec3 sphere_normal(const void *object, const struct vec3 *a);

#endif //SPHERE_H
