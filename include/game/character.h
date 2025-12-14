#include "utils/array.h"
#include "game/vector.h"
#ifndef CHARACTER_H
#define CHARACTER_H

DYN_ARRAY_DECL(vec2_list, vec2_t);

typedef struct
{
    vec2_t position, velocity;
} character_t;

typedef struct
{
    vec2_list_t *positions, *velocities;
} characters_t;

characters_t characters_init(size_t);
void characters_destroy(characters_t *);

character_t characters_get(characters_t, size_t);
void characters_set(characters_t *, size_t, character_t);

int characters_push(characters_t *, character_t);
character_t characters_pop(characters_t *);

void characters_remove(characters_t *, size_t);
size_t characters_count(characters_t *characters);

#endif