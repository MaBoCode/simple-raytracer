#ifndef CANVAS_H
#define CANVAS_H

#include <stdio.h>

#include "vector.h"

struct canvas
{
    FILE *f;
    int width;
    int height;
    struct vec3 color;
};

struct canvas canvas_init(int width, int height);

void canvas_get_pixel(struct canvas *canvas, struct vec3 *px, struct vec3 *color);

void canvas_create_image(struct canvas *canvas, struct vec3 *image);

void canvas_destroy(struct canvas *canvas);

#endif //CANVAS_H
