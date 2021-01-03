#ifndef VECTOR_H
#define VECTOR_H

struct vec3
{
    float x;
    float y;
    float z;
};

struct vec3 vec3_add(const struct vec3 *a, const  struct  vec3 *b);

struct vec3 vec3_sub(const struct vec3 *a, const struct vec3 *b);

struct vec3 vec3_neg(const struct vec3 *a);

struct vec3 vec3_mul(const struct vec3 *a, const struct vec3 *b);

struct vec3 vec3_mul_nb(const struct vec3 *a, float nb);

struct vec3 vec3_div_nb(const struct vec3 *a, float nb);

float vec3_len(const struct vec3 *a);

void vec3_normalize(struct vec3 *a);

float vec3_dot(const struct vec3 *a, const struct vec3 *b);

struct vec3 vec3_cross(const struct vec3 *a, const struct vec3 *b);

#endif //VECTOR_H
