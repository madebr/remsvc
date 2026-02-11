#ifndef TIMING_H
#define TIMING_H

#include "decomp.h"

typedef struct tTiming {
    const char *description;
    unsigned int tick;
} tTiming;

extern bool32 Cmd_Times;

extern int gCountTimings;

extern unsigned int gPrevTickCount;

extern tTiming gTimings[20];

extern void __fastcall AddTiming(const char *description);

extern void InitTiming(void);

extern void PrintTimings();

#endif /* TIMING_H */
