#include "main.h"

#include "decomp.h"
#include "error.h"
#include "globals.h"
#include "initmain.h"
#include "nheapall.h"
#include "p0macros.h"
#include "timing.h"
#include "zz_unknown.h"

#include <signal.h>
#include <stdio.h>

// GLOBAL: MSVC5_C1 0x00000000
// ?FrontendBssStart@@3HA
// int FrontendBssStart

// GLOBAL: MSVC5_C1 0x00000000
// ?FrontendDataStart@@3HA
// int FrontendDataStart

// GLOBAL: MSVC5_C1 0x00000000
// ?InitFuncStart@@3P6AXXZA
// void (__cdecl *InitFuncStart)(void)

// GLOBAL: MSVC5_C1 0x00000088
// ?InitFuncEnd@@3P6AXXZA
// void (__cdecl *InitFuncEnd)(void)

// GLOBAL: MSVC5_C1 0x00000150
// ??_7FileTokenStream@@6B@
// const FileTokenStream::`vftable'

// GLOBAL: MSVC5_C1 0x00001510
// ?HandlingControlC@@3HA
// GLOBAL: C1 0x0045c6cc
bool32 HandlingControlC = 0;

#ifdef _WIN32
// GLOBAL: MSVC5_C1 0x00001518
// ?systemInfo@@3U_SYSTEM_INFO@@A
// GLOBAL: C1 0x0045c6d8
SYSTEM_INFO systemInfo;
#endif

// GLOBAL: MSVC5_C1 0x0000153c
// ?hSemaphore@@3PAXA
// void *hSemaphore

// GLOBAL: MSVC5_C1 0x0000199c
// ?FrontendDataEnd@@3HA
// int FrontendDataEnd

// GLOBAL: MSVC5_C1 0x00004cd0
// ??_C@_03OOGB@wt?$CL?$AA@
// "wt+"

// GLOBAL: MSVC5_C1 0x00004cd4
// ??_C@_02IHFD@db?$AA@
// "db"

// GLOBAL: MSVC5_C1 0x00004cd8
// ??_C@_02BHGG@gl?$AA@
// "gl"

// GLOBAL: MSVC5_C1 0x00004cdc
// ??_C@_02IONO@sy?$AA@
// "sy"

// GLOBAL: MSVC5_C1 0x00004ce0
// ??_C@_04MPCN@?9G?$CFd?$AA@
// "-G%d"

// GLOBAL: MSVC5_C1 0x00004ce8
// ??_C@_08DMKH@?4?2main?4c?$AA@
// ".\\main.c"

// GLOBAL: MSVC5_C1 0x00004cf4
// ??_C@_01JAP@i?$AA@
// "i"

// GLOBAL: MSVC5_C1 0x00004cf8
// ??_C@_03DDHC@?9Zm?$AA@
// "-Zm"

// GLOBAL: MSVC5_C1 0x00004cfc
// ??_C@_03OMIP@?9Bm?$AA@
// "-Bm"

// GLOBAL: MSVC5_C1 0x00004d00
// ??_C@_08CLOM@msc1?4cpp?$AA@
// "msc1.cpp"

// GLOBAL: MSVC5_C1 0x00004d0c
// ??_C@_0BC@LEIG@?5Abort?5complete?4?6?$AA@
// " Abort complete.\n"

// GLOBAL: MSVC5_C1 0x00004d20
// ??_C@_0CE@ELOD@Compiler?5terminating?4?5?5Please?5wa@
// "Compiler terminating.  Please wa"...

// GLOBAL: MSVC5_C1 0x00007838
// ?pInitDataOnHeap@@3RAXA
// void *volatile pInitDataOnHeap

// GLOBAL: MSVC5_C1 0x0000783c
// ?cAtExitFuncs@@3HA
// int cAtExitFuncs

// GLOBAL: MSVC5_C1 0x00007840
// ?AtExitList@@3PAP6AXXZA
// void (__cdecl **AtExitList)(void)

// GLOBAL: MSVC5_C1 0x000078c8
// ?rgchIDBName@?4??szIDBName@@YAPADXZ@4PADA
// char *`char * __cdecl szIDBName(void)'::`5'::rgchIDBName

// GLOBAL: MSVC5_C1 0x0000a094
// ?FrontendBssEnd@@3HA
// int FrontendBssEnd

// FUNCTION: MSVC5_C1 0x00035c10
// _DllMain@12

// FUNCTION: MSVC5_C1 0x00035c40
// ?init_main2@@YAXXZ
// void __cdecl init_main2(void)

// FUNCTION: MSVC5_C1 0x000363f0
// ?init_main3@@YAXXZ
// void __cdecl init_main3(void)

// FUNCTION: MSVC5_C1 0x00036920
// ?inspectArgument@preParseArgsHelpers@@CAHPADH@Z
// private: static int __cdecl preParseArgsHelpers::inspectArgument(char *, int)

// FUNCTION: MSVC5_C1 0x00036a00
// ?gatherOneCommandLineNugget@preParseArgsHelpers@@CAPADPAD0I@Z
// private: static char * __cdecl preParseArgsHelpers::gatherOneCommandLineNugget(char *, char *, unsigned int)

