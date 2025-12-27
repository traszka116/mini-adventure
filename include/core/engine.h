#ifndef ENGINE_H
#define ENGINE_H

#include "io/graphics.h"
#include "io/input.h"

typedef struct
{
    // io bound modules
    graphic_t graphic;
    input_t input;

    // renderer command list
    command_list_t *commands;

    // texture atlas
    texture_t atlas;

    // timer
    uint64_t last_tick;
    float delta_time;
} engine_t;

engine_t engine_create(char *title, int width, int height, char* atlas);
void engine_destroy(engine_t *engine);
void engine_read_input(engine_t *engine);
void engine_render(engine_t *engine);
void engine_time_tick(engine_t *engine);

#endif