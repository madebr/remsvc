#ifndef LIST_H
#define LIST_H

#include "c1_types.h"
#include "decomp.h"

template <typename Type>
struct list {
    unsigned short size;
    unsigned short capacity;
    lifetime_e lifetime;
    Type *data;
};

// ?FListInvariants@@YAHQAUlist@@@Z
// int __cdecl FListInvariants(struct list *const)

// ?ListNewSize@@YAPAUlist@@FW4lifetime_e@@@Z
extern list<void *> * ListNewSize(unsigned short capacity, lifetime_e lifetime);

// ?ListGrow@@YAPAUlist@@PAU1@@Z
// struct list * __cdecl ListGrow(struct list *)

// ?ListCopyExtra@@YAPAUlist@@QAU1@FW4lifetime_e@@@Z
// struct list * __cdecl ListCopyExtra(struct list *const, short, enum lifetime_e)

// ?ListCopy@@YAPAUlist@@QAU1@W4lifetime_e@@@Z
// struct list * __cdecl ListCopy(struct list *const, enum lifetime_e)

// ?ListCopyWithSpace@@YAPAUlist@@QAU1@W4lifetime_e@@@Z
// struct list * __cdecl ListCopyWithSpace(struct list *const, enum lifetime_e)

// ?ListItemsCopy@@YAPAUlist@@QAU1@W4lifetime_e@@P6APAXPAX1@Z@Z
// struct list * __cdecl ListItemsCopy(struct list *const, enum lifetime_e, void * (__cdecl *)(void *, enum lifetime_e))

// ?ListAppend@@YAXPAUlist@@QAX@Z
// void __cdecl ListAppend(struct list *, void *const)

// ?FListContains@@YAHQAUlist@@QAX@Z
// int __cdecl FListContains(struct list *const, void *const)

// ?FListEqual@@YAHQAUlist@@0@Z
// int __cdecl FListEqual(struct list *const, struct list *const)

// ?ListModifyItem@@YAXPAUlistIter_t@@PAX@Z
// void __cdecl ListModifyItem(struct listIter_t *, void *)

// ?FListIterInvariants@@YAHPBUlistIter_t@@@Z
// int __cdecl FListIterInvariants(struct listIter_t const *)

extern void __fastcall StdFree(void *pointer);

#endif /* LIST_H */
