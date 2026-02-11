#include "main.h"

#include "ainline.h"
#include "decomp.h"
#include "error.h"
#include "globals.h"
#include "initmain.h"
#include "intrin.h"
#include "ipm.h"
#include "nbrowser.h"
#include "nheapall.h"
#include "p0chrmap.h"
#include "p0io.h"
#include "p0gettok.h"
#include "p0id.h"
#include "p0keys.h"
#include "p0macros.h"
#include "p0pragma.h"
#include "pch.h"
#include "pragma.h"
#include "sigmgr.h"
#include "symbols.h"
#include "symtable.h"
#include "timing.h"
#include "types.h"
#include "Token_IO.h"
#include "util.h"
#include "zz_unknown.h"

#include <signal.h>
#include <stdio.h>
#ifdef _WIN32
#include <io.h>
#include <windows.h>
#endif

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

// GLOBAL: MSVC5_C1 0x00001518
// ?systemInfo@@3U_SYSTEM_INFO@@A
// GLOBAL: C1 0x0045c6d8
SYSTEM_INFO systemInfo = {
    {0},
    4096,    // dwPageSize
    NULL,    // lpMinimumApplicationAddress
    NULL,    // lpMaximumApplicationAddress
    0,       // dwActiveProcessorMask
    0,       // dwNumberOfProcessors
    0,       // dwProcessorType
    0x10000, // dwAllocationGranularity
    0,       // wProcessorLevel
    0,       // wProcessorRevision
};

// GLOBAL: MSVC5_C1 0x0000153c
// ?hSemaphore@@3PAXA
#ifdef _WIN32
// GLOBAL: C1 0x0045c6fc
HANDLE hSemaphore;
#endif

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

