#include <iso646.h>
#include <SDL3/SDL.h>

#include "io/graphics.h"
#include "io/input.h"
#include "core/engine.h"
#include "game/character.h"

int main(void)
{
    ASSERT(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO));

    engine_t engine = engine_create();

    characters_t chars = characters_init(10);

    while (!engine.input.quit)
    {
        engine_read_input(&engine);

        engine_render(&engine);
    }

    characters_destroy(&chars);

    engine_destroy(&engine);

    SDL_Quit();
    return 0;
}
