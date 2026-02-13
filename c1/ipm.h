#ifndef IPM_H
#define IPM_H

#include "sigmgr.h"

// ??_7StubIPM@@6B@
// const StubIPM::`vftable'

// ??_7IPM@@6B@
// const IPM::`vftable'

// ??_7IncrParseMgr@@6B@
// const IncrParseMgr::`vftable'

// ?notInASkippableFn@IncrParseMgr@@2HA
// public: static int IncrParseMgr::notInASkippableFn

// ?pIPMSigMgr@@3PAUIPMSigMgr@@A
extern IPMSigMgr *pIPMSigMgr;

// ?ciNil@@3UCI@@A
// struct CI ciNil

// _$E31

// _$E30

// ?save@FI@@QBEHPAVBuffer@@@Z
// public: int __thiscall FI::save(class Buffer *) const

// ?reload@FI@@QAEHPAPAE@Z
// public: int __thiscall FI::reload(unsigned char **)

// ?szName@FI@@QBEPBDPAUNameMap@@@Z
// public: char const * __thiscall FI::szName(struct NameMap *) const

// ?open@IncrParseMgr@@SAHPAUPDB@@0PAUNameMap@@PAD2PAUIPMSigMgr@@HHHPAPAU1@@Z
// public: static int __cdecl IncrParseMgr::open(struct PDB *, struct PDB *, struct NameMap *, char *, char *, struct IPMSigMgr *, int, int, int, struct IncrParseMgr **)

// ??0IPM@@AAE@PAUPDB@@0PAUNameMap@@PAUIPMSigMgr@@HHH@Z
// private: __thiscall IPM::IPM(struct PDB *, struct PDB *, struct NameMap *, struct IPMSigMgr *, int, int, int)

// ?open@IPM@@AAEHPAD0@Z
// private: int __thiscall IPM::open(char *, char *)

// ?save@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::save(void)

// ?saveIPM@IPM@@AAEHXZ
// private: int __thiscall IPM::saveIPM(void)

// ?saveMod@IPM@@AAEHXZ
// private: int __thiscall IPM::saveMod(void)

// ?reloadIPM@IPM@@AAEHPAUStream@@PAH@Z
// private: int __thiscall IPM::reloadIPM(struct Stream *, int *)

// ?reloadMod@IPM@@AAEHPAUStream@@@Z
// private: int __thiscall IPM::reloadMod(struct Stream *)

// ?saveHeader@IPM@@ABEHPAVFI@@@Z
// private: int __thiscall IPM::saveHeader(class FI *) const

// ?reloadHeader@IPM@@AAEHPAVFI@@@Z
// private: int __thiscall IPM::reloadHeader(class FI *)

// ?szIPMHeaderStream@IPM@@ABEPBDPAVFI@@QADI@Z
// private: char const * __thiscall IPM::szIPMHeaderStream(class FI *, char *const, unsigned int) const

// ?release@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::release(void)

// ?noteStartMod@IPM@@UAEHPAW4FPM@@@Z
// public: virtual int __thiscall IPM::noteStartMod(enum FPM *)

// ?noteStartPchUse@IPM@@UAEHPAW4FPM@@@Z
// public: virtual int __thiscall IPM::noteStartPchUse(enum FPM *)

// ?noteEndMod@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteEndMod(void)

// ?checkHeaderTimestamps@IPM@@AAEHXZ
// private: int __thiscall IPM::checkHeaderTimestamps(void)

// ?noteStartGlobalRegn@IPM@@AAEHHW4Type@Regn@@@Z
// private: int __thiscall IPM::noteStartGlobalRegn(int, enum Regn::Type)

// ?noteEndGlobalRegn@IPM@@AAEHW4Type@Regn@@@Z
// private: int __thiscall IPM::noteEndGlobalRegn(enum Regn::Type)