// FUNCTION: C1 0x00448450
FILE * OpenFileInDirectory(const char *basename, const char *suffix, const char *mode)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00035c40
// ?init_main2@@YAXXZ
// GLOBAL: C1 0x10a30c20
void init_main2()
{
    if (!FESigMgr::open(PchC.p_Cmd_fICC && !Prep && !Out_funcdef, &pSigMgr, &pIPMSigMgr)) {
        fatal_varargs(C1073, "main.c", 151);
    }
#ifdef _WIN32
    SetHandleCount(30);
#endif
    PchC.p_NoPoundLines = PchC.p_NoPoundLines || !Prep;
    if (Cmd_pack_size != -1) {
        Pragma_stack->pTopOfStack->value = Cmd_pack_size;
    } else {
        Pragma_stack->pTopOfStack->value = 8;
    }
    PchC.p_Stack_check = PchC.p_Cmd_stack_check;
    PchC.p_StrPool = PchC.p_Cmd_StrPool;
    PchC.p_ROStringPool = PchC.p_Cmd_ROStrPool;
    PchC.p_Option_Oq = PchC.p_Cmd_Option_Oq;
    if (4 < PchC.p_Cmd_processor) {
        char buffer[20];
        format(buffer, "-G%d",sizeof(buffer), PchC.p_Cmd_processor);
        fatal_varargs(C1007, buffer, "c1");
    }
    SetProcessor();
    if (Prep || Out_funcdef) {
        SourceBrowserNamFlg = NULL;
        SourceBrowserExt = NULL;
        PchC.p_SourceBrowserExtended = FALSE;
        PchC.p_SourceBrowser = FALSE;
    } else {
        if (SourceBrowserExt != NULL) {
            PchC.p_SourceBrowserExtended = TRUE;
            SourceBrowserNamFlg = SourceBrowserExt;
        }
        PchC.p_SourceBrowser = SourceBrowserNamFlg != NULL;
        SourceBrowserNam = SourceBrowserNamFlg;
    }
    SBR::Open(SourceBrowserNamFlg);
    pSbr = SBR::Disable();
    if (fPersistentPch) {
        if (PchCFile == NULL && (PchPFile == NULL || PchUFlag)) {
            fPersistentPch = FALSE;
        } else {
            if (ValidatePersistentPch(PchCFile)) {
                PchOldUFlag = PchUFlag;
                PchOldUFile = PchUFile;
                fReusePersistPch = TRUE;
                if (PchUFlag != 0) {
                    PchPFile = (char *)0x0;
                }
                PchUFlag = 1;
                PchUFile = PchCFile;
                PchCFlag = FALSE;
                PchCFile = NULL;
            } else {
                fGenPersistPch = TRUE;
                PchInitPersistentCreate();
            }
        }
    }
    PchMustCreate = PchCFlag;
    PchReuseCVTypes = PchC.p_Symbolic_debug_holder && !PchC.p_PchDFlag && PchCFlag;
    InitHardTokens();
    InitIdTable();
    InitKeywords();
    /* NOP_FUN_004193d4(); */
    if (gWrite_er && !Out_funcdef) {
        gFile_er = OpenFileInDirectory(Basename, "er", "w");
        gFile_lp = OpenFileInDirectory(Basename, "lp", "w");
    }
    if (!Prep && !Out_funcdef) {
        if (PchC.p_Cmd_C9IL) {
            OpenExpFile();
            ilsLSym.fopen(Basename, "sy", "w+");
            ilsLSym.fopen(Basename, "gl", "w+");
            ilsLSym.fopen(Basename, "in", "w+");
            if (PchC.p_Symbolic_debug_holder != 0) {
                ilsDB.fopen(Basename, "db", "w+");
            }
        } else {
            ilsLSym.SetField0x24(3);
            ilsInit.SetField0x24(4);
            ilsExp.SetField0x24(2);
            ils_UNK004609b0.SetField0x24(5);
            ilsGSym.SetField0x24(1);
            ils_UNK00465fb0.SetField0x24(1);
        }
    }
    if (StdoutFile != NULL) {
        if (dup(STDOUT_FILENO) == -1) {
            fatal_io_CRT(C1083, 340, StdoutFile);
        } else {
            I_stdoutfp = freopen(StdoutFile, "wt+", stdout);
            if (I_stdoutfp == NULL) {
                fatal_io_CRT(C1083, 340, StdoutFile);
            }
        }
    }
    I_Eoutput = stdout;
    InitTypes();
    Type_t *proto_type = HeapManager::Allocate<Type_t>(M_LIFETIME3);

    proto_type->field_0x2 = 0;
    proto_type->field_0x4 = 0;
    proto_type->field_0x8 = 0;
    proto_type->field_0x0 = 0;
    PchS.rs.p_ST_0045b67c = hash_type(proto_type);

    proto_type->field_0x0 = 0x4041;
    PchS.rs.p_ST_0045b670 = hash_type(proto_type);

    proto_type->field_0x0 = 0x63;
    PchS.rs.p_ST_BTint = hash_type(proto_type);

    proto_type->field_0x0 = 0x4063;
    PchS.rs.p_ST_0045b674 = hash_type(proto_type);

    proto_type->field_0x0 = 0x41;
    PchS.rs.p_ST_0045b634 = hash_type(proto_type);

    proto_type->field_0x0 = 0x4041;
    PchS.rs.p_ST_0045b638 = hash_type(proto_type);

    proto_type->field_0x0 = 0x42;
    PchS.rs.p_ST_0045b63c = hash_type(proto_type);

    proto_type->field_0x0 = 0x4042;
    PchS.rs.p_ST_0045b640 = hash_type(proto_type);

    proto_type->field_0x0 = 0x43;
    PchS.rs.p_ST_0045b644 = hash_type(proto_type);

    proto_type->field_0x0 = 0x4043;
    PchS.rs.p_ST_0045b648 = hash_type(proto_type);

    proto_type->field_0x0 = 0x4c;
    PchS.rs.p_ST_0045b64c = hash_type(proto_type);

    proto_type->field_0x0 = 0x404c;
    PchS.rs.p_ST_0045b650 = hash_type(proto_type);

    proto_type->field_0x0 = 0x4063;
    PchS.rs.p_ST_0045b678 = hash_type(proto_type);

    proto_type->field_0x0 = 0x42;
    PchS.rs.p_ST_0045b668 = hash_type(proto_type);

    proto_type->field_0x0 = 0x4042;
    PchS.rs.p_ST_0045b66c = hash_type(proto_type);

    proto_type->field_0x0 = 0x44;
    PchS.rs.p_ST_0045b65c = hash_type(proto_type);

    proto_type->field_0x0 = 0x4044;
    PchS.rs.p_ST_0045b660 = hash_type(proto_type);

    proto_type->field_0x0 = 0x107;
    PchS.rs.p_ST_0045b62c = hash_type(proto_type);

    proto_type->field_0x0 = 0x802;
    PchS.rs.p_ST_0045b664 = hash_type(proto_type);

    proto_type->field_0x0 = 0x80;
    PchS.rs.p_ST_0045b680 = hash_type(proto_type);

    proto_type->field_0x2 = 1;
    proto_type->field_0x0 = 0x41;
    PchS.rs.p_ST_0045b620 = hash_type(proto_type);

    proto_type->field_0x0 = 0x4041;
    PchS.rs.p_ST_0045b628 = hash_type(proto_type);

    proto_type->field_0x0 = 99;
    PchS.rs.p_ST_0045b624 = hash_type(proto_type);

    proto_type->field_0x2 = 0;

    Token::ResetTokenLife();
    PchS.rs.p_pSymbolTableManager = new SymbolTableManager_t;
    InitializeStandardIdentifiers();
    if (!Prep) {
        PchS.rs.p_ST_function = get_funcret(0, PchS.rs.p_ST_BTint);
        PchS.rs.p_ST_pVoid = PTypeForBT(0x80);
        if (!Out_funcdef) {
            dflt_intrinsic();
        }
        FUN_0041c5d3();
    }
    p0_init(listDefs);
    tokenInputStack.pushStream(new FileTokenStream, M_PUSHMODE_0x0, NULL, tokenInputStack.GetPosition());

    if (pTheBrowserStatus == NULL) {
        pTheBrowserStatus = new BrowserStatus(SourceBrowserNam, pSbr);
    }
    if (!PchUFlag) {
        init_main3();
    }
}

