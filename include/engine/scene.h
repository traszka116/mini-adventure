#ifndef SCENE_H
#define SCENE_H

#include "utils/func.h"
#include "system/input.h"
#include "system/graphic.h"

typedef struct
{
    char name[NAME_LEN];
    void *context;
    FUNC(update, void, void *, input_t, float);
    FUNC(render, void, void *, graphic_t *);
} scene_t;

scene_t scene_create(char *name, void *ctx,
                     FUNC(update, void, void *, input_t, float),
                     FUNC(render, void, void *, graphic_t *));



#endif