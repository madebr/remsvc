#ifndef UTIL_H
#define UTIL_H

#include "decomp.h"

#include <stdlib.h>
#include <stdio.h>

void * __fastcall xnew(size_t size);

void * __fastcall xrealloc(void *ptr,size_t size);

int __fastcall xfclose(FILE *f);

extern void __fastcall StdFree(void *ptr);

#endif /* UTIL_H */
