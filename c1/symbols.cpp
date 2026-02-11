#include "symbols.h"

#include "decomp.h"

// GLOBAL: MSVC5_C1 0x00001404
// ?LocalStaticAliases@@3PAUs_dict_t@@A
// struct s_dict_t *LocalStaticAliases

// GLOBAL: MSVC5_C1 0x00001408
// ?sizeSymAlloc@@3PAIA
// unsigned int *sizeSymAlloc

// GLOBAL: MSVC5_C1 0x00001470
// ?symFreelistIndex@@3PAW4SymbolFreelistKind_t@@A
// enum SymbolFreelistKind_t *symFreelistIndex

// GLOBAL: MSVC5_C1 0x00003a60
// ??_C@_07EHPK@__seg__?$AA@
// "__seg__"

// FUNCTION: MSVC5_C1 0x00025ca0
// ?rm_btmod@@YAPAVType_t@@PAV1@G@Z
// class Type_t * __cdecl rm_btmod(class Type_t *, unsigned short)

// FUNCTION: MSVC5_C1 0x00025ce0
// ?NonDestructiveRmBtMod@@YAXPAVSymbol_t@@G@Z
// void __cdecl NonDestructiveRmBtMod(class Symbol_t *, unsigned short)

// FUNCTION: MSVC5_C1 0x00025d50
// ?MergeSclassFlags@@YAHPAUs_class@@U1@@Z
// int __cdecl MergeSclassFlags(struct s_class *, struct s_class)

// FUNCTION: MSVC5_C1 0x00025e80
// ?ForceDataInit@@YAXPAVSymbol_t@@@Z
// void __cdecl ForceDataInit(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00025f30
// ?DeclareSymbol@@YAPAVSymbol_t@@PAUs_declspec@@PAV1@PBVGrammarTypeBuilder@@@Z
// class Symbol_t * __cdecl DeclareSymbol(struct s_declspec *, class Symbol_t *, class GrammarTypeBuilder const *)

// FUNCTION: MSVC5_C1 0x00026140
// ?AttributeSymbol@@YAPAVSymbol_t@@PAUs_declspec@@PAV1@PBVGrammarTypeBuilder@@@Z
// class Symbol_t * __cdecl AttributeSymbol(struct s_declspec *, class Symbol_t *, class GrammarTypeBuilder const *)

// FUNCTION: MSVC5_C1 0x00026510
// ?W40_warning@@YAXPAVSymbol_t@@@Z
// void __cdecl W40_warning(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00026530
// ?AllocateSymbol@@YAXPAVSymbol_t@@@Z
// void __cdecl AllocateSymbol(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00026660
// ?modRemoveMemMods@@YAGGPAVSymbol_t@@@Z
// unsigned short __cdecl modRemoveMemMods(unsigned short, class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00026690
// ?same_mods@@YAHGGPAVSymbol_t@@PBVGrammarTypeBuilder@@@Z
// int __cdecl same_mods(unsigned short, unsigned short, class Symbol_t *, class GrammarTypeBuilder const *)

// FUNCTION: MSVC5_C1 0x000266d0
// ?cbFormals@@YAKPAUs_flist@@@Z
// unsigned long __cdecl cbFormals(struct s_flist *)

// FUNCTION: MSVC5_C1 0x00026710
// ?CheckEntryAgainstSymbol@@YAPAVSymbol_t@@PAV1@0PBVGrammarTypeBuilder@@@Z
// class Symbol_t * __cdecl CheckEntryAgainstSymbol(class Symbol_t *, class Symbol_t *, class GrammarTypeBuilder const *)

// FUNCTION: MSVC5_C1 0x000267d0
// ?ToLevel0@@YAXPAVSymbol_t@@@Z
// void __cdecl ToLevel0(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00026a10
// ?chk_entry@@YAXPAVSymbol_t@@0@Z
// void __cdecl chk_entry(class Symbol_t *, class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00026c80
// ?dereg@@YAXXZ
// void __cdecl dereg(void)

// FUNCTION: MSVC5_C1 0x00026cf0
// ?redefined@@YAHPAVSymbol_t@@0PBVGrammarTypeBuilder@@@Z
// int __cdecl redefined(class Symbol_t *, class Symbol_t *, class GrammarTypeBuilder const *)

// FUNCTION: MSVC5_C1 0x00026ea0
// ?same_btype@@YAHGG@Z
// int __cdecl same_btype(unsigned short, unsigned short)

// FUNCTION: MSVC5_C1 0x00026f30
// ?same_class@@YAHPAVSymbol_t@@0@Z
// int __cdecl same_class(class Symbol_t *, class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00027000
// ?IsFunctionArg@@YAHPAVType_t@@@Z
// int __cdecl IsFunctionArg(class Type_t *)

// FUNCTION: MSVC5_C1 0x00027020
// ?f_declaration@@YAPAVType_t@@PAV1@0HHH@Z
// class Type_t * __cdecl f_declaration(class Type_t *, class Type_t *, int, int, int)

// FUNCTION: MSVC5_C1 0x00027420
// ?ErrorInIndirection@@YAHPAVSymbol_t@@0PAVType_t@@PBVGrammarTypeBuilder@@@Z
// int __cdecl ErrorInIndirection(class Symbol_t *, class Symbol_t *, class Type_t *, class GrammarTypeBuilder const *)

// FUNCTION: MSVC5_C1 0x00027640
// ?CmpCaseIns@@YAHPBD0@Z
// int __cdecl CmpCaseIns(char const *, char const *)

// FUNCTION: MSVC5_C1 0x000276c0
// ?new_sbr_key@@YAKXZ
// unsigned long __cdecl new_sbr_key(void)

