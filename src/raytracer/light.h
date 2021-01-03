#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"

struct light
{
    struct vec3 origin;
    struct vec3 color;
    float intensity;
};

#endif //LIGHT_H
