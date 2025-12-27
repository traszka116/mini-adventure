#include "core/engine.h"
#include "io/input.h"

engine_t engine_create(char *title, int width, int height, char *atlas)
{
    graphic_t graphic = graphic_create(title, width, height, 0);
    input_t input = input_create();
    command_list_t *commands = command_list_create(64);
    texture_t tex = texture_load(atlas, graphic.renderer);

    engine_t result = {
        .graphic = graphic,
        .input = input,
        .commands = commands,
        .last_tick = SDL_GetTicks(),
        .delta_time = 0.0f,
        .atlas = tex,
    };

    return result;
}

void engine_destroy(engine_t *engine)
{
    texture_destroy(&engine->atlas);
    command_list_destroy(engine->commands);
    input_destroy(&engine->input);
    graphic_destroy(&engine->graphic);
}

void engine_read_input(engine_t *engine)
{
    input_update(&engine->input);
}

void engine_render(engine_t *engine)
{
    graphic_run(&engine->graphic, engine->atlas, engine->commands);
    engine->commands->len = 0;
}

void engine_time_tick(engine_t *engine)
{
    uint64_t prev = engine->last_tick;
    uint64_t now = SDL_GetTicks();
    engine->last_tick = now;
    engine->delta_time = ((float)(now - prev)) / 1000.0f;
}