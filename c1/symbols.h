#ifndef SYMBOLS_H
#define SYMBOLS_H
// ?LocalStaticAliases@@3PAUs_dict_t@@A
// struct s_dict_t *LocalStaticAliases

// ?sizeSymAlloc@@3PAIA
// unsigned int *sizeSymAlloc

// ?symFreelistIndex@@3PAW4SymbolFreelistKind_t@@A
// enum SymbolFreelistKind_t *symFreelistIndex

// ??_C@_07EHPK@__seg__?$AA@
// "__seg__"

// ?rm_btmod@@YAPAVType_t@@PAV1@G@Z
// class Type_t * __cdecl rm_btmod(class Type_t *, unsigned short)

// ?NonDestructiveRmBtMod@@YAXPAVSymbol_t@@G@Z
// void __cdecl NonDestructiveRmBtMod(class Symbol_t *, unsigned short)

// ?MergeSclassFlags@@YAHPAUs_class@@U1@@Z
// int __cdecl MergeSclassFlags(struct s_class *, struct s_class)

// ?ForceDataInit@@YAXPAVSymbol_t@@@Z
// void __cdecl ForceDataInit(class Symbol_t *)

// ?DeclareSymbol@@YAPAVSymbol_t@@PAUs_declspec@@PAV1@PBVGrammarTypeBuilder@@@Z
// class Symbol_t * __cdecl DeclareSymbol(struct s_declspec *, class Symbol_t *, class GrammarTypeBuilder const *)

// ?AttributeSymbol@@YAPAVSymbol_t@@PAUs_declspec@@PAV1@PBVGrammarTypeBuilder@@@Z
// class Symbol_t * __cdecl AttributeSymbol(struct s_declspec *, class Symbol_t *, class GrammarTypeBuilder const *)

// ?W40_warning@@YAXPAVSymbol_t@@@Z
// void __cdecl W40_warning(class Symbol_t *)

// ?AllocateSymbol@@YAXPAVSymbol_t@@@Z
// void __cdecl AllocateSymbol(class Symbol_t *)

// ?modRemoveMemMods@@YAGGPAVSymbol_t@@@Z
// unsigned short __cdecl modRemoveMemMods(unsigned short, class Symbol_t *)

// ?same_mods@@YAHGGPAVSymbol_t@@PBVGrammarTypeBuilder@@@Z
// int __cdecl same_mods(unsigned short, unsigned short, class Symbol_t *, class GrammarTypeBuilder const *)

// ?cbFormals@@YAKPAUs_flist@@@Z
// unsigned long __cdecl cbFormals(struct s_flist *)

// ?CheckEntryAgainstSymbol@@YAPAVSymbol_t@@PAV1@0PBVGrammarTypeBuilder@@@Z
// class Symbol_t * __cdecl CheckEntryAgainstSymbol(class Symbol_t *, class Symbol_t *, class GrammarTypeBuilder const *)

// ?ToLevel0@@YAXPAVSymbol_t@@@Z
// void __cdecl ToLevel0(class Symbol_t *)

// ?chk_entry@@YAXPAVSymbol_t@@0@Z
// void __cdecl chk_entry(class Symbol_t *, class Symbol_t *)

// ?dereg@@YAXXZ
// void __cdecl dereg(void)

// ?redefined@@YAHPAVSymbol_t@@0PBVGrammarTypeBuilder@@@Z
// int __cdecl redefined(class Symbol_t *, class Symbol_t *, class GrammarTypeBuilder const *)

// ?same_btype@@YAHGG@Z
// int __cdecl same_btype(unsigned short, unsigned short)

// ?same_class@@YAHPAVSymbol_t@@0@Z
// int __cdecl same_class(class Symbol_t *, class Symbol_t *)

// ?IsFunctionArg@@YAHPAVType_t@@@Z
// int __cdecl IsFunctionArg(class Type_t *)

// ?f_declaration@@YAPAVType_t@@PAV1@0HHH@Z
// class Type_t * __cdecl f_declaration(class Type_t *, class Type_t *, int, int, int)

// ?ErrorInIndirection@@YAHPAVSymbol_t@@0PAVType_t@@PBVGrammarTypeBuilder@@@Z
// int __cdecl ErrorInIndirection(class Symbol_t *, class Symbol_t *, class Type_t *, class GrammarTypeBuilder const *)

// ?CmpCaseIns@@YAHPBD0@Z
// int __cdecl CmpCaseIns(char const *, char const *)

