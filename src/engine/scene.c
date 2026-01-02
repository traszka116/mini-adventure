#include "engine/scene.h"
#include "utils/array.h"
#include "utils/safe.h"

DYN_ARRAY_IMPL(scene_list, scene_t);

scene_manager_t scene_manager_create(size_t cap, scene_t initial)
{
    scene_list_t *scenes = scene_list_create(cap);
    ASSERT(scenes);

    scenes->len = 1;
    *scene_list_at(scenes, 0) = initial;

    return (scene_manager_t){
        .active_scene_idx = 0,
        .scenes = scenes,
    };
}

void scene_manager_destroy(scene_manager_t *manager)
{
    scene_list_destroy(manager->scenes);
    manager->scenes = NULL;
}

void scene_manager_register(scene_manager_t *manager, scene_t scene)
{
    ASSERT(scene_list_push(&manager->scenes, scene));
}

bool scene_manager_select(scene_manager_t *manager, const char *name)
{
    size_t count = manager->scenes->len;
    for (size_t i = 0; i < count; i++)
    {
        scene_t *scene = scene_list_at(manager->scenes, i);
        if (strncmp(scene->name, name, NAME_LEN) == 0)
        {
            // close old scene
            scene_t *old = scene_list_at(manager->scenes, manager->active_scene_idx);
            if (old->onExit)
                old->onExit(old);

            // load if not loaded
            if (!scene->loaded && scene->load)
                scene->load(scene);

            scene->loaded = true;

            // enter scene
            if (scene->onEntry)
                scene->onEntry(scene);
            manager->active_scene_idx = i;

            return true;
        }
    }

    return false;
}

scene_t scene_manager_active(scene_manager_t *manager)
{
    return scene_list_get(manager->scenes, manager->active_scene_idx);
}

void scene_manager_load(scene_manager_t *manager, const char *name)
{
    size_t count = manager->scenes->len;
    for (size_t i = 0; i < count; i++)
    {
        scene_t *scene = scene_list_at(manager->scenes, i);
        if (strncmp(scene->name, name, NAME_LEN) == 0)
        {
            // close old scene
            scene_t *old = scene_list_at(manager->scenes, manager->active_scene_idx);
            old->onExit(old);

            // load if not loaded
            if (!scene->loaded && scene->load)
                scene->load(scene);
            scene->loaded = true;

            // enter scene
            scene->onEntry(scene);
            manager->active_scene_idx = i;

            return;
        }
    }
}

void scene_manager_unload(scene_manager_t *manager, const char *name)
{

    size_t count = manager->scenes->len;
    for (size_t i = 0; i < count; i++)
    {
        scene_t *scene = scene_list_at(manager->scenes, i);
        if (strncmp(scene->name, name, NAME_LEN) == 0)
        {
            if (!scene->loaded && scene->unload)
                scene->unload(scene);

            scene->loaded = false;

            return;
        }
    }
}
