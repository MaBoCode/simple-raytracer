#ifndef PLANE_H
#define PLANE_H

#include <stdbool.h>

#include "vector.h"
#include "ray.h"
#include "material.h"

struct plane
{
    struct vec3 center;
};

bool plane_intersect(const void *object, const struct ray *ray, float *t0, float *t1);

struct vec3 plane_normal(const void *object, const struct vec3 *hit);

#endif //PLANE_H
