#ifndef DECOMP_H
#define DECOMP_H

#include <stdlib.h>

#ifdef _WIN32
typedef unsigned char undefined;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned __int64 undefined8;
#else
#include <stdint.h>

typedef uint8_t undefined;
typedef uint16_t undefined2;
typedef uint32_t undefined4;
typedef uint64_t undefined8;

#define __fastcall

#endif

typedef unsigned int bool32;

#ifndef _WIN32
#include <stdlib.h>
#include <time.h>

#define FALSE 0
#define TRUE 1

static inline unsigned int GetTickCount()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return(unsigned int)(ts.tv_nsec / 1000000ULL + 1000 * ts.tv_sec);
}

static void inline ExitProcess(int code)
{
    exit(code);
}
#endif

#define NOT_IMPLEMENTED() \
    do { \
        abort(); \
    } while (0)

#define arraysize(X) (sizeof(X) / sizeof((X)[0]))

#endif /* DECOMP_H */
