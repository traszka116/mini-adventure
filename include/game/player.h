#include "game/character.h"
#include "io/input.h"

#ifndef PLAYER_H
#define PLAYER_H

typedef struct
{
    size_t character_id;
} player_t;

void player_update(character_t *character, input_t *input, float dt);
void player_draw(character_t *character, camera_t cam, command_list_t **command);

#endif