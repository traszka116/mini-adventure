#include "utils/array.h"
#include "game/vector.h"
#include <stdbool.h>
#ifndef CHARACTER_H
#define CHARACTER_H

typedef struct
{
    size_t id;
    vec2_t position, velocity;
    float radius,
        max_speed,
        acceleration;

} character_t;

DYN_ARRAY_DECL(character_list, character_t);
void character_add_velocity(character_t *character, vec2_t vel);
bool character_collision(character_t *, character_t *, vec2_t *);
void character_move(character_t *character, float dt, float friction);
character_t create_character(vec2_t pos, float r, float max_v, float a);
#endif