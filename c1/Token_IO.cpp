#include "Token_IO.h"

// GLOBAL: MSVC5_C1 0x00001858
// ?tokenDeferedStack@@3PAVTokenStreamStack@@A
// class TokenStreamStack *tokenDeferedStack

// GLOBAL: MSVC5_C1 0x000018a0
// ?tmpValueme@Token@@2Ts_lextype@@A
// public: static union s_lextype Token::tmpValueme

// GLOBAL: MSVC5_C1 0x000018b8
// ?tokenInputStack@@3VTokenStreamStack@@A
// GLOBAL: C1 0x0045e450
TokenStreamStack tokenInputStack;

// GLOBAL: MSVC5_C1 0x000018c8
// ?tokenOutputStack@@3VTokenStreamStack@@A
// class TokenStreamStack tokenOutputStack

// GLOBAL: MSVC5_C1 0x000018d8
// ?tokenLife@Token@@2VLifetimeStack@@A
// GLOBAL: C1 0x0045e470
LifetimeStack Token::tokenLife;

// GLOBAL: MSVC5_C1 0x000018e0
// ?pTheBrowserStatus@@3PAVBrowserStatus@@A
// GLOBAL: C1 0x0045e478
BrowserStatus *pTheBrowserStatus = NULL;

// FUNCTION: MSVC5_C1 0x00009840
// _$E31
// static

// FUNCTION: MSVC5_C1 0x00009850
// _$E30
// static

// FUNCTION: MSVC5_C1 0x00009870
// _$E34
// static

// FUNCTION: MSVC5_C1 0x00009880
// _$E33
// static

// FUNCTION: MSVC5_C1 0x000098a0
// _$E37
// static

// FUNCTION: MSVC5_C1 0x000098b0
// _$E36
// static

// FUNCTION: MSVC5_C1 0x000098d0
// ?FindPointers@TokenBuffer@@QAEXXZ
// public: void __thiscall TokenBuffer::FindPointers(void)

// FUNCTION: MSVC5_C1 0x00009920
// ??0TokenBufferHandle@@QAE@W4lifetime_e@@@Z
// public: __thiscall TokenBufferHandle::TokenBufferHandle(enum lifetime_e)

// FUNCTION: MSVC5_C1 0x00009980
// ?FindPointers@TokenBufferHandle@@QAEXXZ
// public: void __thiscall TokenBufferHandle::FindPointers(void)

// FUNCTION: MSVC5_C1 0x00009990
// ?CleanUpAllBuffers@TokenBufferHandle@@QAEXXZ
// public: void __thiscall TokenBufferHandle::CleanUpAllBuffers(void)

// FUNCTION: MSVC5_C1 0x000099b0
// ?FindPointersInBuffer@TokenBufferHandle@@QAEXXZ
// public: void __thiscall TokenBufferHandle::FindPointersInBuffer(void)

// FUNCTION: MSVC5_C1 0x000099c0
// ?FindPointers@Position@@QAEXXZ
// public: void __thiscall Position::FindPointers(void)

// FUNCTION: MSVC5_C1 0x000099d0
// _$E40
// static

// FUNCTION: MSVC5_C1 0x000099e0
// _$E39
// static

// FUNCTION: MSVC5_C1 0x000099f0
// _$E43
// static

// FUNCTION: MSVC5_C1 0x00009a00
// _$E42
// static

// FUNCTION: MSVC5_C1 0x00009a10
// ?FindPointers@Token@@QAEXXZ
// public: void __thiscall Token::FindPointers(void)

// FUNCTION: MSVC5_C1 0x00009b10
// ?FindPointers@TokenStream@@SAXPAX@Z
// public: static void __cdecl TokenStream::FindPointers(void *)

// FUNCTION: MSVC5_C1 0x00009b50
// ?CurrentPositionToken@@YAPBVToken@@W4lifetime_e@@@Z
// class Token const * __cdecl CurrentPositionToken(enum lifetime_e)

// FUNCTION: MSVC5_C1 0x00009bf0
// ?getToken@TokenStreamStack@@QAEPBVToken@@XZ
// public: class Token const * __thiscall TokenStreamStack::getToken(void)

// FUNCTION: MSVC5_C1 0x00009e30
// ?peekToken@TokenStreamStack@@QAEPBVToken@@XZ
// public: class Token const * __thiscall TokenStreamStack::peekToken(void)

// FUNCTION: MSVC5_C1 0x00009e80
// ?pushStream@TokenStreamStack@@QAEXPAVTokenStream@@W4lifetime_e@@W4PushMode@@P6AXXZABVPosition@@@Z
// FUNCTION: C1 0x0040267e
void TokenStreamStack::pushStream(TokenStream *stream, PushMode pushMode, void (*pNotification)(void), const Position &position) {
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00009f00
// ?MakeSimpletypeToken@@YAPBVToken@@PAVType_t@@EPAUs_class@@PAVSymbol_t@@@Z
// class Token const * __cdecl MakeSimpletypeToken(class Type_t *, unsigned char, struct s_class *, class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00009ff0
// ?initTokens@@YAXXZ
// void __cdecl initTokens(void)

// FUNCTION: MSVC5_C1 0x0000a010
// ??_H@YGXPAXIHP6EX0@Z@Z
// void __stdcall `vector ctor iterator'(void *, unsigned int, int, void (__thiscall *)(void *))


// FUNCTION: C1 0x0041a934
void Token::ResetTokenLife() {
    tokenLife.m_Next = NULL;
    tokenLife.m_currentLife = M_LIFETIME2;
}
