#include "game/character.h"
#include "io/input.h"
#include "game/materials.h"
#include "io/graphics.h"
#include "game/camera.h"
#include "game/player.h"

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

void player_draw(character_t *character, camera_t cam, command_list_t **command)
{

    vec2_t translated = camera_coords(cam, character->position);

    command_t texture = {
        .texture = {
            .cmd = Graphic_TEXTURE,

            .src_x = 0,
            .src_y = 0,
            .src_w = 32,
            .src_h = 32,

            .dst_x = translated.x - character->radius,
            .dst_y = translated.y - character->radius,
            .dst_w = character->radius * 2,
            .dst_h = character->radius * 2,
        },
    };

    command_list_push(command, texture);
}