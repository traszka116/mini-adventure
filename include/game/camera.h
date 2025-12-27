#include "game/vector.h"
#ifndef CAMERA_H
#define CAMERA_H

typedef struct
{
    vec2_t position;
    vec2_t size;
} camera_t;

vec2_t camera_coords(camera_t, vec2_t);

#endif