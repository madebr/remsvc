#include "pch.h"

#include "decomp.h"
#include "error.h"
#include "globals.h"
#include "ilsink.h"

#ifdef _WIN32
#include <io.h>
#include <windows.h>
#else
#include <unistd.h>
#endif

// GLOBAL: MSVC5_C1 0x00001548
// ?PchHd@@3UPchHd_t@@A
// struct PchHd_t PchHd

// GLOBAL: MSVC5_C1 0x000015b0
// ?PchDirMfile@@3PAUs_memfile@@A
// struct s_memfile *PchDirMfile

// GLOBAL: MSVC5_C1 0x000015b4
// ?PchValMfile@@3PAUs_memfile@@A
// struct s_memfile *PchValMfile

// GLOBAL: MSVC5_C1 0x000015b8
// ?PchHdrCount@@3FA
// short PchHdrCount

// GLOBAL: MSVC5_C1 0x000015bc
// ?PchHdrCurrSeg@@3GA
// unsigned short PchHdrCurrSeg

// GLOBAL: MSVC5_C1 0x000015c0
// ?PchXStaleHeader@@3HA
// int PchXStaleHeader

// GLOBAL: MSVC5_C1 0x000015c4
// ?PchNOHEURISTICS@@3HA
// int PchNOHEURISTICS

// GLOBAL: MSVC5_C1 0x000015c8
// ?PchCreateMsg@@3PADA
// char *PchCreateMsg

// GLOBAL: MSVC5_C1 0x000015cc
// ?pcb@CapturePdb@@0PAJA
// private: static long *CapturePdb::pcb

// GLOBAL: MSVC5_C1 0x000015d0
// ?chRun@CapturePdb@@0HA
// private: static int CapturePdb::chRun

// GLOBAL: MSVC5_C1 0x000015d4
// ?cRunLen@CapturePdb@@0JA
// private: static long CapturePdb::cRunLen

// GLOBAL: MSVC5_C1 0x000015d8
// ?NewPchPFile@@3HA
// GLOBAL: C1 0x0045c790
bool32 NewPchPFile = FALSE;

// GLOBAL: MSVC5_C1 0x000015dc
// ?New2PchPFile@@3HA
// GLOBAL: C1 0x0045c794
bool32 New2PchPFile = FALSE;

// GLOBAL: MSVC5_C1 0x00004d48
// ?PchXFilename@@3PBDB
// char const *PchXFilename

// GLOBAL: MSVC5_C1 0x00004db8
// ??_C@_0L@JEHH@?9INCLUDE?3_?$AA@
// "-INCLUDE:_"

// GLOBAL: MSVC5_C1 0x00004dc4
// ??_C@_0N@LBNO@__?$EA?$EA_PchSym_?$AA@
// "__@@_PchSym_"

// GLOBAL: MSVC5_C1 0x00004dd4
// ??_C@_07FJOE@hdrstop?$AA@
// "hdrstop"

// GLOBAL: MSVC5_C1 0x00004ddc
// ??_C@_07FONO@?4?2pch?4c?$AA@
// ".\\pch.c"

// GLOBAL: MSVC5_C1 0x00004de4
// ??_C@_06DAKE@VCPCH0?$AA@
// "VCPCH0"

// GLOBAL: MSVC5_C1 0x00004dec
// ??_C@_02JKAF@rb?$AA@
// "rb"

// GLOBAL: MSVC5_C1 0x00004df0
// ??_C@_02NGAF@wb?$AA@
// "wb"

// GLOBAL: MSVC5_C1 0x00004df4
// ??_C@_04LKAK@?$AD?$AA?$;A?$AH?$AA@

// GLOBAL: MSVC5_C1 0x00004dfc
// ??_C@_03OJHL@rb?$CL?$AA@
// "rb+"

// GLOBAL: MSVC5_C1 0x00004e00
// ??_C@_03KOPO@?1Gi?$AA@
// "/Gi"

// GLOBAL: MSVC5_C1 0x00004e04
// ??_C@_03OMCH@?1Fd?$AA@
// "/Fd"

// GLOBAL: MSVC5_C1 0x00004e08
// ??_C@_0BE@CFGL@Nov?514?5199614?343?303?$AA@
// "Nov 14 199614:43:03"

// GLOBAL: MSVC5_C1 0x00004e1c
// ??_C@_02DJBP@ex?$AA@
// "ex"

// GLOBAL: MSVC5_C1 0x00004e20
// ??_C@_01LHO@r?$AA@
// "r"

// GLOBAL: MSVC5_C1 0x00004e24
// ??_C@_04CNAB@?$EA00?$EA?$AA@
// "@00@"

// GLOBAL: MSVC5_C1 0x000079d0
// ?PchCurrDir@@3PAUPchDir_t@@A
// struct PchDir_t *PchCurrDir

