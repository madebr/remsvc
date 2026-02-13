#include "globals.h"

#include "decomp.h"
#include "globals.h"
#include "initmain.h"
#include "nheapall.h"
#include "timing.h"
#include "zz_diagnostic.h"

#ifdef _WIN32
#include <windows.h>
#endif

// GLOBAL: MSVC5_C1 0x00000050
// ?g_hDLLHandle@@3PAXA
// void *g_hDLLHandle

// GLOBAL: MSVC5_C1 0x00000058
// ?TPIMgr@@3VPDBManager_t@@A
// GLOBAL: C1 0x004662a8
PDBManager_t TPIMgr;

// GLOBAL: C1 0x004664b0
PDBManager_t SplitTPIMgr;

// GLOBAL: C1 0x00466458
PDBManager_t *p_TPIMgr = NULL;

// GLOBAL: MSVC5_C1 0x00000074
// ?fSkipPDBOpen@@3HA
// int fSkipPDBOpen

// GLOBAL: MSVC5_C1 0x00000078
// ?pIDBMgr@@3PAVPDBManager_t@@A
// class PDBManager_t *pIDBMgr

// GLOBAL: MSVC5_C1 0x00000080
// ?IDBMgr@@3VPDBManager_t@@A
// class PDBManager_t IDBMgr

// GLOBAL: MSVC5_C1 0x0000009c
// ?fClosePDB@@3HA
// int fClosePDB

// GLOBAL: MSVC5_C1 0x000003f0
// ?PchS@@3UPchS_t@@A
// GLOBAL: C1 0x????????
PchS_t PchS;

// GLOBAL: MSVC5_C1 0x00000f00
// ?PchC@@3UPchC_t@@A
// GLOBAL: C1 0x????????
PchC_t PchC;

// GLOBAL: MSVC5_C1 0x00001304
// ?MemoryStatsLevel@@3HA
// GLOBAL: C1 0x0045c4b0
int MemoryStatsLevel = 0;

// GLOBAL: MSVC5_C1 0x00001308
// ?PchUFlag@@3HA
// GLOBAL: C1 0x0045c4b4
bool32 PchUFlag = FALSE;

// GLOBAL: MSVC5_C1 0x0000130c
// ?PchUFile@@3PAEA
// GLOBAL: C1 0x0045c4b8
char *PchUFile = NULL;

// GLOBAL: MSVC5_C1 0x00001310
// ?PchCFlag@@3HA
// GLOBAL: C1 0x0045c4bc
bool32 PchCFlag = FALSE;

// GLOBAL: MSVC5_C1 0x00001314
// ?PchCFile@@3PAEA
// GLOBAL: C1 0x0045c4c0
char *PchCFile = NULL;

// GLOBAL: MSVC5_C1 0x00001318
// ?PchXFlag@@3HA
// int PchXFlag

// GLOBAL: MSVC5_C1 0x0000131c
// ?PchXFile@@3PAEA
// unsigned char *PchXFile

// GLOBAL: MSVC5_C1 0x00001320
// ?szCmd_Ylstring@@3PADA
// GLOBAL: C1 0x0045c4cc
const char *szCmd_Ylstring;

// GLOBAL: MSVC5_C1 0x00001324
// ?PchPFile@@3PAEA
// GLOBAL: C1 0x0045c4d0
char *PchPFile = NULL;

// GLOBAL: MSVC5_C1 0x00001328
// ?PchFinalFileName@@3PAEA
// unsigned char *PchFinalFileName

// GLOBAL: MSVC5_C1 0x0000132c
// ?PchCreateFlag@@3HA
// int PchCreateFlag

// GLOBAL: MSVC5_C1 0x00001330
// ?PchFileCreated@@3HA
// int PchFileCreated

// GLOBAL: MSVC5_C1 0x00001334
// ?PchMustCreate@@3HA
// GLOBAL: C1 0x0045c4e0
bool32 PchMustCreate = FALSE;

// GLOBAL: MSVC5_C1 0x00001338
// ?PchFileNameFromCmdLine@@3HA
// GLOBAL: C1 0x0045c4e4
bool32 PchFileNameFromCmdLine = FALSE;

// GLOBAL: MSVC5_C1 0x0000133c
// ?fPersistentPch@@3HA
// GLOBAL: C1 0x0045c4e8
bool32 fPersistentPch = TRUE;

// GLOBAL: MSVC5_C1 0x00001340
// ?PchReuseCVTypes@@3HA
// GLOBAL: C1 0x0045c4ec
bool32 PchReuseCVTypes = FALSE;

// GLOBAL: MSVC5_C1 0x00001344
// ?CurFuncInPch@@3HA
// int CurFuncInPch

// GLOBAL: MSVC5_C1 0x00001348
// ?CurFuncSkipped@@3HA
// int CurFuncSkipped

// GLOBAL: MSVC5_C1 0x0000134c
// ?Debug@@3PADA
// char *Debug

// GLOBAL: MSVC5_C1 0x00001350
// ?NVStr@@3PADA
// GLOBAL: C1 0x0045c4f8
const char *NVStr = NULL;

// GLOBAL: MSVC5_C1 0x00001354
// ?ParentEsu@@3PAVSymbol_t@@A
// class Symbol_t *ParentEsu

// GLOBAL: MSVC5_C1 0x00001358
// ?Nsilent_errors@@3HA
// int Nsilent_errors

// GLOBAL: MSVC5_C1 0x0000135c
// ?Nsilent_warnings@@3HA
// int Nsilent_warnings

// GLOBAL: MSVC5_C1 0x00001360
// ?Prep_ifstack@@3HA
// int Prep_ifstack

// GLOBAL: MSVC5_C1 0x00001364
// ?OutFil@@3PADA
// GLOBAL: C1 0x0045c508
const char *OutFil = NULL;

// GLOBAL: MSVC5_C1 0x00001368
// ?szPDBName@@3PADA
// GLOBAL: C1 0x0045c50c
const char *szPDBName = "vc40.pdb";

