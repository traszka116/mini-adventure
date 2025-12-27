#include "game/character.h"
#include "io/input.h"
#include "game/materials.h"

void player_update(character_t *character, input_t *input, float dt)
{
    vec2_t motion = {0, 0};
    if (is_key_down(input, SDL_SCANCODE_W))
    {
        motion.y -= 1;
    }
    if (is_key_down(input, SDL_SCANCODE_S))
    {
        motion.y += 1;
    }
    if (is_key_down(input, SDL_SCANCODE_A))
    {
        motion.x -= 1;
    }
    if (is_key_down(input, SDL_SCANCODE_D))
    {
        motion.x += 1;
    }

    character_add_velocity(character, vec2_scale(vec2_norm(motion), dt * character->acceleration));
}
