#include "utils/safe.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void _panic(char *msg)
{
#ifdef DDEBUG
    fprintf(stderr, "Panic: %s", msg);
    exit(-1);
#else
    (void)msg;
#endif
}

void _warning(char *msg)
{
#ifdef DDEBUG
    fprintf(stderr, "Warning: %s", msg);
#else
    (void)msg;
#endif
}

void _assert(bool expr, char *str, char *file, int line)
{

#ifdef DDEBUG
    fprintf(stderr, "Assertion failed: %s, at: %s:%d\n", msg, file, line);
    exit(-1);
#else
    (void)expr;
    (void)str;
    (void)file;
    (void)line;
#endif
}