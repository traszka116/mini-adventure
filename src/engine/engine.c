#include "engine/engine.h"

engine_t engine_create(char *title, int w, int h, scene_t init)
{
    return (engine_t){

        .graphic = graphic_create(title, w, h),
        .input = input_create(),
        .timer = tick_create(),
        .scenes = scene_manager_create(10, init),
    };
}

void engine_destroy(engine_t *engine)
{
    graphic_destroy(&engine->graphic);
    input_destroy(&engine->input);
    scene_manager_destroy(&engine->scenes);
}