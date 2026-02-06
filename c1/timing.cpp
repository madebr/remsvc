#include "timing.h"

#include "decomp.h"

#ifdef _WIN32
#include <windows.h>
#endif

// GLOBAL: C1 0x00468c20
int gTiming_index = 0;

// GLOBAL: C1 0x00468c1c
unsigned int gPrevTickCount = 0;

// GLOBAL: C1 0x00468c30
tTiming gTimings[20];

// FUNCTION: C1 0x00408275
void __fastcall AddTiming(const char *description)
{
    unsigned int tick;
    tick = GetTickCount();
    gTimings[gTiming_index].description = description;
    gTimings[gTiming_index].tick = tick - gPrevTickCount;
    int next_count = gTiming_index + 1;
    if (next_count >= arraysize(gTimings)) {
        next_count = 0;
    }
    gPrevTickCount = tick;
}

// FUNCTION: C1 0x00419396
void InitTiming(void)
{
    gTiming_index = 0;
    gPrevTickCount = GetTickCount();
}
