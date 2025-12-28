#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <SDL3/SDL.h>

#include <iso646.h>
#include "utils/debug.h"
#include "utils/safe.h"
#include "io/graphics.h"
#include "io/input.h"
#include "core/engine.h"
#include "game/character.h"
#include "game/game.h"
#include "io/texture.h"
#include "game/player.h"

const int width = 800,
          height = 600;

int main(void)
{
    ASSERT(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO));

    game_t game = {
        .camera = {
            .position = {0, 0},
            .size = {width, height},
        },
        .characters = character_list_create(10),
    };

    character_t character =
        create_character((vec2_t){0, 0}, 10, 5, 4);

    player_t player = {.character_id = character.id};

    character_list_push_no_resize(game.characters, character);

    engine_t engine = engine_create("game", width, height, "textures/atlas.png");

    while (!engine.input.quit)
    {
        engine_read_input(&engine);

        game_update(&game, &engine.input, engine.delta_time);
        game_draw(&game, &(engine.commands));

        engine_render(&engine);
        engine_time_tick(&engine);
    }

    engine_destroy(&engine);

    SDL_Quit();

    return 0;
}
