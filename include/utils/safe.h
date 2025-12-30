#ifndef SAFE_H
#define SAFE_H
#include <stdbool.h>
#include <stdio.h>

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

#define MARK                                       \
    do                                             \
    {                                              \
        printf("file: %s:%d", __FILE__, __LINE__); \
        fflush(stdout);                            \
    } while (0)

#define LOG(msg)        \
    do                  \
    {                   \
        MARK;           \
        puts(msg);      \
        fflush(stdout); \
    } while (0)

#define LOG_F(format, args...)                     \
    do                                             \
    {                                              \
        printf("file: %s:%d", __FILE__, __LINE__); \
        printf(format, args);                      \
        fflush(stdout);                            \
    } while (0)

#endif
