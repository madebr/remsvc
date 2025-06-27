#pragma once

#include <windows.h>
#include "decomp.h"

class IStruct_Incremental1 {
public:
    virtual BOOL vtable_inc1_0x0(undefined4) = 0;   // field_0x0
    virtual BOOL vtable_inc1_0x4(undefined4) = 0;   // field_0x4
    virtual void vtable_inc1_0x8() = 0;   // field_0x8
    virtual void vtable_inc1_0xc() = 0;   // field_0xc
    virtual void vtable_inc1_0x10() = 0;   // field_0x10
    virtual void vtable_inc1_0x14(undefined4, undefined4) = 0;  // field_0x14
};

class IStruct_Incremental2 {
public:
    virtual BOOL vtable_inc2_0x0(void *, void *) = 0;   // field_0x0
    virtual BOOL vtable_inc2_0x4(undefined4,void*,void*) = 0;   // field_0x4
    virtual void vtable_inc2_0x8() = 0;   // field_0x8
};

class tReal_incremental_0041a434 : public IStruct_Incremental1, public IStruct_Incremental2 {
public:
    tReal_incremental_0041a434() {
        m_field_0x8 = -1;
        m_field_0xc = 0;
    }
    BOOL vtable_inc1_0x0(undefined4)  override;
    BOOL vtable_inc1_0x4(undefined4)  override;
    void vtable_inc1_0x8()  override;
    void vtable_inc1_0xc()  override;
    void vtable_inc1_0x10() override;
    void vtable_inc1_0x14(undefined4, undefined4) override;
    BOOL vtable_inc2_0x0(void *, void *) override;
    BOOL vtable_inc2_0x4(undefined4,void*,void*) override;
    void vtable_inc2_0x8() override;
private:
    int m_field_0x8;
    undefined4 m_field_0xc;
    undefined4 m_field_0x10;
};

class tDummy_incremental_0041a434 : public IStruct_Incremental1, public IStruct_Incremental2 {
public:
    BOOL vtable_inc1_0x0(undefined4) override;
    BOOL vtable_inc1_0x4(undefined4) override;
    void vtable_inc1_0x8()  override;
    void vtable_inc1_0xc()  override;
    void vtable_inc1_0x10()  override;
    void vtable_inc1_0x14(undefined4, undefined4) override;
    BOOL vtable_inc2_0x0(void *, void *) override;
    BOOL vtable_inc2_0x4(undefined4,void*,void*) override;
    void vtable_inc2_0x8() override;
};

#ifdef __cplusplus
extern "C" {
#endif

extern BOOL __fastcall CreateIncrementalInterfaces(BOOL enabled, IStruct_Incremental1 **interface1, IStruct_Incremental2 **interface2);

#ifdef __cplusplus
};
#endif