// GLOBAL: MSVC5_C1 0x0000136c
// ?StunDepth@@3HA
// int StunDepth

// GLOBAL: MSVC5_C1 0x00001370
// ?Warn_level@@3HA
// GLOBAL: C1 0x0045c514
int Warn_level = 1;

// GLOBAL: MSVC5_C1 0x00001374
// ?InlineDepth@@3FA
// short InlineDepth

// GLOBAL: MSVC5_C1 0x00001378
// ?InlineRecursion@@3FA
// short InlineRecursion

// GLOBAL: MSVC5_C1 0x0000137c
// ?PragmaAutoInline@@3HA
// int PragmaAutoInline

// GLOBAL: MSVC5_C1 0x00001380
// ?AutoInline@@3HA
// int AutoInline

// GLOBAL: MSVC5_C1 0x00001384
// ?ExplicitComdat@@3HA
// int ExplicitComdat

// GLOBAL: MSVC5_C1 0x00001388
// ?NoExpansion@@3HA
// int NoExpansion

// GLOBAL: MSVC5_C1 0x00001390
// ?Enum_val@@3_JA
// __int64 Enum_val

// GLOBAL: MSVC5_C1 0x00001398
// ?LexicalIndex@@3GA
// unsigned short LexicalIndex

// GLOBAL: MSVC5_C1 0x0000139c
// ?pStringBuffer@@3PAEA
// unsigned char *pStringBuffer

// GLOBAL: MSVC5_C1 0x000013a0
// ?Path_chars@@3PADA
// GLOBAL: C1 0x00454a24
const char *Path_chars = "\\:/";

// GLOBAL: MSVC5_C1 0x000013a4
// ?Basename@@3PADA
const char *Basename;

// GLOBAL: MSVC5_C1 0x000013a8
// ?Cmd_pack_size@@3HA
// GLOBAL: C1 0x0045c548
int Cmd_pack_size = -1;

// GLOBAL: MSVC5_C1 0x000013ac
// ?iTryBlockLevel@@3HA
// int iTryBlockLevel

// GLOBAL: MSVC5_C1 0x000013b0
// ?iExceptBlockLevel@@3HA
// int iExceptBlockLevel

// GLOBAL: MSVC5_C1 0x000013b4
// ?iFinallyBlockLevel@@3HA
// int iFinallyBlockLevel

// GLOBAL: MSVC5_C1 0x000013b8
// ?SizeofDepth@@3HA
// int SizeofDepth

// GLOBAL: MSVC5_C1 0x000013bc
// ?zgDepth@@3HA
// int zgDepth

// GLOBAL: MSVC5_C1 0x000013c0
// ?Hold_I_DATA@@3PAVSymbol_t@@A
// class Symbol_t *Hold_I_DATA

// GLOBAL: MSVC5_C1 0x000013c4
// ?Cmd_NoExportInlines@@3HA
// GLOBAL: C1 0x0045c568
bool32 Cmd_NoExportInlines = FALSE;

// GLOBAL: MSVC5_C1 0x000013c8
// ?Realt_const0@@3Us_realt@@A
// struct s_realt Realt_const0

// GLOBAL: MSVC5_C1 0x000013d4
// ?pMRMgr@@3PAVMRMgr_t@@A
// class MRMgr_t *pMRMgr

// ?ExecutionState@@3W4CompilerExecutionState_t@@A
// enum CompilerExecutionState_t ExecutionState
// GLOBAL: MSVC5_C1 0x000013d8
// C1: DATA 0x0045c580
CompilerExecutionState_t ExecutionState = CES_Undef;

// GLOBAL: MSVC5_C1 0x00002a28
// ?JDateVer@@3PBDB
// char const *JDateVer

// GLOBAL: MSVC5_C1 0x00002a58
// ?Copyright@@3PBDB
// char const *Copyright

// GLOBAL: MSVC5_C1 0x00002a80
// ?C1Str@@3PBDB
// char const *C1Str

// GLOBAL: MSVC5_C1 0x00002a88
// ?Cdecl_str@@3PBDB
// char const *Cdecl_str

// GLOBAL: MSVC5_C1 0x00002a90
// ?Pascal_str@@3PBDB
// char const *Pascal_str

// GLOBAL: MSVC5_C1 0x00002aa0
// ?PPelse_str@@3PBDB
// char const *PPelse_str

// GLOBAL: MSVC5_C1 0x00002aa8
// ?PPendif_str@@3PBDB
// char const *PPendif_str

// GLOBAL: MSVC5_C1 0x00002ab0
// ?PPifel_str@@3PBDB
// char const *PPifel_str

// GLOBAL: MSVC5_C1 0x00002ac0
// ?PPdefine_str@@3PBDB
// char const *PPdefine_str

// GLOBAL: MSVC5_C1 0x00002ac8
// ?PPundef_str@@3PBDB
// char const *PPundef_str

// GLOBAL: MSVC5_C1 0x00002ad0
// ?PPerror_str@@3PBDB
// char const *PPerror_str

// GLOBAL: MSVC5_C1 0x00002ad8
// ?PPinclude_str@@3PBDB
// char const *PPinclude_str

// GLOBAL: MSVC5_C1 0x00002ae8
// ?PPifdef_str@@3PBDB
// char const *PPifdef_str

// GLOBAL: MSVC5_C1 0x00002af0
// ?PPifndef_str@@3PBDB
// char const *PPifndef_str

// GLOBAL: MSVC5_C1 0x00002af8
// ?PPline_str@@3PBDB
// char const *PPline_str

// GLOBAL: MSVC5_C1 0x00002b00
// ?PPpragma_str@@3PBDB
// char const *PPpragma_str

// GLOBAL: MSVC5_C1 0x00002b08
// ?Near_str@@3PBDB
// char const *Near_str

// GLOBAL: MSVC5_C1 0x00002b10
// ?Far_str@@3PBDB
// char const *Far_str

// GLOBAL: MSVC5_C1 0x00002b18
// ?Far16_str@@3PBDB
// char const *Far16_str

