#ifndef C1_TYPES_H
#define C1_TYPES_H

#include "decomp.h"

typedef enum {
    CES_Undef           = 0,
    CES_Init            = 1,
    CES_LoadingPCH      = 2,
    CES_Compiling       = 3,
    CES_SavingPCH       = 4,
    CES_NormalCleanup   = 5,
    CES_AbortCleanup    = 6,
    CES_ErrorCleanup    = 7,
    CES_Done            = 8
} CompilerExecutionState_t;

enum lifetime_e {
    M_LIFEMIN = 0,
    M_LIFETIME0 = 0,
    M_LIFETIME1 = 1,
    M_LIFETIME2 = 2,
    M_LIFETIME3 = 3,
    M_LIFETIME4 = 4,
    M_LIFETIME5 = 5,
    M_LIFEMAX = 6
};

struct s_cmd_line_warning_t {
    int number;
    int severity;
};

struct s_tree {
    undefined field_0x0[0x1 - 0x0];
    undefined tr_shape;
    undefined field_0x2[0x18 - 0x2];
};

struct Buffer {
    Buffer() {
        pbStart = NULL;
        pbEnd = NULL;
        cb = 0;
        m_field_0xc = 0;
    }

    ~Buffer() {
        if (pbStart != NULL) {
            delete pbStart;
            pbStart = NULL;
        }
    }

    // ?Ensure@Buffer@@QAEHJ@Z
    // public: int __thiscall Buffer::Ensure(long)

    // ?AppendNoCheck@Buffer@@QAEHPAEJ@Z
    // public: int __thiscall Buffer::AppendNoCheck(unsigned char *, long)

    // ?Free@Buffer@@QAEXXZ
    // public: void __thiscall Buffer::Free(void)

    // ?Ensure@Buffer@@QAEHJPAPAE@Z
    // public: int __thiscall Buffer::Ensure(long, unsigned char **)

    // ?Reserve@Buffer@@QAEHJPAPAE@Z
    // public: int __thiscall Buffer::Reserve(long, unsigned char **)

    // ?Append@Buffer@@QAEHPAEJPAPAE@Z
    // public: int __thiscall Buffer::Append(unsigned char *, long, unsigned char **)

    bool32 ensureAvailable(size_t amount) {
        if (pbStart + cb < pbEnd + amount) {
            return grow(amount);
        }
        return TRUE;
    }

    char *pbStart;
    char *pbEnd;
    size_t cb;
    undefined4 m_field_0xc;

private:
    // ?grow@Buffer@@AAEHJ@Z
    bool32 grow(size_t amount);

    // ?setPbExtent@Buffer@@AAEHPAE0@Z
    // private: int __thiscall Buffer::setPbExtent(unsigned char *, unsigned char *)

};

#endif
