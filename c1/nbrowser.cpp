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
// protected: static enum SbrEmission SBR::emission

// GLOBAL: MSVC5_C1 0x000003cc
// ?offPastModule@SBR@@1JA
// protected: static long SBR::offPastModule

// GLOBAL: MSVC5_C1 0x000003d0
// ?pSbr@@3PAVSBR@@A
// class SBR *pSbr

// GLOBAL: MSVC5_C1 0x000003d4
// ?pSbrEnabled@SBR@@0PAVSBREnabled@@A
// private: static class SBREnabled *SBR::pSbrEnabled

// GLOBAL: MSVC5_C1 0x000003d8
// ?pSbrDisabled@SBR@@0PAVSBRDisabled@@A
// private: static class SBRDisabled *SBR::pSbrDisabled

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
// public: static class SBR * __cdecl SBR::Disable(void)

// FUNCTION: MSVC5_C1 0x00019270
// ?Open@SBR@@SAPAV1@PAD@Z
// public: static class SBR * __cdecl SBR::Open(char *)

// FUNCTION: MSVC5_C1 0x000192e0
// ?Close@SBR@@SAXXZ
// public: static void __cdecl SBR::Close(void)

// FUNCTION: MSVC5_C1 0x00019330
// ?Finish@SBREnabled@@UAEXXZ
// public: virtual void __thiscall SBREnabled::Finish(void)

// FUNCTION: MSVC5_C1 0x000193c0
// ?Interrupt@SBR@@SAXXZ
// FUNCTION: C1 0x00442a47
void  SBR::Interrupt()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00019420
// ?interrupt@SBREnabled@@EAEXXZ
// private: virtual void __thiscall SBREnabled::interrupt(void)

// FUNCTION: MSVC5_C1 0x00019480
// ?OpenFull@SBREnabled@@UAEXXZ
// public: virtual void __thiscall SBREnabled::OpenFull(void)

// FUNCTION: MSVC5_C1 0x00019540
// ?OpenIcc@SBREnabled@@UAEHXZ
// public: virtual int __thiscall SBREnabled::OpenIcc(void)

// FUNCTION: MSVC5_C1 0x00019740
// ?StartRgn@SBR@@QAEXH@Z
// public: void __thiscall SBR::StartRgn(int)

// FUNCTION: MSVC5_C1 0x00019790
// ?IncCurSbrPatch@@YAXXZ
// void __cdecl IncCurSbrPatch(void)

// FUNCTION: MSVC5_C1 0x000197b0
// ?startRgn@SBREnabled@@EAEXXZ
// private: virtual void __thiscall SBREnabled::startRgn(void)

// FUNCTION: MSVC5_C1 0x00019810
// ?startRgn@SBRDisabled@@EAEXXZ
// private: virtual void __thiscall SBRDisabled::startRgn(void)

// FUNCTION: MSVC5_C1 0x00019820
// ?EndRgn@SBREnabled@@UAEXXZ
// public: virtual void __thiscall SBREnabled::EndRgn(void)

// FUNCTION: MSVC5_C1 0x00019870
// ?EndRgn@SBRDisabled@@UAEXXZ
// public: virtual void __thiscall SBRDisabled::EndRgn(void)

// FUNCTION: MSVC5_C1 0x000198c0
// ?Flush@SBREnabled@@UAEXXZ
// public: virtual void __thiscall SBREnabled::Flush(void)

// FUNCTION: MSVC5_C1 0x000198d0
// ?Blkend@SBREnabled@@UAEXXZ
// public: virtual void __thiscall SBREnabled::Blkend(void)

// FUNCTION: MSVC5_C1 0x00019900
// ?Blkbeg@SBREnabled@@UAEXXZ
// public: virtual void __thiscall SBREnabled::Blkbeg(void)

// FUNCTION: MSVC5_C1 0x00019920
// ?Abort@SBREnabled@@UAEXXZ
// public: virtual void __thiscall SBREnabled::Abort(void)