// GLOBAL: MSVC5_C1 0x00002b20
// ?Syscall_str@@3PBDB
// char const *Syscall_str

// GLOBAL: MSVC5_C1 0x00002b30
// ?Asm_str@@3PBDB
// char const *Asm_str

// GLOBAL: MSVC5_C1 0x00002b38
// ?xlateECerr@@3PBHB
// int const *xlateECerr

// GLOBAL: MSVC5_C1 0x00002b78
// ??_C@_03IGI@?2?3?1?$AA@
// "\\:/"

// GLOBAL: MSVC5_C1 0x00002b7c
// ??_C@_08CNLK@vc50?4pdb?$AA@
// "vc50.pdb"

// GLOBAL: MSVC5_C1 0x00003d80
// ?TagIsInCurrentBlock@@3HA
// int TagIsInCurrentBlock

// GLOBAL: MSVC5_C1 0x00003d84
// ?Dump_tables@@3HA
// int Dump_tables

// GLOBAL: MSVC5_C1 0x00003d88
// ?XformedFormalListType@@3W4FormalListKind_e@GTBFormalList@@A
// enum GTBFormalList::FormalListKind_e XformedFormalListType

// GLOBAL: MSVC5_C1 0x00003d8c
// ?fReusePersistPch@@3HA
// GLOBAL: C1 0x0045f994
bool32 fReusePersistPch = FALSE;

// GLOBAL: MSVC5_C1 0x00003d90
// ?m_allocator@?$SAClass@UFlistEntry_t@@$00@@0USubAllocator@VirtualHeap@@A
// GLOBAL: C1 0x00460998
template <>
VirtualHeap::SubAllocator SAClass<FlistEntry_t>::m_allocator = {};

// GLOBAL: MSVC5_C1 0x00003da0
// ?NParseErrors@@3HA
// int NParseErrors

// GLOBAL: MSVC5_C1 0x00003da8
// ?ilsEEAttrib@@3VILSink@@A
// class ILSink ilsEEAttrib

// GLOBAL: MSVC5_C1 0x00003ed8
// ?ilsGSym@@3VILSink@@A
// GLOBAL: C1 0x004609e0
ILSink ilsGSym;

// GLOBAL: MSVC5_C1 0x00004008
// ?Optimize_state@@3HA
// int Optimize_state

// GLOBAL: MSVC5_C1 0x0000400c
// ?Inteltypes@@3HA
// int Inteltypes

// GLOBAL: MSVC5_C1 0x00004010
// ?Cons_case@@3PAUs_tree@@A
// struct s_tree *Cons_case

// GLOBAL: MSVC5_C1 0x00004018
// ?m_allocator@?$SAClass@VToken@@$00@@0USubAllocator@VirtualHeap@@A
// GLOBAL: C1 0x00460a18
template <>
VirtualHeap::SubAllocator SAClass<Token>::m_allocator = {};

// GLOBAL: MSVC5_C1 0x00004028
// ?ZnFlag@@3HA
// int ZnFlag

// GLOBAL: MSVC5_C1 0x0000402c
// ?Break@@3PAUs_stack@@A
// struct s_stack *Break

// GLOBAL: MSVC5_C1 0x00004030
// ?szIlModName@@3PBDB
// char const *szIlModName

// GLOBAL: MSVC5_C1 0x00004034
// ?CurrFormalList@@3PAVDLSymbolList_t@@A
// class DLSymbolList_t *CurrFormalList

// GLOBAL: MSVC5_C1 0x00004038
// ?Default@@3PAUs_stack@@A
// struct s_stack *Default

// GLOBAL: MSVC5_C1 0x00004040
// ?m_allocator@?$SAClass@UIndirEntry_t@@$00@@0USubAllocator@VirtualHeap@@A
// GLOBAL: C1 0x00460a40
template <>
VirtualHeap::SubAllocator SAClass<IndirEntry_t>::m_allocator = {};

// GLOBAL: MSVC5_C1 0x00004050
// ?ilsDB@@3VILSink@@A
// GLOBAL: C1 0x00460a58
ILSink ilsDB;

// GLOBAL: MSVC5_C1 0x00004180
// ?listIncludes@@3PAUlist@@A
// GLOBAL: C1 0x00460a84
list<void *> *listIncludes;

// GLOBAL: MSVC5_C1 0x00004184
// ?ParenDepth@@3HA
// int ParenDepth

// GLOBAL: MSVC5_C1 0x00004188
// ?Input_file@@3PADA
// GLOBAL: C1 0x00463a98
const char *Input_file = NULL;

// GLOBAL: MSVC5_C1 0x00004190
// ?RecursiveParseFlags@@3PAUs_RecursiveParseFlags@@A
// struct s_RecursiveParseFlags *RecursiveParseFlags

// GLOBAL: MSVC5_C1 0x00004208
// ?TypesForThisDepth@@3PAUs_declspec@@A
// struct s_declspec *TypesForThisDepth

// GLOBAL: MSVC5_C1 0x000046b8
// ?CurrentTimeStamp@@3PADA
// char *CurrentTimeStamp

// GLOBAL: MSVC5_C1 0x000046d8
// ?ilsRGL@@3VILSink@@A
// class ILSink ilsRGL

// GLOBAL: MSVC5_C1 0x00004808
// ?Continue@@3PAUs_stack@@A
// struct s_stack *Continue

// GLOBAL: MSVC5_C1 0x00004810
// ?ilsInitStrings@@3VILSink@@A
// class ILSink ilsInitStrings

// GLOBAL: MSVC5_C1 0x00004940
// ?ilsExp@@3VILSink@@A
// GLOBAL: C1 0x00466010
ILSink ilsExp;

// GLOBAL: MSVC5_C1 0x00004a70
// ?ZfExtension@@3HA
// int ZfExtension

