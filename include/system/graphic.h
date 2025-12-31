#ifndef GRAPHIC_H
#define GRAPHIC_H
#include <SDL3/SDL.h>
#include "system/texture/texture.h"
#include "system/texture/atlas.h"
#include "system/command.h"
#include "utils/array.h"

DYN_ARRAY_DECL(gcmd_list, graphic_cmd_t);

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    texture_manager_t texture_manager;
    gcmd_list_t *commands;
    int w, h;
} graphic_t;

graphic_t graphic_create(char *name, int h, int w);
void graphic_destroy(graphic_t *);

void graphic_add_command(graphic_t *, graphic_cmd_t);
void graphic_execute(graphic_t *);

#endif