// FUNCTION: MSVC5_C1 0x000363f0
// ?init_main3@@YAXXZ
// FUNCTION: C1 0x004199cc
void init_main3()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00036920
// ?inspectArgument@preParseArgsHelpers@@CAHPADH@Z
// private: static int __cdecl preParseArgsHelpers::inspectArgument(char *, int)

// FUNCTION: MSVC5_C1 0x00036a00
// ?gatherOneCommandLineNugget@preParseArgsHelpers@@CAPADPAD0I@Z
// private: static char * __cdecl preParseArgsHelpers::gatherOneCommandLineNugget(char *, char *, unsigned int)
// FUNCTION: C1 0x00419928
int __fastcall gatherOneCommandLineNugget(char *arg, unsigned int state)
{
    if (arg == NULL) {
        return 0;
    }
    for (;;) {
        switch (state) {
        case 0:
            if (strncmp(arg, "-Bm", 3) == 0) {
                arg += 3;
                state = 1;
            } else if (strncmp(arg, "-ZB", 3) == 0) {
                arg += 3;
                state = 2;
            } else if (strncmp(arg, "-ZM", 3) == 0) {
                arg += 3;
                state = 3;
            }
            break;
        case 1:
            MemoryStatsLevel = atoi(arg);
            return 0;
        case 2:
            PchC.p_SizeOfBigInt = atoi(arg);
            return 0;
        case 3:
            VirtualHeap::Cmd_ScaleMemory = atoi(arg);
            if (VirtualHeap::Cmd_ScaleMemory == 0) {
                VirtualHeap::Cmd_ScaleMemory = 100;
            }
            return 0;
        }
        if (*arg == '\0') {
            return 0;
        }
        if (state == 0) {
            return 0;
        }
    }
}

