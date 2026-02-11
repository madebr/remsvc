#include "ipm.h"

#include <stddef.h>

// GLOBAL: MSVC5_C1 0x00000220
// ??_7StubIPM@@6B@
// const StubIPM::`vftable'

// GLOBAL: MSVC5_C1 0x00000308
// ??_7IPM@@6B@
// const IPM::`vftable'

// GLOBAL: MSVC5_C1 0x000003f0
// ??_7IncrParseMgr@@6B@
// const IncrParseMgr::`vftable'

// GLOBAL: MSVC5_C1 0x00001974
// ?notInASkippableFn@IncrParseMgr@@2HA
// public: static int IncrParseMgr::notInASkippableFn

// GLOBAL: MSVC5_C1 0x00008f68
// ?pIPMSigMgr@@3PAUIPMSigMgr@@A
// GLOBAL: C1 0x0046a310
IPMSigMgr *pIPMSigMgr = NULL;

// GLOBAL: MSVC5_C1 0x00008f70
// ?ciNil@@3UCI@@A
// struct CI ciNil

// FUNCTION: MSVC5_C1 0x0003f200
// _$E31
// static

// FUNCTION: MSVC5_C1 0x0003f210
// _$E30
// static

// FUNCTION: MSVC5_C1 0x0003f240
// ?save@FI@@QBEHPAVBuffer@@@Z
// public: int __thiscall FI::save(class Buffer *) const

// FUNCTION: MSVC5_C1 0x0003f360
// ?reload@FI@@QAEHPAPAE@Z
// public: int __thiscall FI::reload(unsigned char **)

// FUNCTION: MSVC5_C1 0x0003f480
// ?szName@FI@@QBEPBDPAUNameMap@@@Z
// public: char const * __thiscall FI::szName(struct NameMap *) const

// FUNCTION: MSVC5_C1 0x0003f4b0
// ?open@IncrParseMgr@@SAHPAUPDB@@0PAUNameMap@@PAD2PAUIPMSigMgr@@HHHPAPAU1@@Z
// public: static int __cdecl IncrParseMgr::open(struct PDB *, struct PDB *, struct NameMap *, char *, char *, struct IPMSigMgr *, int, int, int, struct IncrParseMgr **)

// FUNCTION: MSVC5_C1 0x0003f690
// ??0IPM@@AAE@PAUPDB@@0PAUNameMap@@PAUIPMSigMgr@@HHH@Z
// private: __thiscall IPM::IPM(struct PDB *, struct PDB *, struct NameMap *, struct IPMSigMgr *, int, int, int)

// FUNCTION: MSVC5_C1 0x0003f8c0
// ?open@IPM@@AAEHPAD0@Z
// private: int __thiscall IPM::open(char *, char *)

// FUNCTION: MSVC5_C1 0x0003fa10
// ?save@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::save(void)

// FUNCTION: MSVC5_C1 0x0003fa50
// ?saveIPM@IPM@@AAEHXZ
// private: int __thiscall IPM::saveIPM(void)

// FUNCTION: MSVC5_C1 0x0003fd30
// ?saveMod@IPM@@AAEHXZ
// private: int __thiscall IPM::saveMod(void)

// FUNCTION: MSVC5_C1 0x0003fff0
// ?reloadIPM@IPM@@AAEHPAUStream@@PAH@Z
// private: int __thiscall IPM::reloadIPM(struct Stream *, int *)

// FUNCTION: MSVC5_C1 0x000402c0
// ?reloadMod@IPM@@AAEHPAUStream@@@Z
// private: int __thiscall IPM::reloadMod(struct Stream *)

// FUNCTION: MSVC5_C1 0x00040560
// ?saveHeader@IPM@@ABEHPAVFI@@@Z
// private: int __thiscall IPM::saveHeader(class FI *) const

// FUNCTION: MSVC5_C1 0x00040790
// ?reloadHeader@IPM@@AAEHPAVFI@@@Z
// private: int __thiscall IPM::reloadHeader(class FI *)

// FUNCTION: MSVC5_C1 0x000408d0
// ?szIPMHeaderStream@IPM@@ABEPBDPAVFI@@QADI@Z
// private: char const * __thiscall IPM::szIPMHeaderStream(class FI *, char *const, unsigned int) const

// FUNCTION: MSVC5_C1 0x00040910
// ?release@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::release(void)

