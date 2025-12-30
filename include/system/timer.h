#ifndef TIMER_H
#define TIMER_H
#include <SDL3/SDL.h>

typedef struct
{
    Uint64 last_tick;
} timer_t;

timer_t timer_create();
float timer_elapsed(timer_t *);

#endif