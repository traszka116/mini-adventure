#include "utils/lmath.h"
#include <math.h>
vec2_t vec2_add(vec2_t a, vec2_t b)
{
    vec2_t result = {a.x + b.x, a.y + b.y};
    return result;
}

vec2_t vec2_sub(vec2_t a, vec2_t b)
{
    vec2_t result = {a.x - b.x, a.y - b.y};
    return result;
}

vec2_t vec2_scale(vec2_t v, float s)
{
    vec2_t result = {v.x * s, v.y * s};
    return result;
}

float vec2_len(vec2_t v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

vec2_t vec2_norm(vec2_t v)
{
    float len = vec2_len(v);
    float fac = 1 / len;

    if (len == 0)
    {
        v.x = 0;
        v.y = 0;
        return v;
    }

    v.x *= fac;
    v.y *= fac;

    return v;
}

float vec2_len2(vec2_t v)
{
    float len = v.x * v.x + v.y * v.y;
    return len;
}