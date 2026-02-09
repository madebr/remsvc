#include "globals.h"

#include "decomp.h"
#include "nheapall.h"

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
// int MemoryStatsLevel

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
// unsigned char *PchPFile

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
// int PchMustCreate

// GLOBAL: MSVC5_C1 0x00001338
// ?PchFileNameFromCmdLine@@3HA
// int PchFileNameFromCmdLine

// GLOBAL: MSVC5_C1 0x0000133c
// ?fPersistentPch@@3HA
// GLOBAL: C1 0x0045c4e8
bool32 fPersistentPch = TRUE;

// GLOBAL: MSVC5_C1 0x00001340
// ?PchReuseCVTypes@@3HA
// int PchReuseCVTypes

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
// char *NVStr

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
// char *OutFil

// GLOBAL: MSVC5_C1 0x00001368
// ?szPDBName@@3PADA
// GLOBAL: C1 0x0045c50c
const char *szPDBName = "vc40.pdb";

// GLOBAL: MSVC5_C1 0x0000136c
// ?StunDepth@@3HA
// int StunDepth

// GLOBAL: MSVC5_C1 0x00001370
// ?Warn_level@@3HA
// int Warn_level

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
// char *Path_chars

// GLOBAL: MSVC5_C1 0x000013a4
// ?Basename@@3PADA
// char *Basename

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
// int Cmd_NoExportInlines

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
// int fReusePersistPch

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
// class ILSink ilsGSym

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
// class ILSink ilsDB

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
// class ILSink ilsExp

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
// char *Version

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
// GLOBAL: C1 0x00466118
list<void *> *listForcedIncludes;

// GLOBAL: MSVC5_C1 0x00004b54
// ?ShowIncludes@@3HA
// int ShowIncludes

// GLOBAL: MSVC5_C1 0x00004b58
// ?ilsLSym@@3VILSink@@A
// class ILSink ilsLSym

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
// char *StdoutFile

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
// struct _iobuf *I_Eoutput

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
// char *SourceBrowserNam

// GLOBAL: MSVC5_C1 0x00004df8
// ?BadInternalClassErrors@@3HA
// int BadInternalClassErrors

// GLOBAL: MSVC5_C1 0x00004dfc
// ?crc32ClCmd@@3VCRC32@@A
// GLOBAL: C1 0x004662d0
CRC32 crc32ClCmd;

// GLOBAL: MSVC5_C1 0x00004e00
// ?SourceBrowserExt@@3PADA
// char *SourceBrowserExt

// GLOBAL: MSVC5_C1 0x00004e08
// ?ilsInit@@3VILSink@@A
// class ILSink ilsInit

// GLOBAL: MSVC5_C1 0x00004f38
// ?fGenPersistPch@@3HA
// int fGenPersistPch

// GLOBAL: MSVC5_C1 0x00004f3c
// ?Cmd_inlineparsing@@3HA
// int Cmd_inlineparsing

// GLOBAL: MSVC5_C1 0x00004f40
// ?Prep@@3HA
// GLOBAL: C1 0x00466314
bool32 Prep = FALSE;

// GLOBAL: MSVC5_C1 0x00004f44
// ?SourceBrowserNamFlg@@3PADA
// char *SourceBrowserNamFlg

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
// struct FESigMgr *pSigMgr

// GLOBAL: MSVC5_C1 0x00004fd4
// ?CurrentDate@@3PADA
// char *CurrentDate

// GLOBAL: MSVC5_C1 0x00004fd8
// ?PchOldUFlag@@3HA
// int PchOldUFlag

// GLOBAL: MSVC5_C1 0x00004fdc
// ?TmpTypeIndex@@3HA
// int TmpTypeIndex

// GLOBAL: MSVC5_C1 0x00004fe0
// ?Exit_label@@3PAUs_tree@@A
// struct s_tree *Exit_label

// GLOBAL: MSVC5_C1 0x00004fe4
// ?PchOldUFile@@3PAEA
// unsigned char *PchOldUFile

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
// unsigned long CurFuncNumExNodes

// GLOBAL: MSVC5_C1 0x00005078
// ?Cflag@@3HA
// int Cflag

