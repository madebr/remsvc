#ifndef P0GETTOK_H
#define P0GETTOK_H

#include "c1_types.h"

// ??_C@_05KPNI@_CODE?$AA@
// "_CODE"

// ??_C@_05OJFB@_DATA?$AA@
// "_DATA"

// ??_C@_02A@?$AA?$AA?$AA@
// "\0\0"

// ??_C@_01KNFJ@?$CD?$AA@
// "#"

// ??_C@_08IJL@allocate?$AA@
// "allocate"

// ??_7TokenStream@@6B@
// const TokenStream::`vftable'

// ?InitHardTokens@@YAXXZ
extern void InitHardTokens();

// ?LexerParseDeclspec@@YAXPAUs_class@@@Z
// void __cdecl LexerParseDeclspec(struct s_class *)

// ?CheckAndAttachDeclspecAttributes@@YAXPAVSymbol_t@@ABUs_class@@@Z
// void __cdecl CheckAndAttachDeclspecAttributes(class Symbol_t *, struct s_class const &)

// ?AddIdent@ParseCESUHead@@QAEHPBVToken@@@Z
// public: int __thiscall ParseCESUHead::AddIdent(class Token const *)

// ?AddDeclspec@ParseCESUHead@@QAEHXZ
// public: int __thiscall ParseCESUHead::AddDeclspec(void)

// ?AddDeclaration@ParseCESUHead@@QAEPBVToken@@PBV2@@Z
// public: class Token const * __thiscall ParseCESUHead::AddDeclaration(class Token const *)

// ?AddDefinition@ParseCESUHead@@QAEPBVToken@@PBV2@@Z
// public: class Token const * __thiscall ParseCESUHead::AddDefinition(class Token const *)

// ?LexerGetCESU@@YAPBVToken@@GABUs_class@@@Z
// class Token const * __cdecl LexerGetCESU(unsigned short, struct s_class const &)

// ?ExpandTagIntoItsType@@YAPAVType_t@@PAVSymbol_t@@@Z
// class Type_t * __cdecl ExpandTagIntoItsType(class Symbol_t *)

// ?LexerExpandTypeSym@@YAPAVType_t@@PAVSymbol_t@@@Z
// class Type_t * __cdecl LexerExpandTypeSym(class Symbol_t *)

// ?mf_HandleClassHead@LexerTypeGatherer@@AAEXXZ
// private: void __thiscall LexerTypeGatherer::mf_HandleClassHead(void)

// ?mf_HandleElabTypeSpecifier@LexerTypeGatherer@@AAE?AW4action@1@XZ
// private: enum LexerTypeGatherer::action __thiscall LexerTypeGatherer::mf_HandleElabTypeSpecifier(void)

// ?mf_HandleQualifier@LexerTypeGatherer@@AAE?AW4action@1@XZ
// private: enum LexerTypeGatherer::action __thiscall LexerTypeGatherer::mf_HandleQualifier(void)

// ?mf_HandleStorageClass@LexerTypeGatherer@@AAEXXZ
// private: void __thiscall LexerTypeGatherer::mf_HandleStorageClass(void)

// ?mf_HandleStorageClassModifier@LexerTypeGatherer@@AAEXXZ
// private: void __thiscall LexerTypeGatherer::mf_HandleStorageClassModifier(void)

// ?mf_HandleBuiltinTypeSpecifier@LexerTypeGatherer@@AAEXXZ
// private: void __thiscall LexerTypeGatherer::mf_HandleBuiltinTypeSpecifier(void)

// ?mf_UnhandleId@LexerTypeGatherer@@AAEXXZ
// private: void __thiscall LexerTypeGatherer::mf_UnhandleId(void)

// ?mf_HandleId@LexerTypeGatherer@@AAE?AW4action@1@XZ
// private: enum LexerTypeGatherer::action __thiscall LexerTypeGatherer::mf_HandleId(void)

// ?mf_HandleTypeName@LexerTypeGatherer@@AAEXXZ
// private: void __thiscall LexerTypeGatherer::mf_HandleTypeName(void)

// ?mf_CombineTypeParts@LexerTypeGatherer@@AAEXXZ
// private: void __thiscall LexerTypeGatherer::mf_CombineTypeParts(void)

// ?mf_MakeReturnToken@LexerTypeGatherer@@AAEPBVToken@@E@Z
// private: class Token const * __thiscall LexerTypeGatherer::mf_MakeReturnToken(unsigned char)

// ?mf_GatherTheType@LexerTypeGatherer@@AAEPBVToken@@XZ
// private: class Token const * __thiscall LexerTypeGatherer::mf_GatherTheType(void)

// ?LexerGatherType@@YAPBVToken@@PBV1@@Z
// class Token const * __cdecl LexerGatherType(class Token const *)

// ?LexerResolveIdentifierWorker@@YAPBVToken@@PBV1@@Z
// class Token const * __cdecl LexerResolveIdentifierWorker(class Token const *)

// ?yylex@@YAPBVToken@@XZ
// class Token const * __cdecl yylex(void)

// ?GetTokenFromCurrentChar@@YAPBVToken@@XZ
// class Token const * __cdecl GetTokenFromCurrentChar(void)

// ?yyCheckBTtypes@@YAGGG@Z
// unsigned short __cdecl yyCheckBTtypes(unsigned short, unsigned short)

// ?yyCheckSCtypes@@YAXPAUs_class@@EEZZ
// void __cdecl yyCheckSCtypes(struct s_class *, unsigned char, unsigned char, ...)

class TokenStream {
public:
    // ?IsFileStream@TokenStream@@UBEHXZ
    // public: virtual int __thiscall TokenStream::IsFileStream(void) const

    // ??_GTokenStream@@MAEPAXI@Z
    // protected: virtual void * __thiscall TokenStream::`scalar deleting dtor'(unsigned int)

    // ??_ETokenStream@@MAEPAXI@Z
    // protected: virtual void * __thiscall TokenStream::`vector deleting dtor'(unsigned int)

    // ?getToken@TokenStream@@UAEPBVToken@@XZ
    // public: virtual class Token const * __thiscall TokenStream::getToken(void)

    // ?peekToken@TokenStream@@UAEPBVToken@@XZ
    // public: virtual class Token const * __thiscall TokenStream::peekToken(void)

    // ?pushToken@TokenStream@@UAEXPBVToken@@@Z
    // public: virtual void __thiscall TokenStream::pushToken(class Token const *)

    // ??0TokenStream@@QAE@W4lifetime_e@@H@Z
    TokenStream(lifetime_e lifetime, int);

    // ?saveToken@TokenStream@@UAEXPBVToken@@@Z
    // public: virtual void __thiscall TokenStream::saveToken(class Token const *)

    // ?rewind@TokenStream@@UAEXXZ
    // public: virtual void __thiscall TokenStream::rewind(void)
};

// ?EnterSymbolInCurrentScope@SymbolTableManager_t@@QBEXPAVSymbol_t@@@Z
// public: void __thiscall SymbolTableManager_t::EnterSymbolInCurrentScope(class Symbol_t *) const

// ?AllocEven@VirtualHeap@@QAEPAXI@Z
// public: void * __thiscall VirtualHeap::AllocEven(unsigned int)

// ?get_non_eof@@YAEXZ
// unsigned char __cdecl get_non_eof(void)

// ?SkipComment_C@@YAHXZ
// int __cdecl SkipComment_C(void)

// ?SkipStarComment@@YAXXZ
// void __cdecl SkipStarComment(void)

#endif /* P0GETTOK_H */