// GLOBAL: MSVC5_C1 0x00004a78
// ?m_allocator@?$SAClass@Us_defn@@$00@@0USubAllocator@VirtualHeap@@A
// GLOBAL: C1 0x00466040
template <>
VirtualHeap::SubAllocator SAClass<s_defn>::m_allocator = {};

// GLOBAL: MSVC5_C1 0x00004a88
// ?TmpTypePool@@3PAVType_t@@A
// class Type_t *TmpTypePool

// GLOBAL: MSVC5_C1 0x00004b28
// ?Version@@3PADA
// GLOBAL: C1 0x004660f0
const char *Version = NULL;

// GLOBAL: MSVC5_C1 0x00004b30
// ?m_allocator@?$SAClass@UId_t@@$00@@0USubAllocator@VirtualHeap@@A
// GLOBAL: C1 0x004660f8
template <>
VirtualHeap::SubAllocator SAClass<Id_t>::m_allocator = {};

// GLOBAL: MSVC5_C1 0x00004b40
// ?C_value@@3Tu_value@@A
// union u_value C_value

// GLOBAL: MSVC5_C1 0x00004b48
// ?Reg_vars@@3PAUs_stack@@A
// struct s_stack *Reg_vars

// GLOBAL: MSVC5_C1 0x00004b4c
// ?Asm_align@@3FA
// short Asm_align

// GLOBAL: MSVC5_C1 0x00004b50
// ?listForcedIncludes@@3PAUlist@@A
// GLOBAL: C1 0x00466274
list<void *> *listForcedIncludes;

// GLOBAL: MSVC5_C1 0x00004b54
// ?ShowIncludes@@3HA
// GLOBAL: C1 0x0046611c
bool32 ShowIncludes = FALSE;

// GLOBAL: MSVC5_C1 0x00004b58
// ?ilsLSym@@3VILSink@@A
// GLOBAL: C1 0x00466120
ILSink ilsLSym;

// GLOBAL: MSVC5_C1 0x00004c88
// ?InternalUnaryTree_ivBasedInfo@@3Tu_ivalue@@A
// union u_ivalue InternalUnaryTree_ivBasedInfo

// GLOBAL: MSVC5_C1 0x00004c8c
// ?listDefs@@3PAUlist@@A
// GLOBAL: C1 0x00466150
list<void *> *listDefs;

// GLOBAL: MSVC5_C1 0x00004c90
// ?SymbolLevel@@3EA
// unsigned char SymbolLevel

// GLOBAL: MSVC5_C1 0x00004c94
// ?Lex_level@@3EA
// unsigned char Lex_level

// GLOBAL: MSVC5_C1 0x00004c98
// ?CurFuncStartLineNumber@@3JA
// long CurFuncStartLineNumber

// GLOBAL: MSVC5_C1 0x00004c9c
// ?Optimize_string@@3PAEA
// unsigned char *Optimize_string

// GLOBAL: MSVC5_C1 0x00004ca0
// ?Out_funcdef@@3HA
// GLOBAL: C1 0x00466164
bool32 Out_funcdef;

// GLOBAL: MSVC5_C1 0x00004ca4
// ?EnumTag@@3PAVSymbol_t@@A
// class Symbol_t *EnumTag

// GLOBAL: MSVC5_C1 0x00004ca8
// ?SwitchLabel@@3PAVSymbol_t@@A
// class Symbol_t *SwitchLabel

// GLOBAL: MSVC5_C1 0x00004cb0
// ?m_allocator@?$SAClass@UAssoc_t@@$00@@0USubAllocator@VirtualHeap@@A
// GLOBAL: C1 0x00466170
template <>
VirtualHeap::SubAllocator SAClass<Assoc_t>::m_allocator = {};

// GLOBAL: MSVC5_C1 0x00004cc0
// ?QnamedTypeForThisDepth@@3PAPAVSymbol_t@@A
// class Symbol_t **QnamedTypeForThisDepth

// GLOBAL: MSVC5_C1 0x00004db0
// ?InstantiateFunc@@3HA
// int InstantiateFunc

// GLOBAL: MSVC5_C1 0x00004db4
// ?StdoutFile@@3PADA
// GLOBAL: C1 0x00466274
const char *StdoutFile = NULL;

// GLOBAL: MSVC5_C1 0x00004db8
// ?Macro_depth@@3HA
// int Macro_depth

// GLOBAL: MSVC5_C1 0x00004dc0
// ?iterForcedIncludes@@3UlistIter_t@@A
// struct listIter_t iterForcedIncludes

// GLOBAL: MSVC5_C1 0x00004dcc
// ?CurrentTime@@3PADA
// char *CurrentTime

// GLOBAL: MSVC5_C1 0x00004dd0
// ?FormalListDepth@@3HA
// int FormalListDepth

// GLOBAL: MSVC5_C1 0x00004dd4
// ?I_Eoutput@@3PAU_iobuf@@A
// GLOBAL: C1 0x00466294
FILE *I_Eoutput = NULL;

// GLOBAL: MSVC5_C1 0x00004dd8
// ?m_allocator@?$SAClass@VGeneralAllocator_t@@$00@@0USubAllocator@VirtualHeap@@A
// GLOBAL: C1 0x00466298
template <>
VirtualHeap::SubAllocator SAClass<GeneralAllocator_t>::m_allocator = {};

// GLOBAL: MSVC5_C1 0x00004de8
// ?Case@@3PAUs_stack@@A
// struct s_stack *Case

// GLOBAL: MSVC5_C1 0x00004dec
// ?Current_function@@3PAVSymbol_t@@A
// class Symbol_t *Current_function

// GLOBAL: MSVC5_C1 0x00004df0
// ?StrNoInCurFunc@@3IA
// unsigned int StrNoInCurFunc

// GLOBAL: MSVC5_C1 0x00004df4
// ?SourceBrowserNam@@3PADA
// GLOBAL: C1 0x004662cc
const char *SourceBrowserNam = NULL;

// GLOBAL: MSVC5_C1 0x00004df8
// ?BadInternalClassErrors@@3HA
// int BadInternalClassErrors

