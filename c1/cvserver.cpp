#include "cvserver.h"

#include "decomp.h"

#include "c1_types.h"

// GLOBAL: MSVC5_C1 0x00001194
// ??_C@_0N@GHNK@?4?2cvserver?4c?$AA@
// ".\\cvserver.c"

// GLOBAL: MSVC5_C1 0x000038a8
// ?bufRecLeaf@@3PADA
// char *bufRecLeaf

// GLOBAL: MSVC5_C1 0x000038ac
// ?bufRec@@3PADA
// char *bufRec

// FUNCTION: MSVC5_C1 0x00012460
// ?CVTSInit@@YAXH@Z
// void __cdecl CVTSInit(int)

// FUNCTION: MSVC5_C1 0x00012500
// ?WriteTypeServerRecord@@YAXXZ
// void __cdecl WriteTypeServerRecord(void)

// FUNCTION: MSVC5_C1 0x000125a0
// ?CVTSEnd@@YAXXZ
// void __cdecl CVTSEnd(void)

// FUNCTION: MSVC5_C1 0x000125f0
// ?TiForBuf@@YAKG@Z
// unsigned long __cdecl TiForBuf(unsigned short)

// FUNCTION: MSVC5_C1 0x00012760
// ?TiForType@@YAKPAVType_t@@@Z
// unsigned long __cdecl TiForType(class Type_t *)

// FUNCTION: MSVC5_C1 0x000127a0
// ?TiForIndirType@@YAKPAVType_t@@PAUs_indir@@@Z
// unsigned long __cdecl TiForIndirType(class Type_t *, struct s_indir *)

// FUNCTION: MSVC5_C1 0x00012830
// ?TiForPrimitiveIndir@@YAKPAVType_t@@PAUs_indir@@@Z
// unsigned long __cdecl TiForPrimitiveIndir(class Type_t *, struct s_indir *)

// FUNCTION: MSVC5_C1 0x00012870
// ?TiForPartialPrimitiveBtype@@YAKG@Z
// unsigned long __cdecl TiForPartialPrimitiveBtype(unsigned short)

// FUNCTION: MSVC5_C1 0x000129e0
// ?TiForPtrType@@YAKPAVType_t@@K@Z
// unsigned long __cdecl TiForPtrType(class Type_t *, unsigned long)

// FUNCTION: MSVC5_C1 0x00012b10
// ?TiForArrayType@@YAKPAVType_t@@K@Z
// unsigned long __cdecl TiForArrayType(class Type_t *, unsigned long)

// FUNCTION: MSVC5_C1 0x00012b70
// ?TiForFuncType@@YAKPAVType_t@@K@Z
// unsigned long __cdecl TiForFuncType(class Type_t *, unsigned long)

// FUNCTION: MSVC5_C1 0x00012be0
// ?TiForFuncArgs@@YAKPAUs_flist@@@Z
// unsigned long __cdecl TiForFuncArgs(struct s_flist *)

// FUNCTION: MSVC5_C1 0x00012cb0
// ?CargsForFlist@@YAIPAUs_flist@@@Z
// unsigned int __cdecl CargsForFlist(struct s_flist *)

// FUNCTION: MSVC5_C1 0x00012cd0
// ?TiForConstVolType@@YAKPAVType_t@@@Z
// unsigned long __cdecl TiForConstVolType(class Type_t *)

// FUNCTION: MSVC5_C1 0x00012d40
// ?TiForPrimitiveType@@YAKPAVType_t@@@Z
// unsigned long __cdecl TiForPrimitiveType(class Type_t *)

// FUNCTION: MSVC5_C1 0x00012dc0
// ?TiForBaseClass@@YAKPAVSymbol_t@@@Z
// unsigned long __cdecl TiForBaseClass(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00012de0
// ?TiForEnumDecl@@YAKPAVSymbol_t@@@Z
// unsigned long __cdecl TiForEnumDecl(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00012e70
// ?TiForEnumDefn@@YAKPAVSymbol_t@@@Z
// unsigned long __cdecl TiForEnumDefn(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00012f40
// ?TiForEnumFlist@@YAKPAVSymbol_t@@@Z
// unsigned long __cdecl TiForEnumFlist(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x000130c0
// ?CmpMoe@@YAHPAPAVSymbol_t@@0@Z
// int __cdecl CmpMoe(class Symbol_t **, class Symbol_t **)

// FUNCTION: MSVC5_C1 0x000130e0
// ?TiForTagDecl@@YAKPAVSymbol_t@@@Z
// unsigned long __cdecl TiForTagDecl(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00013250
// ?TiForTagDefn@@YAKPAVSymbol_t@@@Z
// unsigned long __cdecl TiForTagDefn(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00013410
// ?TiForMemberList@@YAKPAVSymbol_t@@PAIPAUCV_prop_t@@@Z
// unsigned long __cdecl TiForMemberList(class Symbol_t *, unsigned int *, struct CV_prop_t *)

// FUNCTION: MSVC5_C1 0x00013460
// ?TiForMemberListPass@@YAKW4PASS@@PAVSymbol_t@@PAIPAUCV_prop_t@@@Z
// unsigned long __cdecl TiForMemberListPass(enum PASS, class Symbol_t *, unsigned int *, struct CV_prop_t *)

