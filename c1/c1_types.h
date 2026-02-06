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

#endif