// ?noteStartFn@IPM@@UAEHKGHPAW4FPM@@PAJPAGPAH@Z
// public: virtual int __thiscall IPM::noteStartFn(unsigned long, unsigned short, int, enum FPM *, long *, unsigned short *, int *)

// ?noteEndFn@IPM@@UAEHKGHPAW4FPM@@PAH@Z
// public: virtual int __thiscall IPM::noteEndFn(unsigned long, unsigned short, int, enum FPM *, int *)

// ?noteDefine@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteDefine(void)

// ?notePragmaHasGlobalEffect@IPM@@UAEHH@Z
// public: virtual int __thiscall IPM::notePragmaHasGlobalEffect(int)

// ?notePragmaNeedsRegen@IPM@@UAEHH@Z
// public: virtual int __thiscall IPM::notePragmaNeedsRegen(int)

// ?noteStartCondCompTrue@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteStartCondCompTrue(void)

// ?noteEndCondCompTrue@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteEndCondCompTrue(void)

// ?noteStartInclude@IPM@@UAEHPADH@Z
// public: virtual int __thiscall IPM::noteStartInclude(char *, int)

// ?noteEndInclude@IPM@@UAEHG@Z
// public: virtual int __thiscall IPM::noteEndInclude(unsigned short)

// ?noteStartClassDefn@IPM@@UAEHGK@Z
// public: virtual int __thiscall IPM::noteStartClassDefn(unsigned short, unsigned long)

// ?noteEndClassDefn@IPM@@UAEHGKPAH@Z
// public: virtual int __thiscall IPM::noteEndClassDefn(unsigned short, unsigned long, int *)

// ?noteStartInlineMemberFn@IPM@@UAEHGH@Z
// public: virtual int __thiscall IPM::noteStartInlineMemberFn(unsigned short, int)

// ?noteEndInlineMemberFn@IPM@@UAEHGHPAH@Z
// public: virtual int __thiscall IPM::noteEndInlineMemberFn(unsigned short, int, int *)

// ?noteStartOutOfLineInlineMemberFn@IPM@@AAEHKGH@Z
// private: int __thiscall IPM::noteStartOutOfLineInlineMemberFn(unsigned long, unsigned short, int)

// ?noteEndOutOfLineInlineMemberFn@IPM@@AAEHKGHPAH@Z
// private: int __thiscall IPM::noteEndOutOfLineInlineMemberFn(unsigned long, unsigned short, int, int *)

// ?noteInlineMemberFnChange@IPM@@UAEHKPBD@Z
// public: virtual int __thiscall IPM::noteInlineMemberFnChange(unsigned long, char const *)

// ?noteStartDefaultArg@IPM@@UAEHGH@Z
// public: virtual int __thiscall IPM::noteStartDefaultArg(unsigned short, int)

// ?noteEndDefaultArg@IPM@@UAEHGH@Z
// public: virtual int __thiscall IPM::noteEndDefaultArg(unsigned short, int)

// ?noteCurrentMREFile@IPM@@UAEHPAUMREFile@@@Z
// public: virtual int __thiscall IPM::noteCurrentMREFile(struct MREFile *)

// ?noteDefeatsMR@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteDefeatsMR(void)

// ?notePragma@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::notePragma(void)

// ?noteStartFriendDeclaration@IPM@@UAEHGH@Z
// public: virtual int __thiscall IPM::noteStartFriendDeclaration(unsigned short, int)

// ?noteEndFriendDeclaration@IPM@@UAEHGH@Z
// public: virtual int __thiscall IPM::noteEndFriendDeclaration(unsigned short, int)

// ?noteAccessDeclaration@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteAccessDeclaration(void)

// ?noteQuasiTypeMod@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteQuasiTypeMod(void)

// ?noteSizeof@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteSizeof(void)

// ?noteGlobalEffectAndDefeatsMR@IPM@@AAEHXZ
// private: int __thiscall IPM::noteGlobalEffectAndDefeatsMR(void)

