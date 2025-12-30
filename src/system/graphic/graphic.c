#include "system/graphic.h"
#include "utils/safe.h"

graphic_t graphic_create(char *name, int h, int w)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    ASSERT(SDL_CreateWindowAndRenderer(name, w, h,
                                       SDL_WINDOW_RESIZABLE,
                                       &window, &renderer));

    return (graphic_t){
        .window = window,
        .renderer = renderer,
    };
}

void graphic_destroy(graphic_t *graphic)
{
    SDL_DestroyRenderer(graphic->renderer);
    SDL_DestroyWindow(graphic->window);

    graphic->renderer = NULL;
    graphic->window = NULL;
}

