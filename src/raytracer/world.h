#ifndef WORLD_H
#define WORLD_H

#include <stddef.h>

#include "world.h"
#include "vector.h"
#include "ray.h"
#include "shape.h"

struct world
{
    struct shape *objects;
    struct light *lights;
    size_t obj_len;
    size_t light_len;
};

void world_add_object(struct world *world, struct shape *object);

void world_add_light(struct world *world, struct light *light);

void world_get_color(struct world *world, struct vec3 *color, struct ray *ray, int depth);

void world_destroy(struct world *world);

#endif //WORLD_H
