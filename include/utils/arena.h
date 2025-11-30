#ifndef ARENA_H
#define ARENA_H
#include <stdint.h>
#include <stddef.h>

typedef struct arena
{
    size_t total, allocated;
    uint8_t memory[];
} arena_t;

/** @brief allocates memory for memory arena, if not possible to allocate memory return NULL */
arena_t *arena_create(size_t);
/** @brief removes memory arena */
void arena_destroy(arena_t *);
/** @brief allocates memory for given object size, if not possible return NULL */
void *arena_alloc(arena_t *, size_t);
/** @brief resets memory arena, invalidates all previously allocated objects */
void arena_reset(arena_t *);

#endif