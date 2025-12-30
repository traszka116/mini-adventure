// #include "game/game.h"
// #include "io/graphics.h"
// #include "game/camera.h"
// #include "utils/debug.h"
// #include "game/materials.h"
// #include "game/player.h"

// void game_draw(game_t *game, command_list_t **commands)
// {
//     static const command_t present = {
//         .present = {
//             .cmd = Graphic_PRESENT,
//         },
//     };

//     static const command_t clear = {
//         .clear = {
//             .cmd = Graphic_CLEAR,
//         },
//     };

//     static const command_t reset_color = {
//         .set_color = {
//             .cmd = Graphic_SET_COLOR,
//             .r = .0,
//             .g = .0,
//             .b = .0,
//             .a = 1.0,
//         },
//     };

//     command_list_push(commands, reset_color);
//     command_list_push(commands, clear);

    

//     for (size_t i = 0; i < game->characters->len; i++)
//     {
        
//     }

//     command_list_push(commands, present);
// }

// void game_update(game_t *game, input_t *input, float dt)
// {
//     character_t *player_char = character_list_at(game->characters, 0);
//     player_update(player_char, input, dt);

//     size_t char_count = game->characters->len;
//     for (size_t i = 0; i < char_count; i++)
//     {
//         character_t *character = character_list_at(game->characters, i);
//         character_move(character, dt, GRASS);
//     }
// }