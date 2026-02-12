#include "nbrowser.h"

#include "decomp.h"

// GLOBAL: MSVC5_C1 0x00000090
// ??_7SBRDisabled@@6B@
// const SBRDisabled::`vftable'

// GLOBAL: MSVC5_C1 0x000000f0
// ??_7SBREnabled@@6B@
// const SBREnabled::`vftable'

// GLOBAL: MSVC5_C1 0x000003b8
// ?DisableBrowser@@3HA
// int DisableBrowser

// GLOBAL: MSVC5_C1 0x000003bc
// ?BrowserAborted@@3HA
// int BrowserAborted

// GLOBAL: MSVC5_C1 0x000003c0
// ?last_line@@3JA
// long last_line

// GLOBAL: MSVC5_C1 0x000003c8
// ?emission@SBR@@1W4SbrEmission@@A
// GLOBAL: C1 0x0045b564
SbrEmission SBR::emission = noEmission;

// GLOBAL: MSVC5_C1 0x000003cc
// ?offPastModule@SBR@@1JA
// protected: static long SBR::offPastModule

// GLOBAL: MSVC5_C1 0x000003d0
// ?pSbr@@3PAVSBR@@A
// GLOBAL: C1 0x0045b56c
SBR *pSbr;

// GLOBAL: MSVC5_C1 0x000003d4
// ?pSbrEnabled@SBR@@0PAVSBREnabled@@A
// GLOBAL: C1 0x0045b570
SBREnabled *SBR::pSbrEnabled = NULL;

// GLOBAL: MSVC5_C1 0x000003d8
// ?pSbrDisabled@SBR@@0PAVSBRDisabled@@A
// GLBOAL: C1 0x0045b574
SBRDisabled *SBR::pSbrDisabled = NULL;

// GLOBAL: MSVC5_C1 0x000029f8
// ??_C@_03KBID@w?$CLb?$AA@
// "w+b"

// GLOBAL: MSVC5_C1 0x000029fc
// ??_C@_03LLMP@r?$CLb?$AA@
// "r+b"

// GLOBAL: MSVC5_C1 0x00002a00
// ??_C@_0N@GJJ@?4?2nbrowser?4c?$AA@
// ".\\nbrowser.c"

// GLOBAL: MSVC5_C1 0x00003bd8
// ?SBR_SymRefBuffer@@3PAVSymbol_t@@A
// class Symbol_t *SBR_SymRefBuffer

// GLOBAL: MSVC5_C1 0x00003bdc
// ?SBR_BufferMacro@@3HA
// int SBR_BufferMacro

// GLOBAL: MSVC5_C1 0x00003be0
// ?pStrBuffer@@3PADA
// char *pStrBuffer

// GLOBAL: MSVC5_C1 0x00003be4
// ?PCHMarkEmitted@@3HA
// int PCHMarkEmitted

// GLOBAL: MSVC5_C1 0x00003be8
// ?lineStart@SBR@@1GA
// protected: static unsigned short SBR::lineStart

// FUNCTION: MSVC5_C1 0x00018550
// ?GetStr@@YAPADXZ
// char * __cdecl GetStr(void)

// FUNCTION: MSVC5_C1 0x00018600
// ?build_macrodef@@YAXPAULazyQueueEntry@@PAUs_defn@@@Z
// void __cdecl build_macrodef(struct LazyQueueEntry *, struct s_defn *)

// FUNCTION: MSVC5_C1 0x00018660
// ?SaveFileName@@YAXPAULazyQueueEntry@@@Z
// void __cdecl SaveFileName(struct LazyQueueEntry *)

// FUNCTION: MSVC5_C1 0x00018690
// ?strsave@@YAPADPBD@Z
// char * __cdecl strsave(char const *)
// static

// FUNCTION: MSVC5_C1 0x000186d0
// ?sbr_set_sym@@YAXPAULazyQueueEntry@@PAVSymbol_t@@@Z
// void __cdecl sbr_set_sym(struct LazyQueueEntry *, class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00018700
// ?build_symdef@@YAXPAULazyQueueEntry@@PAVSymbol_t@@@Z
// void __cdecl build_symdef(struct LazyQueueEntry *, class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00018870
// ?setSymDef@@YAXPAULazyQueueEntry@@PAVSymbol_t@@@Z
// void __cdecl setSymDef(struct LazyQueueEntry *, class Symbol_t *)
// static

// FUNCTION: MSVC5_C1 0x000188a0
// ?build_macroref@@YAXPAULazyQueueEntry@@PAUs_defn@@@Z
// void __cdecl build_macroref(struct LazyQueueEntry *, struct s_defn *)