// FUNCTION: MSVC5_C1 0x00040af0
// ?noteStartMod@IPM@@UAEHPAW4FPM@@@Z
// public: virtual int __thiscall IPM::noteStartMod(enum FPM *)

// FUNCTION: MSVC5_C1 0x00040b10
// ?noteStartPchUse@IPM@@UAEHPAW4FPM@@@Z
// public: virtual int __thiscall IPM::noteStartPchUse(enum FPM *)

// FUNCTION: MSVC5_C1 0x00040b30
// ?noteEndMod@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteEndMod(void)

// FUNCTION: MSVC5_C1 0x00040c20
// ?checkHeaderTimestamps@IPM@@AAEHXZ
// private: int __thiscall IPM::checkHeaderTimestamps(void)

// FUNCTION: MSVC5_C1 0x00040e90
// ?noteStartGlobalRegn@IPM@@AAEHHW4Type@Regn@@@Z
// private: int __thiscall IPM::noteStartGlobalRegn(int, enum Regn::Type)

// FUNCTION: MSVC5_C1 0x00040f60
// ?noteEndGlobalRegn@IPM@@AAEHW4Type@Regn@@@Z
// private: int __thiscall IPM::noteEndGlobalRegn(enum Regn::Type)

// FUNCTION: MSVC5_C1 0x00041160
// ?noteStartFn@IPM@@UAEHKGHPAW4FPM@@PAJPAGPAH@Z
// public: virtual int __thiscall IPM::noteStartFn(unsigned long, unsigned short, int, enum FPM *, long *, unsigned short *, int *)

// FUNCTION: MSVC5_C1 0x00041380
// ?noteEndFn@IPM@@UAEHKGHPAW4FPM@@PAH@Z
// public: virtual int __thiscall IPM::noteEndFn(unsigned long, unsigned short, int, enum FPM *, int *)

// FUNCTION: MSVC5_C1 0x000416a0
// ?noteDefine@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteDefine(void)

// FUNCTION: MSVC5_C1 0x000416c0
// ?notePragmaHasGlobalEffect@IPM@@UAEHH@Z
// public: virtual int __thiscall IPM::notePragmaHasGlobalEffect(int)

// FUNCTION: MSVC5_C1 0x000416e0
// ?notePragmaNeedsRegen@IPM@@UAEHH@Z
// public: virtual int __thiscall IPM::notePragmaNeedsRegen(int)

// FUNCTION: MSVC5_C1 0x00041710
// ?noteStartCondCompTrue@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteStartCondCompTrue(void)

// FUNCTION: MSVC5_C1 0x00041740
// ?noteEndCondCompTrue@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteEndCondCompTrue(void)

// FUNCTION: MSVC5_C1 0x00041770
// ?noteStartInclude@IPM@@UAEHPADH@Z
// public: virtual int __thiscall IPM::noteStartInclude(char *, int)

// FUNCTION: MSVC5_C1 0x00041a40
// ?noteEndInclude@IPM@@UAEHG@Z
// public: virtual int __thiscall IPM::noteEndInclude(unsigned short)

// FUNCTION: MSVC5_C1 0x00041cb0
// ?noteStartClassDefn@IPM@@UAEHGK@Z
// public: virtual int __thiscall IPM::noteStartClassDefn(unsigned short, unsigned long)

// FUNCTION: MSVC5_C1 0x00041cc0
// ?noteEndClassDefn@IPM@@UAEHGKPAH@Z
// public: virtual int __thiscall IPM::noteEndClassDefn(unsigned short, unsigned long, int *)

// FUNCTION: MSVC5_C1 0x00041ce0
// ?noteStartInlineMemberFn@IPM@@UAEHGH@Z
// public: virtual int __thiscall IPM::noteStartInlineMemberFn(unsigned short, int)

// FUNCTION: MSVC5_C1 0x00041cf0
// ?noteEndInlineMemberFn@IPM@@UAEHGHPAH@Z
// public: virtual int __thiscall IPM::noteEndInlineMemberFn(unsigned short, int, int *)

// FUNCTION: MSVC5_C1 0x00041d00
// ?noteStartOutOfLineInlineMemberFn@IPM@@AAEHKGH@Z
// private: int __thiscall IPM::noteStartOutOfLineInlineMemberFn(unsigned long, unsigned short, int)

