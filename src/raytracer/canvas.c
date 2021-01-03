#include "canvas.h"

#include <assert.h>
#include <stdio.h>

#include "utils.h"

static void canvas_adjust_px(struct vec3 *px) {
    px->x = 255 * px->x > 255 ? 255 : px->x < 0 ? 0 : 255 * min(1, px->x);
    px->y = 255 * px->y > 255 ? 255 : px->y < 0 ? 0 : 255 * min(1, px->y);
    px->z = 255 * px->z > 255 ? 255 : px->z < 0 ? 0 : 255 * min(1, px->z);
}

struct canvas canvas_init(int width, int height) {
    struct canvas canvas;

    FILE *f = fopen("output.ppm", "w");

    canvas.width = width;
    canvas.height = height;
    canvas.f = f;

    fprintf(f, "P3\n%d %d\n255\n", width, height);

    return canvas;
}

void canvas_get_pixel(struct canvas *canvas, struct vec3 *px, struct vec3 *color) {
    assert(canvas);
    assert(color);

    canvas_adjust_px(color);

    *px = *color;
}

void canvas_create_image(struct canvas *canvas, struct vec3 *image) {
    assert(canvas);
    assert(image);

    for (int i = 0; i < canvas->height * canvas->width; ++i) {
        fprintf(canvas->f, "%u %u %u\n", (unsigned char) image[i].x, (unsigned char) image[i].y, (unsigned char) image[i].z);
    }
}

void canvas_destroy(struct canvas *canvas) {
    assert(canvas);

    fclose(canvas->f);
}