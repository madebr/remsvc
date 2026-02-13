#ifndef ALLOC_H
#define ALLOC_H

#include "c1_types.h"
#include "decomp.h"

// ?currentTreeLife@@3W4lifetime_e@@A
extern lifetime_e currentTreeLife;

// ?currentTypeLife@@3W4lifetime_e@@A
// enum lifetime_e currentTypeLife

// ?DoRealloc@@YAPAXPAXI@Z
// void * __cdecl DoRealloc(void *, unsigned int)

// ?DoMalloc@@YAPAXI@Z
// void * __cdecl DoMalloc(unsigned int)

// ?DoFree@@YAXPAX@Z
// void __cdecl DoFree(void *)

// ?StartMalloc@@YAXXZ
// void __cdecl StartMalloc(void)

// ?FinishMalloc@@YAXXZ
// void __cdecl FinishMalloc(void)

// ?pstrdup@@YAPADPADW4lifetime_e@@@Z
extern char * __fastcall pstrdup(const char *text, lifetime_e lifetime);

// ?pstrndup@@YAPADPADW4lifetime_e@@H@Z
// char * __cdecl pstrndup(char *, enum lifetime_e, int)

#endif /* ALLOC_H */