// FUNCTION: MSVC5_C1 0x00041d10
// ?noteEndOutOfLineInlineMemberFn@IPM@@AAEHKGHPAH@Z
// private: int __thiscall IPM::noteEndOutOfLineInlineMemberFn(unsigned long, unsigned short, int, int *)

// FUNCTION: MSVC5_C1 0x00041d20
// ?noteInlineMemberFnChange@IPM@@UAEHKPBD@Z
// public: virtual int __thiscall IPM::noteInlineMemberFnChange(unsigned long, char const *)

// FUNCTION: MSVC5_C1 0x00041d30
// ?noteStartDefaultArg@IPM@@UAEHGH@Z
// public: virtual int __thiscall IPM::noteStartDefaultArg(unsigned short, int)

// FUNCTION: MSVC5_C1 0x00041d40
// ?noteEndDefaultArg@IPM@@UAEHGH@Z
// public: virtual int __thiscall IPM::noteEndDefaultArg(unsigned short, int)

// FUNCTION: MSVC5_C1 0x00041d50
// ?noteCurrentMREFile@IPM@@UAEHPAUMREFile@@@Z
// public: virtual int __thiscall IPM::noteCurrentMREFile(struct MREFile *)

// FUNCTION: MSVC5_C1 0x00041d60
// ?noteDefeatsMR@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteDefeatsMR(void)

// FUNCTION: MSVC5_C1 0x00041d70
// ?notePragma@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::notePragma(void)

// FUNCTION: MSVC5_C1 0x00041d80
// ?noteStartFriendDeclaration@IPM@@UAEHGH@Z
// public: virtual int __thiscall IPM::noteStartFriendDeclaration(unsigned short, int)

// FUNCTION: MSVC5_C1 0x00041d90
// ?noteEndFriendDeclaration@IPM@@UAEHGH@Z
// public: virtual int __thiscall IPM::noteEndFriendDeclaration(unsigned short, int)

// FUNCTION: MSVC5_C1 0x00041da0
// ?noteAccessDeclaration@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteAccessDeclaration(void)

// FUNCTION: MSVC5_C1 0x00041db0
// ?noteQuasiTypeMod@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteQuasiTypeMod(void)

// FUNCTION: MSVC5_C1 0x00041dc0
// ?noteSizeof@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteSizeof(void)

// FUNCTION: MSVC5_C1 0x00041dd0
// ?noteGlobalEffectAndDefeatsMR@IPM@@AAEHXZ
// private: int __thiscall IPM::noteGlobalEffectAndDefeatsMR(void)

// FUNCTION: MSVC5_C1 0x00041de0
// ?noteWarning@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteWarning(void)

// FUNCTION: MSVC5_C1 0x00041e10
// ?noteError@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteError(void)

// FUNCTION: MSVC5_C1 0x00041e40
// ?noteNeedsRetdGL@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteNeedsRetdGL(void)

// FUNCTION: MSVC5_C1 0x00041e70
// ?note__LINE__@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::note__LINE__(void)

// FUNCTION: MSVC5_C1 0x00041ed0
// ?noteNeedsRegen@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteNeedsRegen(void)

// FUNCTION: MSVC5_C1 0x00041f00
// ?fCLChanged@IPM@@UAEHKPAW4CLChanged@@@Z
// public: virtual int __thiscall IPM::fCLChanged(unsigned long, enum CLChanged *)

// FUNCTION: MSVC5_C1 0x00041f90
// ?noteTPISigAge@IPM@@UAEHKK@Z
// public: virtual int __thiscall IPM::noteTPISigAge(unsigned long, unsigned long)

// FUNCTION: MSVC5_C1 0x00041fe0
// ?noteEndPchCreate@IPM@@UAEHPAW4FPM@@@Z
// public: virtual int __thiscall IPM::noteEndPchCreate(enum FPM *)

// FUNCTION: MSVC5_C1 0x00042040
// ?noteEndPchUse@IPM@@UAEHPAW4FPM@@@Z
// public: virtual int __thiscall IPM::noteEndPchUse(enum FPM *)

// FUNCTION: MSVC5_C1 0x000420d0
// ?noteUnprotoFn@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteUnprotoFn(void)

// FUNCTION: MSVC5_C1 0x00042100
// ?noteHasGlobalEffect@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteHasGlobalEffect(void)

