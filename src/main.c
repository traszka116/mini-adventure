#include <iso646.h>
#include <SDL3/SDL.h>

#include "utils/debug.h"
#include "io/graphics.h"
#include "io/input.h"
#include "core/engine.h"
#include "game/character.h"

int main(void)
{
    ASSERT(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO));

    engine_t engine = engine_create();

    characters_t chars = characters_init(10);
    character_t character = {
        .position = {1, 1},
        .velocity = {0, 0},
    };
    characters_push(&chars, character);
    MARK;

    size_t count = characters_count(&chars);
    for (size_t i = 0; i < count; i++)
    {
        character_t c = characters_get(chars, i);
        LOG_F("%d) %d %d, %d %d", i, c.position.x, c.position.y, c.velocity.x, c.velocity.y);
    }

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
