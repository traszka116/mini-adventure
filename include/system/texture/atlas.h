#ifndef ATLAS_H
#define ATLAS_H
#include "system/texture/texture.h"

typedef struct
{
    tsize_t item_size;
    uint8_t padding;
    texture_t texture;
} atlas_t;

atlas_t atlas_from_texture(texture_t, tsize_t, uint8_t);


#endif