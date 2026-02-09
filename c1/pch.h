#ifndef PCH_H
#define PCH_H

#include "decomp.h"

#include <stdio.h>

// ?PchHd@@3UPchHd_t@@A
// struct PchHd_t PchHd

// ?PchDirMfile@@3PAUs_memfile@@A
// struct s_memfile *PchDirMfile

// ?PchValMfile@@3PAUs_memfile@@A
// struct s_memfile *PchValMfile

// ?PchHdrCount@@3FA
// short PchHdrCount

// ?PchHdrCurrSeg@@3GA
// unsigned short PchHdrCurrSeg

// ?PchXStaleHeader@@3HA
// int PchXStaleHeader

// ?PchNOHEURISTICS@@3HA
// int PchNOHEURISTICS

// ?PchCreateMsg@@3PADA
// char *PchCreateMsg

// ?pcb@CapturePdb@@0PAJA
// private: static long *CapturePdb::pcb

// ?chRun@CapturePdb@@0HA
// private: static int CapturePdb::chRun

// ?cRunLen@CapturePdb@@0JA
// private: static long CapturePdb::cRunLen

// ?NewPchPFile@@3HA
extern bool32 NewPchPFile;

// ?New2PchPFile@@3HA
extern bool32 New2PchPFile;

// ?PchXFilename@@3PBDB
// char const *PchXFilename

// ??_C@_0L@JEHH@?9INCLUDE?3_?$AA@
// "-INCLUDE:_"

// ??_C@_0N@LBNO@__?$EA?$EA_PchSym_?$AA@
// "__@@_PchSym_"

// ??_C@_07FJOE@hdrstop?$AA@
// "hdrstop"

// ??_C@_07FONO@?4?2pch?4c?$AA@
// ".\\pch.c"

// ??_C@_06DAKE@VCPCH0?$AA@
// "VCPCH0"

// ??_C@_02JKAF@rb?$AA@
// "rb"

// ??_C@_02NGAF@wb?$AA@
// "wb"

// ??_C@_04LKAK@?$AD?$AA?$;A?$AH?$AA@

// ??_C@_03OJHL@rb?$CL?$AA@
// "rb+"

// ??_C@_03KOPO@?1Gi?$AA@
// "/Gi"

// ??_C@_03OMCH@?1Fd?$AA@
// "/Fd"

// ??_C@_0BE@CFGL@Nov?514?5199614?343?303?$AA@
// "Nov 14 199614:43:03"

// ??_C@_02DJBP@ex?$AA@
// "ex"

// ??_C@_01LHO@r?$AA@
// "r"

// ??_C@_04CNAB@?$EA00?$EA?$AA@
// "@00@"

// ?PchCurrDir@@3PAUPchDir_t@@A
// struct PchDir_t *PchCurrDir

// ?PchILBuf@@3PADA
// char *PchILBuf

// ?PchDirectives@@3PAUPchDir_t@@A
// struct PchDir_t *PchDirectives

// ?Newfp@@3PAU_iobuf@@A
extern FILE *Newfp;

// ?locPchC@@3UPchC_t@@A
// struct PchC_t locPchC

// ?PchXState@@3W4PchXState_t@@A
// enum PchXState_t PchXState

// ?PchWriteDirHd@@YAXW4PchDirKind_t@@JJ@Z
// void __cdecl PchWriteDirHd(enum PchDirKind_t, long, long)

// ?PchWriteDirString@@YAXW4PchDirKind_t@@JPAE@Z
// void __cdecl PchWriteDirString(enum PchDirKind_t, long, unsigned char *)

// ?PchDirx@@YA?AW4PchXResCode_t@@W4PchDirKind_t@@JPAE@Z
// enum PchXResCode_t __cdecl PchDirx(enum PchDirKind_t, long, unsigned char *)

// ?PchDirDefine@@YA?AW4PchXResCode_t@@PAE0G@Z
// enum PchXResCode_t __cdecl PchDirDefine(unsigned char *, unsigned char *, unsigned short)

// ?PchDirifeval@@YAJJ@Z
// long __cdecl PchDirifeval(long)

// ?PchXSetMfile@@YAXXZ
// void __cdecl PchXSetMfile(void)

