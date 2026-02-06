#ifndef TIMING_H
#define TIMING_H

#include "decomp.h"

typedef struct tTiming {
    const char *description;
    unsigned int tick;
} tTiming;

// GLOBAL: C1 0x00468c20
extern int gCountTimings;

// GLOBAL: C1 0x00468c1c
extern unsigned int gPrevTickCount;

// GLOBAL: C1 0x00468c30
extern tTiming gTimings[20];

extern void __fastcall AddTiming(const char *description);

extern void InitTiming(void);

#endif /* TIMING_H */
