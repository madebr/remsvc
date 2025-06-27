#pragma once

class ISourceBrowser {
public:
    virtual void vtable_0x00() = 0;
    virtual void vtable_0x04() = 0;
    virtual void vtable_0x08() = 0;
    virtual void vtable_0x0c() = 0;
    virtual void vtable_0x10() = 0;
    virtual void vtable_0x14() = 0;
    virtual void vtable_0x18() = 0;
    virtual void vtable_0x1c() = 0;
    virtual void vtable_0x20() = 0;
    virtual void vtable_0x24() = 0;
    virtual void vtable_0x28() = 0;
    virtual void vtable_0x2c() = 0;
    virtual void vtable_0x30() = 0;
    virtual void vtable_0x34() = 0;
    virtual void vtable_0x38() = 0;
    virtual void vtable_0x3c() = 0;
    virtual void vtable_0x40() = 0;
    virtual void vtable_0x44() = 0;
    virtual void vtable_0x48() = 0;
    virtual void vtable_0x4c() = 0;
    virtual void vtable_0x50() = 0;
    virtual void vtable_0x54() = 0;
    virtual void vtable_0x58() = 0;
    virtual void vtable_0x5c() = 0;
};

ISourceBrowser * __fastcall InitializeSourceBrowser(const char *path);

ISourceBrowser * GetDummySourceBrowser();