// FUNCTION: MSVC5_C1 0x00013590
// ?CbInsertAlign@@YAGPADG@Z
// unsigned short __cdecl CbInsertAlign(char *, unsigned short)

// FUNCTION: MSVC5_C1 0x000135d0
// ?CbInsertDataMember@@YAGW4PASS@@PAVSymbol_t@@PAUlfMember@@@Z
// unsigned short __cdecl CbInsertDataMember(enum PASS, class Symbol_t *, struct lfMember *)

// FUNCTION: MSVC5_C1 0x000136a0
// ?TiForField@@YAKPAVSymbol_t@@@Z
// unsigned long __cdecl TiForField(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x000136e0
// ?szCVFuncName@@YAPADPAVSymbol_t@@H@Z
// char * __cdecl szCVFuncName(class Symbol_t *, int)

// FUNCTION: MSVC5_C1 0x000136f0
// ?CbInsertFuncName@@YAGPAEPAVSymbol_t@@H@Z
// unsigned short __cdecl CbInsertFuncName(unsigned char *, class Symbol_t *, int)

// FUNCTION: MSVC5_C1 0x00013720
// ?CbInsertTagName@@YAGPADPAVSymbol_t@@@Z
// unsigned short __cdecl CbInsertTagName(char *, class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00013740
// ?CbInsertNumeric@@YAGPAD_J@Z
// unsigned short __cdecl CbInsertNumeric(char *, __int64)

// FUNCTION: MSVC5_C1 0x00013780
// ?CbInsertSigned@@YAGPAD_J@Z
// unsigned short __cdecl CbInsertSigned(char *, __int64)

// FUNCTION: MSVC5_C1 0x00013880
// ?CbInsertUnsigned@@YAGPAD_K@Z
// unsigned short __cdecl CbInsertUnsigned(char *, unsigned __int64)

// FUNCTION: MSVC5_C1 0x00013900
// ?CbInsertString@@YAGPAD0@Z
// unsigned short __cdecl CbInsertString(char *, char *)

// FUNCTION: MSVC5_C1 0x00013920
// ?CbInsertSymbol@@YAGPADPAVSymbol_t@@@Z
// unsigned short __cdecl CbInsertSymbol(char *, class Symbol_t *)

// FUNCTION: MSVC5_C1 0x000139b0
// ?CVStartTypes@@YAXXZ
// void __cdecl CVStartTypes(void)

// FUNCTION: MSVC5_C1 0x000139c0
// ?CVAssignTagTi@@YAKPAVSymbol_t@@@Z
// unsigned long __cdecl CVAssignTagTi(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x000139e0
// ?CVEmitUsePch@@YAXPAD@Z
// void __cdecl CVEmitUsePch(char *)

// FUNCTION: MSVC5_C1 0x00013a70
// ?CVEmitEndPch@@YAXXZ
// void __cdecl CVEmitEndPch(void)

// FUNCTION: MSVC5_C1 0x00013ac0
// ?CVCallingConvention@@YA?AW4CV_call_e@@G@Z
// enum CV_call_e __cdecl CVCallingConvention(unsigned short)
// static

// FUNCTION: MSVC5_C1 0x00013b90
// ?EmitTypeRec@@YAXHPAD@Z
// void __cdecl EmitTypeRec(int, char *)
// static

// FUNCTION: MSVC5_C1 0x00013c00
// ?WriteTypesToInil@@YAXW4INIT_TYPE@@ZZ
// void __cdecl WriteTypesToInil(enum INIT_TYPE, ...)
// static

// FUNCTION: MSVC5_C1 0x00014000
// ?NFstrztol@@YAPADPAD0@Z
// char * __cdecl NFstrztol(char *, char *)

// FUNCTION: MSVC5_C1 0x00014080
// ?Ensure@Buffer@@QAEHJ@Z
// public: int __thiscall Buffer::Ensure(long)

// FUNCTION: MSVC5_C1 0x000140c0
// ?AppendNoCheck@Buffer@@QAEHPAEJ@Z
// public: int __thiscall Buffer::AppendNoCheck(unsigned char *, long)

// FUNCTION: MSVC5_C1 0x00014100
// ?grow@Buffer@@AAEHJ@Z
bool32 Buffer::grow(size_t amount)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x000141b0
// ?chwrite@ILSink@@QAEXE@Z
// public: void __thiscall ILSink::chwrite(unsigned char)

// FUNCTION: MSVC5_C1 0x00014200
// ?loshwrite@ILSink@@QAEXJ@Z
// public: void __thiscall ILSink::loshwrite(long)

// FUNCTION: MSVC5_C1 0x00014280
// ?fEmitOneByte@ILSink@@AAEHH@Z
// private: int __thiscall ILSink::fEmitOneByte(int)

// FUNCTION: MSVC5_C1 0x000142b0
// ?shwriteNoCheck@ILSink@@AAEXF@Z
// private: void __thiscall ILSink::shwriteNoCheck(short)