// FUNCTION: MSVC5_C1 0x000188e0
// ?build_symref@@YAXPAULazyQueueEntry@@PAVSymbol_t@@@Z
// void __cdecl build_symref(struct LazyQueueEntry *, class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00018930
// ?symNeedsDecl@@YAHPAULazyQueueEntry@@PAVSymbol_t@@@Z
// int __cdecl symNeedsDecl(struct LazyQueueEntry *, class Symbol_t *)
// static

// FUNCTION: MSVC5_C1 0x00018960
// ?build_error@@YAXPAULazyQueueEntry@@@Z
// void __cdecl build_error(struct LazyQueueEntry *)

// FUNCTION: MSVC5_C1 0x00018990
// ?BuildEntry@@YAXPAULazyQueueEntry@@PAVSymbol_t@@@Z
// void __cdecl BuildEntry(struct LazyQueueEntry *, class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00018ae0
// ?setSymRef@@YAXPAULazyQueueEntry@@PAVSymbol_t@@@Z
// void __cdecl setSymRef(struct LazyQueueEntry *, class Symbol_t *)
// static

// FUNCTION: MSVC5_C1 0x00018b30
// ?AbortBrowser@@YAXXZ
// void __cdecl AbortBrowser(void)

// FUNCTION: MSVC5_C1 0x00018b80
// ?SbrEmitRec@@YAXPAULazyQueueEntry@@@Z
// void __cdecl SbrEmitRec(struct LazyQueueEntry *)
// static

// FUNCTION: MSVC5_C1 0x00018cf0
// ?PutSBRRec@@YAXPAULazyQueueEntry@@@Z
// void __cdecl PutSBRRec(struct LazyQueueEntry *)
// static

// FUNCTION: MSVC5_C1 0x000191c0
// ?LazyEnqueue@@YAXEPAVSymbol_t@@@Z
// void __cdecl LazyEnqueue(unsigned char, class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00019230
// ?Enable@SBR@@SAPAV1@XZ
// public: static class SBR * __cdecl SBR::Enable(void)

// FUNCTION: MSVC5_C1 0x00019240
// ?Disable@SBR@@SAPAV1@XZ
// FUNCTION: C1 0x00408335
SBR * SBR::Disable()
{
    if (pSbrDisabled == NULL) {
        pSbrDisabled = new SBRDisabled;
    }
    return pSbrDisabled;
}

// FUNCTION: MSVC5_C1 0x00019270
// ?Open@SBR@@SAPAV1@PAD@Z
// FUNCTION: C1 0x004192e3
SBR * SBR::Open(const char *path)
{
    if (path != NULL) {
        emission = sbrNotOpen;
        pSbrEnabled = new SBREnabled(path);
        return pSbrEnabled;
    } else {
        pSbrDisabled = new SBRDisabled;
        return pSbrDisabled;
    }
}

// FUNCTION: MSVC5_C1 0x000192e0
// ?Close@SBR@@SAXXZ
// public: static void __cdecl SBR::Close(void)

// FUNCTION: MSVC5_C1 0x00019330
// ?Finish@SBREnabled@@UAEXXZ
// FUNCTION: C1 0x0042715f
void SBREnabled::Finish()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x000193c0
// ?Interrupt@SBR@@SAXXZ
// FUNCTION: C1 0x00442a47
void SBR::Interrupt()
{
    if (pSbrEnabled != NULL) {
        SBREnabled::Interrupt(pSbrEnabled);
        delete pSbrEnabled;
        pSbrEnabled = NULL;
    }
    if (pSbrDisabled != NULL) {
        delete pSbrDisabled;
        pSbrDisabled = NULL;
    }
}

// FUNCTION: MSVC5_C1 0x00019420
// ?interrupt@SBREnabled@@EAEXXZ
// FUNCTION: C1 0x00442ab0
void SBREnabled::interrupt()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019480
// ?OpenFull@SBREnabled@@UAEXXZ
// FUNCTION: C1 0x00426fe8
void SBREnabled::OpenFull()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019540
// ?OpenIcc@SBREnabled@@UAEHXZ
// FUNCTION: C1 0x00442b0b
int SBREnabled::OpenIcc()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019740
// ?StartRgn@SBR@@QAEXH@Z
// public: void __thiscall SBR::StartRgn(int)

// FUNCTION: MSVC5_C1 0x00019790
// ?IncCurSbrPatch@@YAXXZ
// void __cdecl IncCurSbrPatch(void)

