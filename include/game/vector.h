#ifndef VECTOR_H
#define VECTOR_H
typedef struct
{
    float x, y;
} vec2_t;

vec2_t vec2_add(vec2_t a, vec2_t b);
vec2_t vec2_sub(vec2_t a, vec2_t b);
vec2_t vec2_scale(vec2_t v, float s);
vec2_t vec2_norm(vec2_t v);
float vec2_len(vec2_t v);
float vec2_len2(vec2_t v);
#endif