// ?new_sbr_key@@YAKXZ
// unsigned long __cdecl new_sbr_key(void)

// ?AllocSegment@@YAPAVSymbol_t@@PAUId_t@@0KE@Z
// class Symbol_t * __cdecl AllocSegment(struct Id_t *, struct Id_t *, unsigned long, unsigned char)

// ?InitDefaultSymbols@@YAXXZ
// void __cdecl InitDefaultSymbols(void)

// ?strendswith@@YAHPAD0@Z
// int __cdecl strendswith(char *, char *)

// ?NewSegment@@YAPAVSymbol_t@@PAUId_t@@0EH@Z
// class Symbol_t * __cdecl NewSegment(struct Id_t *, struct Id_t *, unsigned char, int)

// ?EnsureSegVarForSegment@@YAXPAVSymbol_t@@@Z
// void __cdecl EnsureSegVarForSegment(class Symbol_t *)

// ?GetIdForSegVarForSegment@@YAPAUId_t@@PAVSymbol_t@@@Z
// struct Id_t * __cdecl GetIdForSegVarForSegment(class Symbol_t *)

// ?same_segment@@YAXPAUId_t@@@Z
// void __cdecl same_segment(struct Id_t *)

// ?InternalEnterBlock@@YAXXZ
// void __cdecl InternalEnterBlock(void)

// ?InternalLeaveBlock@@YAXXZ
// void __cdecl InternalLeaveBlock(void)

// ?DumpPchCVInfo@@YAXXZ
// void __cdecl DumpPchCVInfo(void)

// ?InvalidateFuncLifeAliases@@YAXXZ
// void __cdecl InvalidateFuncLifeAliases(void)

// ?AddLocalStaticAlias@@YAXPAVSymbol_t@@0@Z
// void __cdecl AddLocalStaticAlias(class Symbol_t *, class Symbol_t *)

// ?GetLocalStaticAlias@@YAPAVSymbol_t@@PAV1@@Z
// class Symbol_t * __cdecl GetLocalStaticAlias(class Symbol_t *)

// ?AliasEq@@YAHPAX0@Z
// int __cdecl AliasEq(void *, void *)

// ?AliasHash@@YAIPAX@Z
// unsigned int __cdecl AliasHash(void *)

// ?SetSegmentInfoForSym@@YAXPAVSymbol_t@@0@Z
// void __cdecl SetSegmentInfoForSym(class Symbol_t *, class Symbol_t *)

// ?GetSegmentInfoForSym@@YAPAVSymbol_t@@PBV1@@Z
// class Symbol_t * __cdecl GetSegmentInfoForSym(class Symbol_t const *)

// ?FindPointersOfSegmentInfoDict@@YAXXZ
// void __cdecl FindPointersOfSegmentInfoDict(void)

// ?IdForLocalStaticData@@YAPAUId_t@@PAVSymbol_t@@@Z
// struct Id_t * __cdecl IdForLocalStaticData(class Symbol_t *)

// ?Copy@Symbol_t@@QAEXPBV1@W4lifetime_e@@@Z
// public: void __thiscall Symbol_t::Copy(class Symbol_t const *, enum lifetime_e)

// ?CreateGlobalVoidFormalSymbol@@YAPAVSymbol_t@@XZ
// class Symbol_t * __cdecl CreateGlobalVoidFormalSymbol(void)

// ?AssignUserDefinedSeg@@YAXPAVSymbol_t@@0@Z
// void __cdecl AssignUserDefinedSeg(class Symbol_t *, class Symbol_t *)

// ?SearchForSymbol@Scope_t@SymbolTableManager_t@@QBEPAVFoundSymbol_t@2@PAVSymbol_t@@@Z
// public: class SymbolTableManager_t::FoundSymbol_t * __thiscall SymbolTableManager_t::Scope_t::SearchForSymbol(class Symbol_t *) const

// ?SegmentInfo@Symbol_t@@QAEXPAV1@@Z
// public: void __thiscall Symbol_t::SegmentInfo(class Symbol_t *)

// ??2Symbol_t@@SAPAXIEW4lifetime_e@@@Z
// public: static void * __cdecl Symbol_t::operator new(unsigned int, unsigned char, enum lifetime_e)

// ?IsAnyDllLinkage@s_sclass@@QBEEXZ
// public: unsigned char __thiscall s_sclass::IsAnyDllLinkage(void) const

#endif /* SYMBOLS_H */