// FUNCTION: MSVC5_C1 0x000197b0
// ?startRgn@SBREnabled@@EAEXXZ
// FUNCTION: C1 0x00423689
void SBREnabled::startRgn()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019810
// ?startRgn@SBRDisabled@@EAEXXZ
// FUNCTION: C1 0x0040bf0d
void SBRDisabled::startRgn()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019820
// ?EndRgn@SBREnabled@@UAEXXZ
// FUNCTION: C1 0x00442d11
void SBREnabled::EndRgn()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00442d5e
void SBRDisabled::EndRgn()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x000198c0
// ?Flush@SBREnabled@@UAEXXZ
// FUNCTION: C1 0x00423750
void SBREnabled::Flush()
{
    // empty
}

// FUNCTION: MSVC5_C1 0x000198d0
// ?Blkend@SBREnabled@@UAEXXZ
// FUNCTION: C1 0x00422658
void SBREnabled::Blkend()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019900
// ?Blkbeg@SBREnabled@@UAEXXZ
// FUNCTION: C1 0x00422c5f
void SBREnabled::Blkbeg()
{
    NOT_IMPLEMENTED();
}


// FUNCTION: MSVC5_C1 0x00019920
// ?Abort@SBREnabled@@UAEXXZ
// FUNCTION: C1 0x00442da7
void SBREnabled::Abort()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019940
// ?terminate@SBREnabled@@AAEXXZ
// private: void __thiscall SBREnabled::terminate(void)

