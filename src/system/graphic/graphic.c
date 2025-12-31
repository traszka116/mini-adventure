#include <SDL3/SDL.h>
#include "system/graphic.h"
#include "utils/safe.h"
#include "utils/array.h"

DYN_ARRAY_IMPL(gcmd_list, graphic_cmd_t);

graphic_t graphic_create(char *name, int w, int h)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    ASSERT(SDL_CreateWindowAndRenderer(name, w, h,
                                       SDL_WINDOW_RESIZABLE,
                                       &window, &renderer));

    ASSERT(SDL_SetRenderLogicalPresentation(
        renderer,
        w,
        h,
        SDL_LOGICAL_PRESENTATION_LETTERBOX));


    texture_manager_t man = texture_manager_create(10, renderer);

    gcmd_list_t *commands = gcmd_list_create(64);
    ASSERT(commands);

    return (graphic_t){
        .window = window,
        .renderer = renderer,
        .texture_manager = man,
        .commands = commands,
        .w = w,
        .h = h,
    };
}

void graphic_destroy(graphic_t *graphic)
{
    texture_manager_destroy(&graphic->texture_manager);

    SDL_DestroyRenderer(graphic->renderer);
    SDL_DestroyWindow(graphic->window);

    graphic->renderer = NULL;
    graphic->window = NULL;
}

void graphic_add_command(graphic_t *graphic, graphic_cmd_t command)
{
    // get window size
    int w = graphic->w,
        h = graphic->h;

    // omit all draw requests fully out of
    switch (command.cmd)
    {
    case GCMD_RECT:
    case GCMD_TEXTURE:
    case GCMD_ATLAS:
        SDL_FRect rect;
        if (command.cmd == GCMD_RECT)
        {
            rect = command.rect.rect;
        }
        else if (command.cmd == GCMD_TEXTURE)
        {
            rect = command.texture.dst;
        }
        else if (command.cmd == GCMD_ATLAS)
        {
            rect = command.atlas.dst;
        }
        float xl = rect.x, xh = rect.x + rect.w;
        float yl = rect.y, yh = rect.y + rect.h;
        if ((xl < 0 && xh < 0) ||
            (xl > w && xh > w) ||
            (yl < 0 && yh < 0) ||
            (yl > h && yh > h))
        {
            return;
        }
    default:
        // fallthrough
    }
    ASSERT(gcmd_list_push(&graphic->commands, command));
}

// dispatch helper function
static inline void graphic_run(graphic_t *graphic, graphic_cmd_t *command)
{
    switch (command->cmd)
    {
    case GCMD_SET_COLOR:
    {
        gcmd_color_set_t set = command->set_color;
        SDL_SetRenderDrawColorFloat(graphic->renderer,
                                    set.r, set.g,
                                    set.b, set.a);
    }
    break;
    case GCMD_POINTS:
    {
        gcmd_points_t points = command->points;
        SDL_RenderPoints(graphic->renderer, points.points, points.count);
    }
    break;
    case GCMD_LINES:
    {
        gcmd_lines_t lines = command->lines;
        SDL_RenderLines(graphic->renderer, lines.points, lines.count);
    }
    break;
    case GCMD_RECT:
    {
        gcmd_rect_t rect = command->rect;
        SDL_RenderFillRect(graphic->renderer, &rect.rect);
    }
    break;
    case GCMD_TEXTURE:
    {
        gcmd_texture_t tex = command->texture;
        ASSERT(tex.src.x >= 0);
        ASSERT(tex.src.y >= 0);
        ASSERT(tex.src.x + tex.src.w < tex.texture->size.x);
        ASSERT(tex.src.y + tex.src.h < tex.texture->size.y);
        SDL_RenderTexture(graphic->renderer, tex.texture->tex, &tex.src, &tex.dst);
    }
    break;
    case GCMD_ATLAS:
    {
        gcmd_atlas_t atlas = command->atlas;
        float w = atlas.atlas->item_size.x,
              h = atlas.atlas->item_size.y,
              row = atlas.row,
              col = atlas.column,
              padding = atlas.atlas->padding;

        float x = col * (w + padding),
              y = row * (h + padding);

        ASSERT(x + w < atlas.atlas->texture.size.x);
        ASSERT(y + h < atlas.atlas->texture.size.y);

        SDL_FRect src = {
            .w = w,
            .h = h,
            .x = col * (w + padding),
            .y = row * (h + padding),
        };
        SDL_RenderTexture(graphic->renderer, atlas.atlas->texture.tex, &src, &atlas.dst);
    }
    break;
    case GCMD_BLEND_MOD:
    {
        gcmd_mod_blend_t mod = command->mod_blend;
        SDL_SetTextureBlendMode(mod.texture->tex, mod.mode);
    }
    break;
    case GCMD_ALPHA_MOD:
    {
        gcmd_mod_alpha_t mod = command->mod_alpha;
        SDL_SetTextureAlphaModFloat(mod.texture->tex, mod.alpha);
    }
    break;
    case GCMD_COLOR_MOD:
    {
        gcmd_mod_color_t mod = command->mod_color;
        SDL_SetTextureColorModFloat(mod.texture->tex, mod.r, mod.g, mod.b);
    }
    break;
    default:
        UNREACHABLE;
    }
}

void graphic_execute(graphic_t *graphic)
{
    SDL_SetRenderDrawColorFloat(graphic->renderer, 0, 0, 0, 1);
    SDL_RenderClear(graphic->renderer);

    SDL_SetRenderDrawColorFloat(graphic->renderer, 0, .3, .8, 1);
    SDL_FRect rect = {0, 0, graphic->w, graphic->h};
    SDL_RenderFillRect(graphic->renderer, &rect);

    SDL_SetRenderDrawColorFloat(graphic->renderer, 0, 0, 0, 1);

    size_t len = graphic->commands->len;

    for (size_t i = 0; i < len; i++)
    {
        graphic_run(graphic, gcmd_list_at(graphic->commands, i));
    }

    graphic->commands->len = 0;

    SDL_RenderPresent(graphic->renderer);
}