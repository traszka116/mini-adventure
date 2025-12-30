#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iso646.h>
#include <SDL3/SDL.h>

#include "utils/safe.h"
#include "system/input.h"
#include "system/graphic.h"
#include "system/timer.h"

int main(void)
{
    /*
    ASSERT(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO));

    graphic_t graphic = graphic_create("mini-adventure", 800, 600);
    input_t input = input_create();
    timer_t timer = timer_create();

    while (not input.quit)
    {
        float dt = timer_elapsed(&timer);
        input_update(&input);

    }

    input_destroy(&input);
    graphic_destroy(&graphic);

    SDL_Quit();
    */


    return 0;
}
