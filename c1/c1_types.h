#ifndef C1_TYPES_H
#define C1_TYPES_H

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

typedef enum lifetime_e {
    M_LIFEMIN = 0,
    M_LIFETIME0 = 0,
    M_LIFETIME1 = 1,
    M_LIFETIME2 = 2,
    M_LIFETIME3 = 3,
    M_LIFETIME4 = 4,
    M_LIFETIME5 = 5,
    M_LIFEMAX = 6
} lifetime_e;

#endif
