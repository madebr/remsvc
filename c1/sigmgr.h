#ifndef SIGMGR_H
#define SIGMGR_H

#include "decomp.h"

// ?rgSigMgrStack@SigMgr@@0PAPAV1@A
// private: static class SigMgr **SigMgr::rgSigMgrStack

class IPMSigMgr {
    //virtual preceedingRgn = 0;
    //virtual nextRgn = 0;
    //virtual reset = 0;

    // ??_7IPMSigMgr@@6B@
    // const IPMSigMgr::`vftable'
};

class FESigMgr {
public:
    // virtual noteOpenFile = 0;
    // virtual noteCloseFile = 0;
    // virtual sigToCurChar = 0;
    // virtual freshBuf = 0;
    // virtual close = 0;
    // virtual sigNonSource = 0;
    // virtual adjustForCurrentChar = 0;


    // ?open@FESigMgr@@SAHHPAPAU1@PAPAUIPMSigMgr@@@Z
    static bool32 open(bool32 enable, FESigMgr **feSigMgr, IPMSigMgr **ipmSigMgr);
};

class SigMgr : public FESigMgr, public IPMSigMgr {

    // ??_7SigMgr@@6BIPMSigMgr@@@
    // const SigMgr::`vftable'{for `IPMSigMgr'}

    // ??_7SigMgr@@6BFESigMgr@@@
    // const SigMgr::`vftable'{for `FESigMgr'}

    // ?noteOpenFile@SigMgr@@UAEHPAUIPMSigMgr@@@Z
    // public: virtual int __thiscall SigMgr::noteOpenFile(struct IPMSigMgr *)

    // ?noteCloseFile@SigMgr@@UAEHPAUIPMSigMgr@@@Z
    // public: virtual int __thiscall SigMgr::noteCloseFile(struct IPMSigMgr *)

    // ?freshBuf@SigMgr@@UAEXXZ
    // public: virtual void __thiscall SigMgr::freshBuf(void)

    // ?sigToCurChar@SigMgr@@UAEXXZ
    // public: virtual void __thiscall SigMgr::sigToCurChar(void)

    // ?close@SigMgr@@UAEXXZ
    // public: virtual void __thiscall SigMgr::close(void)

    // ?preceedingRgn@SigMgr@@UAEHPAKPAJ@Z
    // public: virtual int __thiscall SigMgr::preceedingRgn(unsigned long *, long *)

    // ?nextRgn@SigMgr@@UAEHJPAKPAJ@Z
    // public: virtual int __thiscall SigMgr::nextRgn(long, unsigned long *, long *)

    // ?sigNonSource@SigMgr@@UAEXPAEJ@Z
    // public: virtual void __thiscall SigMgr::sigNonSource(unsigned char *, long)

    // ?reset@SigMgr@@UAEXXZ
    // public: virtual void __thiscall SigMgr::reset(void)

    // ?level@SigMgr@@0IA
    // private: static unsigned int SigMgr::level
};

class SigMgrStub : public FESigMgr, public IPMSigMgr {
    // ??_7SigMgrStub@@6BIPMSigMgr@@@
    // const SigMgrStub::`vftable'{for `IPMSigMgr'}

    // ??_7SigMgrStub@@6BFESigMgr@@@
    // const SigMgrStub::`vftable'{for `FESigMgr'}

    // ?noteOpenFile@SigMgrStub@@UAEHPAUIPMSigMgr@@@Z
    // public: virtual int __thiscall SigMgrStub::noteOpenFile(struct IPMSigMgr *)

    // ?noteCloseFile@SigMgrStub@@UAEHPAUIPMSigMgr@@@Z
    // public: virtual int __thiscall SigMgrStub::noteCloseFile(struct IPMSigMgr *)

    // ?sigToCurChar@SigMgrStub@@UAEXXZ
    // public: virtual void __thiscall SigMgrStub::sigToCurChar(void)

    // ?freshBuf@SigMgrStub@@UAEXXZ
    // public: virtual void __thiscall SigMgrStub::freshBuf(void)

    // ?close@SigMgrStub@@UAEXXZ
    // public: virtual void __thiscall SigMgrStub::close(void)

    // ?preceedingRgn@SigMgrStub@@UAEHPAKPAJ@Z
    // public: virtual int __thiscall SigMgrStub::preceedingRgn(unsigned long *, long *)

    // ?nextRgn@SigMgrStub@@UAEHJPAKPAJ@Z
    // public: virtual int __thiscall SigMgrStub::nextRgn(long, unsigned long *, long *)

    // ?sigNonSource@SigMgrStub@@UAEXPAEJ@Z
    // public: virtual void __thiscall SigMgrStub::sigNonSource(unsigned char *, long)

    // ?reset@SigMgrStub@@UAEXXZ
    // public: virtual void __thiscall SigMgrStub::reset(void)
};

#endif /* SIGMGR_H */
