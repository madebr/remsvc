#include "sigmgr.h"

#include "globals.h"

// GLOBAL: MSVC5_C1 0x000001c0
// ??_7SigMgrStub@@6BIPMSigMgr@@@
// const SigMgrStub::`vftable'{for `IPMSigMgr'}

// GLOBAL: MSVC5_C1 0x000001d0
// ??_7SigMgrStub@@6BFESigMgr@@@
// const SigMgrStub::`vftable'{for `FESigMgr'}

// GLOBAL: MSVC5_C1 0x000001e8
// ??_7SigMgr@@6BIPMSigMgr@@@
// const SigMgr::`vftable'{for `IPMSigMgr'}

// GLOBAL: MSVC5_C1 0x000001f8
// ??_7SigMgr@@6BFESigMgr@@@
// const SigMgr::`vftable'{for `FESigMgr'}

// GLOBAL: MSVC5_C1 0x00000210
// ??_7IPMSigMgr@@6B@
// const IPMSigMgr::`vftable'

// GLOBAL: MSVC5_C1 0x00001968
// ?level@SigMgr@@0IA
// private: static unsigned int SigMgr::level

// GLOBAL: MSVC5_C1 0x00007f68
// ?rgSigMgrStack@SigMgr@@0PAPAV1@A
// private: static class SigMgr **SigMgr::rgSigMgrStack

// FUNCTION: MSVC5_C1 0x0003ed10
// ?open@FESigMgr@@SAHHPAPAU1@PAPAUIPMSigMgr@@@Z
// FUNCTION: C1 0x0041a434
bool32 FESigMgr::open(bool32 enable, FESigMgr **feSigMgr, IPMSigMgr **ipmSigMgr)
{
    if (enable) {
        NOT_IMPLEMENTED();
    } else {
        SigMgrStub *stub = new SigMgrStub;
        *feSigMgr = static_cast<FESigMgr *>(stub);
        *ipmSigMgr = static_cast<IPMSigMgr *>(stub);
    }
    return TRUE;
}

// FUNCTION: MSVC5_C1 0x0003edc0
// ?noteOpenFile@SigMgrStub@@UAEHPAUIPMSigMgr@@@Z
// public: virtual int __thiscall SigMgrStub::noteOpenFile(struct IPMSigMgr *)

// FUNCTION: MSVC5_C1 0x0003edd0
// ?noteCloseFile@SigMgrStub@@UAEHPAUIPMSigMgr@@@Z
// public: virtual int __thiscall SigMgrStub::noteCloseFile(struct IPMSigMgr *)

// FUNCTION: MSVC5_C1 0x0003ede0
// ?sigToCurChar@SigMgrStub@@UAEXXZ
// public: virtual void __thiscall SigMgrStub::sigToCurChar(void)

// FUNCTION: MSVC5_C1 0x0003edf0
// ?freshBuf@SigMgrStub@@UAEXXZ
// public: virtual void __thiscall SigMgrStub::freshBuf(void)

// FUNCTION: MSVC5_C1 0x0003ee00
// ?close@SigMgrStub@@UAEXXZ
// public: virtual void __thiscall SigMgrStub::close(void)

// FUNCTION: MSVC5_C1 0x0003ee10
// ?preceedingRgn@SigMgrStub@@UAEHPAKPAJ@Z
// public: virtual int __thiscall SigMgrStub::preceedingRgn(unsigned long *, long *)

// FUNCTION: MSVC5_C1 0x0003ee20
// ?nextRgn@SigMgrStub@@UAEHJPAKPAJ@Z
// public: virtual int __thiscall SigMgrStub::nextRgn(long, unsigned long *, long *)

// FUNCTION: MSVC5_C1 0x0003ee30
// ?sigNonSource@SigMgrStub@@UAEXPAEJ@Z
// public: virtual void __thiscall SigMgrStub::sigNonSource(unsigned char *, long)

// FUNCTION: MSVC5_C1 0x0003ee40
// ?noteOpenFile@SigMgr@@UAEHPAUIPMSigMgr@@@Z
// public: virtual int __thiscall SigMgr::noteOpenFile(struct IPMSigMgr *)

// FUNCTION: MSVC5_C1 0x0003eef0
// ?noteCloseFile@SigMgr@@UAEHPAUIPMSigMgr@@@Z
// public: virtual int __thiscall SigMgr::noteCloseFile(struct IPMSigMgr *)

// FUNCTION: MSVC5_C1 0x0003ef50
// ?freshBuf@SigMgr@@UAEXXZ
// public: virtual void __thiscall SigMgr::freshBuf(void)

// FUNCTION: MSVC5_C1 0x0003ef60
// ?sigToCurChar@SigMgr@@UAEXXZ
// public: virtual void __thiscall SigMgr::sigToCurChar(void)

// FUNCTION: MSVC5_C1 0x0003efa0
// ?close@SigMgr@@UAEXXZ
// public: virtual void __thiscall SigMgr::close(void)

// FUNCTION: MSVC5_C1 0x0003efb0
// ?preceedingRgn@SigMgr@@UAEHPAKPAJ@Z
// public: virtual int __thiscall SigMgr::preceedingRgn(unsigned long *, long *)

// FUNCTION: MSVC5_C1 0x0003eff0
// ?nextRgn@SigMgr@@UAEHJPAKPAJ@Z
// public: virtual int __thiscall SigMgr::nextRgn(long, unsigned long *, long *)

// FUNCTION: MSVC5_C1 0x0003f1a0
// ?sigNonSource@SigMgr@@UAEXPAEJ@Z
// public: virtual void __thiscall SigMgr::sigNonSource(unsigned char *, long)

// FUNCTION: MSVC5_C1 0x0003f1d0
// ?reset@SigMgrStub@@UAEXXZ
// public: virtual void __thiscall SigMgrStub::reset(void)

// FUNCTION: MSVC5_C1 0x0003f1e0
// ?reset@SigMgr@@UAEXXZ
// public: virtual void __thiscall SigMgr::reset(void)