// GLOBAL: MSVC5_C1 0x00004dfc
// ?crc32ClCmd@@3VCRC32@@A
// GLOBAL: C1 0x004662d0
CRC32 crc32ClCmd;

// GLOBAL: MSVC5_C1 0x00004e00
// ?SourceBrowserExt@@3PADA
// GLOBAL: C1 0x004662d8
const char *SourceBrowserExt = NULL;

// GLOBAL: MSVC5_C1 0x00004e08
// ?ilsInit@@3VILSink@@A
// GLOBAL: C1 0x004662e0
ILSink ilsInit;

// GLOBAL: MSVC5_C1 0x00004f38
// ?fGenPersistPch@@3HA
// GLOBAL: C1 0x0046630c
bool32 fGenPersistPch = FALSE;

// GLOBAL: MSVC5_C1 0x00004f3c
// ?Cmd_inlineparsing@@3HA
// int Cmd_inlineparsing

// GLOBAL: MSVC5_C1 0x00004f40
// ?Prep@@3HA
// GLOBAL: C1 0x00466314
bool32 Prep = FALSE;

// GLOBAL: MSVC5_C1 0x00004f44
// ?SourceBrowserNamFlg@@3PADA
// GLOBAL: C1 0x00466318
const char *SourceBrowserNamFlg = NULL;

// GLOBAL: MSVC5_C1 0x00004f48
// ?Current_char@@3PAEA
// unsigned char *Current_char

// GLOBAL: MSVC5_C1 0x00004f4c
// ?CurFuncSyOff@@3JA
// long CurFuncSyOff

// GLOBAL: MSVC5_C1 0x00004f50
// ?Reuse_1@@3PAEA
// unsigned char *Reuse_1

// GLOBAL: MSVC5_C1 0x00004fd0
// ?pSigMgr@@3PAUFESigMgr@@A
// GLOBAL: C1 0x004663a8
FESigMgr *pSigMgr = NULL;

// GLOBAL: MSVC5_C1 0x00004fd4
// ?CurrentDate@@3PADA
// char *CurrentDate

// GLOBAL: MSVC5_C1 0x00004fd8
// ?PchOldUFlag@@3HA
// GLOBAL: C1 0x004663b0
bool32 PchOldUFlag = FALSE;

// GLOBAL: MSVC5_C1 0x00004fdc
// ?TmpTypeIndex@@3HA
// int TmpTypeIndex

// GLOBAL: MSVC5_C1 0x00004fe0
// ?Exit_label@@3PAUs_tree@@A
// struct s_tree *Exit_label

// GLOBAL: MSVC5_C1 0x00004fe4
// ?PchOldUFile@@3PAEA
// GLOBAL: C1 0x10a9ce40
char *PchOldUFile = NULL;

// GLOBAL: MSVC5_C1 0x00004fe8
// ?CurFuncNumFormals@@3IA
// unsigned int CurFuncNumFormals

// GLOBAL: MSVC5_C1 0x00004ff0
// ?AsmString@@3PAEA
// unsigned char *AsmString

// GLOBAL: MSVC5_C1 0x00005070
// ?Test@@3PAUs_stack@@A
// struct s_stack *Test

// GLOBAL: MSVC5_C1 0x00005074
// ?CurFuncNumExNodes@@3KA
// GLOBAL: C1 0x00466448
unsigned int CurFuncNumExNodes = 0;

// GLOBAL: MSVC5_C1 0x00005078
// ?Cflag@@3HA
// GLOBAL: C1 0x00466450
bool32 Cflag = FALSE;

// GLOBAL: MSVC5_C1 0x0000507c
// ?I_stdoutfp@@3PAU_iobuf@@A
// GLOBAL: C1 0x00466454
FILE *I_stdoutfp = NULL;

// GLOBAL: MSVC5_C1 0x00005080
// ?I_sbrfp@@3PAU_iobuf@@A
// struct _iobuf *I_sbrfp

// GLOBAL: MSVC5_C1 0x00005084
// ?Nerrors@@3HA
// GLOBAL: C1 0x
int Nerrors = 0;

// GLOBAL: MSVC5_C1 0x00005088
// ?BdFlg@@3HA
// GLOBAL: C1 0x10a98ceb
bool32 BdFlg = FALSE;

// GLOBAL: MSVC5_C1 0x00005090
// ?m_allocator@?$SAClass@UTypeEntry_t@@$00@@0USubAllocator@VirtualHeap@@A
// GLOBAL: C1 0x00466468
template <>
VirtualHeap::SubAllocator SAClass<TypeEntry_t>::m_allocator = {};

// GLOBAL: MSVC5_C1 0x000050a0
// ?CurrFormalListType@@3W4FormalListKind_e@GTBFormalList@@A
// enum GTBFormalList::FormalListKind_e CurrFormalListType

// GLOBAL: MSVC5_C1 0x000050a4
// ?BlockScope@@3EA
// unsigned char BlockScope

// GLOBAL: MSVC5_C1 0x000050a8
// ?Start@@3PAUs_stack@@A
// struct s_stack *Start

// GLOBAL: MSVC5_C1 0x000050ac
// ?Loopi_stack@@3PAUs_stack@@A
// struct s_stack *Loopi_stack

// GLOBAL: MSVC5_C1 0x000050b0
// ?Cross_compile@@3HA
// GLOBAL: C1 0x00466484
bool32 Cross_compile = FALSE;

// GLOBAL: MSVC5_C1 0x000050b4
// ?Processor@@3HA
// GLOBAL: C1 0x00466488
unsigned int Processor = 0;

// GLOBAL: MSVC5_C1 0x000050b8
// ?XformedFormalList@@3PAVDLSymbolList_t@@A
// class DLSymbolList_t *XformedFormalList

// GLOBAL: MSVC5_C1 0x000050bc
// ?I_pchfp@@3PAU_iobuf@@A
// GLOBAL: C1 0x00466490
FILE *I_pchfp = NULL;

// GLOBAL: MSVC5_C1 0x000050c0
// ?Stack_depth@@3HA
// int Stack_depth

