#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdlib.h>
#include "utils/safe.h"

#define DYN_ARRAY_DECL(name, type)                             \
    typedef struct name                                        \
    {                                                          \
        size_t size, len;                                      \
        type values[];                                         \
    } name##_t;                                                \
                                                               \
    name##_t *name##_create(size_t size);                      \
    void name##_destroy(name##_t *array);                      \
    type name##_get(name##_t *array, size_t idx);              \
    type *name##_at(name##_t *array, size_t idx);              \
    void name##_set(name##_t *array, size_t idx, type val);    \
    type name##_pop(name##_t *array);                          \
    void name##_push_no_resize(name##_t *array, type val);     \
    name##_t *name##_resize(name##_t *array, size_t new_size); \
    int name##_push(name##_t **array, type val);               \
    type name##_remove(name##_t **array, size_t idx);

#define DYN_ARRAY_IMPL(name, type)                                                        \
    name##_t *name##_create(size_t size)                                                  \
    {                                                                                     \
        name##_t *array = malloc(sizeof(name##_t) + sizeof(type) * size);                 \
        if (!array)                                                                       \
            return NULL;                                                                  \
        array->size = size;                                                               \
        array->len = 0;                                                                   \
        return array;                                                                     \
    }                                                                                     \
                                                                                          \
    void name##_destroy(name##_t *array)                                                  \
    {                                                                                     \
        if (!array)                                                                       \
            return;                                                                       \
        free(array);                                                                      \
    }                                                                                     \
                                                                                          \
    type name##_get(name##_t *array, size_t idx)                                          \
    {                                                                                     \
        if (idx >= array->size)                                                           \
            _panic("out of bounds array access");                                         \
        if (idx >= array->len)                                                            \
            _warning("reading undefined item");                                           \
        return array->values[idx];                                                        \
    }                                                                                     \
                                                                                          \
    type *name##_at(name##_t *array, size_t idx)                                          \
    {                                                                                     \
        if (idx >= array->size)                                                           \
            _panic("out of bounds array access");                                         \
        return &array->values[idx];                                                       \
    }                                                                                     \
                                                                                          \
    void name##_set(name##_t *array, size_t idx, type val)                                \
    {                                                                                     \
        if (idx >= array->size)                                                           \
            _panic("out of bounds array access");                                         \
        array->values[idx] = val;                                                         \
    }                                                                                     \
                                                                                          \
    type name##_pop(name##_t *array)                                                      \
    {                                                                                     \
        if (array->len == 0)                                                              \
            _panic("poping empty array");                                                 \
        type val = array->values[array->len];                                             \
        array->len--;                                                                     \
        return val;                                                                       \
    }                                                                                     \
                                                                                          \
    void name##_push_no_resize(name##_t *array, type val)                                 \
    {                                                                                     \
        if (array->len >= array->size)                                                    \
            _panic("pushing to full array");                                              \
        array->values[array->len] = val;                                                  \
        array->len++;                                                                     \
    }                                                                                     \
                                                                                          \
    name##_t *name##_resize(name##_t *array, size_t new_size)                             \
    {                                                                                     \
        name##_t *new_array = realloc(array, sizeof(name##_t) + sizeof(type) * new_size); \
        if (!new_array)                                                                   \
            return NULL;                                                                  \
        new_array->size = new_size;                                                       \
        if (new_array->len > new_size)                                                    \
            new_array->len = new_size;                                                    \
        return new_array;                                                                 \
    }                                                                                     \
                                                                                          \
    int name##_push(name##_t **array, type val)                                           \
    {                                                                                     \
        if ((*array)->len >= (*array)->size)                                              \
        {                                                                                 \
            size_t new_size = (*array)->size * 2;                                         \
            if (new_size == 0)                                                            \
                new_size = 1;                                                             \
            name##_t *new_array = name##_resize(*array, new_size);                        \
            if (!new_array)                                                               \
                return 0;                                                                 \
            *array = new_array;                                                           \
        }                                                                                 \
        name##_push_no_resize(*array, val);                                               \
        return 1;                                                                         \
    }                                                                                     \
                                                                                          \
    type name##_remove(name##_t **array, size_t idx)                                      \
    {                                                                                     \
        type val = name##_pop(*array);                                                    \
        name##_set(*array, idx, val);                                                     \
        return val;                                                                       \
    }

#endif