// ?noteWarning@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteWarning(void)

// ?noteError@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteError(void)

// ?noteNeedsRetdGL@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteNeedsRetdGL(void)

// ?note__LINE__@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::note__LINE__(void)

// ?noteNeedsRegen@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteNeedsRegen(void)

// ?fCLChanged@IPM@@UAEHKPAW4CLChanged@@@Z
// public: virtual int __thiscall IPM::fCLChanged(unsigned long, enum CLChanged *)

// ?noteTPISigAge@IPM@@UAEHKK@Z
// public: virtual int __thiscall IPM::noteTPISigAge(unsigned long, unsigned long)

// ?noteEndPchCreate@IPM@@UAEHPAW4FPM@@@Z
// public: virtual int __thiscall IPM::noteEndPchCreate(enum FPM *)

// ?noteEndPchUse@IPM@@UAEHPAW4FPM@@@Z
// public: virtual int __thiscall IPM::noteEndPchUse(enum FPM *)

// ?noteUnprotoFn@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteUnprotoFn(void)

// ?noteHasGlobalEffect@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteHasGlobalEffect(void)

// ?noteTemplateSpecialization@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteTemplateSpecialization(void)

// ?noteNameUse@IPM@@UAEHPAD@Z
// public: virtual int __thiscall IPM::noteNameUse(char *)

// ?wasNameEverUsed@IPM@@UBEHPAD@Z
// public: virtual int __thiscall IPM::wasNameEverUsed(char *) const

// ?noteBrowsePatch@IPM@@UAEHGG@Z
// public: virtual int __thiscall IPM::noteBrowsePatch(unsigned short, unsigned short)

// ?noteBrowsePatch@IPM@@UAEHGGJ@Z
// public: virtual int __thiscall IPM::noteBrowsePatch(unsigned short, unsigned short, long)

// ?cbBrowsePatches@IPM@@UAEJXZ
// public: virtual long __thiscall IPM::cbBrowsePatches(void)

// ?queryBrowsePatch@IPM@@UAEHIPAPAUSbrPatch@@@Z
// public: virtual int __thiscall IPM::queryBrowsePatch(unsigned int, struct SbrPatch **)

// ?clearBrowsePatches@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::clearBrowsePatches(void)

// ?noteBscmakeUpdate@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteBscmakeUpdate(void)

// ?noteGlobalEdit@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteGlobalEdit(void)

// ?fInASkippableFn@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::fInASkippableFn(void)

// ?noteNeeds__LINE__Var@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteNeeds__LINE__Var(void)

// ?queryNeeds__LINE__Var@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::queryNeeds__LINE__Var(void)

// ??_EFI@@QAEPAXI@Z
// public: void * __thiscall FI::`vector deleting dtor'(unsigned int)

// ??_I@YGXPAXIHP6EX0@Z@Z
// void __stdcall `vector dtor iterator'(void *, unsigned int, int, void (__thiscall *)(void *))

// ??1?$Array@K@@QAE@XZ
// public: __thiscall Array<unsigned long>::~Array<unsigned long>(void)

// ?save@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::save(void)

// ?release@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::release(void)

// ?noteStartMod@StubIPM@@UAEHPAW4FPM@@@Z
// public: virtual int __thiscall StubIPM::noteStartMod(enum FPM *)

// ?noteStartPchUse@StubIPM@@UAEHPAW4FPM@@@Z
// public: virtual int __thiscall StubIPM::noteStartPchUse(enum FPM *)

// ?noteEndMod@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteEndMod(void)

// ?noteStartFn@StubIPM@@UAEHKGHPAW4FPM@@PAJPAGPAH@Z
// public: virtual int __thiscall StubIPM::noteStartFn(unsigned long, unsigned short, int, enum FPM *, long *, unsigned short *, int *)

// ?noteEndFn@StubIPM@@UAEHKGHPAW4FPM@@PAH@Z
// public: virtual int __thiscall StubIPM::noteEndFn(unsigned long, unsigned short, int, enum FPM *, int *)

