#include "game/vector.h"
#include "game/character.h"
#include "game/camera.h"
#include "io/graphics.h"
#include "io/input.h"
#include "io/texture.h"
#include "game/player.h"

#ifndef GAME_H
#define GAME_H

typedef struct
{
    camera_t camera;
    player_t player;
    character_list_t *characters;
} game_t;

game_t game_create();
void game_destroy(game_t *);

void game_draw(game_t *, command_list_t **);
void game_update(game_t *, input_t *, float);

#endif