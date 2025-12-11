#include <SDL3/SDL.h>
#include "utils/function.h"
#include "utils/array.h"

#ifndef GRAPHICS_H
#define GRAPHICS_H

enum GraphicCommandType
{
    Graphic_CLEAR,
    Graphic_PRESENT,
    Graphic_SET_COLOR,
    Graphic_RECT,
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
} command_t;

DYN_ARRAY_DECL(command_list, command_t)

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} graphic_t;

graphic_t graphic_create(char *name, int width, int height, SDL_WindowFlags);
void graphic_destroy(graphic_t *);

void graphic_run(const graphic_t *, command_list_t *);

#endif