// ?noteDefine@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteDefine(void)

// ?notePragmaHasGlobalEffect@StubIPM@@UAEHH@Z
// public: virtual int __thiscall StubIPM::notePragmaHasGlobalEffect(int)

// ?notePragmaNeedsRegen@StubIPM@@UAEHH@Z
// public: virtual int __thiscall StubIPM::notePragmaNeedsRegen(int)

// ?noteStartCondCompTrue@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteStartCondCompTrue(void)

// ?noteEndCondCompTrue@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteEndCondCompTrue(void)

// ?noteStartInclude@StubIPM@@UAEHPADH@Z
// public: virtual int __thiscall StubIPM::noteStartInclude(char *, int)

// ?noteEndInclude@StubIPM@@UAEHG@Z
// public: virtual int __thiscall StubIPM::noteEndInclude(unsigned short)

// ?noteStartClassDefn@StubIPM@@UAEHGK@Z
// public: virtual int __thiscall StubIPM::noteStartClassDefn(unsigned short, unsigned long)

// ?noteEndClassDefn@StubIPM@@UAEHGKPAH@Z
// public: virtual int __thiscall StubIPM::noteEndClassDefn(unsigned short, unsigned long, int *)

// ?noteWarning@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteWarning(void)

// ?noteError@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteError(void)

// ?noteNeedsRetdGL@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteNeedsRetdGL(void)

// ?note__LINE__@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::note__LINE__(void)

// ?noteNeedsRegen@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteNeedsRegen(void)

// ?fCLChanged@StubIPM@@UAEHKPAW4CLChanged@@@Z
// public: virtual int __thiscall StubIPM::fCLChanged(unsigned long, enum CLChanged *)

// ?noteEndPchCreate@StubIPM@@UAEHPAW4FPM@@@Z
// public: virtual int __thiscall StubIPM::noteEndPchCreate(enum FPM *)

// ?noteEndPchUse@StubIPM@@UAEHPAW4FPM@@@Z
// public: virtual int __thiscall StubIPM::noteEndPchUse(enum FPM *)

// ?forceParseAll@StubIPM@@UAEXXZ
// public: virtual void __thiscall StubIPM::forceParseAll(void)

// ?noteUnprotoFn@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteUnprotoFn(void)

// ?noteHasGlobalEffect@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteHasGlobalEffect(void)

// ?noteTemplateSpecialization@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteTemplateSpecialization(void)

// ?unused@StubIPM@@UAEXXZ
// public: virtual void __thiscall StubIPM::unused(void)

// ?noteNameUse@StubIPM@@UAEHPAD@Z
// public: virtual int __thiscall StubIPM::noteNameUse(char *)

// ?wasNameEverUsed@StubIPM@@UBEHPAD@Z
// public: virtual int __thiscall StubIPM::wasNameEverUsed(char *) const

// ?noteCurrentMREFile@StubIPM@@UAEHPAUMREFile@@@Z
// public: virtual int __thiscall StubIPM::noteCurrentMREFile(struct MREFile *)

// ?noteStartInlineMemberFn@StubIPM@@UAEHGH@Z
// public: virtual int __thiscall StubIPM::noteStartInlineMemberFn(unsigned short, int)

// ?noteEndInlineMemberFn@StubIPM@@UAEHGHPAH@Z
// public: virtual int __thiscall StubIPM::noteEndInlineMemberFn(unsigned short, int, int *)

// ?noteInlineMemberFnChange@StubIPM@@UAEHKPBD@Z
// public: virtual int __thiscall StubIPM::noteInlineMemberFnChange(unsigned long, char const *)

// ?noteDefeatsMR@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteDefeatsMR(void)

// ?noteStartDefaultArg@StubIPM@@UAEHGH@Z
// public: virtual int __thiscall StubIPM::noteStartDefaultArg(unsigned short, int)

