#ifndef SCENE_H
#define SCENE_H

#include "utils/func.h"
#include "system/input.h"
#include "system/graphic.h"
#include "utils/array.h"

typedef struct
{
    char name[NAME_LEN];
    void *context;
    bool loaded;

    FUNC(update, void, scene_t *, input_t, float);
    FUNC(render, void, const scene_t *, graphic_t *);

    FUNC(onEntry, void, scene_t *);
    FUNC(onExit, void, scene_t *);
    FUNC(load, void, scene_t *);
    FUNC(unload, void, scene_t *);
} scene_t;

static inline scene_t scene_create(
    const char *name,
    void *context,
    FUNC(load, void, scene_t *),
    FUNC(unload, void, scene_t *),
    FUNC(onEntry, void, scene_t *),
    FUNC(onExit, void, scene_t *),
    FUNC(update, void, scene_t *, input_t, float),
    FUNC(render, void, const scene_t *, graphic_t *))
{
    scene_t scene = {
        .context = context,
        .onEntry = onEntry,
        .onExit = onExit,

        .update = update,
        .render = render,

        // for preloading
        .load = load,
        .unload = unload,
        .loaded = false,
    };
    strncpy(scene.name, name, NAME_LEN);
    return scene;
}

DYN_ARRAY_DECL_T(scene_list, scene_t);

typedef struct
{
    scene_list_t *scenes;
    size_t active_scene_idx;
} scene_manager_t;

scene_manager_t scene_manager_create(size_t cap, scene_t initial);
void scene_manager_destroy(scene_manager_t *);
void scene_manager_register(scene_manager_t *, scene_t);

bool scene_manager_load(scene_manager_t *, const char *name);
bool scene_manager_unload(scene_manager_t *, const char *name);

bool scene_manager_select(scene_manager_t *, const char *name);
scene_t scene_manager_active(scene_manager_t *);



#endif