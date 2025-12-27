#include <SDL3/SDL.h>
#include "stdint.h"
#include "io/texture.h"
#include "stb_image.h"
#include "utils/debug.h"
#include "utils/safe.h"

texture_t texture_load(char *name, SDL_Renderer *renderer)
{
    texture_t tex = {0};

    int w, h;
    uint8_t *pixels = stbi_load(name, &w, &h, NULL, 4);
    ASSERT(pixels);

    tex.texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        w,
        h);

    ASSERT(tex.texture);

    SDL_UpdateTexture(tex.texture, NULL, pixels, w * 4);

    stbi_image_free(pixels);

    tex.w = w;
    tex.h = h;

    return tex;
}

void texture_destroy(texture_t *texture)
{
    if (!texture || !texture->texture)
        return;

    SDL_DestroyTexture(texture->texture);
    texture->texture = NULL;
    texture->w = 0;
    texture->h = 0;
}