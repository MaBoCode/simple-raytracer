#include "world.h"

#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "material.h"
#include "utils.h"

void world_add_object(struct world *world, struct shape *object) {
    assert(world);
    assert(object);

    size_t data_size = (world->obj_len + 1) * sizeof(struct shape);
    world->objects = realloc(world->objects, data_size);
    world->objects[world->obj_len++] = *object;
}

void world_add_light(struct world *world, struct light *light) {
    assert(world);
    assert(light);

    size_t data_size = (world->light_len + 1) * sizeof(struct light);
    world->lights = realloc(world->lights, data_size);
    world->lights[world->light_len++] = *light;
}

static struct shape *world_intersect(struct world *world, struct ray *ray, struct vec3 *hit) {
    assert(world);
    assert(ray);

    struct shape *object = NULL;
    float t = INFINITY;

    for (int i = 0; i < world->obj_len; ++i) {
        float t0 = INFINITY;
        float t1 = INFINITY;
        struct shape *shape = &world->objects[i];
        if (shape->intersect(shape, ray, &t0, &t1)) {
            if (t0 < 0) t0 = t1;
            if (t0 < t) {
                t = t0;
                object = shape;
            }
        }
    }

    if (object) {
        *hit = vec3_mul_nb(&ray->direction, t);
        *hit = vec3_add(hit, &ray->origin);
    }

    return object;
}

void world_get_color(struct world *world, struct vec3 *color, struct ray *ray, int depth) {
    assert(world);
    assert(color);
    assert(ray);

    struct vec3 hit;
    struct shape *object = world_intersect(world, ray, &hit);

    if (!object) {
        color->x = 255;
        color->y = 255;
        color->z = 255;
        return;
    }

    struct vec3 n = object->normal(object, &hit);
    vec3_normalize(&n);

    bool in_sphere = false;

    if (vec3_dot(&ray->direction, &n) > 0) {
        n = vec3_neg(&n);
        in_sphere = true;
    }

    if ((object->material.reflection > 0 || object->material.refraction > 0) && depth < 5) {
        float facing_ratio = - vec3_dot(&ray->direction, &n);
        float fresnel = shuffle(pow(1 - facing_ratio, 3), 1, 0.1);

        struct vec3 reflect_dir = material_reflect(&n, &ray->direction);
        struct vec3 reflect_ori = vec3_mul_nb(&n, 1e-4);
        reflect_ori = vec3_add(&reflect_ori, &hit);

        struct ray reflect_ray = {
                .origin = reflect_ori,
                .direction = reflect_dir
        };

        struct vec3 reflect_color = {0, 0, 0};
        // cast new ray
        world_get_color(world, &reflect_color, &reflect_ray, depth + 1);
        // apply fresnel effect
        reflect_color = vec3_mul_nb(&reflect_color, fresnel);

        struct vec3 refract_dir = material_refract(&n, &ray->direction, in_sphere);
        struct vec3 refract_ori = vec3_mul_nb(&n, 1e-4);
        refract_ori = vec3_sub(&hit, &refract_ori);

        struct ray refract_ray = {
                .origin = refract_ori,
                .direction = refract_dir
        };

        struct vec3 refract_color = {0, 0, 0};
        world_get_color(world, &refract_color, &refract_ray, depth + 1);
        //printf("refract=%f, %f, %f\n", refract_color.x, refract_color.y, refract_color.z);
        refract_color = vec3_mul_nb(&refract_color, 1 - fresnel);
        refract_color = vec3_mul_nb(&refract_color, object->material.refraction);

        struct vec3 surface_color = vec3_add(&reflect_color, &refract_color);
        *color = vec3_mul(&surface_color, &object->color);
    } else {
        for (int i = 0; i < world->light_len; ++i) {

            struct vec3 light_dir = vec3_sub(&world->lights[i].origin, &hit);
            vec3_normalize(&light_dir);

            struct vec3 light_ori = vec3_mul_nb(&n, 1e-4);
            light_ori = vec3_add(&hit, &light_ori);
            int transmission = 1;

            struct ray light_ray = {
                    .origin = light_ori,
                    .direction = light_dir
            };

            for (int j = 0; j < world->obj_len; ++j) {
                struct shape *shape = &world->objects[j];
                float t0, t1;
                if (shape->intersect(shape, &light_ray, &t0, &t1)) {
                    transmission = 0;
                    break;
                }
            }

            //struct vec3 diffuse = material_diffuse(object, ray, &hit, &world->lights[i]);
            //diffuse = vec3_mul_nb(&diffuse, object->material.diffusion);
            //diffuse = vec3_mul_nb(&diffuse, transmission);

            //*color = diffuse;

            float coeff = max(0, vec3_dot(&n, &light_dir));
            struct vec3 surface_color = vec3_mul_nb(&object->color, coeff);
            *color = vec3_add(color, &surface_color);
            //*color = vec3_mul_nb(color, transmission);
        }
    }
}

void world_destroy(struct world *world) {
    assert(world);

    free(world->objects);
}