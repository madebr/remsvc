#pragma once

#include "decomp.h"

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MREngine MREngine;
typedef struct MREDriver MREDriver;
typedef struct SRCTARG SRCTARG;

typedef struct SRCTARG {
    SRCTARG *psrctargNext;
    bool32 fCpp;
    char *szSrc;
    char *szTarg;
    char *szOptions;
    unsigned int dwWeightMaybe;
} SRCTARG;

typedef struct CAList {
    SRCTARG *pstDoCompile;
    SRCTARG *pstMaybeCompile;
    SRCTARG *pstDontCompile;
    SRCTARG *pstDone;
    SRCTARG *pstError;
} CAList;

bool32 __stdcall MREFOpenByName(
        MREngine **engine, char *pdbPath, int *code, char *actualPdbPathOut, bool32 repro, bool32 write);
void __stdcall MREQueryMreDrv(MREngine *engine, MREDriver **driver);
bool32 __stdcall MREDrvOneTimeInit(MREDriver *driver);
bool32 __stdcall MREDrvFRelease(MREDriver *driver);
bool32 __stdcall MREFClose(MREngine *engine, bool32 arg2);
bool32 __stdcall MREDrvFFilesOutOfDate(MREDriver *driver, CAList *state);
uint32_t __cdecl SigForPbCb(const void *data, size_t size, uint32_t hash);

#ifdef __cplusplus
}
#endif
