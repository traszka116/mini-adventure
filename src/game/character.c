#include "game/character.h"
#include "utils/array.h"
#include "game/vector.h"
#include "utils/debug.h"
#include "utils/lmath.h"
#include <math.h>

DYN_ARRAY_IMPL(character_list, character_t);

void character_translate(character_t *character)
{
    character->position = vec2_add(character->position, character->velocity);
}

void character_friction(character_t *character, float friction, float dt)
{
    if (friction <= 0.0f)
        return;

    if (friction >= 1.0f)
    {
        character->velocity = (vec2_t){0, 0};
        return;
    }

    float retention = 1.0f - friction;

    float scale = powf(retention, dt);
    character->velocity = vec2_scale(character->velocity, scale);

    if (vec2_len2(character->velocity) < 1e-6f)
        character->velocity = (vec2_t){0, 0};
}

void character_add_velocity(character_t *character, vec2_t vel)
{
    vec2_t result = character->velocity;
    result = vec2_add(character->velocity, vel);
    if (vec2_len2(result) >= powf(character->max_speed, 2))
    {
        result = vec2_scale(vec2_norm(result), character->max_speed);
    }
    character->velocity = result;
}

bool character_collision(character_t *a, character_t *b, vec2_t *v)
{
    if (a == b)
        return false;

    vec2_t delta = vec2_sub(a->position, b->position);
    float dist2 = vec2_len2(delta);
    float r = a->radius + b->radius;

    if (dist2 > r * r)
        return false;

    if (v)
    {
        float totalRadius = a->radius + b->radius;
        float t = a->radius / totalRadius;
        *v = vec2_add(a->position, vec2_scale(vec2_sub(b->position, a->position), 0.3 * t));
    }

    return true;
}

void character_move(character_t *character, float dt, float friction)
{
    character_translate(character);
    character_friction(character, friction, dt);
}

character_t create_character(vec2_t pos, float r, float max_v, float a)
{
    static size_t last_id = 0;
    
    character_t character = {
        .position = pos,
        .radius = r,
        .velocity = {0, 0},
        .max_speed = max_v,
        .acceleration = a,
    };

    last_id++;

    return character;
}
