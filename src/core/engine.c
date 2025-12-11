#include "core/engine.h"
#include "io/input.h"

engine_t engine_create()
{
    graphic_t graphic = graphic_create("Game", 800, 600, 0);
    input_t input = input_create();
    command_list_t *commands = command_list_create(64);

    engine_t result = {
        .graphic = graphic,
        .input = input,
        .commands = commands,
    };

    return result;
}

void engine_destroy(engine_t *engine)
{
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
    graphic_run(&engine->graphic, engine->commands);
    engine->commands->len = 0;
}