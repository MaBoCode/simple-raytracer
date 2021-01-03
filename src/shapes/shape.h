#ifndef SHAPE_H
#define SHAPE_H

#include <stdbool.h>

#include "vector.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "material.h"

enum shape_type
{
    SHAPE_SPHERE,
    SHAPE_PLANE
};

struct shape
{
    bool (*intersect)(const void *object, const struct ray *ray, float *t0, float *t1);
    struct vec3 (*normal)(const void *object, const struct vec3 *hit);
    struct vec3 color;
    struct material material;
    enum shape_type type;
    union {
        struct sphere s;
        struct plane p;
    } object;
};

#endif //SHAPE_H