// GLOBAL: MSVC5_C1 0x0000507c
// ?I_stdoutfp@@3PAU_iobuf@@A
// struct _iobuf *I_stdoutfp

// GLOBAL: MSVC5_C1 0x00005080
// ?I_sbrfp@@3PAU_iobuf@@A
// struct _iobuf *I_sbrfp

// GLOBAL: MSVC5_C1 0x00005084
// ?Nerrors@@3HA
// GLOBAL: C1 0x
int Nerrors = 0;

// GLOBAL: MSVC5_C1 0x00005088
// ?BdFlg@@3HA
// int BdFlg

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
// int Cross_compile

// GLOBAL: MSVC5_C1 0x000050b4
// ?Processor@@3HA
// int Processor

// GLOBAL: MSVC5_C1 0x000050b8
// ?XformedFormalList@@3PAVDLSymbolList_t@@A
// class DLSymbolList_t *XformedFormalList

// GLOBAL: MSVC5_C1 0x000050bc
// ?I_pchfp@@3PAU_iobuf@@A
// struct _iobuf *I_pchfp

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
// int WarnIsError

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
// int Nologo

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

// GLOBAL: C1 0x00454dd8
cmdtab_s cmdtab[] = {
    // { "@$", { &gOption_rsp_path }, true, 0x22, },
    // { "-nologo", { &gOption_nologo }, true, 0x01, },
    // { "-FAT", { &gOption_FAT }, true, 0x01, },
    // { "-pc#", { &gOption_pc_map }, true, 0x22, },
    // { "-pf", { &PchC.option_pf }, true, 0x01, },
    // { "-C", { &Cflag }, true, 0x01, },
    // { "-D#", { &listDefs }, true, 0x26, },
    // { "-E", { &Prep }, true, 0x01, },
    // { "-I#", { &listIncludes }, true, 0x26, },
    // { "-FI#", { &listForcedIncludes }, true, 0x26, },
    // { "-EP", { &PchC.p_NoPoundLines }, true, 0x01, },
    // { "-Fi#", { &gOption_Fi_path }, true, 0x22, },
    // { "-f", { &Input_file }, true, 0x22, },
    // { "-J", { &PchC.option_J }, true, 0x01, },
    // { "-Jd", { &PchC.option_Jd }, true, 0x01, },
    // { "-Bd%", { &PchC.option_Bd }, true, 0x01, },
    // { "-Bu#", { &PchC.option_Bu }, true, 0x24, },
    // { "-Bm#", { &MemoryStatsLevel }, true, 0x24, },
    // { "-Bvb#", { &gOption_memory }, true, 0x24, },
    // { "-Bvm#", { &gOption_memory }, true, 0x24, },
    // { "-Zm#", { &gOption_memory }, true, 0x24, },
    // { "-Brepro", { &PchC.p_fReproduceable }, true, 0x01, },
    // { "-MT", { &PchC.option_MT }, true, 0x01, },
    // { "-MD", { &PchC.option_MD }, true, 0x01, },
    // { "-WX", { &WarnIsError }, true, 0x01, },
    // { "-W#", { &gOption_W }, true, 0x24, },
    // { "-Zp", { &gOption_Zp }, true, 0x01, },
    // { "-Zp#", { &gOption_Zp }, true, 0x24, },
    // { "-ZBe", { &PchC.p_BigIntExtension }, true, 0x01, },
    // { "-ZB", { &PchC.p_SizeOfBigInt }, true, 0x01, },
    // { "-ZB*", { &PchC.p_SizeOfBigInt }, true, 0x24, },
    // { "-Z*", { &Ztab }, true, 0x23, },
    // { "-ef#", { &gDiagnostic_messages_path }, true, 0x22, },
    // { "-il$", { &Basename }, true, 0x22, },
    // { "-xc", { &gOption_xc }, true, 0x01, },
    // { "-V#", { &gOption_V_path }, true, 0x22, },
    // { "-Gs", { &PchC.option_Gs }, true, 0x05, },
    // { "-Gc", { &PchC.option_Gc }, true, 0x01, },
    // { "-Gr", { &PchC.option_Gr }, true, 0x01, },
    // { "-Gd", { &PchC.option_Gd }, true, 0x01, },
    // { "-Gz", { &PchC.option_Gz }, true, 0x01, },
    // { "-Gi", { &PchC.option_Gi }, true, 0x01, },
    // { "-GI", { &PchC.option_GI }, true, 0x01, },
    // { "-GFR", { &PchC.p_Cmd_fICCBrowse }, true, 0x01, },
    // { "-GFR-", { &PchC.p_Cmd_fICCBrowse }, true, 0x05, },
    // { "-NV#", { &gOption_NV_path }, true, 0x22, },
    // { "-Fr#", { &SourceBrowserNamFlg }, true, 0x22, },
    // { "-FR#", { &SourceBrowserExt }, true, 0x22, },
    // { "-Fj", { &gOption_Fj }, true, 0x01, },
    // { "-Fd#", { &gPDB_arg_path }, true, 0x22, },
    // { "-Fo*", { &gObject_output_arg_path }, true, 0x22, },
    // { "-Gf", { &PchC.option_Gf }, true, 0x01, },
    // { "-GF", { &PchC.option_GF }, true, 0x01, },
    // { "-cbstring", { &PchC.option_cbstring }, true, 0x01, },
    // { "-Oa", { &PchC.option_Oa }, true, 0x01, },
    // { "-Ob#", { &gOption_Ob }, true, 0x24, },
    // { "-Oi", { &PchC.option_Oi }, true, 0x01, },
    // { "-Og", { &PchC.option_Og }, true, 0x01, },
    // { "-Op", { &PchC.option_Op }, true, 0x01, },
    // { "-Os", { &PchC.option_Ot }, true, 0x05, },
    // { "-Ot", { &PchC.option_Ot }, true, 0x01, },
    // { "-Ow", { &PchC.option_Ow }, true, 0x01, },
    // { "-Oq", { &PchC.option_Oq }, true, 0x01, },
    // { "-Ov", { &PchC.option_Ov }, true, 0x01, },
    // { "-Oy", { &PchC.option_Oy }, true, 0x01, },
    // { "-C8MODE", { &PchC.option_C8MODE }, true, 0x01, },
    // { "-debugBreak%", { &gOption_debugBreak }, true, 0x01, },
    // { "-Times%", { &gPrint_timings }, true, 0x01, },
    // { "-Yu*", { &PchUFile }, true, 0x22, },
    // { "-Yu", { &PchUFlag }, true, 0x01, },
    // { "-Yc*", { &PchCFile }, true, 0x22, },
    // { "-Yc", { &PchCFlag }, true, 0x01, },
    // { "-Yd", { &PchC.p_PchDFlag }, true, 0x01, },
    // { "-Fp#", { &PchPFile }, true, 0x22, },
    // { "-YX*", { &gYX_arg_path }, true, 0x22, },
    // { "-YX", { &gOption_YX }, true, 0x01, },
    // { "-Yl*", { &gYl_arg_path }, true, 0x22, },
    // { "-BNOPPCH", { &fPersistentPch }, true, 0x05, },
    // { "-noexpinl", { &gOption_noexpinl }, true, 0x01, },
    // { "-GM", { &PchC.option_GM }, true, 0x01, },
    // { "-G#", { &PchC.option_G }, true, 0x24, },
    // { "-BMOVE", { &gOption_BMOVE }, true, 0x01, },
    // { "-C9IL", { &PchC.option_C9IL }, true, 0x01, },
    // { "-SplitPdbs", { &PchC.p_Cmd_splitPdbs }, true, 0x01, },
    // { "-SplitPdbs-", { &PchC.p_Cmd_splitPdbs }, true, 0x05, },
    // { "-NoEHForNew", { &PchC.option_NoEHForNew }, true, 0x01, },
    // { "-Bshow_incl", { &gOption_BShowIncl }, true, 0x01, },
    // { "*", { &Unknown }, false, 0x22, },
    { 0 }
};

// GLOBAL: C1 0x0045c58c
bool32 p_Embed_debug = FALSE;

// GLOBAL: C1 0x0045c4c8
const char *gYX_arg_path = NULL;

// GLOBAL: C1 0x0045c4c4
bool32 gOption_YX = FALSE;
