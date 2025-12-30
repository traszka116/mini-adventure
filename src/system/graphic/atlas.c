#include "system/texture/atlas.h"

atlas_t atlas_from_texture(texture_t texture, tsize_t size, uint8_t padding)
{
    return (atlas_t){
        .item_size = size,
        .padding = padding,
        .texture = texture,
    };
}