// FUNCTION: MSVC5_C1 0x00036ac0
// ?PreParseArgs@@YAXPAPAD@Z
// FUNCTION: C1 0x00419862
void PreParseArgs(char **argv)
{
    int state = 0;
    char **arg = argv + 1;

    while (*arg != NULL) {
        state = gatherOneCommandLineNugget(*arg, state);
        arg++;
    }

    bool in_quotes = false;
    state = 0;
    char *envstr = getenv("MSC_CMD_FLAGS");
    if (envstr != NULL) {
        char buffer[512];
        char *ptr_write = buffer;
        while (*envstr != '\0') {
            while (*envstr == ' ') {
                envstr++;
            }
            if (*envstr == '\0') {
                break;
            }
            for (;;) {
                if (*envstr == ' ' && !in_quotes) {
                    break;
                }
                unsigned char cls1 = Charmap[*envstr];
                if (cls1 == 0) {
                    if (*envstr == '?') {
                        *ptr_write++ = *envstr;
                    } else if (envstr[1] == '"') {
                        *ptr_write++ = *envstr++;
                    } else {
                        *ptr_write++ = '\\';
                        envstr++;
                        if (*envstr != '\0' && (*envstr != ' ' || in_quotes)) {
                            *ptr_write++ = *envstr++;
                        }
                    }
                } else if (cls1 == 0x16) {
                    in_quotes = !in_quotes;  // '"'
                    envstr++;
                } else {
                    *ptr_write++ = *envstr++;
                    if (cls1 == 0x23) {
                        // ???
                        NOT_IMPLEMENTED();
                    }
                }
                if (*envstr == '\0') {
                    break;
                }
            }
            if (*envstr != '\0') {
                envstr++;
            }
            *ptr_write = '\0';
            state = gatherOneCommandLineNugget(buffer, state);
        }
    }
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
#else
    systemInfo.dwPageSize = getpagesize();
#endif
    HeapManager::InitGlobalHeaps();
    init_main1(argc, argv);
    AddTiming("init1");
    if (PchC.p_Cmd_C9IL) {
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

    init_main2();
    PstatInitState = PstatGetStatus();
    AddTiming("the reset of init2");
    ExecutionState = CES_Compiling;
    PchC.p_PchDFlag &= !PchC.p_FUseTypeServer;
    if (Prep) {
        to_human();
        ExecutionState = CES_NormalCleanup;
    } else {
        NOT_IMPLEMENTED();
#if 0
        if (PchC.p_Cmd_C9IL) {
            FUN_0041c5bf();
        }
        if (PchOldUFlag) {
            if (PchOldUFlag) {
                SkipToPchUse(PchOldUFile, FALSE);
            }
            SkipToPchUse(PchUFile, TRUE);
        } else {
            PchC.p_SavePragStat = PstatGetStatus();
            if (gOption_YX) {
                PchC.p_PchDFlag = !PchC.p_FUseTypeServer;
                FUN_0044648e();
            } else {
                gINT_00469158 = 0;
                if (PchC.option_C9IL && !Prep && !Out_funcdef && PchC.p_Symbolic_debug_holder) {
                    FUN_0041e9c3();
                }
            }
            gOptions_PCH_00468d50 = PchC;
        }
        AddTiming("PCH open");
        if (!PchC.option_C9IL && !gOption_YX) {
            if (gBOOL_0045c4e0) {
                FUN_004495f1();
            } else {
                FUN_004496d8();
                FUN_004445a1();
            }
        }
        RunYACC_0041e7f1();
        if (PchC.option_C9IL || gBOOL_0045c6d0) {
            AddTiming("primary parsing");
        } else {
            AddTiming("headers");
        }
        if (!Out_funcdef) {
            AddTiming("compiler generated stuff");
            FUN_0041f45d(gStruct_0045b690);
            AddTiming("global symbols");
            if (PchC.option_C9IL) {
                if (gBOOL_0045f98c) {
                    FUN_0041402e(83, NULL);
                    FUN_0041402e(84, FUN_0040929e(0));
                }
                FUN_0041402e(77, NULL);
            }
            FUN_0040872a();
        }
        AddTiming("expect nothing");
        ExecutionState = CES_NormalCleanup;
        pSbr = GetSourceBrowser();
        pSbr->vtable_0x00();
        DestroySourceBrowser();
        if ((WarnIsError > 1) + Nerrors == 0) {
            if (!gIncremental_interface3->vmethod_inc3_0x00()) {
                char buffer[260];
                EmitError(471, gPTR_00466458->field_0x0->vmethod_0x0c(buffer));
            }
        }
        if (!gIncremental_interface3->vmethod_inc3_0x04()) {
            FatalErrorF(73, "main.c", 1326);
        }
        if (!Out_funcdef) {
            if (!Prep && (PchC.p_Symbolic_debug_holder || PchC.p_FUseTypeServer)) {
                FUN_0041f3a9();
            }
            if (PchC.p_Cmd_C9IL) {
                ilsExp.closeFile();
                ilsLSym.closeFile();
                ilsGSym.closeFile();
                gFILESTREAM_00465fe0.FlushBuffer();
                ilsInit.closeFile();
                if (PchC.p_Symbolic_debug_holder) {
                    ilsDB.closeFile();
                }
            } else {
                FUN_004497c1(FALSE);
                FUN_004491dd();
            }
            gPTR_00466458->FUN_0041f2db();
        }
        p_TPIMgr->CloseNameServer();
#endif
    }
    if (StdoutFile != NULL && xfclose(I_stdoutfp)) {
        fatal_io_CRT_position(C1085, 340, StdoutFile, "main.c", 1388);
    }
    if (fflush(stdout) != 0) {
        fatal_io_CRT_position(C1085, 340, NULL, "main.c", 1393);
    }
    PchInterrupt();
    AddTiming("IPM/MR/IL close and wrap-up");
    PrintTimings();
    CleanupMemory();
    ExecutionState = CES_Done;
    if (HandlingControlC) {
        OKToHandleCtrlC();
    }
    exit(Nerrors + (1 < WarnIsError));
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
// FUNCTION: C1 0x0041f0ca
void CleanupMemory() {
    HeapManager::Destroy();
}

// FUNCTION: MSVC5_C1 0x000373e0
// ?ErrorCleanup@@YAXXZ
// GLOBAL: C1 0x00445a14
void ErrorCleanup()
{
    CloseAllSources();
    PchInterrupt();
    SBR::Interrupt();
    TPIMgr.Cleanup();
    if (p_TPIMgr != NULL) {
        p_TPIMgr->Cleanup();
    }
    CleanupMemory();
    ExecutionState = CES_Done;
    if (HandlingControlC) {
        OKToHandleCtrlC();
    }
}

// FUNCTION: MSVC5_C1 0x00037430
// ?ErrorCleanupGuard@@YAXW4CompilerExecutionState_t@@@Z
// void __cdecl ErrorCleanupGuard(enum CompilerExecutionState_t)

// FUNCTION: MSVC5_C1 0x00037460
// ?ExitPass@@YAXHH@Z
// void __cdecl ExitPass(int, int)

// FUNCTION: MSVC5_C1 0x00037480
// ?OKToHandleCtrlC@@YAXXZ
// FUNCTION: C1 0x
void OKToHandleCtrlC()
{
    if (ExecutionState != CES_Done) {
        if (ExecutionState == CES_AbortCleanup) {
            return;
        }
        limit_recursion(CES_AbortCleanup);
        ErrorCleanup();
    }
#ifdef _WIN32
    if (hSemaphore != NULL) {
        ReleaseSemaphore(hSemaphore, 1, NULL);
    }
    Sleep(0);
#endif
#ifdef _WIN32
    ExitProcess(0x8000);
#else
    exit(255);
#endif
}

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
// FUNCTION: C1 0x00426b10
void to_human()
{
    NOT_IMPLEMENTED();
}


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
