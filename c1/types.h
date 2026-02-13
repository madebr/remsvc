#ifndef TYPES_H
#define TYPES_H

#include "c1_types.h"

// ?sizeof_bt@@3PBDB
// char const *sizeof_bt

// ?UseAType@@YAPAVType_t@@PAVSymbol_t@@@Z
// class Type_t * __cdecl UseAType(class Symbol_t *)

// ?InitTypes@@YAXXZ
extern void InitTypes();

// ?check_mods@@YAGGG@Z
// unsigned short __cdecl check_mods(unsigned short, unsigned short)

// ?yyCopyType@@YAPAVType_t@@PAV1@@Z
// class Type_t * __cdecl yyCopyType(class Type_t *)

// ?yyCookType@@YAPAVType_t@@PAV1@@Z
// class Type_t * __cdecl yyCookType(class Type_t *)

// ?hash_type@@YAPAVType_t@@PAV1@@Z
extern Type_t * hash_type(Type_t *proto);

// ?hash_indir@@YAPAUs_indir@@PAU1@@Z
// struct s_indir * __cdecl hash_indir(struct s_indir *)

// ?get_funcret@@YAPAVType_t@@GPAV1@@Z
extern Type_t * get_funcret(unsigned short args, Type_t *ret_type);

// ?SkipRefIndir@@YAPAUs_indir@@PAU1@@Z
// struct s_indir * __cdecl SkipRefIndir(struct s_indir *)

// ?TypeSkipRefIndir@@YAPAVType_t@@PAV1@@Z
// class Type_t * __cdecl TypeSkipRefIndir(class Type_t *)

// ?fix_indir@@YAPAVType_t@@PAV1@GGPATu_ivalue@@@Z
// class Type_t * __cdecl fix_indir(class Type_t *, unsigned short, unsigned short, union u_ivalue *)

// ?pTypeChopRefOrPtr@@YAPAVType_t@@PAV1@@Z
// class Type_t * __cdecl pTypeChopRefOrPtr(class Type_t *)

// ?ChopFirstIndirection@@YAPAVType_t@@PAV1@@Z
// class Type_t * __cdecl ChopFirstIndirection(class Type_t *)

// ?TypeSansFirstIndir@@YAPAVType_t@@PAV1@@Z
// class Type_t * __cdecl TypeSansFirstIndir(class Type_t *)

// ?TypeSansConstVolMods@@YAPAVType_t@@PAV1@@Z
// class Type_t * __cdecl TypeSansConstVolMods(class Type_t *)

// ?ChangeFabPFunc@@YAPAVType_t@@PAV1@H@Z
// class Type_t * __cdecl ChangeFabPFunc(class Type_t *, int)

// ?pTypeAddPFunc@@YAPAVType_t@@PAV1@@Z
// class Type_t * __cdecl pTypeAddPFunc(class Type_t *)

// ?pTypeAddTmpIndir@@YAPAVType_t@@PAV1@GGPATu_ivalue@@@Z
// class Type_t * __cdecl pTypeAddTmpIndir(class Type_t *, unsigned short, unsigned short, union u_ivalue *)

// ?add_indir@@YAPAVType_t@@PAV1@GGPATu_ivalue@@@Z
// class Type_t * __cdecl add_indir(class Type_t *, unsigned short, unsigned short, union u_ivalue *)

// ?PtypePtrToType@@YAPAVType_t@@GPAV1@@Z
// class Type_t * __cdecl PtypePtrToType(unsigned short, class Type_t *)

// ?AddTmpSegmentIndir@@YAXPAVSymbol_t@@0@Z
// void __cdecl AddTmpSegmentIndir(class Symbol_t *, class Symbol_t *)

// ?AddSegmentIndir@@YAXPAVSymbol_t@@0@Z
// void __cdecl AddSegmentIndir(class Symbol_t *, class Symbol_t *)

// ?copy_type@@YAPAVType_t@@PAV1@@Z
// class Type_t * __cdecl copy_type(class Type_t *)

// ?new_indir@@YAPAUs_indir@@GGPATu_ivalue@@@Z
// struct s_indir * __cdecl new_indir(unsigned short, unsigned short, union u_ivalue *)

