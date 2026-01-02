#ifndef TIMER_H
#define TIMER_H
#include <SDL3/SDL.h>

typedef struct
{
    Uint64 last_tick;
} tick_t;


tick_t tick_create();
float tick_elapsed(tick_t *);

#endif