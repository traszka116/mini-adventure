#ifndef COMMAND_H
#define COMMAND_H
#include <SDL3/SDL.h>
#include "system/texture/texture.h"
#include "system/texture/atlas.h"

typedef enum
{
    // color controll
    GCMD_SET_COLOR,

    // basic shapes
    GCMD_POINTS,
    GCMD_LINES,
    GCMD_RECT,

    // textures
    GCMD_TEXTURE,
    GCMD_ATLAS,

    // modifiers
    GCMD_BLEND_MOD,
    GCMD_ALPHA_MOD,
    GCMD_COLOR_MOD,
} GraphicCmd;

// color controll

typedef struct
{
    GraphicCmd cmd;
    float r, g, b, a;
} gcmd_color_set_t;

// basic shapes

typedef struct
{
    GraphicCmd cmd;
    const SDL_FPoint *points;
    size_t count;
} gcmd_points_t;

typedef struct
{
    GraphicCmd cmd;
    const SDL_FPoint *points;
    size_t count;
} gcmd_lines_t;

typedef struct
{
    GraphicCmd cmd;
    SDL_FRect rect;
} gcmd_rect_t;

// textures

typedef struct
{
    GraphicCmd cmd;
    const texture_t *texture;
    SDL_FRect src, dst;
} gcmd_texture_t;

typedef struct
{
    GraphicCmd cmd;
    const atlas_t *atlas;
    uint8_t row, column;
    SDL_FRect dst;
} gcmd_atlas_t;

// modifiers

typedef struct
{
    GraphicCmd cmd;
    const texture_t *texture;
    float r, g, b;
} gcmd_mod_color_t;

typedef struct
{
    GraphicCmd cmd;
    const texture_t *texture;
    float alpha;
} gcmd_mod_alpha_t;

typedef struct
{
    GraphicCmd cmd;
    const texture_t *texture;
    SDL_BlendMode mode;
} gcmd_mod_blend_t;

// command type

typedef union
{
    GraphicCmd cmd;

    gcmd_color_set_t set_color;

    gcmd_points_t points;
    gcmd_lines_t lines;
    gcmd_rect_t rect;

    gcmd_texture_t texture;
    gcmd_atlas_t atlas;

    gcmd_mod_color_t mod_color;
    gcmd_mod_alpha_t mod_alpha;
    gcmd_mod_blend_t mod_blend;
} graphic_cmd_t;

// constructors
static inline graphic_cmd_t gcmd_set_color(float r, float g, float b, float a)
{
    graphic_cmd_t cmd = {};
    cmd.set_color.cmd = GCMD_SET_COLOR;
    cmd.set_color.r = r;
    cmd.set_color.g = g;
    cmd.set_color.b = b;
    cmd.set_color.a = a;
    return cmd;
}

static inline graphic_cmd_t gcmd_points(const SDL_FPoint *points, size_t count)
{
    graphic_cmd_t cmd = {};
    cmd.points.cmd = GCMD_POINTS;
    cmd.points.points = (SDL_FPoint *)points;
    cmd.points.count = count;
    return cmd;
}

static inline graphic_cmd_t gcmd_lines(const SDL_FPoint *points, size_t count)
{
    graphic_cmd_t cmd = {};
    cmd.lines.cmd = GCMD_LINES;
    cmd.lines.points = (SDL_FPoint *)points;
    cmd.lines.count = count;
    return cmd;
}

static inline graphic_cmd_t gcmd_rect(SDL_FRect rect)
{
    graphic_cmd_t cmd = {};
    cmd.rect.cmd = GCMD_RECT;
    cmd.rect.rect = rect;
    return cmd;
}

static inline graphic_cmd_t gcmd_texture(const texture_t *texture, SDL_FRect src, SDL_FRect dst)
{
    graphic_cmd_t cmd = {};
    cmd.texture.cmd = GCMD_TEXTURE;
    cmd.texture.texture = texture;
    cmd.texture.src = src;
    cmd.texture.dst = dst;
    return cmd;
}

static inline graphic_cmd_t gcmd_atlas(const atlas_t *atlas, uint8_t row, uint8_t col, SDL_FRect dst)
{
    graphic_cmd_t cmd = {};
    cmd.atlas.cmd = GCMD_ATLAS;
    cmd.atlas.atlas = atlas;
    cmd.atlas.row = row;
    cmd.atlas.column = col;
    cmd.atlas.dst = dst;
    return cmd;
}

static inline graphic_cmd_t gcmd_mod_color(const texture_t *texture, float r, float g, float b)
{
    graphic_cmd_t cmd = {};
    cmd.mod_color.cmd = GCMD_COLOR_MOD;
    cmd.mod_color.texture = texture;
    cmd.mod_color.r = r;
    cmd.mod_color.g = g;
    cmd.mod_color.b = b;
    return cmd;
}

static inline graphic_cmd_t gcmd_mod_alpha(const texture_t *texture, float alpha)
{
    graphic_cmd_t cmd = {};
    cmd.mod_alpha.cmd = GCMD_ALPHA_MOD;
    cmd.mod_alpha.texture = texture;
    cmd.mod_alpha.alpha = alpha;
    return cmd;
}

static inline graphic_cmd_t gcmd_mod_blend(const texture_t *texture, SDL_BlendMode mode)
{
    graphic_cmd_t cmd = {};
    cmd.mod_blend.cmd = GCMD_BLEND_MOD;
    cmd.mod_blend.texture = texture;
    cmd.mod_blend.mode = mode;
    return cmd;
}

#endif