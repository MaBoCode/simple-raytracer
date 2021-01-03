#include "camera.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include "vector.h"
#include "ray.h"
#include "canvas.h"

void camera_cast_ray(const struct camera *camera, struct ray *ray, int x, int y) {
    assert(camera);
    assert(ray);
    assert(x < camera->width);
    assert(y < camera->height);

    /*
     * xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio
     * yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle
     * fov = 30, aspectratio = width / float(height)
     * angle = tan(M_PI * 0.5 * fov / 180.)
     */

    float fov = 30;
    float angle = tan(M_PI * 0.5 * fov / 180.);
    float aspect_ratio = camera->width / camera->height;
    float x_offset = (2 * ((x + 0.5) * (1 / camera->width)) - 1) * angle * aspect_ratio;
    float y_offset = (1 - 2 * ((y + 0.5) * (1 / camera->height))) * angle;

    struct vec3 origin = {0, 0, 0};
    ray->origin = origin;

    struct vec3 direction = {x_offset, y_offset, -1};
    vec3_normalize(&direction);
    ray->direction = direction;
}

struct canvas camera_render(const struct camera *camera, struct world *world) {
    assert(camera);

    size_t img_size = camera->width * camera->height;
    struct vec3 *img = calloc(img_size, sizeof(struct vec3));
    struct vec3 *px = img;

    struct canvas canvas = canvas_init(camera->width, camera->height);

    for (int y = 0; y < camera->height; ++y) {
        for (int x = 0; x < camera->width; ++x, ++px) {
            struct ray ray;
            struct vec3 color = {0, 0, 0};

            camera_cast_ray(camera, &ray, x, y);
            world_get_color(world, &color, &ray, 0);
            canvas_get_pixel(&canvas, px, &color);
        }
    }
    canvas_create_image(&canvas, img);
    free(img);
    return canvas;
}

float camera_get_focal(float width, float fov_deg) {
    //float fov_rad = 80 * M_PI / 180;
    return 0;
}