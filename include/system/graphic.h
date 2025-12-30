#ifndef GRAPHIC_H
#define GRAPHIC_H
#include <SDL3/SDL.h>
#include "system/texture/texture.h"
#include "system/texture/atlas.h"

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    texture_manager_t texture_manager;
} graphic_t;

graphic_t graphic_create(char *name, int h, int w);
void graphic_destroy(graphic_t *);

#endif