#ifndef ILSINK_H
#define ILSINK_H

#include "decomp.h"
#include "util.h"

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

// ??_C@_03OLCH@nul?$AA@
// "nul"

// ??_C@_03HGBE@EEA?$AA@
// "EEA"

struct ILSink {
    ILSink() {
        m_field_0x0 = 0;
        m_field_0x4 = 0;
        m_field_0x8 = 0;
        m_field_0xc = 0;
        m_field_0x10 = 0;
        m_file = NULL;
        m_field_0x18 = TRUE;
        m_field_0x1c = -1;
    }

    ~ILSink() {
        if (m_file != NULL) {
            ::fclose(m_file);
        }
        if (m_field_0x28 != NULL) {
            StdFree(m_field_0x28);
        }
        if (m_field_0x0 != NULL) {
            delete m_field_0x0;
            m_field_0x0 = 0;
        }
    }

    // ?fopen@ILSink@@QAEXPAD00@Z
    void fopen(const char *basename, const char *extension, const char *mode);

    // ??1ILSink@@QAE@XZ
    // public: __thiscall ILSink::~ILSink(void)

    // ?fclose@ILSink@@QAEHXZ
    int fclose();

    // ?flushFile@ILSink@@QAEXXZ
    // public: void __thiscall ILSink::flushFile(void)

    // ?closeFile@ILSink@@QAEXXZ
    // public: void __thiscall ILSink::closeFile(void)

    // ?ilStoreFatal@ILSink@@SAXXZ
    // public: static void __cdecl ILSink::ilStoreFatal(void)

    // ?openILStore@ILSink@@SAXPAUPDB@@@Z
    // public: static void __cdecl ILSink::openILStore(struct PDB *)

    // ?closeILStore@ILSink@@SAXXZ
    // public: static void __cdecl ILSink::closeILStore(void)

    // ?openILMod@ILSink@@SAXPAD@Z
    // public: static void __cdecl ILSink::openILMod(char *)

    // ?closeILMod@ILSink@@SAXXZ
    // public: static void __cdecl ILSink::closeILMod(void)

    // ?flushILStore@ILSink@@QAEXKE@Z
    // public: void __thiscall ILSink::flushILStore(unsigned long, unsigned char)

    // ?deleteIL@ILSink@@QAEXK@Z
    // public: void __thiscall ILSink::deleteIL(unsigned long)

    // ?openPchStream@ILSink@@QAEXPAD0@Z
    // public: void __thiscall ILSink::openPchStream(char *, char *)

    // ?flushPchStream@ILSink@@QAEXXZ
    // public: void __thiscall ILSink::flushPchStream(void)

    // ?closePchStream@ILSink@@QAEXXZ
    // public: void __thiscall ILSink::closePchStream(void)

    // ?outputPdbIlRef@ILSink@@QAEPADPAJ@Z
    // public: char * __thiscall ILSink::outputPdbIlRef(long *)

    // ?readPchIl@ILSink@@QAEXPAU_iobuf@@J@Z
    // public: void __thiscall ILSink::readPchIl(struct _iobuf *, long)

    // ?getIL@ILSink@@SAXKEPAUBuf@@@Z
    // public: static void __cdecl ILSink::getIL(unsigned long, unsigned char, struct Buf *)

    // ?getAllIL@ILSink@@SAXEPAUBuf@@@Z
    // public: static void __cdecl ILSink::getAllIL(unsigned char, struct Buf *)

    void SetField0x24(undefined v) {
        m_field_0x24 = v;
    }
private:
    // ?ppdb@ILSink@@0PAUPDB@@A
    // private: static struct PDB *ILSink::ppdb

    // ?pilstore@ILSink@@0PAUILStore@@A
    // private: static struct ILStore *ILSink::pilstore

    // ?pilmod@ILSink@@0PAUILMod@@A
    // private: static struct ILMod *ILSink::pilmod

    // ?niIlMod@ILSink@@0KA
    // private: static unsigned long ILSink::niIlMod

    char *m_field_0x0;
    char *m_field_0x4;
    undefined4 m_field_0x8;
    undefined4 m_field_0xc;
    undefined4 m_field_0x10;
    FILE *m_file;
    bool32 m_field_0x18;
    int m_field_0x1c;
    undefined m_field_0x20[0x24 - 0x20];
    undefined m_field_0x24;
    undefined m_field_0x25[0x28 - 0x25];
    void *m_field_0x28;
};

#endif /* ILSINK_H */