// FUNCTION: MSVC5_C1 0x00042130
// ?noteTemplateSpecialization@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteTemplateSpecialization(void)

// FUNCTION: MSVC5_C1 0x00042160
// ?noteNameUse@IPM@@UAEHPAD@Z
// public: virtual int __thiscall IPM::noteNameUse(char *)

// FUNCTION: MSVC5_C1 0x00042290
// ?wasNameEverUsed@IPM@@UBEHPAD@Z
// public: virtual int __thiscall IPM::wasNameEverUsed(char *) const

// FUNCTION: MSVC5_C1 0x00042300
// ?noteBrowsePatch@IPM@@UAEHGG@Z
// public: virtual int __thiscall IPM::noteBrowsePatch(unsigned short, unsigned short)

// FUNCTION: MSVC5_C1 0x00042440
// ?noteBrowsePatch@IPM@@UAEHGGJ@Z
// public: virtual int __thiscall IPM::noteBrowsePatch(unsigned short, unsigned short, long)

// FUNCTION: MSVC5_C1 0x00042480
// ?cbBrowsePatches@IPM@@UAEJXZ
// public: virtual long __thiscall IPM::cbBrowsePatches(void)

// FUNCTION: MSVC5_C1 0x00042490
// ?queryBrowsePatch@IPM@@UAEHIPAPAUSbrPatch@@@Z
// public: virtual int __thiscall IPM::queryBrowsePatch(unsigned int, struct SbrPatch **)

// FUNCTION: MSVC5_C1 0x000424d0
// ?clearBrowsePatches@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::clearBrowsePatches(void)

// FUNCTION: MSVC5_C1 0x00042590
// ?noteBscmakeUpdate@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteBscmakeUpdate(void)

// FUNCTION: MSVC5_C1 0x000425e0
// ?noteGlobalEdit@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteGlobalEdit(void)

// FUNCTION: MSVC5_C1 0x00042700
// ?fInASkippableFn@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::fInASkippableFn(void)

// FUNCTION: MSVC5_C1 0x00042710
// ?noteNeeds__LINE__Var@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteNeeds__LINE__Var(void)

// FUNCTION: MSVC5_C1 0x00042720
// ?queryNeeds__LINE__Var@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::queryNeeds__LINE__Var(void)

// FUNCTION: MSVC5_C1 0x00042730
// ??_EFI@@QAEPAXI@Z
// public: void * __thiscall FI::`vector deleting dtor'(unsigned int)

// FUNCTION: MSVC5_C1 0x000427a0
// ??_I@YGXPAXIHP6EX0@Z@Z
// void __stdcall `vector dtor iterator'(void *, unsigned int, int, void (__thiscall *)(void *))

// FUNCTION: MSVC5_C1 0x000427e0
// ??1?$Array@K@@QAE@XZ
// public: __thiscall Array<unsigned long>::~Array<unsigned long>(void)

// FUNCTION: MSVC5_C1 0x000427f0
// ?save@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::save(void)

// FUNCTION: MSVC5_C1 0x00042800
// ?release@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::release(void)

// FUNCTION: MSVC5_C1 0x00042810
// ?noteStartMod@StubIPM@@UAEHPAW4FPM@@@Z
// public: virtual int __thiscall StubIPM::noteStartMod(enum FPM *)

// FUNCTION: MSVC5_C1 0x00042830
// ?noteStartPchUse@StubIPM@@UAEHPAW4FPM@@@Z
// public: virtual int __thiscall StubIPM::noteStartPchUse(enum FPM *)

// FUNCTION: MSVC5_C1 0x00042850
// ?noteEndMod@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteEndMod(void)

// FUNCTION: MSVC5_C1 0x00042860
// ?noteStartFn@StubIPM@@UAEHKGHPAW4FPM@@PAJPAGPAH@Z
// public: virtual int __thiscall StubIPM::noteStartFn(unsigned long, unsigned short, int, enum FPM *, long *, unsigned short *, int *)

// FUNCTION: MSVC5_C1 0x00042880
// ?noteEndFn@StubIPM@@UAEHKGHPAW4FPM@@PAH@Z
// public: virtual int __thiscall StubIPM::noteEndFn(unsigned long, unsigned short, int, enum FPM *, int *)

// FUNCTION: MSVC5_C1 0x000428a0
// ?noteDefine@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteDefine(void)

