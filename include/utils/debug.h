#include <stdio.h>

#ifndef DEBUG_H
#define DEBUG_H

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