#include "system/input.h"

bool is_key_down(input_t const *input, SDL_Keycode key)
{
    return input->keyboard_now[key];
}

bool is_key_pressed(input_t const *input, SDL_Keycode key)
{
    return !input->keyboard_prev[key] && input->keyboard_now[key];
}

bool is_key_released(input_t const *input, SDL_Keycode key)
{
    return input->keyboard_prev[key] && !input->keyboard_now[key];
}
