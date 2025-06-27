#pragma once

#include <windows.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MREngine MREngine;
typedef struct MREDriver MREDriver;
typedef struct SRCTARG SRCTARG;

typedef struct SRCTARG {
    SRCTARG *psrctargNext;
    BOOL fCpp;
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

BOOL __stdcall MREFOpenByName(
        MREngine **engine, char *pdbPath, int *code, char *actualPdbPathOut, BOOL repro, BOOL write);
void __stdcall MREQueryMreDrv(MREngine *engine, MREDriver **driver);
BOOL __stdcall MREDrvOneTimeInit(MREDriver *driver);
BOOL __stdcall MREDrvFRelease(MREDriver *driver);
BOOL __stdcall MREFClose(MREngine *engine, BOOL arg2);
BOOL __stdcall MREDrvFFilesOutOfDate(MREDriver *driver, CAList *state);
unsigned int __cdecl SigForPbCb(const void *data, size_t size, unsigned int hash);

#ifdef __cplusplus
}
#endif