// GLOBAL: MSVC5_C1 0x000050c8
// ?m_allocator@?$SAClass@VSymbolAllocator_t@@$00@@0USubAllocator@VirtualHeap@@A
// GLOBAL: C1 0x004664a0
template <>
VirtualHeap::SubAllocator SAClass<SymbolAllocator_t>::m_allocator = {};

// GLOBAL: MSVC5_C1 0x000050d8
// ?WarnIsError@@3HA
// GLOBAL: C1 0x004664c4
int WarnIsError = 0;

// GLOBAL: MSVC5_C1 0x000050dc
// ?pSymBitTemp@@3PAVSymbol_t@@A
// class Symbol_t *pSymBitTemp

// GLOBAL: MSVC5_C1 0x000050e0
// ?Leave@@3PAUs_stack@@A
// struct s_stack *Leave

// GLOBAL: MSVC5_C1 0x000050e4
// ?pIPM@@3PAUIncrParseMgr@@A
// struct IncrParseMgr *pIPM

// GLOBAL: MSVC5_C1 0x000050e8
// ?CurrentDateTime@@3PADA
// char *CurrentDateTime

// GLOBAL: MSVC5_C1 0x00005104
// ?Nologo@@3HA
// GLOBAL: C1 0x004664f4
bool32 Nologo = FALSE;

// GLOBAL: MSVC5_C1 0x00005108
// ?Asm_opt@@3HA
// int Asm_opt

// GLOBAL: MSVC5_C1 0x0000510c
// ?Cmd_ShowBehaviorChanges@@3HA
// int Cmd_ShowBehaviorChanges

// GLOBAL: MSVC5_C1 0x00005110
// ?FATFlg@@3HA
// int FATFlg

// GLOBAL: MSVC5_C1 0x00005114
// ?CurFuncExOff@@3JA
// long CurFuncExOff

// GLOBAL: MSVC5_C1 0x00005118
// ?gNoToken@@3VToken@@A
// class Token gNoToken

// GLOBAL: MSVC5_C1 0x00005138
// ?StringBuffer@@3PAEA
// unsigned char *StringBuffer

// GLOBAL: MSVC5_C1 0x0000593c
// ?MF_inlinefunc@@3PAUs_memfile@@A
// struct s_memfile *MF_inlinefunc

// FUNCTION: MSVC5_C1 0x0001f5e0
// _$E33
// static

// FUNCTION: MSVC5_C1 0x0001f5f0
// _$E30
// static

// FUNCTION: MSVC5_C1 0x0001f630
// _$E32
// static

// FUNCTION: MSVC5_C1 0x0001f640
// _$E31
// static

// FUNCTION: MSVC5_C1 0x0001f650
// _$E38
// static

// FUNCTION: MSVC5_C1 0x0001f660
// _$E35
// static

// FUNCTION: MSVC5_C1 0x0001f6a0
// _$E37
// static

// FUNCTION: MSVC5_C1 0x0001f6b0
// _$E36
// static

// FUNCTION: MSVC5_C1 0x0001f6c0
// _$E43
// static

// FUNCTION: MSVC5_C1 0x0001f6d0
// _$E40
// static

// FUNCTION: MSVC5_C1 0x0001f710
// _$E42
// static

// FUNCTION: MSVC5_C1 0x0001f720
// _$E41
// static

// FUNCTION: MSVC5_C1 0x0001f730
// _$E48
// static

// FUNCTION: MSVC5_C1 0x0001f740
// _$E45
// static

// FUNCTION: MSVC5_C1 0x0001f780
// _$E47
// static

// FUNCTION: MSVC5_C1 0x0001f790
// _$E46
// static

// FUNCTION: MSVC5_C1 0x0001f7a0
// _$E53
// static

// FUNCTION: MSVC5_C1 0x0001f7b0
// _$E50
// static

// FUNCTION: MSVC5_C1 0x0001f7f0
// _$E52
// static

// FUNCTION: MSVC5_C1 0x0001f800
// _$E51
// static

// FUNCTION: MSVC5_C1 0x0001f810
// _$E58
// static

// FUNCTION: MSVC5_C1 0x0001f820
// _$E55
// static

// FUNCTION: MSVC5_C1 0x0001f860
// _$E57
// static

// FUNCTION: MSVC5_C1 0x0001f870
// _$E56
// static

// FUNCTION: MSVC5_C1 0x0001f880
// _$E63
// static

// FUNCTION: MSVC5_C1 0x0001f890
// _$E60
// static

// FUNCTION: MSVC5_C1 0x0001f8d0
// _$E62
// static

// FUNCTION: MSVC5_C1 0x0001f8e0
// _$E61
// static

// FUNCTION: MSVC5_C1 0x0001f8f0
// _$E68
// static

// FUNCTION: MSVC5_C1 0x0001f900
// _$E65
// static

// FUNCTION: MSVC5_C1 0x0001f940
// _$E67
// static

// FUNCTION: MSVC5_C1 0x0001f950
// _$E66
// static

// FUNCTION: MSVC5_C1 0x0001f960
// _$E71
// static

// FUNCTION: MSVC5_C1 0x0001f970
// _$E70
// static

// FUNCTION: MSVC5_C1 0x0001f980
// _$E74
// static

// FUNCTION: MSVC5_C1 0x0001f990
// _$E73
// static

// FUNCTION: MSVC5_C1 0x0001f9b0
// _$E77
// static

// FUNCTION: MSVC5_C1 0x0001f9c0
// _$E76
// static

// FUNCTION: MSVC5_C1 0x0001f9d0
// _$E80
// static

// FUNCTION: MSVC5_C1 0x0001f9e0
// _$E79
// static

// FUNCTION: MSVC5_C1 0x0001f9f0
// _$E85
// static

// FUNCTION: MSVC5_C1 0x0001fa00
// _$E82
// static

// FUNCTION: MSVC5_C1 0x0001fa30
// _$E84
// static