// FUNCTION: MSVC5_C1 0x00036ac0
// ?PreParseArgs@@YAXPAPAD@Z
// FUNCTION: C1 0x00419862
void PreParseArgs(char **args)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00036b60
// ?CallMain@@YAHHPAPAD@Z
// int __cdecl CallMain(int, char **)
// C1: FUNCTION 0x004197a4
int main(int argc, char *argv[])
{
    ExecutionState = CES_Init;
    ReserveMacroBuffers();
    InitTiming();
    atexit(FUN_0041f0b2);
    signal(SIGINT, OnTerminalSignal);
    signal(SIGTERM, OnTerminalSignal);
#ifdef _WIN32
    signal(SIGBREAK, OnTerminalSignal);
#endif
    Argc = argc;
    Argv = argv;
    PreParseArgs(argv);
    FUN_0041934f();
#ifdef _WIN32
    GetSystemInfo(&systemInfo);
#endif
    HeapManager::InitGlobalHeaps();
    init_main1(argc, argv);
    AddTiming("init1");
    if (PchS.p_Cmd_C9IL) {
        PchS.p_ParseFlags.field_0x8_bit13 = 1;
    } else {
        PchS.p_ParseFlags.field_0x8_bit13 = 0;
    }
    if (PchC.p_option_Bd) {
        main_compile();
    } else {
        main_compile();
    }
}

// FUNCTION: MSVC5_C1 0x00036c00
// _InvokeCompilerPass@12

// FUNCTION: MSVC5_C1 0x00036ca0
// ?CheckException@@YAHPAU_EXCEPTION_POINTERS@@@Z
// int __cdecl CheckException(struct _EXCEPTION_POINTERS *)

// FUNCTION: MSVC5_C1 0x00036cc0
// ?Trap_main_compile@@YAHXZ
// int __cdecl Trap_main_compile(void)

// FUNCTION: MSVC5_C1 0x00036d60
// ?OutputNV@@YAXXZ
// void __cdecl OutputNV(void)

// FUNCTION: MSVC5_C1 0x00036df0
// ?main_compile@@YAHXZ
// FUNCTION: C1 0x004193d6
int main_compile()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00037270
// ?GetCurrentPath@@YAPADXZ
// char * __cdecl GetCurrentPath(void)

// FUNCTION: MSVC5_C1 0x000372c0
// ?pszOSFileName@@YAPAEPAE@Z
// unsigned char * __cdecl pszOSFileName(unsigned char *)

// FUNCTION: MSVC5_C1 0x00037360
// ?OpenFileName@@YAHPAE@Z
// int __cdecl OpenFileName(unsigned char *)

// FUNCTION: MSVC5_C1 0x000373c0
// ?CleanupMemory@@YAXXZ
// void __cdecl CleanupMemory(void)

// FUNCTION: MSVC5_C1 0x000373e0
// ?ErrorCleanup@@YAXXZ
// void __cdecl ErrorCleanup(void)

// FUNCTION: MSVC5_C1 0x00037430
// ?ErrorCleanupGuard@@YAXW4CompilerExecutionState_t@@@Z
// void __cdecl ErrorCleanupGuard(enum CompilerExecutionState_t)

// FUNCTION: MSVC5_C1 0x00037460
// ?ExitPass@@YAXHH@Z
// void __cdecl ExitPass(int, int)

// FUNCTION: MSVC5_C1 0x00037480
// ?OKToHandleCtrlC@@YAXXZ
// void __cdecl OKToHandleCtrlC(void)

// FUNCTION: C1 0x00445a9b
void __fastcall limit_recursion(CompilerExecutionState_t state)
{
    // GLOBAL: C1 0x00468c18
    static int depth;

    if (depth++ > 0) {
        GaspAndDie(1);
    }
    ExecutionState = state;
}

// FUNCTION: C1 0x00445a14
void ReleaseEverythingUponError()
{
    NOT_IMPLEMENTED();

}


// FUNCTION: MSVC5_C1 0x000374d0
// _AbortCompilerPass@4

// FUNCTION: MSVC5_C1 0x000375a0
// _OurAtExit

// FUNCTION: MSVC5_C1 0x000375e0
// ?DoStartupInits@@YAHXZ
// int __cdecl DoStartupInits(void)

// FUNCTION: MSVC5_C1 0x00037710
// ?DoAtExitFuncs@@YAHXZ
// int __cdecl DoAtExitFuncs(void)

// FUNCTION: MSVC5_C1 0x00037790
// ?to_human@@YAXXZ
// void __cdecl to_human(void)

// FUNCTION: MSVC5_C1 0x00037930
// _GetPrecisionFlag

// FUNCTION: MSVC5_C1 0x00037940
// ?pushToken@FileTokenStream@@UAEXPBVToken@@@Z
// public: virtual void __thiscall FileTokenStream::pushToken(class Token const *)

// FUNCTION: MSVC5_C1 0x00037960
// ?saveToken@FileTokenStream@@UAEXPBVToken@@@Z
// public: virtual void __thiscall FileTokenStream::saveToken(class Token const *)

// FUNCTION: MSVC5_C1 0x00037970
// ?rewind@FileTokenStream@@UAEXXZ
// public: virtual void __thiscall FileTokenStream::rewind(void)

// FUNCTION: MSVC5_C1 0x00037980
// ?IsFileStream@FileTokenStream@@UBEHXZ
// public: virtual int __thiscall FileTokenStream::IsFileStream(void) const

// FUNCTION: MSVC5_C1 0x00037990
// ??_GFileTokenStream@@EAEPAXI@Z
// private: virtual void * __thiscall FileTokenStream::`scalar deleting dtor'(unsigned int)

// FUNCTION: MSVC5_C1 0x00037990
// ??_EFileTokenStream@@EAEPAXI@Z
// private: virtual void * __thiscall FileTokenStream::`vector deleting dtor'(unsigned int)

// FUNCTION: MSVC5_C1 0x000379b0
// ?getToken@FileTokenStream@@UAEPBVToken@@XZ
// public: virtual class Token const * __thiscall FileTokenStream::getToken(void)

// FUNCTION: MSVC5_C1 0x000379d0
// ?peekToken@FileTokenStream@@UAEPBVToken@@XZ
// public: virtual class Token const * __thiscall FileTokenStream::peekToken(void)
