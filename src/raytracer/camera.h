#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "canvas.h"
#include "world.h"

/*
** The camera is a physical object in its own right, positioned in space just
** like any other. When casting a ray, the raytracer must express the coordinates
** of the starting point of the ray, relative to the image plane defined by the
** camera.
**
** One way to do it is to define the bottom left corner of the image plane to be
** at (-0.5, 0.5), its center to be at (0, 0), and its top right corner to be at
** (0.5, 0.5).
**
** This way, the camera doesn't have to know about the dimensions of the output
** image: it just traces rays where asked to.
**
**  (x=-0.5, y=0.5)                (x=0.5, y=0.5)
**        +------------------------------+
**        |                              |
**        |              ^ y             |
**        |              |               |
**        |              +---> x         |
**        |            center            |
**        |                              |
**        |                              |
**        +------------------------------+
** (x=-0.5, y=-0.5)                (x=0.5, y=-0.5)
*/

struct camera
{
    struct vec3 center;
    struct vec3 up;
    struct vec3 forward;
    float width;
    float height;
    float focal;
};

struct canvas camera_render(const struct camera *camera, struct world *world);

float camera_get_focal(float width, float fov_deg);

#endif //CAMERA_H