// GLOBAL: MSVC5_C1 0x000079d4
// ?PchILBuf@@3PADA
// char *PchILBuf

// GLOBAL: MSVC5_C1 0x000079d8
// ?PchDirectives@@3PAUPchDir_t@@A
// struct PchDir_t *PchDirectives

// GLOBAL: MSVC5_C1 0x00007a48
// ?Newfp@@3PAU_iobuf@@A
// GLOBAL: C1 0x00468d48
FILE *Newfp = NULL;

// GLOBAL: MSVC5_C1 0x00007a50
// ?locPchC@@3UPchC_t@@A
// struct PchC_t locPchC

// GLOBAL: MSVC5_C1 0x00007e54
// ?PchXState@@3W4PchXState_t@@A
// enum PchXState_t PchXState

// FUNCTION: MSVC5_C1 0x000379f0
// ?PchWriteDirHd@@YAXW4PchDirKind_t@@JJ@Z
// void __cdecl PchWriteDirHd(enum PchDirKind_t, long, long)

// FUNCTION: MSVC5_C1 0x00037a30
// ?PchWriteDirString@@YAXW4PchDirKind_t@@JPAE@Z
// void __cdecl PchWriteDirString(enum PchDirKind_t, long, unsigned char *)

// FUNCTION: MSVC5_C1 0x00037a80
// ?PchDirx@@YA?AW4PchXResCode_t@@W4PchDirKind_t@@JPAE@Z
// enum PchXResCode_t __cdecl PchDirx(enum PchDirKind_t, long, unsigned char *)

// FUNCTION: MSVC5_C1 0x00037b20
// ?PchDirDefine@@YA?AW4PchXResCode_t@@PAE0G@Z
// enum PchXResCode_t __cdecl PchDirDefine(unsigned char *, unsigned char *, unsigned short)

// FUNCTION: MSVC5_C1 0x00037cc0
// ?PchDirifeval@@YAJJ@Z
// long __cdecl PchDirifeval(long)

// FUNCTION: MSVC5_C1 0x00037d20
// ?PchXSetMfile@@YAXXZ
// void __cdecl PchXSetMfile(void)

// FUNCTION: MSVC5_C1 0x00037d70
// ?PchDirLex@@YA?AW4PchXResCode_t@@XZ
// enum PchXResCode_t __cdecl PchDirLex(void)

// FUNCTION: MSVC5_C1 0x00037e90
// ?PchTimeStamp@@YAKPAE@Z
// unsigned long __cdecl PchTimeStamp(unsigned char *)

// FUNCTION: MSVC5_C1 0x00037ec0
// ?PchFDTimeStamp@@YAKH@Z
// unsigned long __cdecl PchFDTimeStamp(int)

// FUNCTION: MSVC5_C1 0x00037ef0
// ?PchDirInclude@@YA?AW4PchXResCode_t@@PAE@Z
// enum PchXResCode_t __cdecl PchDirInclude(unsigned char *)

// FUNCTION: MSVC5_C1 0x00037ff0
// ?PchDirPath@@YAXPAEH@Z
// void __cdecl PchDirPath(unsigned char *, int)

// FUNCTION: MSVC5_C1 0x00038010
// ?PchDirPathUnopened@@YAXPAE@Z
// void __cdecl PchDirPathUnopened(unsigned char *)

// FUNCTION: MSVC5_C1 0x00038030
// ?PchXCreate@@YAXXZ
// void __cdecl PchXCreate(void)

// FUNCTION: MSVC5_C1 0x000381b0
// ?PchXRecover@@YA?AW4PchXResCode_t@@XZ
// enum PchXResCode_t __cdecl PchXRecover(void)

// FUNCTION: MSVC5_C1 0x000383f0
// ?PchX@@YA?AW4PchXResCode_t@@XZ
// enum PchXResCode_t __cdecl PchX(void)

// FUNCTION: MSVC5_C1 0x00038460
// ?PchXInit@@YAXXZ
// void __cdecl PchXInit(void)

// FUNCTION: MSVC5_C1 0x000387f0
// ?Reset@CapturePdb@@SAXPAJ@Z
// public: static void __cdecl CapturePdb::Reset(long *)

// FUNCTION: MSVC5_C1 0x00038820
// ?DumpRun@CapturePdb@@CAXXZ
// private: static void __cdecl CapturePdb::DumpRun(void)

// FUNCTION: MSVC5_C1 0x00038a90
// ?SaveToPch@CapturePdb@@SAHPBXJ@Z
// public: static int __cdecl CapturePdb::SaveToPch(void const *, long)

// FUNCTION: MSVC5_C1 0x00038b80
// ?RestoreFromPch@CapturePdb@@SAXPADJ@Z
// public: static void __cdecl CapturePdb::RestoreFromPch(char *, long)

// FUNCTION: MSVC5_C1 0x00038d50
// ?PchCheckDefs@@YAXXZ
// void __cdecl PchCheckDefs(void)

