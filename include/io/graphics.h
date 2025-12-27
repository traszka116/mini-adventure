#include <SDL3/SDL.h>
#include "utils/function.h"
#include "utils/array.h"
#include "io/texture.h"

#ifndef GRAPHICS_H
#define GRAPHICS_H

enum GraphicCommandType
{
    Graphic_CLEAR,
    Graphic_PRESENT,
    Graphic_SET_COLOR,
    Graphic_RECT,
    Graphic_TEXTURE,
};

struct GraphicSetColor
{
    enum GraphicCommandType cmd;
    float r, g, b, a;
};

struct GraphicRect
{
    enum GraphicCommandType cmd;
    float x, y, w, h;
};

struct GraphicClear
{
    enum GraphicCommandType cmd;
};

struct GraphicTexture
{
    enum GraphicCommandType cmd;
    float src_x, src_y, src_w, src_h;
    float dst_x, dst_y, dst_w, dst_h;
};

struct GraphicPresent
{
    enum GraphicCommandType cmd;
};

typedef union
{
    enum GraphicCommandType cmd;
    struct GraphicRect rect;
    struct GraphicSetColor set_color;
    struct GraphicClear clear;
    struct GraphicPresent present;
    struct GraphicTexture texture;
} command_t;

DYN_ARRAY_DECL(command_list, command_t);

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} graphic_t;

graphic_t graphic_create(char *name, int width, int height, SDL_WindowFlags);
void graphic_destroy(graphic_t *);

void graphic_run(const graphic_t *graphic, texture_t atlas, command_list_t *commands);

#endif