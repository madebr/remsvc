#include "list.h"

#include "decomp.h"
#include "nheapall.h"

// FUNCTION: MSVC5_C1 0x00024aa0
// ?FListInvariants@@YAHQAUlist@@@Z
// int __cdecl FListInvariants(struct list *const)

// FUNCTION: MSVC5_C1 0x00024ae0
// ?ListNewSize@@YAPAUlist@@FW4lifetime_e@@@Z
// FUNCTION: C1 0x00411ea0
list<void *> * ListNewSize(unsigned short capacity, lifetime_e lifetime)
{
    list<void *> *result = HeapManager::Allocate<list<void *>>(lifetime);
    result->size = 0;
    result->capacity = capacity;
    result->lifetime = lifetime;
    result->data = (void **)HeapManager::Allocate(capacity, lifetime);
    return result;
}

// FUNCTION: MSVC5_C1 0x00024b50
// ?ListGrow@@YAPAUlist@@PAU1@@Z
// struct list * __cdecl ListGrow(struct list *)

// FUNCTION: MSVC5_C1 0x00024bd0
// ?ListCopyExtra@@YAPAUlist@@QAU1@FW4lifetime_e@@@Z
// struct list * __cdecl ListCopyExtra(struct list *const, short, enum lifetime_e)

// FUNCTION: MSVC5_C1 0x00024c20
// ?ListCopy@@YAPAUlist@@QAU1@W4lifetime_e@@@Z
// struct list * __cdecl ListCopy(struct list *const, enum lifetime_e)

// FUNCTION: MSVC5_C1 0x00024c40
// ?ListCopyWithSpace@@YAPAUlist@@QAU1@W4lifetime_e@@@Z
// struct list * __cdecl ListCopyWithSpace(struct list *const, enum lifetime_e)

// FUNCTION: MSVC5_C1 0x00024c60
// ?ListItemsCopy@@YAPAUlist@@QAU1@W4lifetime_e@@P6APAXPAX1@Z@Z
// struct list * __cdecl ListItemsCopy(struct list *const, enum lifetime_e, void * (__cdecl *)(void *, enum lifetime_e))

// FUNCTION: MSVC5_C1 0x00024cd0
// ?ListAppend@@YAXPAUlist@@QAX@Z
// void __cdecl ListAppend(struct list *, void *const)

// FUNCTION: MSVC5_C1 0x00024d00
// ?FListContains@@YAHQAUlist@@QAX@Z
// int __cdecl FListContains(struct list *const, void *const)

// FUNCTION: MSVC5_C1 0x00024d40
// ?FListEqual@@YAHQAUlist@@0@Z
// int __cdecl FListEqual(struct list *const, struct list *const)

// FUNCTION: MSVC5_C1 0x00024d70
// ?ListModifyItem@@YAXPAUlistIter_t@@PAX@Z
// void __cdecl ListModifyItem(struct listIter_t *, void *)

// FUNCTION: MSVC5_C1 0x00024d90
// ?FListIterInvariants@@YAHPBUlistIter_t@@@Z
// int __cdecl FListIterInvariants(struct listIter_t const *)

// FUNCTION: C1 0x00411f38
void __fastcall StdFree(void *pointer)
{
    free(pointer);
}
