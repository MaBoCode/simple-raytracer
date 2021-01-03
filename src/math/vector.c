#include "vector.h"

#include <assert.h>
#include <math.h>

struct vec3 vec3_add(const struct vec3 *a, const struct vec3 *b) {
    assert(a);
    assert(b);

    struct vec3 c = {
            .x = a->x + b->x,
            .y = a->y + b->y,
            .z = a->z + b->z
    };
    return c;
}

struct vec3 vec3_sub(const struct vec3 *a, const struct vec3 *b) {
    assert(a);
    assert(b);

    struct vec3 c = {
            .x = a->x - b->x,
            .y = a->y - b->y,
            .z = a->z - b->z
    };
    return c;
}

struct vec3 vec3_neg(const struct vec3 *a) {
    assert(a);

    struct vec3 c = {
            .x = - a->x,
            .y = - a->y,
            .z = - a->z
    };
    return c;
}

struct vec3 vec3_mul(const struct vec3 *a, const struct vec3 *b) {
    assert(a);
    assert(b);

    struct vec3 c = {
            .x = a->x * b->x,
            .y = a->y * b->y,
            .z = a->z * b->z
    };
    return c;
}

struct vec3 vec3_mul_nb(const struct vec3 *a, float nb) {
    assert(a);
    struct vec3 c = {
            a->x * nb,
            a->y * nb,
            a->z * nb
    };
    return c;
}

struct vec3 vec3_div_nb(const struct vec3 *a, float nb) {
    assert(a);

    struct vec3 c = {
            a->x / nb,
            a->y / nb,
            a->z / nb
    };
    return c;
}

float vec3_len(const struct vec3 *a) {
    assert(a);

    float s = a->x * a->x + a->y * a->y + a->z * a->z;
    return sqrt(s);
}

void vec3_normalize(struct vec3 *a) {
    assert(a);

    float len = vec3_len(a);
    if (len <= 0)
        return;

    a->x /= sqrt(len);
    a->y /= sqrt(len);
    a->z /= sqrt(len);
}

float vec3_dot(const struct vec3 *a, const struct vec3 *b) {
    assert(a);
    assert(b);
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

struct vec3 vec3_cross(const struct vec3 *a, const struct vec3 *b) {
    assert(a);
    assert(b);

    struct vec3 c = {
            .x = a->y * b->z - b->y * a->z,
            .y = a->z * b->x - b->z * a->x,
            .z = a->x * b->y - b->x * a->y
    };
    return c;
}