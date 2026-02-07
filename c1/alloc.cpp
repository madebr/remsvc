#include "alloc.h"

// GLOBAL: MSVC5_C1 0x000015ec
// ?currentTreeLife@@3W4lifetime_e@@A
// enum lifetime_e currentTreeLife

// GLOBAL: MSVC5_C1 0x000015f0
// ?currentTypeLife@@3W4lifetime_e@@A
// enum lifetime_e currentTypeLife

// FUNCTION: MSVC5_C1 0x0003bc10
// ?DoRealloc@@YAPAXPAXI@Z
// void * __cdecl DoRealloc(void *, unsigned int)

// FUNCTION: MSVC5_C1 0x0003bc40
// ?DoMalloc@@YAPAXI@Z
// void * __cdecl DoMalloc(unsigned int)

// FUNCTION: MSVC5_C1 0x0003bc70
// ?DoFree@@YAXPAX@Z
// void __cdecl DoFree(void *)

// FUNCTION: MSVC5_C1 0x0003bc80
// ?StartMalloc@@YAXXZ
// void __cdecl StartMalloc(void)

// FUNCTION: MSVC5_C1 0x0003bc90
// ?FinishMalloc@@YAXXZ
// void __cdecl FinishMalloc(void)

// FUNCTION: MSVC5_C1 0x0003bca0
// ?pstrdup@@YAPADPADW4lifetime_e@@@Z
// FUNCTION C1: 0x00423857
char * __fastcall pstrdup(char *text, lifetime_e lifetime)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x0003bd10
// ?pstrndup@@YAPADPADW4lifetime_e@@H@Z
// char * __cdecl pstrndup(char *, enum lifetime_e, int)