// FUNCTION: MSVC5_C1 0x000276d0
// ?AllocSegment@@YAPAVSymbol_t@@PAUId_t@@0KE@Z
// class Symbol_t * __cdecl AllocSegment(struct Id_t *, struct Id_t *, unsigned long, unsigned char)

// FUNCTION: MSVC5_C1 0x000277c0
// ?InitDefaultSymbols@@YAXXZ
// void __cdecl InitDefaultSymbols(void)

// FUNCTION: MSVC5_C1 0x00027960
// ?strendswith@@YAHPAD0@Z
// int __cdecl strendswith(char *, char *)

// FUNCTION: MSVC5_C1 0x000279e0
// ?NewSegment@@YAPAVSymbol_t@@PAUId_t@@0EH@Z
// class Symbol_t * __cdecl NewSegment(struct Id_t *, struct Id_t *, unsigned char, int)

// FUNCTION: MSVC5_C1 0x00027b80
// ?EnsureSegVarForSegment@@YAXPAVSymbol_t@@@Z
// void __cdecl EnsureSegVarForSegment(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00027ca0
// ?GetIdForSegVarForSegment@@YAPAUId_t@@PAVSymbol_t@@@Z
// struct Id_t * __cdecl GetIdForSegVarForSegment(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00027d20
// ?same_segment@@YAXPAUId_t@@@Z
// void __cdecl same_segment(struct Id_t *)

// FUNCTION: MSVC5_C1 0x00027e20
// ?InternalEnterBlock@@YAXXZ
// void __cdecl InternalEnterBlock(void)

// FUNCTION: MSVC5_C1 0x00027e90
// ?InternalLeaveBlock@@YAXXZ
// void __cdecl InternalLeaveBlock(void)

// FUNCTION: MSVC5_C1 0x00027f70
// ?DumpPchCVInfo@@YAXXZ
// void __cdecl DumpPchCVInfo(void)

// FUNCTION: MSVC5_C1 0x00027f90
// ?InvalidateFuncLifeAliases@@YAXXZ
// void __cdecl InvalidateFuncLifeAliases(void)

// FUNCTION: MSVC5_C1 0x00027fa0
// ?AddLocalStaticAlias@@YAXPAVSymbol_t@@0@Z
// void __cdecl AddLocalStaticAlias(class Symbol_t *, class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00027fe0
// ?GetLocalStaticAlias@@YAPAVSymbol_t@@PAV1@@Z
// class Symbol_t * __cdecl GetLocalStaticAlias(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00028000
// ?AliasEq@@YAHPAX0@Z
// int __cdecl AliasEq(void *, void *)

// FUNCTION: MSVC5_C1 0x00028010
// ?AliasHash@@YAIPAX@Z
// unsigned int __cdecl AliasHash(void *)

// FUNCTION: MSVC5_C1 0x00028020
// ?SetSegmentInfoForSym@@YAXPAVSymbol_t@@0@Z
// void __cdecl SetSegmentInfoForSym(class Symbol_t *, class Symbol_t *)

// FUNCTION: MSVC5_C1 0x000280b0
// ?GetSegmentInfoForSym@@YAPAVSymbol_t@@PBV1@@Z
// class Symbol_t * __cdecl GetSegmentInfoForSym(class Symbol_t const *)

// FUNCTION: MSVC5_C1 0x000280d0
// ?FindPointersOfSegmentInfoDict@@YAXXZ
// void __cdecl FindPointersOfSegmentInfoDict(void)

// FUNCTION: MSVC5_C1 0x000280f0
// ?IdForLocalStaticData@@YAPAUId_t@@PAVSymbol_t@@@Z
// struct Id_t * __cdecl IdForLocalStaticData(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00028110
// ?Copy@Symbol_t@@QAEXPBV1@W4lifetime_e@@@Z
// public: void __thiscall Symbol_t::Copy(class Symbol_t const *, enum lifetime_e)

// FUNCTION: MSVC5_C1 0x000281d0
// ?CreateGlobalVoidFormalSymbol@@YAPAVSymbol_t@@XZ
// class Symbol_t * __cdecl CreateGlobalVoidFormalSymbol(void)

// FUNCTION: MSVC5_C1 0x000282b0
// ?AssignUserDefinedSeg@@YAXPAVSymbol_t@@0@Z
// void __cdecl AssignUserDefinedSeg(class Symbol_t *, class Symbol_t *)

// FUNCTION: MSVC5_C1 0x000282f0
// ?SearchForSymbol@Scope_t@SymbolTableManager_t@@QBEPAVFoundSymbol_t@2@PAVSymbol_t@@@Z
// public: class SymbolTableManager_t::FoundSymbol_t * __thiscall SymbolTableManager_t::Scope_t::SearchForSymbol(class Symbol_t *) const

// FUNCTION: MSVC5_C1 0x00028360
// ?SegmentInfo@Symbol_t@@QAEXPAV1@@Z
// public: void __thiscall Symbol_t::SegmentInfo(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00028380
// ??2Symbol_t@@SAPAXIEW4lifetime_e@@@Z
// public: static void * __cdecl Symbol_t::operator new(unsigned int, unsigned char, enum lifetime_e)

// FUNCTION: MSVC5_C1 0x000283c0
// ?IsAnyDllLinkage@s_sclass@@QBEEXZ
// public: unsigned char __thiscall s_sclass::IsAnyDllLinkage(void) const

// FUNCTION: C1 0xFUN_0041c5d3
void FUN_0041c5d3()
{
    NOT_IMPLEMENTED();
}