// ?noteEndDefaultArg@StubIPM@@UAEHGH@Z
// public: virtual int __thiscall StubIPM::noteEndDefaultArg(unsigned short, int)

// ?notePragma@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::notePragma(void)

// ?noteStartFriendDeclaration@StubIPM@@UAEHGH@Z
// public: virtual int __thiscall StubIPM::noteStartFriendDeclaration(unsigned short, int)

// ?noteEndFriendDeclaration@StubIPM@@UAEHGH@Z
// public: virtual int __thiscall StubIPM::noteEndFriendDeclaration(unsigned short, int)

// ?noteAccessDeclaration@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteAccessDeclaration(void)

// ?noteQuasiTypeMod@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteQuasiTypeMod(void)

// ?noteSizeof@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteSizeof(void)

// ?noteBscmakeUpdate@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteBscmakeUpdate(void)

// ?noteBrowsePatch@StubIPM@@UAEHGG@Z
// public: virtual int __thiscall StubIPM::noteBrowsePatch(unsigned short, unsigned short)

// ?noteBrowsePatch@StubIPM@@UAEHGGJ@Z
// public: virtual int __thiscall StubIPM::noteBrowsePatch(unsigned short, unsigned short, long)

// ?cbBrowsePatches@StubIPM@@UAEJXZ
// public: virtual long __thiscall StubIPM::cbBrowsePatches(void)

// ?queryBrowsePatch@StubIPM@@UAEHIPAPAUSbrPatch@@@Z
// public: virtual int __thiscall StubIPM::queryBrowsePatch(unsigned int, struct SbrPatch **)

// ?clearBrowsePatches@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::clearBrowsePatches(void)

// ?noteGlobalEdit@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteGlobalEdit(void)

// ?noteSbrFileSize@StubIPM@@UAEXJ@Z
// public: virtual void __thiscall StubIPM::noteSbrFileSize(long)

// ?cbSbrFileSize@StubIPM@@UAEJXZ
// public: virtual long __thiscall StubIPM::cbSbrFileSize(void)

// ?noteTPISigAge@StubIPM@@UAEHKK@Z
// public: virtual int __thiscall StubIPM::noteTPISigAge(unsigned long, unsigned long)

// ?noteMROnly@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteMROnly(void)

// ?fInASkippableFn@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::fInASkippableFn(void)

// ?noteNeeds__LINE__Var@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::noteNeeds__LINE__Var(void)

// ?queryNeeds__LINE__Var@StubIPM@@UAEHXZ
// public: virtual int __thiscall StubIPM::queryNeeds__LINE__Var(void)

// ??0ISet@@QAE@XZ
// public: __thiscall ISet::ISet(void)

// ??0?$Array@K@@QAE@I@Z
// public: __thiscall Array<unsigned long>::Array<unsigned long>(unsigned int)

// ?fill@?$Array@K@@QAEXABK@Z
// public: void __thiscall Array<unsigned long>::fill(unsigned long const &)

// ??0Regn@@QAE@W4Type@0@@Z
// public: __thiscall Regn::Regn(enum Regn::Type)

// ?unused@IPM@@UAEXXZ
// public: virtual void __thiscall IPM::unused(void)

// ?noteSbrFileSize@IPM@@UAEXJ@Z
// public: virtual void __thiscall IPM::noteSbrFileSize(long)

// ?cbSbrFileSize@IPM@@UAEJXZ
// public: virtual long __thiscall IPM::cbSbrFileSize(void)

// ?forceParseAll@IPM@@UAEXXZ
// public: virtual void __thiscall IPM::forceParseAll(void)

// ?noteMROnly@IPM@@UAEHXZ
// public: virtual int __thiscall IPM::noteMROnly(void)

// ??0?$Map@KJV?$HashClass@K$0A@@@@@QAE@I@Z
// public: __thiscall Map<unsigned long, long, class HashClass<unsigned long, 0>>::Map<unsigned long, long, class HashClass<unsigned long, 0>>(unsigned int)