// FUNCTION: MSVC5_C1 0x00019940
// ?terminate@SBREnabled@@AAEXXZ
// private: void __thiscall SBREnabled::terminate(void)

// FUNCTION: MSVC5_C1 0x00019970
// ?Error@SBREnabled@@UAEXXZ
// public: virtual void __thiscall SBREnabled::Error(void)

// FUNCTION: MSVC5_C1 0x00019990
// ?Modend@SBREnabled@@UAEXXZ
// public: virtual void __thiscall SBREnabled::Modend(void)

// FUNCTION: MSVC5_C1 0x000199a0
// ?EndOfFile@SBREnabled@@UAEXH@Z
// public: virtual void __thiscall SBREnabled::EndOfFile(int)

// FUNCTION: MSVC5_C1 0x000199c0
// ?Module@SBREnabled@@UAEXXZ
// public: virtual void __thiscall SBREnabled::Module(void)

// FUNCTION: MSVC5_C1 0x000199d0
// ?Symref@SBREnabled@@UAEXPAVSymbol_t@@@Z
// public: virtual void __thiscall SBREnabled::Symref(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00019a00
// ?Symdef@SBREnabled@@UAEXPAVSymbol_t@@@Z
// public: virtual void __thiscall SBREnabled::Symdef(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00019a20
// ?Symdef@SBRDisabled@@UAEXPAVSymbol_t@@@Z
// public: virtual void __thiscall SBRDisabled::Symdef(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00019a40
// ?Macroref@SBREnabled@@UAEXPAUs_defn@@@Z
// public: virtual void __thiscall SBREnabled::Macroref(struct s_defn *)

// FUNCTION: MSVC5_C1 0x00019a70
// ?Macrodef@SBREnabled@@UAEXPAUs_defn@@@Z
// public: virtual void __thiscall SBREnabled::Macrodef(struct s_defn *)

// FUNCTION: MSVC5_C1 0x00019aa0
// ?Macrodef@SBRDisabled@@UAEXPAUs_defn@@@Z
// public: virtual void __thiscall SBRDisabled::Macrodef(struct s_defn *)

// FUNCTION: MSVC5_C1 0x00019ac0
// ?Macroend@SBREnabled@@UAEXXZ
// public: virtual void __thiscall SBREnabled::Macroend(void)

// FUNCTION: MSVC5_C1 0x00019ad0
// ?Owner@SBREnabled@@UAEXPAVSymbol_t@@@Z
// public: virtual void __thiscall SBREnabled::Owner(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00019af0
// ?PCHName@SBREnabled@@UAEXPAD@Z
// public: virtual void __thiscall SBREnabled::PCHName(char *)

// FUNCTION: MSVC5_C1 0x00019b30
// ?PCHMark@SBREnabled@@UAEXXZ
// public: virtual void __thiscall SBREnabled::PCHMark(void)

// FUNCTION: MSVC5_C1 0x00019b70
// ?writeSbrPatchTable@SBREnabled@@AAEXXZ
// private: void __thiscall SBREnabled::writeSbrPatchTable(void)

// FUNCTION: MSVC5_C1 0x00019cd0
// ?keyRef@SBREnabled@@UAEKPAVSymbol_t@@@Z
// public: virtual unsigned long __thiscall SBREnabled::keyRef(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00019d00
// ?keyAssign@SBREnabled@@UAE?AUSbrKey@@U2@@Z
// public: virtual struct SbrKey __thiscall SBREnabled::keyAssign(struct SbrKey)

// FUNCTION: MSVC5_C1 0x00019d70
// ?keyRef@SBRDisabled@@UAEKPAVSymbol_t@@@Z
// public: virtual unsigned long __thiscall SBRDisabled::keyRef(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00019d80
// ?keyAssign@SBRDisabled@@UAE?AUSbrKey@@U2@@Z
// public: virtual struct SbrKey __thiscall SBRDisabled::keyAssign(struct SbrKey)

