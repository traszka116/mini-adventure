#include <SDL3/SDL.h>
#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct
{
    size_t w, h;
    SDL_Texture *texture;
} texture_t;

texture_t texture_load(char *name, SDL_Renderer *renderer);
void texture_destroy(texture_t *);

#endif