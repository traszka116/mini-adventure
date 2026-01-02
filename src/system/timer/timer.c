#include "system/timer.h"
#include <SDL3/SDL.h>

tick_t tick_create()
{
    return (tick_t){
        .last_tick = SDL_GetTicks(),
    };
}

float tick_elapsed(tick_t *timer)
{
    Uint64 last = timer->last_tick;
    Uint64 now = SDL_GetTicks();
    timer->last_tick = now;
    return (float)(now - last) / (1000.0f);
}
