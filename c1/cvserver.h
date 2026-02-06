#ifndef CVSERVER_H
#define CVSERVER_H
// ??_C@_0N@GHNK@?4?2cvserver?4c?$AA@
// ".\\cvserver.c"

// ?bufRecLeaf@@3PADA
// char *bufRecLeaf

// ?bufRec@@3PADA
// char *bufRec

// ?CVTSInit@@YAXH@Z
// void __cdecl CVTSInit(int)

// ?WriteTypeServerRecord@@YAXXZ
// void __cdecl WriteTypeServerRecord(void)

// ?CVTSEnd@@YAXXZ
// void __cdecl CVTSEnd(void)

// ?TiForBuf@@YAKG@Z
// unsigned long __cdecl TiForBuf(unsigned short)

// ?TiForType@@YAKPAVType_t@@@Z
// unsigned long __cdecl TiForType(class Type_t *)

// ?TiForIndirType@@YAKPAVType_t@@PAUs_indir@@@Z
// unsigned long __cdecl TiForIndirType(class Type_t *, struct s_indir *)

// ?TiForPrimitiveIndir@@YAKPAVType_t@@PAUs_indir@@@Z
// unsigned long __cdecl TiForPrimitiveIndir(class Type_t *, struct s_indir *)

// ?TiForPartialPrimitiveBtype@@YAKG@Z
// unsigned long __cdecl TiForPartialPrimitiveBtype(unsigned short)

// ?TiForPtrType@@YAKPAVType_t@@K@Z
// unsigned long __cdecl TiForPtrType(class Type_t *, unsigned long)

// ?TiForArrayType@@YAKPAVType_t@@K@Z
// unsigned long __cdecl TiForArrayType(class Type_t *, unsigned long)

// ?TiForFuncType@@YAKPAVType_t@@K@Z
// unsigned long __cdecl TiForFuncType(class Type_t *, unsigned long)

// ?TiForFuncArgs@@YAKPAUs_flist@@@Z
// unsigned long __cdecl TiForFuncArgs(struct s_flist *)

// ?CargsForFlist@@YAIPAUs_flist@@@Z
// unsigned int __cdecl CargsForFlist(struct s_flist *)

// ?TiForConstVolType@@YAKPAVType_t@@@Z
// unsigned long __cdecl TiForConstVolType(class Type_t *)

// ?TiForPrimitiveType@@YAKPAVType_t@@@Z
// unsigned long __cdecl TiForPrimitiveType(class Type_t *)

// ?TiForBaseClass@@YAKPAVSymbol_t@@@Z
// unsigned long __cdecl TiForBaseClass(class Symbol_t *)

// ?TiForEnumDecl@@YAKPAVSymbol_t@@@Z
// unsigned long __cdecl TiForEnumDecl(class Symbol_t *)

// ?TiForEnumDefn@@YAKPAVSymbol_t@@@Z
// unsigned long __cdecl TiForEnumDefn(class Symbol_t *)

// ?TiForEnumFlist@@YAKPAVSymbol_t@@@Z
// unsigned long __cdecl TiForEnumFlist(class Symbol_t *)

// ?CmpMoe@@YAHPAPAVSymbol_t@@0@Z
// int __cdecl CmpMoe(class Symbol_t **, class Symbol_t **)

// ?TiForTagDecl@@YAKPAVSymbol_t@@@Z
// unsigned long __cdecl TiForTagDecl(class Symbol_t *)

// ?TiForTagDefn@@YAKPAVSymbol_t@@@Z
// unsigned long __cdecl TiForTagDefn(class Symbol_t *)

// ?TiForMemberList@@YAKPAVSymbol_t@@PAIPAUCV_prop_t@@@Z
// unsigned long __cdecl TiForMemberList(class Symbol_t *, unsigned int *, struct CV_prop_t *)