// FUNCTION: MSVC5_C1 0x00019970
// ?Error@SBREnabled@@UAEXXZ
// FUNCTION: C1 0x00442dc2
void SBREnabled::Error()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019990
// ?Modend@SBREnabled@@UAEXXZ
// FUNCTION: C1 0x0042281b
void SBREnabled::Modend()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x000199a0
// ?EndOfFile@SBREnabled@@UAEXH@Z
// FUNCTION: C1 0x00422860
void SBREnabled::EndOfFile(int)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x000199c0
// ?Module@SBREnabled@@UAEXXZ
// FUNCTION: C1 0x00423263
void SBREnabled::Module()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x000199d0
// ?Symref@SBREnabled@@UAEXPAVSymbol_t@@@Z
// FUNCTION: C1 0x00422c71
void SBREnabled::Symref(Symbol_t *) {
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019a00
// ?Symdef@SBREnabled@@UAEXPAVSymbol_t@@@Z
// FUNCTION: C1 0x00422827
void SBREnabled::Symdef(Symbol_t *)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019a20
// ?Symdef@SBRDisabled@@UAEXPAVSymbol_t@@@Z
// FUNCTION: C1 0x0042708c
void SBRDisabled::Symdef(Symbol_t *)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019a40
// ?Macroref@SBREnabled@@UAEXPAUs_defn@@@Z
// FUNCTION: C1 0x00422875
void SBREnabled::Macroref(s_defn *)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019a70
// ?Macrodef@SBREnabled@@UAEXPAUs_defn@@@Z
// FUNCTION: C1 0x00423377
void SBREnabled::Macrodef(s_defn *) {
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019aa0
// ?Macrodef@SBRDisabled@@UAEXPAUs_defn@@@Z
// FUNCTION: C1 0x0040c194
void SBRDisabled::Macrodef(s_defn *)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019ac0
// ?Macroend@SBREnabled@@UAEXXZ
// FUNCTION: C1 0x00442dd8
void SBREnabled::Macroend()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019ad0
// ?Owner@SBREnabled@@UAEXPAVSymbol_t@@@Z
// FUNCTION: C1 0x00422c94
void SBREnabled::Owner(Symbol_t *) {
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019af0
// ?PCHName@SBREnabled@@UAEXPAD@Z
// FUNCTION: C1 0x00442de4
void SBREnabled::PCHName(const char *)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019b30
// ?PCHMark@SBREnabled@@UAEXXZ
// FUNCTION: C1 0x00425da9
void SBREnabled::PCHMark()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019b70
// ?writeSbrPatchTable@SBREnabled@@AAEXXZ
// private: void __thiscall SBREnabled::writeSbrPatchTable(void)

// FUNCTION: MSVC5_C1 0x00019cd0
// ?keyRef@SBREnabled@@UAEKPAVSymbol_t@@@Z
// FUNCTION: C1 0x00423120
unsigned long SBREnabled::keyRef(Symbol_t *) {
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019d00
// ?keyAssign@SBREnabled@@UAE?AUSbrKey@@U2@@Z
// FUNCTION: C1 0x00422bed
SbrKey SBREnabled::keyAssign(SbrKey) {
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019d70
// ?keyRef@SBRDisabled@@UAEKPAVSymbol_t@@@Z
// FUNCTION: C1 0x00442f87
unsigned long SBRDisabled::keyRef(Symbol_t *)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019d80
// ?keyAssign@SBRDisabled@@UAE?AUSbrKey@@U2@@Z
// FUNCTION: C1 0x00442f96
SbrKey SBRDisabled::keyAssign(SbrKey)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019d90
// ?fSeekPastModule@SBR@@SAHXZ
// public: static int __cdecl SBR::fSeekPastModule(void)

// FUNCTION: MSVC5_C1 0x00019db0
// ?adjustPchLine@SBR@@QAEXXZ
// public: void __thiscall SBR::adjustPchLine(void)

// FUNCTION: MSVC5_C1 0x00019e30
// ?Finish@SBRDisabled@@UAEXXZ
// FUNCTION: C1 0x0041f73c
void SBRDisabled::Finish()
{
    // empty
}

// FUNCTION: MSVC5_C1 0x00019e40
// ?Flush@SBRDisabled@@UAEXXZ
// FUNCTION: C1 0x00443035
void SBRDisabled::Flush()
{
    // empty
}

// FUNCTION: MSVC5_C1 0x00019e50
// ?Blkend@SBRDisabled@@UAEXXZ
// FUNCTION: C1 0x004159e1
void SBRDisabled::Blkend() {
    // empty
}

// FUNCTION: MSVC5_C1 0x00019e60
// ?Blkbeg@SBRDisabled@@UAEXXZ
// FUNCTION: C1 0x004159e0
void SBRDisabled::Blkbeg()
{
    // empty
}

// FUNCTION: MSVC5_C1 0x00019e70
// ?Modend@SBRDisabled@@UAEXXZ
// FUNCTION: C1 0x00443036
void SBRDisabled::Modend()
{
    // empty
}

// FUNCTION: MSVC5_C1 0x00019e80
// ?EndOfFile@SBRDisabled@@UAEXH@Z
// FUNCTION: C1 0x00443037
void SBRDisabled::EndOfFile(int)
{
    // empty
}

// FUNCTION: MSVC5_C1 0x00019e90
// ?Module@SBRDisabled@@UAEXXZ
// FUNCTION: C1 0x0044303a
void SBRDisabled::Module()
{
    // empty
}

// FUNCTION: MSVC5_C1 0x00019ea0
// ?Symref@SBRDisabled@@UAEXPAVSymbol_t@@@Z
// FUNCTION: C1 0x0044303b
void SBRDisabled::Symref(Symbol_t *)
{
    // empty
}

// FUNCTION: MSVC5_C1 0x00019eb0
// ?Macroref@SBRDisabled@@UAEXPAUs_defn@@@Z
// FUNCTION: C1 0x0044303e
void SBRDisabled::Macroref(s_defn *) {
    // empty
}

// FUNCTION: MSVC5_C1 0x00019ec0
// ?Macroend@SBRDisabled@@UAEXXZ
// FUNCTION: C1 0x00443041
void SBRDisabled::Macroend()
{
    // empty
}

// FUNCTION: MSVC5_C1 0x00019ed0
// ?Owner@SBRDisabled@@UAEXPAVSymbol_t@@@Z
// FUNCTION: C1 0x00443042
void SBRDisabled::Owner(Symbol_t *)
{
    // empty
}

// FUNCTION: MSVC5_C1 0x00019ee0
// ?Error@SBRDisabled@@UAEXXZ
// FUNCTION: C1 0x00443045
void SBRDisabled::Error()
{
    // empty
}

// FUNCTION: MSVC5_C1 0x00019ef0
// ?Abort@SBRDisabled@@UAEXXZ
// FUNCTION: C1 0x00443046
void SBRDisabled::Abort()
{
    // empty
}

// FUNCTION: MSVC5_C1 0x00019f00
// ?PCHName@SBRDisabled@@UAEXPAD@Z
// FUNCTION: C1 0x00443047
void SBRDisabled::PCHName(const char *)
{
    // empty
}

// FUNCTION: MSVC5_C1 0x00019f10
// ?PCHMark@SBRDisabled@@UAEXXZ
// FUNCTION: C1 0x0044304a
void SBRDisabled::PCHMark() {
    // empty
}

// FUNCTION: MSVC5_C1 0x00019f20
// ?OpenFull@SBRDisabled@@UAEXXZ
// FUNCTION: C1 0x// public: virtual
void SBRDisabled::OpenFull() {
    SBR::emission = noEmission;
}

// FUNCTION: MSVC5_C1 0x00019f30
// ?OpenIcc@SBRDisabled@@UAEHXZ
// FUNCTION: C1 0x0041c248
int SBRDisabled::OpenIcc()
{
    SBR::emission = noEmission;
    return 1;
}

// FUNCTION: MSVC5_C1 0x00019f40
// ?interrupt@SBRDisabled@@EAEXXZ
// FUNCTION: C1 0x00443056
void SBRDisabled::interrupt()
{
    // empty
}