// FUNCTION: MSVC5_C1 0x000428b0
// ?notePragmaHasGlobalEffect@StubIPM@@UAEHH@Z
// public: virtual int __thiscall StubIPM::notePragmaHasGlobalEffect(int)

// FUNCTION: MSVC5_C1 0x000428c0
// ?notePragmaNeedsRegen@StubIPM@@UAEHH@Z
// public: virtual int __thiscall StubIPM::notePragmaNeedsRegen(int)

// FUNCTION: MSVC5_C1 0x000428d0
// ?noteStartCondCompTrue@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteStartCondCompTrue(void)

// FUNCTION: MSVC5_C1 0x000428e0
// ?noteEndCondCompTrue@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteEndCondCompTrue(void)

// FUNCTION: MSVC5_C1 0x000428f0
// ?noteStartInclude@StubIPM@@UAEHPADH@Z
// public: virtual int __thiscall StubIPM::noteStartInclude(char *, int)

// FUNCTION: MSVC5_C1 0x00042900
// ?noteEndInclude@StubIPM@@UAEHG@Z
// public: virtual int __thiscall StubIPM::noteEndInclude(unsigned short)

// FUNCTION: MSVC5_C1 0x00042910
// ?noteStartClassDefn@StubIPM@@UAEHGK@Z
// public: virtual int __thiscall StubIPM::noteStartClassDefn(unsigned short, unsigned long)

// FUNCTION: MSVC5_C1 0x00042920
// ?noteEndClassDefn@StubIPM@@UAEHGKPAH@Z
// public: virtual int __thiscall StubIPM::noteEndClassDefn(unsigned short, unsigned long, int *)

// FUNCTION: MSVC5_C1 0x00042940
// ?noteWarning@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteWarning(void)

// FUNCTION: MSVC5_C1 0x00042950
// ?noteError@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteError(void)

// FUNCTION: MSVC5_C1 0x00042960
// ?noteNeedsRetdGL@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteNeedsRetdGL(void)

// FUNCTION: MSVC5_C1 0x00042970
// ?note__LINE__@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::note__LINE__(void)

// FUNCTION: MSVC5_C1 0x00042980
// ?noteNeedsRegen@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteNeedsRegen(void)

// FUNCTION: MSVC5_C1 0x00042990
// ?fCLChanged@StubIPM@@UAEHKPAW4CLChanged@@@Z
// public: virtual int __thiscall StubIPM::fCLChanged(unsigned long, enum CLChanged *)

// FUNCTION: MSVC5_C1 0x000429b0
// ?noteEndPchCreate@StubIPM@@UAEHPAW4FPM@@@Z
// public: virtual int __thiscall StubIPM::noteEndPchCreate(enum FPM *)

// FUNCTION: MSVC5_C1 0x000429d0
// ?noteEndPchUse@StubIPM@@UAEHPAW4FPM@@@Z
// public: virtual int __thiscall StubIPM::noteEndPchUse(enum FPM *)

// FUNCTION: MSVC5_C1 0x000429f0
// ?forceParseAll@StubIPM@@UAEXXZ
// public: virtual void __thiscall StubIPM::forceParseAll(void)

// FUNCTION: MSVC5_C1 0x00042a00
// ?noteUnprotoFn@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteUnprotoFn(void)

// FUNCTION: MSVC5_C1 0x00042a10
// ?noteHasGlobalEffect@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteHasGlobalEffect(void)

// FUNCTION: MSVC5_C1 0x00042a20
// ?noteTemplateSpecialization@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteTemplateSpecialization(void)

// FUNCTION: MSVC5_C1 0x00042a30
// ?unused@StubIPM@@UAEXXZ
// public: virtual void __thiscall StubIPM::unused(void)

// FUNCTION: MSVC5_C1 0x00042a40
// ?noteNameUse@StubIPM@@UAEHPAD@Z
// public: virtual int __thiscall StubIPM::noteNameUse(char *)

// FUNCTION: MSVC5_C1 0x00042a50
// ?wasNameEverUsed@StubIPM@@UBEHPAD@Z
// public: virtual int __thiscall StubIPM::wasNameEverUsed(char *) const

// FUNCTION: MSVC5_C1 0x00042a60
// ?noteCurrentMREFile@StubIPM@@UAEHPAUMREFile@@@Z
// public: virtual int __thiscall StubIPM::noteCurrentMREFile(struct MREFile *)