// FUNCTION: MSVC5_C1 0x00038e40
// ?PchFinishUse@@YAXXZ
// void __cdecl PchFinishUse(void)

// FUNCTION: MSVC5_C1 0x000395d0
// ?PchUseCheck@@YAHH@Z
// int __cdecl PchUseCheck(int)

// FUNCTION: MSVC5_C1 0x00039820
// ?PchUse@@YAXXZ
// void __cdecl PchUse(void)

// FUNCTION: MSVC5_C1 0x00039c30
// ?OpenExpFile@@YAXXZ
// FUNCTION: C1 0x0041c815
void OpenExpFile()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00039d80
// ?SetUpPchFile@@YAXXZ
// void __cdecl SetUpPchFile(void)

// FUNCTION: MSVC5_C1 0x0003a460
// ?PchCreate@@YAXXZ
// void __cdecl PchCreate(void)

// FUNCTION: MSVC5_C1 0x0003a900
// ?PchInterrupt@@YAXXZ
// FUNCTION: C1 0x0041f15f
void PchInterrupt() {
    // GLOBAL: C1 0x0045c798
    static bool32 guard = FALSE;

    if (!guard) {
        if ((PchMustCreate && (WarnIsError > 1) + Nerrors != 0) || PchFileNameFromCmdLine || New2PchPFile || NewPchPFile != 0) {
            guard = 1;
            if (NewPchPFile) {
                IOGlobalVal = fclose(I_pchfp);
                if (IOGlobalVal == -1) {
                    fatal_io_CRT_position(C1082, 344, PchPFile, "pch.c", 2299);
                }
                I_pchfp = NULL;
            } else if (New2PchPFile == 0) {
                IOGlobalVal = fclose(Newfp);
                if (IOGlobalVal == -1) {
                    fatal_io_CRT_position(C1082, 344, PchPFile, "pch.c",0x8ff);
                }
                Newfp = NULL;
            } else if (PchFileNameFromCmdLine) {
                IOGlobalVal = ilsExp.fclose();
                if (IOGlobalVal == -1) {
                    fatal_io_CRT_position(C1082,344,PchPFile,"pch.c",0x903);
                }
            } else {
                guard = TRUE;
                return;
            }
            if (unlink(PchPFile)) {
                fatal_io_CRT(C1083,340, PchPFile);
            }
            PchFileNameFromCmdLine = FALSE;
            New2PchPFile = FALSE;
            NewPchPFile = FALSE;
        }
    }
}

// FUNCTION: MSVC5_C1 0x0003aa40
// ?PchCopyFile@@YAJPAU_iobuf@@0J@Z
// long __cdecl PchCopyFile(struct _iobuf *, struct _iobuf *, long)

// FUNCTION: MSVC5_C1 0x0003aae0
// ?FinishPchSetup@@YAXXZ
// void __cdecl FinishPchSetup(void)

// FUNCTION: MSVC5_C1 0x0003ad00
// ?PchAppendIL@@YAXXZ
// void __cdecl PchAppendIL(void)

// FUNCTION: MSVC5_C1 0x0003aec0
// ?OpenSbrOnUse@@YAXH@Z
// void __cdecl OpenSbrOnUse(int)
// static

// FUNCTION: MSVC5_C1 0x0003af70
// ?PchCopyIL@@YAXH@Z
// void __cdecl PchCopyIL(int)

// FUNCTION: MSVC5_C1 0x0003b0f0
// ?ValidatePersistentPch@@YAHPAE@Z
// FUNCTION: C1 0x00426f37
bool32 ValidatePersistentPch(const char *path)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x0003b6b0
// ?CheckPersistentPchDirective@@YAHW4PchDirKind_t@@JPAEH@Z
// int __cdecl CheckPersistentPchDirective(enum PchDirKind_t, long, unsigned char *, int)
// static

// FUNCTION: MSVC5_C1 0x0003b770
// ?PchInitPersistentCreate@@YAXXZ
// FUNCTION: C1 0x00426e1b
void PchInitPersistentCreate()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x0003b820
// ?PchGetInjectedSymID@@YAHPAEPAD1@Z
// int __cdecl PchGetInjectedSymID(unsigned char *, char *, char *)
// static

// FUNCTION: MSVC5_C1 0x0003b900
// ?EncodeFilenameAsMungedID@@YAPAEPAEPAD@Z
// unsigned char * __cdecl EncodeFilenameAsMungedID(unsigned char *, char *)
// static

// FUNCTION: MSVC5_C1 0x0003ba80
// ?PchInjectUniqSym@@YAXXZ
// void __cdecl PchInjectUniqSym(void)
// static

// FUNCTION: MSVC5_C1 0x0003baf0
// ?PchRefInjectedSym@@YAXXZ
// void __cdecl PchRefInjectedSym(void)
// static

