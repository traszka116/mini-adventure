#include "game/character.h"
#include "utils/array.h"

DYN_ARRAY_IMPL(vec2_list, vec2_t);

characters_t characters_init(size_t capacity)
{
    characters_t characters = {
        .positions = NULL,
        .velocities = NULL,
    };

    vec2_list_t *positions = vec2_list_create(capacity);
    vec2_list_t *velocities = vec2_list_create(capacity);

    if (!(positions && velocities))
    {
        vec2_list_destroy(positions);
        vec2_list_destroy(velocities);
        return characters;
    }

    characters.positions = positions;
    characters.velocities = velocities;
    return characters;
}

void characters_destroy(characters_t *characters)
{
    vec2_list_destroy(characters->positions);
    vec2_list_destroy(characters->velocities);
    characters->positions = NULL;
    characters->velocities = NULL;
}

character_t characters_get(characters_t characters, size_t n)
{
    vec2_t pos = vec2_list_get(characters.positions, n);
    vec2_t vel = vec2_list_get(characters.velocities, n);

    character_t character = {
        .position = pos,
        .velocity = vel,
    };

    return character;
}

void characters_set(characters_t *characters, size_t n, character_t character)
{
    vec2_list_set(characters->positions, n, character.position);
    vec2_list_set(characters->velocities, n, character.velocity);
}

int characters_push(characters_t *characters, character_t character)
{
    if (!vec2_list_push(&characters->positions, character.position))
    {
        return 0;
    }

    if (!vec2_list_push(&characters->velocities, character.velocity))
    {
        vec2_list_pop(characters->positions);
        return 0;
    }

    return 1;
}

character_t characters_pop(characters_t *characters)
{
    vec2_t pos = vec2_list_pop(characters->positions);
    vec2_t vel = vec2_list_pop(characters->velocities);
    character_t character = {
        .position = pos,
        .velocity = vel,
    };
    return character;
}

void characters_remove(characters_t *characters, size_t n)
{
    character_t character = characters_pop(characters);
    characters_set(characters, n, character);
}