// FUNCTION: MSVC5_C1 0x00042a70
// ?noteStartInlineMemberFn@StubIPM@@UAEHGH@Z
// public: virtual int __thiscall StubIPM::noteStartInlineMemberFn(unsigned short, int)

// FUNCTION: MSVC5_C1 0x00042a80
// ?noteEndInlineMemberFn@StubIPM@@UAEHGHPAH@Z
// public: virtual int __thiscall StubIPM::noteEndInlineMemberFn(unsigned short, int, int *)

// FUNCTION: MSVC5_C1 0x00042aa0
// ?noteInlineMemberFnChange@StubIPM@@UAEHKPBD@Z
// public: virtual int __thiscall StubIPM::noteInlineMemberFnChange(unsigned long, char const *)

// FUNCTION: MSVC5_C1 0x00042ab0
// ?noteDefeatsMR@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteDefeatsMR(void)

// FUNCTION: MSVC5_C1 0x00042ac0
// ?noteStartDefaultArg@StubIPM@@UAEHGH@Z
// public: virtual int __thiscall StubIPM::noteStartDefaultArg(unsigned short, int)

// FUNCTION: MSVC5_C1 0x00042ad0
// ?noteEndDefaultArg@StubIPM@@UAEHGH@Z
// public: virtual int __thiscall StubIPM::noteEndDefaultArg(unsigned short, int)

// FUNCTION: MSVC5_C1 0x00042ae0
// ?notePragma@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::notePragma(void)

// FUNCTION: MSVC5_C1 0x00042af0
// ?noteStartFriendDeclaration@StubIPM@@UAEHGH@Z
// public: virtual int __thiscall StubIPM::noteStartFriendDeclaration(unsigned short, int)

// FUNCTION: MSVC5_C1 0x00042b00
// ?noteEndFriendDeclaration@StubIPM@@UAEHGH@Z
// public: virtual int __thiscall StubIPM::noteEndFriendDeclaration(unsigned short, int)

// FUNCTION: MSVC5_C1 0x00042b10
// ?noteAccessDeclaration@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteAccessDeclaration(void)

// FUNCTION: MSVC5_C1 0x00042b20
// ?noteQuasiTypeMod@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteQuasiTypeMod(void)

// FUNCTION: MSVC5_C1 0x00042b30
// ?noteSizeof@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteSizeof(void)

// FUNCTION: MSVC5_C1 0x00042b40
// ?noteBscmakeUpdate@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteBscmakeUpdate(void)

// FUNCTION: MSVC5_C1 0x00042b50
// ?noteBrowsePatch@StubIPM@@UAEHGG@Z
// public: virtual int __thiscall StubIPM::noteBrowsePatch(unsigned short, unsigned short)

// FUNCTION: MSVC5_C1 0x00042b60
// ?noteBrowsePatch@StubIPM@@UAEHGGJ@Z
// public: virtual int __thiscall StubIPM::noteBrowsePatch(unsigned short, unsigned short, long)

// FUNCTION: MSVC5_C1 0x00042b70
// ?cbBrowsePatches@StubIPM@@UAEJXZ
// public: virtual long __thiscall StubIPM::cbBrowsePatches(void)

// FUNCTION: MSVC5_C1 0x00042b80
// ?queryBrowsePatch@StubIPM@@UAEHIPAPAUSbrPatch@@@Z
// public: virtual int __thiscall StubIPM::queryBrowsePatch(unsigned int, struct SbrPatch **)

// FUNCTION: MSVC5_C1 0x00042b90
// ?clearBrowsePatches@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::clearBrowsePatches(void)

// FUNCTION: MSVC5_C1 0x00042ba0
// ?noteGlobalEdit@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteGlobalEdit(void)

// FUNCTION: MSVC5_C1 0x00042bb0
// ?noteSbrFileSize@StubIPM@@UAEXJ@Z
// public: virtual void __thiscall StubIPM::noteSbrFileSize(long)

// FUNCTION: MSVC5_C1 0x00042bc0
// ?cbSbrFileSize@StubIPM@@UAEJXZ
// public: virtual long __thiscall StubIPM::cbSbrFileSize(void)

// FUNCTION: MSVC5_C1 0x00042bd0
// ?noteTPISigAge@StubIPM@@UAEHKK@Z
// public: virtual int __thiscall StubIPM::noteTPISigAge(unsigned long, unsigned long)

