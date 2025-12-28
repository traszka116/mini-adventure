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

    

    SDL_Quit();

    return 0;
}
