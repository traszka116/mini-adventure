#include "game/character.h"
#include "io/input.h"

#ifndef PLAYER_H
#define PLAYER_H
void player_update(character_t *character, input_t *input, float dt);
#endif