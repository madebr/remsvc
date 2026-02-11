#include "ilsink.h"

#include "decomp.h"

// GLOBAL: MSVC5_C1 0x00001950
// ?ppdb@ILSink@@0PAUPDB@@A
// private: static struct PDB *ILSink::ppdb

// GLOBAL: MSVC5_C1 0x00001954
// ?pilstore@ILSink@@0PAUILStore@@A
// private: static struct ILStore *ILSink::pilstore

// GLOBAL: MSVC5_C1 0x00001958
// ?pilmod@ILSink@@0PAUILMod@@A
// private: static struct ILMod *ILSink::pilmod

// GLOBAL: MSVC5_C1 0x0000195c
// ?niIlMod@ILSink@@0KA
// private: static unsigned long ILSink::niIlMod

// GLOBAL: MSVC5_C1 0x00005894
// ??_C@_03OLCH@nul?$AA@
// "nul"

// GLOBAL: MSVC5_C1 0x00005898
// ??_C@_03HGBE@EEA?$AA@
// "EEA"

// FUNCTION: MSVC5_C1 0x0003e000
// ?fopen@ILSink@@QAEXPAD00@Z
// FUNCTION: C1 0x00419195
void ILSink::fopen(const char *basename, const char *extension, const char *mode)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x0003e0e0
// ??1ILSink@@QAE@XZ
// public: __thiscall ILSink::~ILSink(void)

// FUNCTION: MSVC5_C1 0x0003e120
// ?fclose@ILSink@@QAEHXZ
// FUNCTION: C1 0x0041f36c
int ILSink::fclose()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x0003e170
// ?flushFile@ILSink@@QAEXXZ
// public: void __thiscall ILSink::flushFile(void)

// FUNCTION: MSVC5_C1 0x0003e200
// ?closeFile@ILSink@@QAEXXZ
// public: void __thiscall ILSink::closeFile(void)

// FUNCTION: MSVC5_C1 0x0003e230
// ?ilStoreFatal@ILSink@@SAXXZ
// public: static void __cdecl ILSink::ilStoreFatal(void)

// FUNCTION: MSVC5_C1 0x0003e260
// ?openILStore@ILSink@@SAXPAUPDB@@@Z
// public: static void __cdecl ILSink::openILStore(struct PDB *)

// FUNCTION: MSVC5_C1 0x0003e2b0
// ?closeILStore@ILSink@@SAXXZ
// public: static void __cdecl ILSink::closeILStore(void)

// FUNCTION: MSVC5_C1 0x0003e2d0
// ?openILMod@ILSink@@SAXPAD@Z
// public: static void __cdecl ILSink::openILMod(char *)

// FUNCTION: MSVC5_C1 0x0003e310
// ?closeILMod@ILSink@@SAXXZ
// public: static void __cdecl ILSink::closeILMod(void)

// FUNCTION: MSVC5_C1 0x0003e330
// ?flushILStore@ILSink@@QAEXKE@Z
// public: void __thiscall ILSink::flushILStore(unsigned long, unsigned char)

// FUNCTION: MSVC5_C1 0x0003e3b0
// ?deleteIL@ILSink@@QAEXK@Z
// public: void __thiscall ILSink::deleteIL(unsigned long)

// FUNCTION: MSVC5_C1 0x0003e420
// ?openPchStream@ILSink@@QAEXPAD0@Z
// public: void __thiscall ILSink::openPchStream(char *, char *)

// FUNCTION: MSVC5_C1 0x0003e470
// ?flushPchStream@ILSink@@QAEXXZ
// public: void __thiscall ILSink::flushPchStream(void)

// FUNCTION: MSVC5_C1 0x0003e4e0
// ?closePchStream@ILSink@@QAEXXZ
// public: void __thiscall ILSink::closePchStream(void)

// FUNCTION: MSVC5_C1 0x0003e510
// ?outputPdbIlRef@ILSink@@QAEPADPAJ@Z
// public: char * __thiscall ILSink::outputPdbIlRef(long *)

// FUNCTION: MSVC5_C1 0x0003e5f0
// ?readPchIl@ILSink@@QAEXPAU_iobuf@@J@Z
// public: void __thiscall ILSink::readPchIl(struct _iobuf *, long)

// FUNCTION: MSVC5_C1 0x0003e6c0
// ?getIL@ILSink@@SAXKEPAUBuf@@@Z
// public: static void __cdecl ILSink::getIL(unsigned long, unsigned char, struct Buf *)

// FUNCTION: MSVC5_C1 0x0003e6f0
// ?getAllIL@ILSink@@SAXEPAUBuf@@@Z
// public: static void __cdecl ILSink::getAllIL(unsigned char, struct Buf *)

