#include "io/graphics.h"
#include "utils/array.h"
#include <iso646.h>

DYN_ARRAY_IMPL(command_list, command_t)

graphic_t graphic_create(char *name, int width, int height, SDL_WindowFlags flags)
{
    graphic_t result;

    SDL_Window *window = SDL_CreateWindow(name, width, height, flags);
    if (!window)
        return result;

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        SDL_DestroyWindow(window);
        return result;
    }

    result.window = window;
    result.renderer = renderer;
    return result;
}

void graphic_destroy(graphic_t *graphic)
{
    if (!graphic)
        return;

    if (graphic->renderer)
    {
        SDL_DestroyRenderer(graphic->renderer);
        graphic->renderer = NULL;
    }

    if (graphic->window)
    {
        SDL_DestroyWindow(graphic->window);
        graphic->window = NULL;
    }
}

PRIV void graphic_run_command(const graphic_t *graphic, texture_t atlas, command_t command)
{
    switch (command.cmd)
    {
    case Graphic_CLEAR:
        SDL_RenderClear(graphic->renderer);
        break;

    case Graphic_PRESENT:
        SDL_RenderPresent(graphic->renderer);
        break;

    case Graphic_RECT:
        struct GraphicRect rectangle = command.rect;
        SDL_FRect rect = {
            .x = rectangle.x,
            .y = rectangle.y,
            .w = rectangle.w,
            .h = rectangle.h,
        };
        SDL_RenderFillRect(graphic->renderer, &rect);
        break;

    case Graphic_SET_COLOR:
        struct GraphicSetColor color = command.set_color;
        SDL_SetRenderDrawColorFloat(graphic->renderer,
                                    color.r, color.g,
                                    color.b, color.a);
        break;

    case Graphic_TEXTURE:
        struct GraphicTexture txt = command.texture;
        SDL_FRect src = {
            .x = txt.src_x,
            .y = txt.src_y,
            .w = txt.src_w,
            .h = txt.src_h,
        };

        SDL_FRect dst = {
            .x = txt.dst_x,
            .y = txt.dst_y,
            .w = txt.dst_w,
            .h = txt.dst_h,
        };

        SDL_RenderTexture(graphic->renderer, atlas.texture, &src, &dst);
        break;

    default:
        UNREACHABLE;
    }
}

void graphic_run(const graphic_t *graphic, texture_t atlas, command_list_t *commands)
{
    size_t len = commands->len;
    for (size_t i = 0; i < len; i++)
    {
        command_t command = command_list_get(commands, i);
        graphic_run_command(graphic, atlas, command);
    }
}
