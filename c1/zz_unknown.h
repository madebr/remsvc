#ifndef ZZ_UNKNOWN_H
#define ZZ_UNKNOWN_H

#include "decomp.h"

#include <stddef.h>

extern unsigned char *pMacroActEnd;

extern unsigned char *pMacroExpEnd;

// FIXME: Unknown source
extern void FUN_0041f0b2(void);

// FIXME: Unknown source
extern void OnTerminalSignal(int);

// FIXME: Unknown source
extern void FUN_0041934f();

// FIXME: Unknown source
extern void __fastcall WriteStdErr(const char *text);

extern unsigned char * __fastcall PreAllocateMemory(size_t reserveSize, size_t commitSize);

extern void CleanupMemory();

#endif /* ZZ_UNKNOWN_H */
