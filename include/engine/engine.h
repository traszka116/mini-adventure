#ifndef ENGINE_H
#define ENGINE_H

#include "system/graphic.h"
#include "system/input.h"
#include "system/timer.h"
#include "engine/scene.h"

typedef struct
{
    graphic_t graphic;
    input_t input;
    tick_t timer;
    scene_manager_t scenes;
} engine_t;

engine_t engine_create(char *title, int w, int h, scene_t scene);
void engine_destroy(engine_t *engine);
void engine_run(engine_t *engine);

#endif