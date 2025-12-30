#ifndef INPUT_H
#define INPUT_H
#include <SDL3/SDL.h>
#include "utils/lmath.h"

typedef enum
{
    BUTTON_LEFT,
    BUTTON_MIDDLE,
    BUTTON_RIGHT
} button_t;

/// @brief type representing total input acquired from user during each frame
typedef struct
{
    const bool *keyboard_now;
    bool *keyboard_prev;
    int size;

    float curr_x, curr_y;
    float prev_x, prev_y;

    bool curr_left, curr_right, curr_middle;
    bool prev_left, prev_right, prev_middle;

    bool quit;

} input_t;

input_t input_create();
void input_destroy(input_t *input);

void input_update(input_t *input);

bool is_key_down(input_t const *, SDL_Keycode);
bool is_key_pressed(input_t const *, SDL_Keycode);
bool is_key_released(input_t const *, SDL_Keycode);

bool is_button_down(input_t const *, button_t);
bool is_button_pressed(input_t const *, button_t);
bool is_button_released(input_t const *, button_t);

vec2_t mouse_position(input_t const *);
vec2_t mouse_movement(input_t const *);

#endif