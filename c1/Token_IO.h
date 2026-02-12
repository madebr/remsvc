#ifndef TOKEN_IO_H
#define TOKEN_IO_H

#include "c1_types.h"
#include "nbrowser.h"
#include "p0gettok.h"
#include "p0io.h"
#include "token.h"

#include <stddef.h>

// SIZE: C1 0xc
struct BrowserStatus {
    BrowserStatus(const char *name, SBR *sbr) {
        m_OverallBrowserStatus = name != NULL;
        m_count = 0;
        m_pSbrSave = sbr;
    }

    bool m_OverallBrowserStatus;
    size_t m_count;
    SBR *m_pSbrSave;
};

// SIZE: C1 0x8
struct LifetimeStack {
    lifetime_e m_currentLife;
    LifetimeStack *m_Next;
};

// SIZE: C1 0x20
struct Token {
    // ?FindPointers@Token@@QAEXXZ
    // public: void __thiscall Token::FindPointers(void)

    // ?tmpValueme@Token@@2Ts_lextype@@A
    // public: static union s_lextype Token::tmpValueme

    // ?tokenLife@Token@@2VLifetimeStack@@A
    static LifetimeStack tokenLife;

    static void ResetTokenLife();

    e_token_t lexeme;
    undefined field_0x8;
};

enum PushMode {
    M_PUSHMODE_0x0 = 0x0,
};

struct TokenStreamStack {
    // ?getToken@TokenStreamStack@@QAEPBVToken@@XZ
    // public: class Token const * __thiscall TokenStreamStack::getToken(void)

    // ?peekToken@TokenStreamStack@@QAEPBVToken@@XZ
    // public: class Token const * __thiscall TokenStreamStack::peekToken(void)

    // ?pushStream@TokenStreamStack@@QAEXPAVTokenStream@@W4lifetime_e@@W4PushMode@@P6AXXZABVPosition@@@Z
    void pushStream(TokenStream *stream, PushMode pushMode, void (*pNotification)(void), const Position &position);

    const Position & GetPosition() const {
        return curPos;
    }

    Position curPos;
    TokenStreamStackElement *pTopOfStack;
};

// ?tokenDeferedStack@@3PAVTokenStreamStack@@A
// class TokenStreamStack *tokenDeferedStack

// ?tokenInputStack@@3VTokenStreamStack@@A
extern TokenStreamStack tokenInputStack;

// ?tokenOutputStack@@3VTokenStreamStack@@A
// class TokenStreamStack tokenOutputStack

// ?pTheBrowserStatus@@3PAVBrowserStatus@@A
extern BrowserStatus *pTheBrowserStatus;

// _$E31

// _$E30

// _$E34

// _$E33

// _$E37

// _$E36

// ?FindPointers@TokenBuffer@@QAEXXZ
// public: void __thiscall TokenBuffer::FindPointers(void)

// ??0TokenBufferHandle@@QAE@W4lifetime_e@@@Z
// public: __thiscall TokenBufferHandle::TokenBufferHandle(enum lifetime_e)

// ?FindPointers@TokenBufferHandle@@QAEXXZ
// public: void __thiscall TokenBufferHandle::FindPointers(void)

// ?CleanUpAllBuffers@TokenBufferHandle@@QAEXXZ
// public: void __thiscall TokenBufferHandle::CleanUpAllBuffers(void)

// ?FindPointersInBuffer@TokenBufferHandle@@QAEXXZ
// public: void __thiscall TokenBufferHandle::FindPointersInBuffer(void)

// _$E40

// _$E39

// _$E43

// _$E42

// ?FindPointers@TokenStream@@SAXPAX@Z
// public: static void __cdecl TokenStream::FindPointers(void *)

// ?CurrentPositionToken@@YAPBVToken@@W4lifetime_e@@@Z
// class Token const * __cdecl CurrentPositionToken(enum lifetime_e)
// ?MakeSimpletypeToken@@YAPBVToken@@PAVType_t@@EPAUs_class@@PAVSymbol_t@@@Z
// class Token const * __cdecl MakeSimpletypeToken(class Type_t *, unsigned char, struct s_class *, class Symbol_t *)

// ?initTokens@@YAXXZ
// void __cdecl initTokens(void)

// ??_H@YGXPAXIHP6EX0@Z@Z
// void __stdcall `vector ctor iterator'(void *, unsigned int, int, void (__thiscall *)(void *))

#endif /* TOKEN_IO_H */
