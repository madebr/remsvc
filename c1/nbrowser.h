#ifndef NBROWSER_H
#define NBROWSER_H

#include "decomp.h"

#include <stdlib.h>

class Symbol_t;
class s_defn;
class SBREnabled;
class SBRDisabled;

struct SbrKey{};

// ??_7SBRDisabled@@6B@
// const SBRDisabled::`vftable'

// ??_7SBREnabled@@6B@
// const SBREnabled::`vftable'

// ?DisableBrowser@@3HA
// int DisableBrowser

// ?BrowserAborted@@3HA
// int BrowserAborted

// ?last_line@@3JA
// long last_line

// ??_C@_03KBID@w?$CLb?$AA@
// "w+b"

// ??_C@_03LLMP@r?$CLb?$AA@
// "r+b"

// ??_C@_0N@GJJ@?4?2nbrowser?4c?$AA@
// ".\\nbrowser.c"

// ?SBR_SymRefBuffer@@3PAVSymbol_t@@A
// class Symbol_t *SBR_SymRefBuffer

// ?SBR_BufferMacro@@3HA
// int SBR_BufferMacro

// ?pStrBuffer@@3PADA
// char *pStrBuffer

// ?PCHMarkEmitted@@3HA
// int PCHMarkEmitted

// ?GetStr@@YAPADXZ
// char * __cdecl GetStr(void)

// ?build_macrodef@@YAXPAULazyQueueEntry@@PAUs_defn@@@Z
// void __cdecl build_macrodef(struct LazyQueueEntry *, struct s_defn *)

// ?SaveFileName@@YAXPAULazyQueueEntry@@@Z
// void __cdecl SaveFileName(struct LazyQueueEntry *)

// ?strsave@@YAPADPBD@Z
// char * __cdecl strsave(char const *)

// ?sbr_set_sym@@YAXPAULazyQueueEntry@@PAVSymbol_t@@@Z
// void __cdecl sbr_set_sym(struct LazyQueueEntry *, class Symbol_t *)

// ?build_symdef@@YAXPAULazyQueueEntry@@PAVSymbol_t@@@Z
// void __cdecl build_symdef(struct LazyQueueEntry *, class Symbol_t *)

// ?setSymDef@@YAXPAULazyQueueEntry@@PAVSymbol_t@@@Z
// void __cdecl setSymDef(struct LazyQueueEntry *, class Symbol_t *)

// ?build_macroref@@YAXPAULazyQueueEntry@@PAUs_defn@@@Z
// void __cdecl build_macroref(struct LazyQueueEntry *, struct s_defn *)

// ?build_symref@@YAXPAULazyQueueEntry@@PAVSymbol_t@@@Z
// void __cdecl build_symref(struct LazyQueueEntry *, class Symbol_t *)

// ?symNeedsDecl@@YAHPAULazyQueueEntry@@PAVSymbol_t@@@Z
// int __cdecl symNeedsDecl(struct LazyQueueEntry *, class Symbol_t *)

// ?build_error@@YAXPAULazyQueueEntry@@@Z
// void __cdecl build_error(struct LazyQueueEntry *)

// ?BuildEntry@@YAXPAULazyQueueEntry@@PAVSymbol_t@@@Z
// void __cdecl BuildEntry(struct LazyQueueEntry *, class Symbol_t *)

// ?setSymRef@@YAXPAULazyQueueEntry@@PAVSymbol_t@@@Z
// void __cdecl setSymRef(struct LazyQueueEntry *, class Symbol_t *)

// ?AbortBrowser@@YAXXZ
// void __cdecl AbortBrowser(void)

// ?SbrEmitRec@@YAXPAULazyQueueEntry@@@Z
// void __cdecl SbrEmitRec(struct LazyQueueEntry *)

// ?PutSBRRec@@YAXPAULazyQueueEntry@@@Z
// void __cdecl PutSBRRec(struct LazyQueueEntry *)

// ?LazyEnqueue@@YAXEPAVSymbol_t@@@Z
// void __cdecl LazyEnqueue(unsigned char, class Symbol_t *)

enum SbrEmission {
    noEmission = 0,
    fullEmission = 1,
    incEmission = 2,
    sbrNotOpen = 3
};

struct SBR {
public:
    virtual void Finish() = 0;

    virtual void Flush() = 0;

