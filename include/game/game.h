#include "game/vector.h"
#include "game/character.h"

#ifndef GAME_H
#define GAME_H

typedef struct
{
    vec2_t position;
} camera_t;

typedef struct
{
    camera_t camera;

} game_t;



#endif