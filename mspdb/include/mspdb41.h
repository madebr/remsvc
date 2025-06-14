#pragma once

#include <windows.h>

typedef struct MREngine MREngine;
typedef struct MREDriver MREDriver;
typedef struct MRState {
    DWORD *field_0x00;
    DWORD *field_0x04;
    DWORD field_0x08;
    DWORD field_0x0c;
    DWORD field_0x10;
} MRState;

BOOL __stdcall MREFOpenByName(
        MREngine **engine, char *pdbPath, int *code, char *actualPdbPathOut, BOOL repro, BOOL write);
void __stdcall MREQueryMreDrv(MREngine *engine, MREDriver **driver);
BOOL __stdcall MREDrvOneTimeInit(MREDriver *driver);
BOOL __stdcall MREDrvFRelease(MREDriver *driver);
BOOL __stdcall MREFClose(MREngine *engine, BOOL arg2);
BOOL __stdcall MREDrvFFilesOutOfDate(MREDriver *driver, MRState *state);