    virtual void Blkend() = 0;

    virtual void Blkbeg() = 0;

    virtual void Modend() = 0;

    virtual void EndOfFile(int) = 0;

    virtual void Module() = 0;

    virtual void Symref(Symbol_t *) = 0;

    virtual void Symdef(Symbol_t *) = 0;

    virtual void Macroref(s_defn *) = 0;

    virtual void Macrodef(s_defn *) = 0;

    virtual void Macroend() = 0;

    virtual void Owner(Symbol_t *) = 0;

    virtual void Error() = 0;

    virtual void Abort() = 0;

    virtual void PCHName(const char *) = 0;

    virtual void PCHMark() = 0;

    virtual void OpenFull() = 0;

    virtual int OpenIcc() = 0;

    virtual void EndRgn() = 0;

    virtual unsigned long keyRef(Symbol_t *) = 0;

    virtual SbrKey keyAssign(SbrKey) = 0;

    virtual void interrupt() = 0;

    virtual void startRgn() = 0;

    // ?Enable@SBR@@SAPAV1@XZ
    // public: static class SBR * __cdecl SBR::Enable(void)

    // ?Disable@SBR@@SAPAV1@XZ
    static SBR * Disable();

    // ?Open@SBR@@SAPAV1@PAD@Z
    static SBR * Open(const char *path);

    // ?Close@SBR@@SAXXZ
    // public: static void __cdecl SBR::Close(void)

    // ?StartRgn@SBR@@QAEXH@Z
    // public: void __thiscall SBR::StartRgn(int)

    // ?Interrupt@SBR@@SAXXZ
    static void Interrupt();

private:
    // ?pSbrEnabled@SBR@@0PAVSBREnabled@@A
    static SBREnabled *pSbrEnabled;

    // ?pSbrDisabled@SBR@@0PAVSBRDisabled@@A
    static SBRDisabled *pSbrDisabled;

protected:
    // ?lineStart@SBR@@1GA
    // protected: static unsigned short SBR::lineStart

    // ?emission@SBR@@1W4SbrEmission@@A
    static SbrEmission emission;

    // ?offPastModule@SBR@@1JA
    // protected: static long SBR::offPastModule
};

// VTABLE: C1 0x00454998
// SIZE 0xc
class SBREnabled : public SBR {
public:
    SBREnabled(const char *path)
    : m_path(strdup(path))
    , m_field_0x8(0) {
    }

    ~SBREnabled() {
        free(m_path);
    }

    // ?Finish@SBREnabled@@UAEXXZ
    void Finish() override;

    // ?OpenFull@SBREnabled@@UAEXXZ
    void OpenFull() override;

    // ?OpenIcc@SBREnabled@@UAEHXZ
    int OpenIcc() override;

    // ?EndRgn@SBREnabled@@UAEXXZ
    void EndRgn() override;

    // ?Flush@SBREnabled@@UAEXXZ
    void Flush() override;

    // ?Blkend@SBREnabled@@UAEXXZ
    void Blkend() override;

    // ?Blkbeg@SBREnabled@@UAEXXZ
    void Blkbeg() override;

    // ?Abort@SBREnabled@@UAEXXZ
    void Abort() override;

    // ?Error@SBREnabled@@UAEXXZ
    void Error() override;

    // ?Modend@SBREnabled@@UAEXXZ
    void Modend() override;

    // ?EndOfFile@SBREnabled@@UAEXH@Z
    void EndOfFile(int) override;

    // ?Module@SBREnabled@@UAEXXZ
    void Module() override;

    // ?Symref@SBREnabled@@UAEXPAVSymbol_t@@@Z
    void Symref(Symbol_t *) override;

    // ?Symdef@SBREnabled@@UAEXPAVSymbol_t@@@Z
    void Symdef(Symbol_t *) override;

    // ?Macroref@SBREnabled@@UAEXPAUs_defn@@@Z
    void Macroref(s_defn *) override;

    // ?Macrodef@SBREnabled@@UAEXPAUs_defn@@@Z
    void Macrodef(s_defn *) override;

    // ?Macroend@SBREnabled@@UAEXXZ
    void Macroend() override;

    // ?Owner@SBREnabled@@UAEXPAVSymbol_t@@@Z
    void Owner(Symbol_t *) override;

    // ?PCHName@SBREnabled@@UAEXPAD@Z
    void PCHName(const char *) override;

