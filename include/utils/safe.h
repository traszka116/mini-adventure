#ifndef SAFE_H
#define SAFE_H
#include <stdbool.h>
#include <stdio.h>

static inline void _panic(const char *message, const char *file, int line) {
    fprintf(stderr, "\n=== PANIC ===\n");
    fprintf(stderr, "File: %s\n", file);
    fprintf(stderr, "Line: %d\n", line);
    fprintf(stderr, "Message: %s\n", message);
    fflush(stderr);
    exit(EXIT_FAILURE);
}

static inline void _panic_fmt(const char* file, int line, 
                             const char* fmt, va_list args) {
    fprintf(stderr, "\n[FATAL] %s:%d: ", file, line);
    
    if (fmt) {
        vfprintf(stderr, fmt, args);
    }
    
    fprintf(stderr, "\n");
    fflush(stderr);
    exit(EXIT_FAILURE);
}

#define REQUIRE_F(expr, fmt, ...) \
    do { \
        if (!(expr)) { \
            va_list args; \
            va_start(args, fmt); \
            _panic_fmt(__FILE__, __LINE__, fmt, args); \
            va_end(args); \
        } \
    } while (0)

#define REQUIRE(expr) \
    REQUIRE_F(expr, "Requirement failed: %s", #expr)


#define ASSERT(EXPR)                                    \
    do                                                  \
    {                                                   \
        if (!EXPR)                                      \
            _panic(#EXPR, __FILE__, __LINE__); \
    } while (0)

#define UNREACHABLE                      \
    do                                   \
    {                                    \
        _panic("Reached unreachable\n", __FILE__, __LINE__); \
    } while (0)

#define MARK                                       \
    do                                             \
    {                                              \
        printf("file: %s:%d", __FILE__, __LINE__); \
        fflush(stdout);                            \
    } while (0)

#define LOG_F(fmt, ...) \
    do { \
        fprintf(stdout, "[LOG] %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        fflush(stdout); \
    } while (0)


#endif