// ?GetHashFlistValue@@YAIPAUs_flist@@@Z
// unsigned int __cdecl GetHashFlistValue(struct s_flist *)

// ?crVoidList@@YAPAUs_flist@@XZ
// struct s_flist * __cdecl crVoidList(void)

// ?crZeroParmList@@YAPAUs_flist@@XZ
// struct s_flist * __cdecl crZeroParmList(void)

// ?create_flist@@YAPAUs_flist@@PAVDLSymbolList_t@@PAGW4FormalListKind_e@GTBFormalList@@@Z
// struct s_flist * __cdecl create_flist(class DLSymbolList_t *, unsigned short *, enum GTBFormalList::FormalListKind_e)

// ?PTypeForBT@@YAPAVType_t@@G@Z
extern Type_t * PTypeForBT(unsigned short bt);

// ?GetQualifiedIndir@@YAPAUs_indir@@PAU1@@Z
// struct s_indir * __cdecl GetQualifiedIndir(struct s_indir *)

// ?GetQualifiedIndirFromType@@YAPAUs_indir@@PAVType_t@@@Z
// struct s_indir * __cdecl GetQualifiedIndirFromType(class Type_t *)

// ?GetTypeQualifierOfUnderlyingType@@YAGPAVType_t@@@Z
// unsigned short __cdecl GetTypeQualifierOfUnderlyingType(class Type_t *)

// ?GetTypeQualifier@@YAGPAVType_t@@@Z
// unsigned short __cdecl GetTypeQualifier(class Type_t *)

// ?GetTypeWithMemMods@@YAPAVType_t@@PAV1@G@Z
// class Type_t * __cdecl GetTypeWithMemMods(class Type_t *, unsigned short)

// ?FIRStopIfNotArray@@YAHPAUs_indir@@@Z
// int __cdecl FIRStopIfNotArray(struct s_indir *)

// ?FIRStopOnPointer@@YAHPAUs_indir@@@Z
// int __cdecl FIRStopOnPointer(struct s_indir *)

// ?FIRFixClearIMODS@@YAPAUs_indir@@PAU1@@Z
// struct s_indir * __cdecl FIRFixClearIMODS(struct s_indir *)

// ?FIRFixAddConst@@YAPAUs_indir@@PAU1@@Z
// struct s_indir * __cdecl FIRFixAddConst(struct s_indir *)

// ?FIRFixAddVolatile@@YAPAUs_indir@@PAU1@@Z
// struct s_indir * __cdecl FIRFixAddVolatile(struct s_indir *)

// ?FIRFixAddUnaligned@@YAPAUs_indir@@PAU1@@Z
// struct s_indir * __cdecl FIRFixAddUnaligned(struct s_indir *)

// ?FIRFixTypeAddQualifiers@@YAPAVType_t@@PAV1@GG@Z
// class Type_t * __cdecl FIRFixTypeAddQualifiers(class Type_t *, unsigned short, unsigned short)

// ?FixIndirectionsRecursively@@YAPAUs_indir@@PAU1@P6AH0@ZP6APAU1@0@Z@Z
// struct s_indir * __cdecl FixIndirectionsRecursively(struct s_indir *, int (__cdecl *)(struct s_indir *), struct s_indir * (__cdecl *)(struct s_indir *))

// ?getTypeSansTopIndirection@Type_t@@QBEPAV1@XZ
// public: class Type_t * __thiscall Type_t::getTypeSansTopIndirection(void) const

// ?getTypePointedTo@Type_t@@QBEPAV1@XZ
// public: class Type_t * __thiscall Type_t::getTypePointedTo(void) const

// ?getElementType@Type_t@@QBEPAV1@XZ
// public: class Type_t * __thiscall Type_t::getElementType(void) const

// ?getNonArrayElementType@Type_t@@QBEPAV1@XZ
// public: class Type_t * __thiscall Type_t::getNonArrayElementType(void) const

// ?getNonBasedType@Type_t@@QBEPAV1@XZ
// public: class Type_t * __thiscall Type_t::getNonBasedType(void) const

