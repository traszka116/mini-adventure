#include "system/graphic.h"
#include "utils/safe.h"

graphic_t graphic_create(char *name, int h, int w)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    ASSERT(SDL_CreateWindowAndRenderer(name, w, h,
                                       SDL_WINDOW_RESIZABLE,
                                       &window, &renderer));

    texture_manager_t man = texture_manager_create(10, renderer);

    return (graphic_t){
        .window = window,
        .renderer = renderer,
        .texture_manager = man,
    };
}

void graphic_destroy(graphic_t *graphic)
{
    texture_manager_destroy(&graphic->texture_manager);

    SDL_DestroyRenderer(graphic->renderer);
    SDL_DestroyWindow(graphic->window);

    graphic->renderer = NULL;
    graphic->window = NULL;
}