// FUNCTION: MSVC5_C1 0x0001fa40
// _$E83
// static

// FUNCTION: MSVC5_C1 0x0001fa50
// _$E90
// static

// FUNCTION: MSVC5_C1 0x0001fa60
// _$E87
// static

// FUNCTION: MSVC5_C1 0x0001fa90
// _$E89
// static

// FUNCTION: MSVC5_C1 0x0001faa0
// _$E88
// static

// FUNCTION: MSVC5_C1 0x0001fab0
// _$E93
// static

// FUNCTION: MSVC5_C1 0x0001fac0
// _$E92
// static

// FUNCTION: MSVC5_C1 0x0001fad0
// _$E96
// static

// FUNCTION: MSVC5_C1 0x0001fae0
// _$E95
// static

// FUNCTION: MSVC5_C1 0x0001faf0
// _$E99
// static

// FUNCTION: MSVC5_C1 0x0001fb00
// _$E98
// static

// FUNCTION: MSVC5_C1 0x0001fb10
// _$E102
// static

// FUNCTION: MSVC5_C1 0x0001fb20
// _$E101
// static

// FUNCTION: MSVC5_C1 0x0001fb30
// _$E105
// static

// FUNCTION: MSVC5_C1 0x0001fb40
// _$E104
// static

// FUNCTION: MSVC5_C1 0x0001fb50
// _$E108
// static

// FUNCTION: MSVC5_C1 0x0001fb60
// _$E107
// static

// FUNCTION: MSVC5_C1 0x0001fb70
// _$E111
// static

// FUNCTION: MSVC5_C1 0x0001fb80
// _$E110
// static

// FUNCTION: MSVC5_C1 0x0001fb90
// _$E114
// static

// FUNCTION: MSVC5_C1 0x0001fba0
// _$E113
// static

// FUNCTION: MSVC5_C1 0x0001fbb0
// _$E117
// static

// FUNCTION: MSVC5_C1 0x0001fbc0
// _$E116
// static
// GLOBAL: C1 0x00455230
s_cmd_line_warning_t CmdLineWarningList[] = {
    { 1, 5 },
    { 49, 5 },
    { 69, 5 },
    { 611, 5 },
    { 226, 14 },
    { 233, 14 },
    { 234, 14 },
    { 235, 14 },
    { 168, 5 },
    { 169, 5 },
    { 0, 0 },
};

// GLOBAL: C1 0x00454d50
const subtab Ztab[] = {
    { 'a', 0x5,  &PchC.p_Extension, },
    { 'e', 0x1,  &PchC.p_Extension, },
    { 'E', 0x1,  &PchC.p_option_ZE, },
    { 'i', 0x1,  &PchC.p_Symbolic_debug_holder, },
    { '7', 0x1,  &C7CompatCVInfo, },
    { 'n', 0x1,  &gOption_Zn, },
    { 'f', 0x1,  &gOption_Zf, },
    { 'g', 0x1,  &Out_funcdef, },
    { 'p', 0x1,  (bool32 *)&Cmd_pack_size, },
    { 'I', 0x1,  &gOption_ZI, },
    { 0 },
};

// GLOBAL: C1 0x00454dd8
/**
 *
 */
