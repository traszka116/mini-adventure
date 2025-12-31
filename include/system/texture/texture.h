#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL3/SDL.h>
#include "stdint.h"
#include "utils/safe.h"
#include "utils/array.h"

#define NAME_LEN 256
// texture size helper

typedef struct
{
    uint16_t x, y;
} tsize_t;

// texture/atlas definition

typedef struct
{
    SDL_Texture *tex;
    tsize_t size;
} texture_t;

// texture manager

typedef struct
{
    char name[NAME_LEN];
    texture_t texture;
} texture_res_t;

DYN_ARRAY_DECL_T(buckets_texture, texture_res_t);

typedef struct
{
    buckets_texture_t *buckets;
    SDL_Renderer *renderer; // borrowed
} texture_manager_t;

texture_manager_t texture_manager_create(size_t, SDL_Renderer *);
void texture_manager_destroy(texture_manager_t *);

texture_t texture_load(texture_manager_t *, char *);
void texture_unload(texture_manager_t *, texture_t);

#endif