#include <stdio.h>
#include <stdlib.h>

#ifndef SAFE_H
#define SAFE_H

void _panic(char *msg)
{
#ifdef DDEBUG
    fprintf(stderr, "Panic: %s", msg);
    exit(-1);
#endif
}

void _warning(char *msg)
{
#ifdef DDEBUG
    fprintf(stderr, "Warning: %s", msg);
#endif
}

void _assert(bool expr, char *str)
{
#ifdef DDEBUG
    fprintf(stderr, "Assertion: %s", msg);
    exit(-1);
#endif
}

#define PANIC(MSG) panic(MSG)
#define WARN(MSG) warning(MSG)
#define ASSERT(EXPR) _assert((EXPR), #EXPR)
#endif