// FUNCTION: MSVC5_C1 0x00042be0
// ?noteMROnly@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteMROnly(void)

// FUNCTION: MSVC5_C1 0x00042bf0
// ?fInASkippableFn@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::fInASkippableFn(void)

// FUNCTION: MSVC5_C1 0x00042c00
// ?noteNeeds__LINE__Var@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteNeeds__LINE__Var(void)

// FUNCTION: MSVC5_C1 0x00042c10
// ?queryNeeds__LINE__Var@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::queryNeeds__LINE__Var(void)

// FUNCTION: MSVC5_C1 0x00042c20
// ??0ISet@@QAE@XZ
// public: __thiscall ISet::ISet(void)

// FUNCTION: MSVC5_C1 0x00042c30
// ??0?$Array@K@@QAE@I@Z
// public: __thiscall Array<unsigned long>::Array<unsigned long>(unsigned int)

// FUNCTION: MSVC5_C1 0x00042c70
// ?fill@?$Array@K@@QAEXABK@Z
// public: void __thiscall Array<unsigned long>::fill(unsigned long const &)

// FUNCTION: MSVC5_C1 0x00042ca0
// ??0Regn@@QAE@W4Type@0@@Z
// public: __thiscall Regn::Regn(enum Regn::Type)

// FUNCTION: MSVC5_C1 0x00042cd0
// ?unused@IPM@@UAEXXZ
// public: virtual void __thiscall IPM::unused(void)

// FUNCTION: MSVC5_C1 0x00042ce0
// ?noteSbrFileSize@IPM@@UAEXJ@Z
// public: virtual void __thiscall IPM::noteSbrFileSize(long)

// FUNCTION: MSVC5_C1 0x00042cf0
// ?cbSbrFileSize@IPM@@UAEJXZ
// public: virtual long __thiscall IPM::cbSbrFileSize(void)

// FUNCTION: MSVC5_C1 0x00042d00
// ?forceParseAll@IPM@@UAEXXZ
// public: virtual void __thiscall IPM::forceParseAll(void)

// FUNCTION: MSVC5_C1 0x00042d10
// ?noteMROnly@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteMROnly(void)

// FUNCTION: MSVC5_C1 0x00042d30
// ??0?$Map@KJV?$HashClass@K$0A@@@@@QAE@I@Z
// public: __thiscall Map<unsigned long, long, class HashClass<unsigned long, 0>>::Map<unsigned long, long, class HashClass<unsigned long, 0>>(unsigned int)

// FUNCTION: MSVC5_C1 0x00042dc0
// ??0?$Array@J@@QAE@I@Z
// public: __thiscall Array<long>::Array<long>(unsigned int)

// FUNCTION: MSVC5_C1 0x00042e00
// ?contains@ISet@@QBEHI@Z
// public: int __thiscall ISet::contains(unsigned int) const

// FUNCTION: MSVC5_C1 0x00042e50
// ?setPbExtent@Buffer@@AAEHPAE0@Z
// private: int __thiscall Buffer::setPbExtent(unsigned char *, unsigned char *)

// FUNCTION: MSVC5_C1 0x00042e90
// ?Free@Buffer@@QAEXXZ
// public: void __thiscall Buffer::Free(void)

// FUNCTION: MSVC5_C1 0x00042eb0
// ?Ensure@Buffer@@QAEHJPAPAE@Z
// public: int __thiscall Buffer::Ensure(long, unsigned char **)

// FUNCTION: MSVC5_C1 0x00042f00
// ?Reserve@Buffer@@QAEHJPAPAE@Z
// public: int __thiscall Buffer::Reserve(long, unsigned char **)

// FUNCTION: MSVC5_C1 0x00042f70
// ?Append@Buffer@@QAEHPAEJPAPAE@Z
// public: int __thiscall Buffer::Append(unsigned char *, long, unsigned char **)

// FUNCTION: MSVC5_C1 0x00043020
// ?setHashSize@?$Map@KKV?$HashClass@K$0A@@@@@AAEHI@Z
// private: int __thiscall Map<unsigned long, unsigned long, class HashClass<unsigned long, 0>>::setHashSize(unsigned int)

// FUNCTION: MSVC5_C1 0x00043120
// ?add@ISet@@QAEHI@Z
// public: int __thiscall ISet::add(unsigned int)

