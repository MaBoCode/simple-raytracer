#include "world.h"
#include "camera.h"
#include "light.h"
#include "plane.h"
#include "sphere.h"

int main() {
    struct camera camera = {
            .width = 1920,
            .height = 1080,
            .center = { 0, 0, 0},
            .forward = { 0, 0, 1},
            .up = { 0, 1, 0},
            .focal = camera_get_focal(1920, 80)
    };

    struct world world;
    world.obj_len = 0;
    world.objects = NULL;
    world.light_len = 0;
    world.lights = NULL;

    struct sphere s0 = {
            .radius = 10000,
            .center = {0, -10004, -20}
    };

    struct shape shape0 = {
            .object.s = s0,
            .color = {0.20f, 0.20f, 0.20f},
            .material = {
                    .reflection = 0,
                    .refraction = 0,
                    .diffusion = 1
            },
            .type = SHAPE_SPHERE,
            .normal = &sphere_normal,
            .intersect = &sphere_intersect
    };

    struct sphere s1 = {
            .radius = 4,
            .center = {0, 0  , -20}
    };

    struct shape shape1 = {
            .object.s = s1,
            .color = { 1, 0.32f, 0.36f },
            .material = {
                    .reflection = 1,
                    .refraction = 0,
                    .diffusion = 0
            },
            .type = SHAPE_SPHERE,
            .normal = &sphere_normal,
            .intersect = &sphere_intersect
    };

    struct sphere s2 = {
            .radius = 2,
            .center = {5,     -1, -15}
    };

    struct shape shape2 = {
            .object.s = s2,
            .color = { 0.90f, 0.76f, 0.46f },
            .material = {
                    .reflection = 1,
                    .refraction = 0,
                    .diffusion = 0
            },
            .type = SHAPE_SPHERE,
            .normal = &sphere_normal,
            .intersect = &sphere_intersect
    };

    struct sphere s3 = {
            .radius = 3,
            .center = {5,      0, -25}
    };

    struct shape shape3 = {
            .object.s = s3,
            .color = {0.65f, 0.77f, 0.97f},
            .material = {
                    .reflection = 0,
                    .refraction = 0,
                    .diffusion = 1
            },
            .type = SHAPE_SPHERE,
            .normal = &sphere_normal,
            .intersect = &sphere_intersect
    };

    struct light light = {
            .origin = {0,     20, -30},
            .color = {1, 1, 1},
            .intensity = 1
    };

    struct light light2 = {
            .origin = {0,     -1000, -10},
            .color = {255, 255, 255},
            .intensity = 1
    };

    //world_add_object(&world, &shape0);
    world_add_object(&world, &shape1);
    world_add_object(&world, &shape2);
    world_add_object(&world, &shape3);

    world_add_light(&world, &light);
    //world_add_light(&world, &light2);

    struct canvas canvas = camera_render(&camera, &world);

    world_destroy(&world);
    canvas_destroy(&canvas);
    return 0;
}
