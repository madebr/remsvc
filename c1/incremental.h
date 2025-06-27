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

class IStruct_Incremental3 {
public:
    virtual BOOL vmethod_inc3_0x00() = 0;   // field_0x00
    virtual BOOL vmethod_inc3_0x04() = 0;   // field_0x04
    virtual void vmethod_inc3_0x08() = 0;   // field_0x08
    virtual void vmethod_inc3_0x0c() = 0;   // field_0x0c
    virtual void vmethod_inc3_0x10() = 0;   // field_0x10
    virtual void vmethod_inc3_0x14() = 0;   // field_0x14
    virtual void vmethod_inc3_0x18() = 0;   // field_0x18
    virtual void vmethod_inc3_0x1c() = 0;   // field_0x1c
    virtual void vmethod_inc3_0x20() = 0;   // field_0x20
    virtual void vmethod_inc3_0x24() = 0;   // field_0x24
    virtual void vmethod_inc3_0x28() = 0;   // field_0x28
    virtual void vmethod_inc3_0x2c() = 0;   // field_0x2c
    virtual void vmethod_inc3_0x30() = 0;   // field_0x30
    virtual void vmethod_inc3_0x34() = 0;   // field_0x34
    virtual void vmethod_inc3_0x38() = 0;   // field_0x38
    virtual void vmethod_inc3_0x3c() = 0;   // field_0x3c
    virtual void vmethod_inc3_0x40() = 0;   // field_0x40
    virtual BOOL vmethod_inc3_0x44() = 0;   // field_0x44
    virtual void vmethod_inc3_0x48() = 0;   // field_0x48
    virtual void vmethod_inc3_0x4c() = 0;   // field_0x4c
    virtual void vmethod_inc3_0x50() = 0;   // field_0x50
    virtual void vmethod_inc3_0x54() = 0;   // field_0x54
    virtual void vmethod_inc3_0x58() = 0;   // field_0x58
    virtual void vmethod_inc3_0x5c() = 0;   // field_0x5c
    virtual void vmethod_inc3_0x60() = 0;   // field_0x60
    virtual void vmethod_inc3_0x64() = 0;   // field_0x64
    virtual void vmethod_inc3_0x68() = 0;   // field_0x68
    virtual void vmethod_inc3_0x6c() = 0;   // field_0x6c
    virtual void vmethod_inc3_0x70() = 0;   // field_0x70
    virtual void vmethod_inc3_0x74() = 0;   // field_0x74
    virtual void vmethod_inc3_0x78() = 0;   // field_0x78
    virtual void vmethod_inc3_0x7c() = 0;   // field_0x7c
    virtual void vmethod_inc3_0x80() = 0;   // field_0x80
    virtual void vmethod_inc3_0x84() = 0;   // field_0x84
    virtual void vmethod_inc3_0x88() = 0;   // field_0x88
    virtual void vmethod_inc3_0x8c() = 0;   // field_0x8c
    virtual void vmethod_inc3_0x90() = 0;   // field_0x90
    virtual void vmethod_inc3_0x94() = 0;   // field_0x94
    virtual void vmethod_inc3_0x98() = 0;   // field_0x98
    virtual void vmethod_inc3_0x9c() = 0;   // field_0x9c
    virtual void vmethod_inc3_0xa0() = 0;   // field_0xa0
    virtual void vmethod_inc3_0xa4() = 0;   // field_0xa4
    virtual void vmethod_inc3_0xa8() = 0;   // field_0xa8
    virtual void vmethod_inc3_0xac() = 0;   // field_0xac
    virtual void vmethod_inc3_0xb0() = 0;   // field_0xb0
    virtual void vmethod_inc3_0xb8() = 0;   // field_0xb8
    virtual void vmethod_inc3_0xbc() = 0;   // field_0xbc
    virtual void vmethod_inc3_0xc0() = 0;   // field_0xc0
    virtual void vmethod_inc3_0xc4() = 0;   // field_0xc4
    virtual void vmethod_inc3_0xc8() = 0;   // field_0xc8
    virtual void vmethod_inc3_0xcc() = 0;   // field_0xcc
    virtual void vmethod_inc3_0xd0() = 0;   // field_0xd0
    virtual void vmethod_inc3_0xd4() = 0;   // field_0xd4
    virtual void vmethod_inc3_0xd8() = 0;   // field_0xd8
    virtual void vmethod_inc3_0xe0() = 0;   // field_0xe0
    virtual void vmethod_inc3_0xe4() = 0;   // field_0xe4
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
