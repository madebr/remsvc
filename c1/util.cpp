#include "util.h"

#include "error.h"


// FUNCTION: C1 0x0041136e
void * __fastcall xnew(size_t size)
{
    void *result = malloc(size);
    if (result == NULL) {
        fatal(C1060);
    }
    return result;
}


// FUNCTION: C1 0x00447fc2
void * __fastcall xrealloc(void *ptr, size_t size)
{
    void *result = realloc(ptr, size);
    if (result == NULL) {
        fatal(C1060);
    }
    return result;
}
