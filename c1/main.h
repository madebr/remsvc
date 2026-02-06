#ifndef MAIN_H
#define MAIN_H

#include "c1_types.h"
#include "decomp.h"

#ifdef _WIN32
#include <windows.h>
#endif

// ?FrontendBssStart@@3HA
// int FrontendBssStart

// ?FrontendDataStart@@3HA
// int FrontendDataStart

// ?InitFuncStart@@3P6AXXZA
// void (__cdecl *InitFuncStart)(void)

// ?InitFuncEnd@@3P6AXXZA
// void (__cdecl *InitFuncEnd)(void)

// ??_7FileTokenStream@@6B@
// const FileTokenStream::`vftable'

// ?HandlingControlC@@3HA
extern bool32 HandlingControlC;

// ?systemInfo@@3U_SYSTEM_INFO@@A
extern SYSTEM_INFO systemInfo;

// ?hSemaphore@@3PAXA
// void *hSemaphore

// ?FrontendDataEnd@@3HA
// int FrontendDataEnd

// ??_C@_03OOGB@wt?$CL?$AA@
// "wt+"

// ??_C@_02IHFD@db?$AA@
// "db"

// ??_C@_02BHGG@gl?$AA@
// "gl"

// ??_C@_02IONO@sy?$AA@
// "sy"

// ??_C@_04MPCN@?9G?$CFd?$AA@
// "-G%d"

// ??_C@_08DMKH@?4?2main?4c?$AA@
// ".\\main.c"

// ??_C@_01JAP@i?$AA@
// "i"

// ??_C@_03DDHC@?9Zm?$AA@
// "-Zm"

// ??_C@_03OMIP@?9Bm?$AA@
// "-Bm"

// ??_C@_08CLOM@msc1?4cpp?$AA@
// "msc1.cpp"

// ??_C@_0BC@LEIG@?5Abort?5complete?4?6?$AA@
// " Abort complete.\n"

// ??_C@_0CE@ELOD@Compiler?5terminating?4?5?5Please?5wa@
// "Compiler terminating.  Please wa"...

// ?pInitDataOnHeap@@3RAXA
// void *volatile pInitDataOnHeap

// ?cAtExitFuncs@@3HA
// int cAtExitFuncs

// ?AtExitList@@3PAP6AXXZA
// void (__cdecl **AtExitList)(void)

// ?rgchIDBName@?4??szIDBName@@YAPADXZ@4PADA
// char *`char * __cdecl szIDBName(void)'::`5'::rgchIDBName

// ?FrontendBssEnd@@3HA
// int FrontendBssEnd

// _DllMain@12

// ?init_main2@@YAXXZ
// void __cdecl init_main2(void)

// ?init_main3@@YAXXZ
// void __cdecl init_main3(void)

// ?inspectArgument@preParseArgsHelpers@@CAHPADH@Z
// private: static int __cdecl preParseArgsHelpers::inspectArgument(char *, int)

// ?gatherOneCommandLineNugget@preParseArgsHelpers@@CAPADPAD0I@Z
// private: static char * __cdecl preParseArgsHelpers::gatherOneCommandLineNugget(char *, char *, unsigned int)
extern int __fastcall gatherOneCommandLineNugget(char *arg, unsigned int state);

// ?PreParseArgs@@YAXPAPAD@Z
extern void PreParseArgs(char **argv);

// ?CallMain@@YAHHPAPAD@Z
// int __cdecl CallMain(int, char **)

// _InvokeCompilerPass@12

// ?CheckException@@YAHPAU_EXCEPTION_POINTERS@@@Z
// int __cdecl CheckException(struct _EXCEPTION_POINTERS *)

// ?Trap_main_compile@@YAHXZ
// int __cdecl Trap_main_compile(void)

// ?OutputNV@@YAXXZ
// void __cdecl OutputNV(void)

// ?main_compile@@YAHXZ
extern int main_compile();

// ?GetCurrentPath@@YAPADXZ
// char * __cdecl GetCurrentPath(void)

// ?pszOSFileName@@YAPAEPAE@Z
// unsigned char * __cdecl pszOSFileName(unsigned char *)

// ?OpenFileName@@YAHPAE@Z
// int __cdecl OpenFileName(unsigned char *)

// ?CleanupMemory@@YAXXZ
// void __cdecl CleanupMemory(void)

// ?ErrorCleanup@@YAXXZ
// void __cdecl ErrorCleanup(void)

// ?ErrorCleanupGuard@@YAXW4CompilerExecutionState_t@@@Z
// void __cdecl ErrorCleanupGuard(enum CompilerExecutionState_t)

// ?ExitPass@@YAXHH@Z
// void __cdecl ExitPass(int, int)

// ?OKToHandleCtrlC@@YAXXZ
// void __cdecl OKToHandleCtrlC(void)

extern void __fastcall limit_recursion(CompilerExecutionState_t state);

extern void ReleaseEverythingUponError();

// _AbortCompilerPass@4

// _OurAtExit

// ?DoStartupInits@@YAHXZ
// int __cdecl DoStartupInits(void)

// ?DoAtExitFuncs@@YAHXZ
// int __cdecl DoAtExitFuncs(void)

// ?to_human@@YAXXZ
// void __cdecl to_human(void)

// _GetPrecisionFlag

// ?pushToken@FileTokenStream@@UAEXPBVToken@@@Z
// public: virtual void __thiscall FileTokenStream::pushToken(class Token const *)

// ?saveToken@FileTokenStream@@UAEXPBVToken@@@Z
// public: virtual void __thiscall FileTokenStream::saveToken(class Token const *)

// ?rewind@FileTokenStream@@UAEXXZ
// public: virtual void __thiscall FileTokenStream::rewind(void)

// ?IsFileStream@FileTokenStream@@UBEHXZ
// public: virtual int __thiscall FileTokenStream::IsFileStream(void) const

// ??_GFileTokenStream@@EAEPAXI@Z
// private: virtual void * __thiscall FileTokenStream::`scalar deleting dtor'(unsigned int)

// ??_EFileTokenStream@@EAEPAXI@Z
// private: virtual void * __thiscall FileTokenStream::`vector deleting dtor'(unsigned int)

// ?getToken@FileTokenStream@@UAEPBVToken@@XZ
// public: virtual class Token const * __thiscall FileTokenStream::getToken(void)

// ?peekToken@FileTokenStream@@UAEPBVToken@@XZ
// public: virtual class Token const * __thiscall FileTokenStream::peekToken(void)

#endif /* MAIN_H */
