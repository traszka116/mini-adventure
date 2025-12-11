#include "io/graphics.h"
#include "array.h"
#include <iso646.h>

DYN_ARRAY_IMPL(command_list, command_t)

graphic_t graphic_create(char *name, int width, int height, SDL_WindowFlags flags)
{
    graphic_t result = {
        .window = NULL,
        .renderer = NULL,
    };

    SDL_Window *window = SDL_CreateWindow(name, width, height, flags);
    if (!window)
        goto clean_window;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
        goto clean_renderer;

    result.renderer = renderer;
    result.window = window;

    return result;

clean_renderer:
    SDL_DestroyRenderer(renderer);
clean_window:
    SDL_DestroyWindow(window);

    return result;
}

void graphic_destroy(graphic_t *graphic)
{
    if (!graphic->renderer or !graphic->window)
        return;

    SDL_DestroyRenderer(graphic->renderer);
    graphic->renderer = NULL;

    SDL_DestroyWindow(graphic->window);
    graphic->window = NULL;
}

// // this is proper implementation of command pattern for graphic implementation
PRIV void graphic_run_command(const graphic_t *graphic, command_t command)
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

    default:
        UNREACHABLE;
    }
}

void graphic_run(const graphic_t *graphic, command_list_t *commands)
{
    size_t len = commands->len;
    for (size_t i = 0; i < len; i++)
    {
        command_t command = command_list_get(commands, i);
        graphic_run_command(graphic, command);
    }
}