// ?PchDirLex@@YA?AW4PchXResCode_t@@XZ
// enum PchXResCode_t __cdecl PchDirLex(void)

// ?PchTimeStamp@@YAKPAE@Z
// unsigned long __cdecl PchTimeStamp(unsigned char *)

// ?PchFDTimeStamp@@YAKH@Z
// unsigned long __cdecl PchFDTimeStamp(int)

// ?PchDirInclude@@YA?AW4PchXResCode_t@@PAE@Z
// enum PchXResCode_t __cdecl PchDirInclude(unsigned char *)

// ?PchDirPath@@YAXPAEH@Z
// void __cdecl PchDirPath(unsigned char *, int)

// ?PchDirPathUnopened@@YAXPAE@Z
// void __cdecl PchDirPathUnopened(unsigned char *)

// ?PchXCreate@@YAXXZ
// void __cdecl PchXCreate(void)

// ?PchXRecover@@YA?AW4PchXResCode_t@@XZ
// enum PchXResCode_t __cdecl PchXRecover(void)

// ?PchX@@YA?AW4PchXResCode_t@@XZ
// enum PchXResCode_t __cdecl PchX(void)

// ?PchXInit@@YAXXZ
// void __cdecl PchXInit(void)

// ?Reset@CapturePdb@@SAXPAJ@Z
// public: static void __cdecl CapturePdb::Reset(long *)

// ?DumpRun@CapturePdb@@CAXXZ
// private: static void __cdecl CapturePdb::DumpRun(void)

// ?SaveToPch@CapturePdb@@SAHPBXJ@Z
// public: static int __cdecl CapturePdb::SaveToPch(void const *, long)

// ?RestoreFromPch@CapturePdb@@SAXPADJ@Z
// public: static void __cdecl CapturePdb::RestoreFromPch(char *, long)

// ?PchCheckDefs@@YAXXZ
// void __cdecl PchCheckDefs(void)

// ?PchFinishUse@@YAXXZ
// void __cdecl PchFinishUse(void)

// ?PchUseCheck@@YAHH@Z
// int __cdecl PchUseCheck(int)

// ?PchUse@@YAXXZ
// void __cdecl PchUse(void)

// ?OpenExpFile@@YAXXZ
// void __cdecl OpenExpFile(void)

// ?SetUpPchFile@@YAXXZ
// void __cdecl SetUpPchFile(void)

// ?PchCreate@@YAXXZ
// void __cdecl PchCreate(void)

// ?PchInterrupt@@YAXXZ
extern void PchInterrupt();

// ?PchCopyFile@@YAJPAU_iobuf@@0J@Z
// long __cdecl PchCopyFile(struct _iobuf *, struct _iobuf *, long)

// ?FinishPchSetup@@YAXXZ
// void __cdecl FinishPchSetup(void)

// ?PchAppendIL@@YAXXZ
// void __cdecl PchAppendIL(void)

// ?OpenSbrOnUse@@YAXH@Z
// void __cdecl OpenSbrOnUse(int)

// ?PchCopyIL@@YAXH@Z
// void __cdecl PchCopyIL(int)

// ?ValidatePersistentPch@@YAHPAE@Z
// int __cdecl ValidatePersistentPch(unsigned char *)

// ?CheckPersistentPchDirective@@YAHW4PchDirKind_t@@JPAEH@Z
// int __cdecl CheckPersistentPchDirective(enum PchDirKind_t, long, unsigned char *, int)

// ?PchInitPersistentCreate@@YAXXZ
// void __cdecl PchInitPersistentCreate(void)

// ?PchGetInjectedSymID@@YAHPAEPAD1@Z
// int __cdecl PchGetInjectedSymID(unsigned char *, char *, char *)

// ?EncodeFilenameAsMungedID@@YAPAEPAEPAD@Z
// unsigned char * __cdecl EncodeFilenameAsMungedID(unsigned char *, char *)

// ?PchInjectUniqSym@@YAXXZ
// void __cdecl PchInjectUniqSym(void)

// ?PchRefInjectedSym@@YAXXZ
// void __cdecl PchRefInjectedSym(void)

#endif /* PCH_H */
