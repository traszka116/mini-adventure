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
} engine_t;

engine_t engine_create();
void engine_destroy(engine_t *engine);
void engine_read_input(engine_t *engine);
void engine_render(engine_t *engine);
#endif