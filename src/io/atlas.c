#include "io/texture.h"
#include "utils/array.h"
#include <SDL3/SDL.h>

typedef struct
{
    // internally stored texture
    texture_t texture;
    // single texture width and height
    size_t tex_w, tex_h;
    // space between textures in atlas
    size_t padding;
} atlas_t;



typedef struct
{

} atlas_manager_t;