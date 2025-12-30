#include "system/input.h"
#include <stdbool.h>
#include "utils/lmath.h"

bool is_button_down(input_t const *input, button_t button)
{
    bool now = false;
    switch (button)
    {
    case BUTTON_LEFT:
        now = input->curr_left;
        break;
    case BUTTON_MIDDLE:
        now = input->curr_middle;
        break;
    case BUTTON_RIGHT:
        now = input->curr_right;
        break;
    }
    return now;
}

bool is_button_pressed(input_t const *input, button_t button)
{
    bool now = false, prev = false;
    switch (button)
    {
    case BUTTON_LEFT:
        now = input->curr_left;
        prev = input->prev_left;
        break;
    case BUTTON_MIDDLE:
        now = input->curr_middle;
        prev = input->prev_middle;
        break;
    case BUTTON_RIGHT:
        now = input->curr_right;
        prev = input->prev_right;
        break;
    }
    return !prev && now;
}

bool is_button_released(input_t const *input, button_t button)
{
    bool now = false, prev = false;
    switch (button)
    {
    case BUTTON_LEFT:
        now = input->curr_left;
        prev = input->prev_left;
        break;
    case BUTTON_MIDDLE:
        now = input->curr_middle;
        prev = input->prev_middle;
        break;
    case BUTTON_RIGHT:
        now = input->curr_right;
        prev = input->prev_right;
        break;
    }
    return prev && !now;
}

vec2_t mouse_position(input_t const *input)
{
    vec2_t result = {
        .x = input->curr_x,
        .y = input->curr_y,
    };
    return result;
}

vec2_t mouse_movement(input_t const *input)
{
    vec2_t result = {
        .x = input->curr_x - input->prev_x,
        .y = input->curr_y - input->prev_y,
    };
    return result;
}