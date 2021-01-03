#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdbool.h>

#include "vector.h"
#include "light.h"
#include "ray.h"

struct material
{
    float reflection;
    float refraction;
    float diffusion;
};

struct vec3 material_reflect(const struct vec3 *normal, const struct vec3 *incident);

struct vec3 material_refract(const struct vec3 *normal, const struct vec3 *incident, bool in_sphere);

struct vec3 material_diffuse(const void *object, const struct ray *r, const struct vec3 *hit, struct light *light);

#endif //MATERIAL_H