    // ?PCHMark@SBREnabled@@UAEXXZ
    void PCHMark() override;

    // ?keyRef@SBREnabled@@UAEKPAVSymbol_t@@@Z
    unsigned long keyRef(Symbol_t *) override;

    // ?keyAssign@SBREnabled@@UAE?AUSbrKey@@U2@@Z
    SbrKey keyAssign(SbrKey) override;

    static void Interrupt(SBREnabled *sbr) {
        sbr->interrupt();
    }

private:
    // ?interrupt@SBREnabled@@EAEXXZ
    void interrupt() override;

    // ?startRgn@SBREnabled@@EAEXXZ
    void startRgn() override;

    // ?terminate@SBREnabled@@AAEXXZ
    // private: void __thiscall SBREnabled::terminate(void)

    // ?writeSbrPatchTable@SBREnabled@@AAEXXZ
    // private: void __thiscall SBREnabled::writeSbrPatchTable(void)

private:
    char *m_path;           // field 0x4
    undefined4 m_field_0x8; // field 0x8
};

// VTABLE: C1 0x00454938
// SIZE 0x4
class SBRDisabled : public SBR {
public:
    SBRDisabled() {
        // empty
    }
    ~SBRDisabled() {
        // empty
    }

    // ?EndRgn@SBRDisabled@@UAEXXZ
    void EndRgn() override;

    // ?Symdef@SBRDisabled@@UAEXPAVSymbol_t@@@Z
    void Symdef(Symbol_t *) override;

    // ?Macrodef@SBRDisabled@@UAEXPAUs_defn@@@Z
    void Macrodef(s_defn *) override;

    // ?keyRef@SBRDisabled@@UAEKPAVSymbol_t@@@Z
    unsigned long keyRef(Symbol_t *) override;

    // ?keyAssign@SBRDisabled@@UAE?AUSbrKey@@U2@@Z
    SbrKey keyAssign(SbrKey) override;

    // ?Finish@SBRDisabled@@UAEXXZ
    void Finish() override;

    // ?Flush@SBRDisabled@@UAEXXZ
    void Flush() override;

    // ?Blkend@SBRDisabled@@UAEXXZ
    void Blkend() override;

    // ?Blkbeg@SBRDisabled@@UAEXXZ
    void Blkbeg() override;

    // ?Modend@SBRDisabled@@UAEXXZ
    void Modend() override;

    // ?EndOfFile@SBRDisabled@@UAEXH@Z
    void EndOfFile(int) override;

    // ?Module@SBRDisabled@@UAEXXZ
    void Module() override;

    // ?Symref@SBRDisabled@@UAEXPAVSymbol_t@@@Z
    void Symref(Symbol_t *) override;

    // ?Macroref@SBRDisabled@@UAEXPAUs_defn@@@Z
    void Macroref(s_defn *) override;

    // ?Macroend@SBRDisabled@@UAEXXZ
    void Macroend() override;

    // ?Owner@SBRDisabled@@UAEXPAVSymbol_t@@@Z
    void Owner(Symbol_t *) override;

    // ?Error@SBRDisabled@@UAEXXZ
    void Error() override;

    // ?Abort@SBRDisabled@@UAEXXZ
    void Abort() override;

    // ?PCHName@SBRDisabled@@UAEXPAD@Z
    void PCHName(const char *) override;

    // ?PCHMark@SBRDisabled@@UAEXXZ
    void PCHMark() override;

    // ?OpenFull@SBRDisabled@@UAEXXZ
    void OpenFull() override;

    // ?OpenIcc@SBRDisabled@@UAEHXZ
    int OpenIcc() override;
private:
    // ?startRgn@SBRDisabled@@EAEXXZ
    void startRgn() override;

    // ?interrupt@SBRDisabled@@EAEXXZ
    void interrupt() override;
};

// ?pSbr@@3PAVSBR@@A
extern SBR *pSbr;

// ?IncCurSbrPatch@@YAXXZ
// void __cdecl IncCurSbrPatch(void)

// ?fSeekPastModule@SBR@@SAHXZ
// public: static int __cdecl SBR::fSeekPastModule(void)

// ?adjustPchLine@SBR@@QAEXXZ
// public: void __thiscall SBR::adjustPchLine(void)

#endif /* NBROWSER_H */
