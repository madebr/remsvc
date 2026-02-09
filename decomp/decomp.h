#ifndef DECOMP_H
#define DECOMP_H

#include <stdint.h>
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

#define __cdecl
#define __fastcall
#define __stdcall

#endif

typedef unsigned int bool32;

#ifndef _WIN32
#include <stdlib.h>
#include <string.h>
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

static int _ismbblead(int c) {
    return 0;
}

static const unsigned char *_mbsstr(const unsigned char *str, const unsigned char *strSearch) {
    return (unsigned char *)strstr((const char *)str, (const char *)strSearch);
}

typedef struct {
    union {
        uint32_t dwOemId;
        struct {
            uint16_t wProcessorArchitecture;
            uint16_t wReserved;
        };
    };
    uint32_t dwPageSize;
    void *lpMinimumApplicationAddress;
    void *lpMaximumApplicationAddress;
    uintptr_t dwActiveProcessorMask;
    uint32_t dwNumberOfProcessors;
    uint32_t dwProcessorType;
    uint32_t dwAllocationGranularity;
    uint16_t wProcessorLevel;
    uint16_t wProcessorRevision;
} SYSTEM_INFO;

#endif

#define NOT_IMPLEMENTED() \
    do { \
        abort(); \
    } while (0)

#define arraysize(X) (sizeof(X) / sizeof((X)[0]))

#endif /* DECOMP_H */
