#include "incremental.h"

#include <windows.h>

// DECOMP_SIZEOF(tReal_incremental_0041a434, 0x14);
// DECOMP_SIZEOF(tDummy_incremental_0041a434, 0x8);

// FUNCTION: C1 0x0041a434
BOOL __fastcall CreateIncrementalInterfaces(BOOL enabled, IStruct_Incremental1 **interface1, IStruct_Incremental2 **interface2)
{
    if (enabled) {
        tReal_incremental_0041a434 *real_obj = new tReal_incremental_0041a434;
        *interface1 = static_cast<IStruct_Incremental1*>(real_obj);
        if (real_obj) {
            *interface2 = static_cast<IStruct_Incremental2*>(real_obj);
        } else {
            *interface2 = NULL;
        }
        return TRUE;
    } else {
        tDummy_incremental_0041a434 *dummy_obj = new tDummy_incremental_0041a434;
        *interface1 = static_cast<IStruct_Incremental1*>(dummy_obj);
        if (dummy_obj) {
            *interface2 = static_cast<IStruct_Incremental2*>(dummy_obj);
        } else {
            *interface2 = NULL;
        }
        return TRUE;
    }
}

// tReal_incremental_0041a434

// FUNCTION: C1 0x00449b3a
BOOL tReal_incremental_0041a434::vtable_inc1_0x0(undefined4)  {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00449c44
BOOL tReal_incremental_0041a434::vtable_inc1_0x4(undefined4)  {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00449ca4
void tReal_incremental_0041a434::vtable_inc1_0x8()  {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00449c97
void tReal_incremental_0041a434::vtable_inc1_0xc()  {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00449cd3
void tReal_incremental_0041a434::vtable_inc1_0x10()  {
    delete this;
}

// FUNCTION: C1 0x00449eac
void tReal_incremental_0041a434::vtable_inc1_0x14(undefined4, undefined4) {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00449cdd
BOOL tReal_incremental_0041a434::vtable_inc2_0x0(void *, void *) {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00449ecd
BOOL tReal_incremental_0041a434::vtable_inc2_0x4(undefined4,void*,void*) {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00411841
void tReal_incremental_0041a434::vtable_inc2_0x8() {
    // emptry
}


// tDummy_incremental_0041a434


// FUNCTION: C1 0x00411839
BOOL tDummy_incremental_0041a434::vtable_inc1_0x0(undefined4) {
    return TRUE;
}

// FUNCTION: C1 0x00403100
BOOL tDummy_incremental_0041a434::vtable_inc1_0x4(undefined4) {
    return TRUE;
}

// FUNCTION: C1 0x00403041
void tDummy_incremental_0041a434::vtable_inc1_0x8()  {
    // emptry
}

// FUNCTION: C1 0x00403040
void tDummy_incremental_0041a434::vtable_inc1_0xc()  {
    // emptry
}

// FUNCTION: C1 0x0041f2c2
void tDummy_incremental_0041a434::vtable_inc1_0x10() {
    delete this;
}

// FUNCTION: C1 0x00402c97
void tDummy_incremental_0041a434::vtable_inc1_0x14(undefined4, undefined4) {
    // emptry
}

// FUNCTION: C1 0x00449b30
BOOL tDummy_incremental_0041a434::vtable_inc2_0x0(void *, void *) {
    return FALSE;
}

// FUNCTION: C1 0x00449b35
BOOL tDummy_incremental_0041a434::vtable_inc2_0x4(undefined4,void*,void*) {
    return FALSE;
}

// FUNCTION: C1 0x00411841
void tDummy_incremental_0041a434::vtable_inc2_0x8() {
    // emptry
}