// FUNCTION: MSVC5_C1 0x00019d90
// ?fSeekPastModule@SBR@@SAHXZ
// public: static int __cdecl SBR::fSeekPastModule(void)

// FUNCTION: MSVC5_C1 0x00019db0
// ?adjustPchLine@SBR@@QAEXXZ
// public: void __thiscall SBR::adjustPchLine(void)

// FUNCTION: MSVC5_C1 0x00019e30
// ?Finish@SBRDisabled@@UAEXXZ
// public: virtual void __thiscall SBRDisabled::Finish(void)

// FUNCTION: MSVC5_C1 0x00019e40
// ?Flush@SBRDisabled@@UAEXXZ
// public: virtual void __thiscall SBRDisabled::Flush(void)

// FUNCTION: MSVC5_C1 0x00019e50
// ?Blkend@SBRDisabled@@UAEXXZ
// public: virtual void __thiscall SBRDisabled::Blkend(void)

// FUNCTION: MSVC5_C1 0x00019e60
// ?Blkbeg@SBRDisabled@@UAEXXZ
// public: virtual void __thiscall SBRDisabled::Blkbeg(void)

// FUNCTION: MSVC5_C1 0x00019e70
// ?Modend@SBRDisabled@@UAEXXZ
// public: virtual void __thiscall SBRDisabled::Modend(void)

// FUNCTION: MSVC5_C1 0x00019e80
// ?EndOfFile@SBRDisabled@@UAEXH@Z
// public: virtual void __thiscall SBRDisabled::EndOfFile(int)

// FUNCTION: MSVC5_C1 0x00019e90
// ?Module@SBRDisabled@@UAEXXZ
// public: virtual void __thiscall SBRDisabled::Module(void)

// FUNCTION: MSVC5_C1 0x00019ea0
// ?Symref@SBRDisabled@@UAEXPAVSymbol_t@@@Z
// public: virtual void __thiscall SBRDisabled::Symref(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00019eb0
// ?Macroref@SBRDisabled@@UAEXPAUs_defn@@@Z
// public: virtual void __thiscall SBRDisabled::Macroref(struct s_defn *)

// FUNCTION: MSVC5_C1 0x00019ec0
// ?Macroend@SBRDisabled@@UAEXXZ
// public: virtual void __thiscall SBRDisabled::Macroend(void)

// FUNCTION: MSVC5_C1 0x00019ed0
// ?Owner@SBRDisabled@@UAEXPAVSymbol_t@@@Z
// public: virtual void __thiscall SBRDisabled::Owner(class Symbol_t *)

// FUNCTION: MSVC5_C1 0x00019ee0
// ?Error@SBRDisabled@@UAEXXZ
// public: virtual void __thiscall SBRDisabled::Error(void)

// FUNCTION: MSVC5_C1 0x00019ef0
// ?Abort@SBRDisabled@@UAEXXZ
// public: virtual void __thiscall SBRDisabled::Abort(void)

// FUNCTION: MSVC5_C1 0x00019f00
// ?PCHName@SBRDisabled@@UAEXPAD@Z
// public: virtual void __thiscall SBRDisabled::PCHName(char *)

// FUNCTION: MSVC5_C1 0x00019f10
// ?PCHMark@SBRDisabled@@UAEXXZ
// public: virtual void __thiscall SBRDisabled::PCHMark(void)

// FUNCTION: MSVC5_C1 0x00019f20
// ?OpenFull@SBRDisabled@@UAEXXZ
// public: virtual void __thiscall SBRDisabled::OpenFull(void)

// FUNCTION: MSVC5_C1 0x00019f30
// ?OpenIcc@SBRDisabled@@UAEHXZ
// public: virtual int __thiscall SBRDisabled::OpenIcc(void)

// FUNCTION: MSVC5_C1 0x00019f40
// ?interrupt@SBRDisabled@@EAEXXZ
// private: virtual void __thiscall SBRDisabled::interrupt(void)

