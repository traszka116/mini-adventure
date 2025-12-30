#include "system/texture/texture.h"
#include "stb_image.h"
#include "utils/safe.h"

texture_t texture_create(char *file, SDL_Renderer *renderer)
{
    texture_t tex = {0};
    int w, h;
    uint8_t *pixels = stbi_load(file, &w, &h, NULL, 4);
    ASSERT(pixels);
    tex.tex = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        w, h);
    ASSERT(tex.tex);
    SDL_UpdateTexture(tex.tex, NULL, pixels, w * 4);
    stbi_image_free(pixels);
    tex.size.x = (uint16_t)(w);
    tex.size.y = (uint16_t)(h);
    return tex;
}

void texture_destroy(texture_t *texture)
{
    if (!texture || !texture->tex)
    {
        return;
    }
    SDL_DestroyTexture(texture->tex);
    texture->tex = NULL;
    texture->size.x = 0;
    texture->size.y = 0;
}

DYN_ARRAY_IMPL(buckets_texture, texture_res_t);

texture_manager_t texture_manager_create(size_t cap, SDL_Renderer *renderer)
{
    buckets_texture_t *buckets = buckets_texture_create(cap);
    ASSERT(buckets);
    return (texture_manager_t){
        .buckets = buckets,
        .renderer = renderer,
    };
}

void texture_manager_destroy(texture_manager_t *manager)
{
    for (size_t i = 0; i < manager->buckets->len; i++)
    {
        texture_res_t *res = buckets_texture_at(manager->buckets, i);
        texture_destroy(&res->texture);
    }
    buckets_texture_destroy(manager->buckets);
}

texture_t texture_load(texture_manager_t *manager, char *name)
{
    // find if texture is loaded
    for (size_t i = 0; i < manager->buckets->len; i++)
    {
        texture_res_t *res = buckets_texture_at(manager->buckets, i);
        // if is loaded
        if (strncmp(res->name, name, NAME_LEN) == 0)
        {
            return res->texture;
        }
    }

    // if not loaded
    texture_t tex = texture_create(name, manager->renderer);

    ASSERT(buckets_texture_push(&manager->buckets, (texture_res_t){}));

    texture_res_t *tex_res = buckets_texture_at(manager->buckets, manager->buckets->len - 1);
    strncpy(tex_res->name, name, NAME_LEN);
    tex_res->texture = tex;

    return tex;
}

void texture_unload(texture_manager_t *manager, texture_t texture)
{
    // find and remove texture
    for (size_t i = 0; i < manager->buckets->len; i++)
    {
        texture_res_t *res = buckets_texture_at(manager->buckets, i);
        if (texture.tex == res->texture.tex)
        {
            // destroy texture
            texture_destroy(&res->texture);
            // removed bucket
            (void)buckets_texture_remove(&manager->buckets, i);
            return;
        }
    }
}