// ??0?$Array@J@@QAE@I@Z
// public: __thiscall Array<long>::Array<long>(unsigned int)

// ?contains@ISet@@QBEHI@Z
// public: int __thiscall ISet::contains(unsigned int) const

// ?setHashSize@?$Map@KKV?$HashClass@K$0A@@@@@AAEHI@Z
// private: int __thiscall Map<unsigned long, unsigned long, class HashClass<unsigned long, 0>>::setHashSize(unsigned int)

// ?add@ISet@@QAEHI@Z
// public: int __thiscall ISet::add(unsigned int)

// ??_FRegn@@QAEXXZ
// public: void __thiscall Regn::`default ctor closure'(void)

// ??4?$Array@URegn@@@@QAEAAV0@ABV0@@Z
// public: class Array<struct Regn> & __thiscall Array<struct Regn>::operator=(class Array<struct Regn> const &)

// ??4FI@@QAEAAV0@ABV0@@Z
// public: class FI & __thiscall FI::operator=(class FI const &)

// ??1?$Array@URegn@@@@QAE@XZ
// public: __thiscall Array<struct Regn>::~Array<struct Regn>(void)

// ?setSize@?$Array@K@@QAEHI@Z
// public: int __thiscall Array<unsigned long>::setSize(unsigned int)

// ?save@?$Array@K@@QBEHPAVBuffer@@@Z
// public: int __thiscall Array<unsigned long>::save(class Buffer *) const

// ?reload@?$Array@K@@QAEHPAPAE@Z
// public: int __thiscall Array<unsigned long>::reload(unsigned char **)

// ?setSize@?$Array@URegn@@@@QAEHI@Z
// public: int __thiscall Array<struct Regn>::setSize(unsigned int)

// ?setSize@?$Array@VFI@@@@QAEHI@Z
// public: int __thiscall Array<class FI>::setSize(unsigned int)

// ?setSize@?$Array@J@@QAEHI@Z
// public: int __thiscall Array<long>::setSize(unsigned int)

// ?save@?$Map@KJV?$HashClass@K$0A@@@@@QAEHPAVBuffer@@@Z
// public: int __thiscall Map<unsigned long, long, class HashClass<unsigned long, 0>>::save(class Buffer *)

// ?save@?$Map@KKV?$HashClass@K$0A@@@@@QAEHPAVBuffer@@@Z
// public: int __thiscall Map<unsigned long, unsigned long, class HashClass<unsigned long, 0>>::save(class Buffer *)

// ?setSize@?$Array@UBRI@@@@QAEHI@Z
// public: int __thiscall Array<struct BRI>::setSize(unsigned int)

// ?find@?$Map@KJV?$HashClass@K$0A@@@@@ABEHKPAI@Z
// private: int __thiscall Map<unsigned long, long, class HashClass<unsigned long, 0>>::find(unsigned long, unsigned int *) const

// ?grow@?$Map@KJV?$HashClass@K$0A@@@@@AAEHXZ
// private: int __thiscall Map<unsigned long, long, class HashClass<unsigned long, 0>>::grow(void)

// ?remove@ISet@@QAEHI@Z
// public: int __thiscall ISet::remove(unsigned int)

// ?swap@?$Array@K@@QAEXAAV1@@Z
// public: void __thiscall Array<unsigned long>::swap(class Array<unsigned long> &)

// ??1?$Map@KJV?$HashClass@K$0A@@@@@QAE@XZ
// public: __thiscall Map<unsigned long, long, class HashClass<unsigned long, 0>>::~Map<unsigned long, long, class HashClass<unsigned long, 0>>(void)

// ?swap@?$Array@J@@QAEXAAV1@@Z
// public: void __thiscall Array<long>::swap(class Array<long> &)

#endif /* IPM_H */
