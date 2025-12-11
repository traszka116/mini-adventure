#ifndef INPUT_H
#define INPUT_H
#include <SDL3/SDL.h>

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

#endif