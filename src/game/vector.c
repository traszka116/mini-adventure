#include "game/vector.h"

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