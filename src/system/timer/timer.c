#include "system/timer.h"
#include <SDL3/SDL.h>

timer_t timer_create()
{
    return (timer_t){
        .last_tick = SDL_GetTicks(),
    };
}

float timer_elapsed(timer_t *timer)
{
    Uint64 last = timer->last_tick;
    Uint64 now = SDL_GetTicks();
    timer->last_tick = now;
    return (float)(now - last) / (1000.0f);
}
