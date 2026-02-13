#ifndef ILSINK_H
#define ILSINK_H

#include "c1_types.h"
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
        m_field_0x10 = 0;
        fp = NULL;
        fWriteOK = TRUE;
        m_field_0x1c = -1;
    }

    ~ILSink() {
        if (fp != NULL) {
            ::fclose(fp);
        }
        if (m_field_0x28 != NULL) {
            StdFree(m_field_0x28);
        }
    }

    // ?fopen@ILSink@@QAEXPAD00@Z
    void fopen(const char *basename, const char *extension, const char *mode);

    // ??1ILSink@@QAE@XZ
    // public: __thiscall ILSink::~ILSink(void)

    // ?fclose@ILSink@@QAEHXZ
    int fclose();

    // ?flushFile@ILSink@@QAEXXZ
    void flushFile();

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

    void chwrite(unsigned char u8) {
        fWriteOK &= buffer.ensureAvailable(2);
        if (fWriteOK) {
            *buffer.pbEnd++ = u8;
        }
    }

    void shwrite(unsigned short u16) {
        fWriteOK &= buffer.ensureAvailable(4);
        if (fWriteOK) {
            if (u16 & 0xff80) {
                *buffer.pbEnd++ = 0x80;
                memcpy(buffer.pbEnd, &u16, 2);
                buffer.pbEnd += 2;
            } else {
                *buffer.pbEnd++ = (unsigned char)u16;
            }
        }
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

public:
    Buffer buffer;
    undefined4 m_field_0x10;
    FILE *fp;
    bool32 fWriteOK;
    int m_field_0x1c;
    undefined m_field_0x20[0x24 - 0x20];
    undefined m_field_0x24;
    undefined m_field_0x25[0x28 - 0x25];
    void *m_field_0x28;
};

#endif /* ILSINK_H */