// ?getTypeDecayToPointerToFunction@Type_t@@QBEPAV1@XZ
// public: class Type_t * __thiscall Type_t::getTypeDecayToPointerToFunction(void) const

// ?getTypeDecayArrayToPointer@Type_t@@QBEPAV1@XZ
// public: class Type_t * __thiscall Type_t::getTypeDecayArrayToPointer(void) const

// ?AddNonTypeInfo@Type_t@@QBEPAV1@PAV1@@Z
// public: class Type_t * __thiscall Type_t::AddNonTypeInfo(class Type_t *) const

// ?SubstituteCallingConvention@Type_t@@QBEPAV1@G@Z
// public: class Type_t * __thiscall Type_t::SubstituteCallingConvention(unsigned short) const

// ?getQualifiers@Type_t@@QBEGXZ
// public: unsigned short __thiscall Type_t::getQualifiers(void) const

// ?SubstituteQualifiers@Type_t@@QBEPAV1@G@Z
// public: class Type_t * __thiscall Type_t::SubstituteQualifiers(unsigned short) const

// ?SubstituteReturnType@Type_t@@QBEPAV1@PAV1@@Z
// public: class Type_t * __thiscall Type_t::SubstituteReturnType(class Type_t *) const

// ?TmpSubstituteBTMods@Type_t@@QBEPAV1@G@Z
// public: class Type_t * __thiscall Type_t::TmpSubstituteBTMods(unsigned short) const

// ?AddProperty@Type_t@@QBEPAV1@G@Z
// public: class Type_t * __thiscall Type_t::AddProperty(unsigned short) const

// ?getReturnType@Type_t@@QBEPAV1@XZ
// public: class Type_t * __thiscall Type_t::getReturnType(void) const

// ?getTypeAddModifiers@Type_t@@QBEPAV1@G@Z
// public: class Type_t * __thiscall Type_t::getTypeAddModifiers(unsigned short) const

// ?getTypePointerTo@Type_t@@QBEPAV1@G@Z
// public: class Type_t * __thiscall Type_t::getTypePointerTo(unsigned short) const

// ?SubstituteElaborationChain@Type_t@@ABEPAV1@PAUs_indir@@@Z
// private: class Type_t * __thiscall Type_t::SubstituteElaborationChain(struct s_indir *) const

// ?MakeTmpElaboration@Type_t@@CAPAUs_indir@@GGABTu_ivalue@@@Z
// private: static struct s_indir * __cdecl Type_t::MakeTmpElaboration(unsigned short, unsigned short, union u_ivalue const &)

// ?MakeTmpElaboration@Type_t@@CAPAUs_indir@@PAU2@@Z
// private: static struct s_indir * __cdecl Type_t::MakeTmpElaboration(struct s_indir *)

// ?getTypePlainPointer@Type_t@@QBEPAV1@XZ
// public: class Type_t * __thiscall Type_t::getTypePlainPointer(void) const

// ?getTypeSansTopQualifiers@Type_t@@QBEPAV1@XZ
// public: class Type_t * __thiscall Type_t::getTypeSansTopQualifiers(void) const

// ?getANSIType@Type_t@@QBEPAV1@XZ
// public: class Type_t * __thiscall Type_t::getANSIType(void) const

// ?CommitAll@s_indir@@AAEPAU1@PAU1@@Z
// private: struct s_indir * __thiscall s_indir::CommitAll(struct s_indir *)

// ?FindElaboration@s_indir@@ABEPAU1@P81@BEHXZ@Z
// private: struct s_indir * __thiscall s_indir::FindElaboration(int (__thiscall s_indir::*)(void) const) const

// ?ReplaceElaborationItem@s_indir@@AAEPAU1@PAU1@0@Z
// private: struct s_indir * __thiscall s_indir::ReplaceElaborationItem(struct s_indir *, struct s_indir *)

// ?predIsNotArray@s_indir@@ABEHXZ
// private: int __thiscall s_indir::predIsNotArray(void) const

// ?SetFunctionInfo@s_indir@@AAEXPAVDLSymbolList_t@@H@Z
// private: void __thiscall s_indir::SetFunctionInfo(class DLSymbolList_t *, int)

#endif /* TYPES_H */
