#include "material.h"

#include <math.h>

#include "shape.h"

struct vec3 material_reflect(const struct vec3 *normal, const struct vec3 *incident) {
    struct vec3 r = vec3_mul_nb(normal, 2 * vec3_dot(incident, normal));
    r = vec3_sub(incident, &r);
    vec3_normalize(&r);
    /*
    float cos_i =  - vec3_dot(normal, incident);
    struct vec3 r = vec3_mul_nb(normal, 2 * cos_i);
    r = vec3_add(&r, incident);
     */
    return r;
}

struct vec3 material_refract(const struct vec3 *normal, const struct vec3 *incident, bool in_sphere) {
    float ior = 1.1;
    float eta = in_sphere ? ior : 1 / ior;
    float cosine = - vec3_dot(normal, incident);
    float k = 1 - eta * eta * (1 - cosine * cosine);
    float c = eta * cosine * sqrt(k);
    struct vec3 dir = vec3_mul_nb(normal, c);
    struct vec3 tmp = vec3_mul_nb(incident, eta);
    dir = vec3_add(&dir, &tmp);
    vec3_normalize(&dir);
    return dir;
}

struct vec3 material_diffuse(const void *object, const struct ray *r, const struct vec3 *hit, struct light *light) {
    const struct shape *shape = object;

    struct vec3 l = vec3_sub(&light->origin, hit);
    struct vec3 n = shape->normal(shape, hit);

    vec3_normalize(&l);
    vec3_normalize(&n);

    float dt = vec3_dot(&l, &n);

    struct vec3 px = vec3_mul_nb(&light->color, light->intensity * dt);
    px = vec3_add(&shape->color, &px);
    px = vec3_mul_nb(&px, 0.5);

    return px;
}