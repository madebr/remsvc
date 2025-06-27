#pragma once

#include "decomp.h"

#include <stdint.h>
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void FUN_0041c815();

extern BOOL __fastcall OpenPrecompiledHeader(const char *path);

void WriteMacrosAndIncludesToPCH();

#ifdef __cplusplus
};
#endif