const cmdtab_s cmdtab[] = {
    { "@$", { &DummyArg }, TRUE, 0x22, },
    { "-nologo", { &Nologo }, TRUE, 0x01, },
    { "-FAT", { &gOption_FAT }, TRUE, 0x01, },
    { "-pc#", { &Path_chars }, TRUE, 0x22, },
    { "-pf", { &PchC.p_option_pf }, TRUE, 0x01, },
    { "-C", { &Cflag }, TRUE, 0x01, },
    { "-D#", { &listDefs }, TRUE, 0x26, },
    { "-E", { &Prep }, TRUE, 0x01, },
    { "-I#", { &listIncludes }, TRUE, 0x26, },
    { "-FI#", { &listForcedIncludes }, TRUE, 0x26, },
    { "-EP", { &PchC.p_NoPoundLines }, TRUE, 0x01, },
    { "-Fi#", { &StdoutFile }, TRUE, 0x22, },
    { "-f", { &Input_file }, TRUE, 0x22, },
    { "-J", { &PchC.p_JFlag }, TRUE, 0x01, },
    { "-Jd", { &PchC.p_JdFlag }, TRUE, 0x01, },
    { "-Bd%", { &PchC.p_option_Bd }, TRUE, 0x01, },
    { "-Bu#", { &PchC.p_option_Bu }, TRUE, 0x24, },
    { "-Bm#", { &MemoryStatsLevel }, TRUE, 0x24, },
    { "-Bvb#", { &Cmd_Zm }, TRUE, 0x24, },
    { "-Bvm#", { &Cmd_Zm }, TRUE, 0x24, },
    { "-Zm#", { &Cmd_Zm }, TRUE, 0x24, },
    { "-Brepro", { &PchC.p_fReproduceable }, TRUE, 0x01, },
    { "-MT", { &PchC.p_MTFlag }, TRUE, 0x01, },
    { "-MD", { &PchC.p_MDFlag }, TRUE, 0x01, },
    { "-WX", { &WarnIsError }, TRUE, 0x01, },
    { "-W#", { &Warn_level }, TRUE, 0x24, },
    { "-Zp", { &Cmd_pack_size }, TRUE, 0x01, },
    { "-Zp#", { &Cmd_pack_size }, TRUE, 0x24, },
    { "-ZBe", { &PchC.p_BigIntExtension }, TRUE, 0x01, },
    { "-ZB", { &PchC.p_SizeOfBigInt }, TRUE, 0x01, },
    { "-ZB*", { &PchC.p_SizeOfBigInt }, TRUE, 0x24, },
    { "-Z*", { &Ztab }, TRUE, 0x23, },
    { "-ef#", { &gDiagnostic_messages_path }, TRUE, 0x22, },
    { "-il$", { &Basename }, TRUE, 0x22, },
    { "-xc", { &Cross_compile }, TRUE, 0x01, },
    { "-V#", { &Version }, TRUE, 0x22, },
    { "-Gs", { &PchC.p_Cmd_stack_check }, TRUE, 0x05, },
    { "-Gc", { &PchC.p_GcFlag }, TRUE, 0x01, },
    { "-Gr", { &PchC.p_Cmd_fastcall }, TRUE, 0x01, },
    { "-Gd", { &PchC.p_Cmd_cdecl }, TRUE, 0x01, },
    { "-Gz", { &PchC.p_Cmd_stdcall }, TRUE, 0x01, },
    { "-Gi", { &PchC.p_Cmd_fICC }, TRUE, 0x01, },
    { "-GI", { &PchC.p_Cmd_GI }, TRUE, 0x01, },
    { "-GFR", { &PchC.p_Cmd_fICCBrowse }, TRUE, 0x01, },
    { "-GFR-", { &PchC.p_Cmd_fICCBrowse }, TRUE, 0x05, },
    { "-NV#", { &NVStr }, TRUE, 0x22, },
    { "-Fr#", { &SourceBrowserNamFlg }, TRUE, 0x22, },
    { "-FR#", { &SourceBrowserExt }, TRUE, 0x22, },
    { "-Fj", { &gOption_Fj }, TRUE, 0x01, },
    { "-Fd#", { &szPDBName }, TRUE, 0x22, },
    { "-Fo*", { &OutFil }, TRUE, 0x22, },
    { "-Gf", { &PchC.p_Cmd_StrPool }, TRUE, 0x01, },
    { "-GF", { &PchC.p_Cmd_ROStrPool }, TRUE, 0x01, },
    { "-cbstring", { &PchC.p_CodeBasedStrings }, TRUE, 0x01, },
    { "-Oa", { &PchC.p_option_Oa }, TRUE, 0x01, },
    { "-Ob#", { &PchC.p_option_Ob }, TRUE, 0x24, },
    { "-Oi", { &PchC.p_Cmd_intrinsic }, TRUE, 0x01, },
    { "-Og", { &PchC.p_OptFlgGlobCse }, TRUE, 0x01, },
    { "-Op", { &PchC.p_option_Op }, TRUE, 0x01, },
    { "-Os", { &PchC.p_OptFlgSpeed }, TRUE, 0x05, },
    { "-Ot", { &PchC.p_OptFlgSpeed }, TRUE, 0x01, },
    { "-Ow", { &PchC.p_option_Ow }, TRUE, 0x01, },
    { "-Oq", { &PchC.p_Cmd_Option_Oq }, TRUE, 0x01, },
    { "-Ov", { &PchC.p_option_Ov }, TRUE, 0x01, },
    { "-Oy", { &PchC.p_OptFlgFrame }, TRUE, 0x01, },
    { "-C8MODE", { &PchC.p_option_C8MODE }, TRUE, 0x01, },
    { "-debugBreak%", { &Cmd_DebugBreak }, TRUE, 0x01, },
    { "-Times%", { &Cmd_Times }, TRUE, 0x01, },
    { "-Yu*", { &PchUFile }, TRUE, 0x22, },
    { "-Yu", { &PchUFlag }, TRUE, 0x01, },
    { "-Yc*", { &PchCFile }, TRUE, 0x22, },
    { "-Yc", { &PchCFlag }, TRUE, 0x01, },
    { "-Yd", { &PchC.p_PchDFlag }, TRUE, 0x01, },
    { "-Fp#", { &PchPFile }, TRUE, 0x22, },
    { "-YX*", { &gYX_arg_path }, TRUE, 0x22, },
    { "-YX", { &gOption_YX }, TRUE, 0x01, },
    { "-Yl*", { &szCmd_Ylstring }, TRUE, 0x22, },
    { "-BNOPPCH", { &fPersistentPch }, TRUE, 0x05, },
    { "-noexpinl", { &Cmd_NoExportInlines }, TRUE, 0x01, },
    { "-GM", { &PchC.p_option_GM }, TRUE, 0x01, },
    { "-G#", { &PchC.p_Cmd_processor }, TRUE, 0x24, },
    { "-BMOVE", { &gOption_BMOVE }, TRUE, 0x01, },
    { "-C9IL", { &PchC.p_Cmd_C9IL }, TRUE, 0x01, },
    { "-SplitPdbs", { &PchC.p_Cmd_splitPdbs }, TRUE, 0x01, },
    { "-SplitPdbs-", { &PchC.p_Cmd_splitPdbs }, TRUE, 0x05, },
    { "-NoEHForNew", { &PchC.p_option_NoEHForNew }, TRUE, 0x01, },
    { "-Bshow_incl", { &ShowIncludes }, TRUE, 0x01, },
    { "*", { &Unknown_ }, FALSE, 0x22, },
    { 0 }
};

// GLOBAL: C1 0x0045c58c
bool32 p_Embed_debug = FALSE;

// GLOBAL: C1 0x0045c4c8
const char *gYX_arg_path = NULL;

// GLOBAL: C1 0x0045c4c4
bool32 gOption_YX = FALSE;

// GLOBAL: C1 0x004664fc
bool32 gOption_FAT = FALSE;

// GLOBAL: C1 0x00467038
int Cmd_Zm = FALSE;

// GLOBAL: C1 0x0045c504
bool32 gOption_Fj = FALSE;

// GLOBAL: C1 0x0045cb28
bool32 gOption_BMOVE = FALSE;

// GLOBAL: C1 0x00460a28
bool32 gOption_Zn = FALSE;

// GLOBAL: C1 0x0046603c
bool32 gOption_Zf = FALSE;

// GLOBAL: C1 0x00460a10
bool32 gOption_ZI = FALSE;

// FIXME: globals.[ch] contains names ILSink objects
// GLOBAL: C1 0x004609b0
ILSink ils_UNK004609b0;

// FIXME: globals.[ch] contains names ILSink objects
// GLOBAL: C1 0x00465fb0
ILSink ils_UNK00465fb0;
