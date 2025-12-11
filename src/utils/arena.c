#include "arena.h"

#include <stdlib.h>
#include <string.h>

arena_t *arena_create(size_t size)
{
    arena_t *arena = malloc(sizeof(struct arena) + size);
    if (!arena)
    {
        return NULL;
    }

#ifdef DDEBUG
    // in debug mode set allocated bytes to 0xFE
    memset(arena->memory, 0xFE, arena->total);
#endif

    arena->total = size;
    arena->allocated = 0;
    return arena;
}

void arena_destroy(arena_t *arena)
{
    free(arena);
}

void *arena_alloc(arena_t *arena, size_t size)
{
    const size_t alignment = 8;
    const size_t padding = (alignment - (arena->allocated % alignment)) % alignment;

    size_t total_size = size + padding;
    size_t remaining = arena->total - arena->allocated;

    if (remaining < total_size)
    {
        return NULL;
    }

    uint8_t *ptr = arena->memory + arena->allocated + padding;
    arena->allocated += total_size;
    return ptr;
}

void arena_reset(arena_t *arena)
{
    arena->allocated = 0;
#ifdef DDEBUG
    // in debug mode set allocated bytes to 0xFE
    memset(arena->memory, 0xFE, arena->total);
#endif
}