// FUNCTION: MSVC5_C1 0x00043200
// ??_FRegn@@QAEXXZ
// public: void __thiscall Regn::`default ctor closure'(void)

// FUNCTION: MSVC5_C1 0x00043230
// ??4?$Array@URegn@@@@QAEAAV0@ABV0@@Z
// public: class Array<struct Regn> & __thiscall Array<struct Regn>::operator=(class Array<struct Regn> const &)

// FUNCTION: MSVC5_C1 0x00043310
// ??4FI@@QAEAAV0@ABV0@@Z
// public: class FI & __thiscall FI::operator=(class FI const &)

// FUNCTION: MSVC5_C1 0x00043430
// ??1?$Array@URegn@@@@QAE@XZ
// public: __thiscall Array<struct Regn>::~Array<struct Regn>(void)

// FUNCTION: MSVC5_C1 0x00043440
// ?setSize@?$Array@K@@QAEHI@Z
// public: int __thiscall Array<unsigned long>::setSize(unsigned int)

// FUNCTION: MSVC5_C1 0x000434c0
// ?save@?$Array@K@@QBEHPAVBuffer@@@Z
// public: int __thiscall Array<unsigned long>::save(class Buffer *) const

// FUNCTION: MSVC5_C1 0x000435e0
// ?reload@?$Array@K@@QAEHPAPAE@Z
// public: int __thiscall Array<unsigned long>::reload(unsigned char **)

// FUNCTION: MSVC5_C1 0x00043690
// ?setSize@?$Array@URegn@@@@QAEHI@Z
// public: int __thiscall Array<struct Regn>::setSize(unsigned int)

// FUNCTION: MSVC5_C1 0x00043780
// ?setSize@?$Array@VFI@@@@QAEHI@Z
// public: int __thiscall Array<class FI>::setSize(unsigned int)

// FUNCTION: MSVC5_C1 0x00043a20
// ?setSize@?$Array@J@@QAEHI@Z
// public: int __thiscall Array<long>::setSize(unsigned int)

// FUNCTION: MSVC5_C1 0x00043aa0
// ?save@?$Map@KJV?$HashClass@K$0A@@@@@QAEHPAVBuffer@@@Z
// public: int __thiscall Map<unsigned long, long, class HashClass<unsigned long, 0>>::save(class Buffer *)

// FUNCTION: MSVC5_C1 0x00043cb0
// ?save@?$Map@KKV?$HashClass@K$0A@@@@@QAEHPAVBuffer@@@Z
// public: int __thiscall Map<unsigned long, unsigned long, class HashClass<unsigned long, 0>>::save(class Buffer *)

// FUNCTION: MSVC5_C1 0x00043ec0
// ?setSize@?$Array@UBRI@@@@QAEHI@Z
// public: int __thiscall Array<struct BRI>::setSize(unsigned int)

// FUNCTION: MSVC5_C1 0x00043f60
// ?find@?$Map@KJV?$HashClass@K$0A@@@@@ABEHKPAI@Z
// private: int __thiscall Map<unsigned long, long, class HashClass<unsigned long, 0>>::find(unsigned long, unsigned int *) const

// FUNCTION: MSVC5_C1 0x00044040
// ?grow@?$Map@KJV?$HashClass@K$0A@@@@@AAEHXZ
// private: int __thiscall Map<unsigned long, long, class HashClass<unsigned long, 0>>::grow(void)

// FUNCTION: MSVC5_C1 0x00044210
// ?remove@ISet@@QAEHI@Z
// public: int __thiscall ISet::remove(unsigned int)

// FUNCTION: MSVC5_C1 0x00044250
// ?swap@?$Array@K@@QAEXAAV1@@Z
// public: void __thiscall Array<unsigned long>::swap(class Array<unsigned long> &)

// FUNCTION: MSVC5_C1 0x00044280
// ??1?$Map@KJV?$HashClass@K$0A@@@@@QAE@XZ
// public: __thiscall Map<unsigned long, long, class HashClass<unsigned long, 0>>::~Map<unsigned long, long, class HashClass<unsigned long, 0>>(void)

// FUNCTION: MSVC5_C1 0x000442d0
// ?swap@?$Array@J@@QAEXAAV1@@Z
// public: void __thiscall Array<long>::swap(class Array<long> &)