// ?TiForMemberListPass@@YAKW4PASS@@PAVSymbol_t@@PAIPAUCV_prop_t@@@Z
// unsigned long __cdecl TiForMemberListPass(enum PASS, class Symbol_t *, unsigned int *, struct CV_prop_t *)

// ?CbInsertAlign@@YAGPADG@Z
// unsigned short __cdecl CbInsertAlign(char *, unsigned short)

// ?CbInsertDataMember@@YAGW4PASS@@PAVSymbol_t@@PAUlfMember@@@Z
// unsigned short __cdecl CbInsertDataMember(enum PASS, class Symbol_t *, struct lfMember *)

// ?TiForField@@YAKPAVSymbol_t@@@Z
// unsigned long __cdecl TiForField(class Symbol_t *)

// ?szCVFuncName@@YAPADPAVSymbol_t@@H@Z
// char * __cdecl szCVFuncName(class Symbol_t *, int)

// ?CbInsertFuncName@@YAGPAEPAVSymbol_t@@H@Z
// unsigned short __cdecl CbInsertFuncName(unsigned char *, class Symbol_t *, int)

// ?CbInsertTagName@@YAGPADPAVSymbol_t@@@Z
// unsigned short __cdecl CbInsertTagName(char *, class Symbol_t *)

// ?CbInsertNumeric@@YAGPAD_J@Z
// unsigned short __cdecl CbInsertNumeric(char *, __int64)

// ?CbInsertSigned@@YAGPAD_J@Z
// unsigned short __cdecl CbInsertSigned(char *, __int64)

// ?CbInsertUnsigned@@YAGPAD_K@Z
// unsigned short __cdecl CbInsertUnsigned(char *, unsigned __int64)

// ?CbInsertString@@YAGPAD0@Z
// unsigned short __cdecl CbInsertString(char *, char *)

// ?CbInsertSymbol@@YAGPADPAVSymbol_t@@@Z
// unsigned short __cdecl CbInsertSymbol(char *, class Symbol_t *)

// ?CVStartTypes@@YAXXZ
// void __cdecl CVStartTypes(void)

// ?CVAssignTagTi@@YAKPAVSymbol_t@@@Z
// unsigned long __cdecl CVAssignTagTi(class Symbol_t *)

// ?CVEmitUsePch@@YAXPAD@Z
// void __cdecl CVEmitUsePch(char *)

// ?CVEmitEndPch@@YAXXZ
// void __cdecl CVEmitEndPch(void)

// ?CVCallingConvention@@YA?AW4CV_call_e@@G@Z
// enum CV_call_e __cdecl CVCallingConvention(unsigned short)

// ?EmitTypeRec@@YAXHPAD@Z
// void __cdecl EmitTypeRec(int, char *)

// ?WriteTypesToInil@@YAXW4INIT_TYPE@@ZZ
// void __cdecl WriteTypesToInil(enum INIT_TYPE, ...)

// ?NFstrztol@@YAPADPAD0@Z
// char * __cdecl NFstrztol(char *, char *)

// ?Ensure@Buffer@@QAEHJ@Z
// public: int __thiscall Buffer::Ensure(long)

// ?AppendNoCheck@Buffer@@QAEHPAEJ@Z
// public: int __thiscall Buffer::AppendNoCheck(unsigned char *, long)

// ?grow@Buffer@@AAEHJ@Z
// private: int __thiscall Buffer::grow(long)

// ?chwrite@ILSink@@QAEXE@Z
// public: void __thiscall ILSink::chwrite(unsigned char)

// ?loshwrite@ILSink@@QAEXJ@Z
// public: void __thiscall ILSink::loshwrite(long)

// ?fEmitOneByte@ILSink@@AAEHH@Z
// private: int __thiscall ILSink::fEmitOneByte(int)

// ?shwriteNoCheck@ILSink@@AAEXF@Z
// private: void __thiscall ILSink::shwriteNoCheck(short)

#endif /* CVSERVER_H */
