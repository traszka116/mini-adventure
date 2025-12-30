#include "system/input.h"
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <string.h>

input_t input_create()
{
    int len;
    const bool *keyboard = SDL_GetKeyboardState(&len);

    bool *prev_keyboard = malloc(len * sizeof(bool));
    memcpy(prev_keyboard, keyboard, len * sizeof(bool));

    float x, y;
    Uint32 buttons = SDL_GetMouseState(&x, &y);

    bool left = buttons & SDL_BUTTON_LMASK;
    bool right = buttons & SDL_BUTTON_RMASK;
    bool middle = buttons & SDL_BUTTON_MMASK;

    input_t result = {
        .keyboard_now = keyboard,
        .keyboard_prev = prev_keyboard,
        .size = len,

        .curr_x = x,
        .curr_y = y,
        .prev_x = x,
        .prev_y = y,

        .curr_left = left,
        .curr_middle = middle,
        .curr_right = right,

        .prev_left = left,
        .prev_middle = middle,
        .prev_right = right,

        .quit = false};

    return result;
}

void input_destroy(input_t *input)
{
    free(input->keyboard_prev);
}

void input_update(input_t *input)
{
    // save old keyboard state
    memcpy(input->keyboard_prev, input->keyboard_now, input->size * sizeof(bool));
    // save old mouse state
    input->prev_left = input->curr_left;
    input->prev_middle = input->curr_middle;
    input->prev_right = input->curr_right;
    input->prev_x = input->curr_x;
    input->prev_y = input->curr_y;

    // pull in new state
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            input->quit = true;
        }
    }

    SDL_MouseButtonFlags buttons = SDL_GetMouseState(&input->curr_x, &input->curr_y);
    bool left = buttons & SDL_BUTTON_LMASK,
         right = buttons & SDL_BUTTON_RMASK,
         middle = buttons & SDL_BUTTON_MMASK;

    input->curr_left = left;
    input->curr_right = right;
    input->curr_middle = middle;
}


