#ifndef SAFE_H
#define SAFE_H
#include <stdbool.h>

void _panic(char *msg);

void _warning(char *msg);

void _assert(bool expr, char *str, char *file, int line);

#define PANIC(MSG)   \
    do               \
    {                \
        _panic(MSG); \
    } while (0)

#define WARN(MSG)      \
    do                 \
    {                  \
        _warning(MSG); \
    } while (0)

#define ASSERT(EXPR)                                \
    do                                              \
    {                                               \
        _assert((EXPR), #EXPR, __FILE__, __LINE__); \
    } while (0)

#define UNREACHABLE                      \
    do                                   \
    {                                    \
        _panic("Reached unreachable\n"); \
    } while (0)

#endif
