#ifndef UTIL_H
#define UTIL_H

#include "decomp.h"

#include <stdlib.h>

void * __fastcall xnew(size_t size);

void * __fastcall xrealloc(void *ptr,size_t size);

#endif /* UTIL_H */
