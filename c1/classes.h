#pragma once

#include "types.h"

#include <mspdb41.h>
#include <stdio.h>

class ISourceBrowser;

extern void __fastcall StdFree(void *p);
extern BOOL gOption_WX;
extern BOOL gOption_E;
extern BOOL gOption_Zg;
extern int gError_count;
extern int __fastcall FUN_0044810e(int code, int category, const char *arg3, const char *file, int line);
extern ISourceBrowser *gCurrent_source_browser;
extern const char *gSource_browser_file_path;

class tStruct_0045b5bc {
private:
    undefined4 *field_0x0;
};

class tSigPbCb {
public:
    tSigPbCb()
            : m_value(0xffffffff) {
    }
    inline void Update(const void *data, size_t size) {
        m_value = SigForPbCb(data, size, m_value);
    }
private:
    uint32_t m_value;
};

class tStruct_00466458_offset_0x0 {
public:
    // FIXME: this class is unknown, unknown size, and unknown vtable size
    virtual void vmethod_0x00() = 0;
    virtual void vmethod_0x04() = 0;
    virtual void vmethod_0x08() = 0;
    virtual char * vmethod_0x0c(char *buffer) = 0;
};

class tStruct_00466458 {
public:
    tStruct_00466458();
    ~tStruct_00466458();

    void FUN_0041f2db();
public:
    tStruct_00466458_offset_0x0 *field_0x0;        // offset 0x00
    undefined4 field_0x4;   // offset 0x04
    undefined4 field_0x8;   // offset 0x08
    undefined4 field_0xc;   // offset 0x0c
    undefined4 field_0x10;  // offset 0x10
};

class tFILESTREAM {
public:
    tFILESTREAM() {
        m_write_left = NULL;
        m_write_end = NULL;
        m_buffer_size = 0;
        m_field_0x0c = 0;
        m_field_0x10 = 0;
        m_file = NULL;
        m_field_0x18 = 1;
        m_field_0x1c = -1;
    }
    ~tFILESTREAM() {
        if (m_file != NULL) {
            fclose(m_file);
        }
        if (m_field_0x28 != NULL) {
            StdFree(m_file);
        }
        if (m_write_left != NULL) {
            delete[] m_write_left;
            m_buffer_size = 0;
        }
    }
    void Open(const char *dirpath, const char *filename, const char *mode);
    int Close();
    void Ilsink_Close();
    inline void FlushBuffer() {
        if (m_write_end != m_write_left) {
            intptr_t left = m_write_end - m_write_left;
            m_field_0x18 &= inlined_unk(left);
            if (m_field_0x18 != 0) {
                memcpy(m_write_end, m_write_left, left);
                m_write_end += left;
            }
            m_write_end = m_write_left;
        }
    }
    inline void FlushWrite() {
        if (m_write_end != m_write_left) {
            if (((gOption_WX > 1) + gError_count) == 0 && !gOption_E && !gOption_Zg) {
                size_t written = 0;
                if (m_field_0x18) {
                    size_t written = fwrite(m_write_left, 1, m_write_end - m_write_left, m_file);
                }
                if (!m_field_0x18 || m_write_left + written != m_write_end) {
                    FUN_0044810e(88, 339, NULL, "ilsink.cpp", 68);
                }
            }
            m_write_end = m_write_left;
        }
    }
    inline void Write(const char *data, size_t len) {
        m_field_0x18 &= inlined_unk(len);
        if (m_field_0x18 != 0) {
            memcpy(m_write_end, data, len);
            m_write_end += len;
        }
    }
    inline void Flush() {
        fflush(m_file);
    }
    inline int Seek(size_t offset) {
        return fseek(m_file, offset, SEEK_SET);
    }

    inline void set_field_0x24(undefined v) { m_field_0x24 = v; }
private:
    inline undefined4 inlined_unk(undefined4 left) {
        if (left + 1 < 0) {
            return 0;
        }
        if (m_write_left + m_buffer_size >= m_write_end + left + 1) {
            return 1;
        }
        if (!IncreaseBuffer(left + 1)) {
            return 0;
        }
        return 1;
    }
    BOOL IncreaseBuffer(size_t size);

    char *m_write_left;          // offset 0x00
    char *m_write_end;           // offset 0x04
    size_t m_buffer_size;        // offset 0x08
    void (*m_field_0x0c)(void*); // offset 0x0c
    undefined4 m_field_0x10;     // offset 0x10
    FILE *m_file;                // offset 0x14
    undefined4 m_field_0x18;     // offset 0x18
    int m_field_0x1c;            // offset 0x1c
    undefined4 m_field_0x20;     // offset 0x20
    undefined m_field_0x24;      // offset 0x24
    undefined field_0x25[3];     // offset 0x28
    void *m_field_0x28;          // offset 0x2c
};


class tStruct_0045b690_field_0x0_parent {
public:
    virtual BOOL vtable_0x00();
    virtual void vtable_0x04(undefined4) = 0;
    virtual undefined4 vtable_0x08(undefined4, undefined4);
    virtual undefined4 vtable_0x0c(undefined4);
    virtual undefined4 vtable_0x10(undefined4);
    virtual void vtable_0x14(undefined4,undefined4) = 0;
    virtual undefined4 vtable_0x18(undefined4,undefined4) = 0;
    virtual void vtable_0x1c();
    virtual void vtable_0x20();
    virtual void vtable_0x24(undefined4);
protected:
    tStruct_0045b690_field_0x0_parent() {
        m_field_0x04 = 0;
        m_field_0x08 = 0;
        m_field_0x0c = 0;
    }
    undefined4 m_field_0x04;
    undefined4 m_field_0x08;
    undefined4 m_field_0x0c;
};

#include "alloc.h"
extern tPCH_allocated_chunk g_PCH_allocated_chunk_004664a0;
extern tPCH_chunk gPCH_chunks[6];

class tStruct_0045b690_field_0x0 : public tStruct_0045b690_field_0x0_parent {
public:
    tStruct_0045b690_field_0x0() {
        m_capacity = 1023;
    }
    BOOL vtable_0x00() override;
    void vtable_0x04(undefined4) override;
    undefined4 vtable_0x08(undefined4, undefined4) override;
    undefined4 vtable_0x0c(undefined4) override;
    undefined4 vtable_0x10(undefined4) override;
    void vtable_0x14(undefined4,undefined4) override;
    undefined4 vtable_0x18(undefined4,undefined4) override;
    void vtable_0x1c() override;
    void vtable_0x20() override;
    void vtable_0x24(undefined4) override;

    inline void Initialize() {
        m_field_0x10 = new undefined4[m_capacity + 1];
    }

    void *operator new (size_t size) {
        return g_PCH_allocated_chunk_004664a0.Allocate(size);
    }
private:
    undefined4 *m_field_0x10;
    size_t m_capacity;
};

class tStruct_0045b690 {
public:
    tStruct_0045b690();

    void *operator new (size_t size) {
        return g_PCH_allocated_chunk_004664a0.Allocate(size);
    }
    void FUN_0040aedc();
private:
    tStruct_0045b690_field_0x0 *m_field_0x000;
    tStruct_0045b690_field_0x0 *m_field_0x004;
    tStruct_0045b690_field_0x0 *m_field_0x008;
    undefined m_field_0x00c[512];
    undefined4 m_field_0x20c;
    undefined4 m_field_0x210;
    undefined4 m_field_0x214;
    undefined4 m_field_0x218;
};


// VTABLE: 0x00452018
class tStruct_00452018 {
public:
    virtual BOOL vtable_0x00();
    virtual undefined4 vtable_0x04();
    virtual void vtable_0x08(undefined4);
    virtual void vtable_0x0c(undefined4);
    virtual undefined4 vtable_0x10();
    virtual void vtable_0x14();
    virtual ~tStruct_00452018();

    void *operator new (size_t size) {
        return gPCH_chunks[1].Allocate(size);
    }
private:
    undefined4 m_field_0x04;
    undefined4 m_field_0x08;
    undefined4 m_field_0x0c;
    undefined4 m_field_0x10;
    tStruct_00402c9a m_field_0x14;
    tStruct_00402c9a m_field_0x20;
    tStruct_00402c9a m_field_0x2c;
    undefined4 m_field_0x38;
};

// VTABLE: 00456d30
class tStruct_00456d30 : public tStruct_00452018 {
public:
    BOOL vtable_0x00() override;
    undefined4 vtable_0x04() override;
    void vtable_0x08(undefined4) override;
    void vtable_0x0c(undefined4) override;
    undefined4 vtable_0x10() override;
    void vtable_0x14() override;
    ~tStruct_00456d30() override;
private:
    undefined4 m_field_0x3c;
    undefined4 m_field_0x40;
    undefined4 m_field_0x44;
    undefined4 m_field_0x48;
    undefined4 m_field_0x4c;
};

class tCurrent_file_thing_0045e450_offset_0x8 {
    tStruct_00456d30 *m_field_0x00;
    tCurrent_file_thing_0045e450_offset_0x8 *next;
    undefined4 m_field_0x08;
    undefined4 m_field_0x0c;
    undefined4 m_field_0x10;
    undefined4 m_field_0x14;
};

class tCurrent_file_thing_0045e450 {
public:
    void FUN_0040267e(tStruct_00456d30 *arg1, undefined4 arg2, undefined4 arg3, tCurrent_file_thing_0045e450 *arg4);

    undefined4 *stream;
    int line;
    tCurrent_file_thing_0045e450_offset_0x8 *m_field_0x08;
};

class tStruct_0045e478 {
public:
    tStruct_0045e478() {
        m_field_0x00 = gSource_browser_file_path != NULL;
        m_field_0x08 = gCurrent_source_browser;
    }
private:
    BOOL m_field_0x00;
    undefined4 m_field_0x04;
    ISourceBrowser *m_field_0x08;
};

class tStruct_0041e7bc_offset_0x18 {
public:
    tStruct_0041e7bc_offset_0x18() {
        m_field_0x4 = 1;
        m_field_0x8 = 0;
        m_field_0x0 = 0;
    }

    void FUN_00405900();
    void *operator new (size_t size) {
        return gPCH_chunks[3].Allocate(size);
    }
    undefined4 *m_field_0x0;
    undefined4 m_field_0x4;
    undefined4 m_field_0x8;
};

class tStruct_00405f3{
public:
    void FUN_004058d8(undefined4 *arg1, undefined4 arg2);

    undefined2 m_field_0x0;
    undefined2 m_field_0x2;
    tStruct_00405f3 *m_field_0x4;
    undefined4 m_field_0x8;
};

class tStruct_0041e7bc {
public:
    tStruct_0041e7bc(tStruct_00401000 *arg1, tStruct_00468c10* arg2);

    void FUN_00405d36(tStruct_0041e7bc_offset_0x18 *arg);
    void FUN_00411349(tStruct_FUN_00411349_arg *arg);
    void FUN_00405faf();
    void FUN_00405ced(tStruct_00405f3 *arg);
    void FUN_00409fc4(tStruct_FUN_00409fc4_arg *arg1, tStruct_FUN_00409fc4_arg *arg2);

    inline undefined4 GetField0x28() { return m_field_0x28; }
private:
    tStruct_00401000 *m_field_0x00;
    tStruct_00405f3 *m_field_0x04;
    tStruct_00405f3 *m_field_0x08;
    undefined2 m_field_0x0c;
    undefined2 m_field_0x0e;
    undefined4 m_field_0x10;
    uint32_t m_field_0x14;
    tStruct_0041e7bc_offset_0x18 *m_field_0x18;
    undefined4 m_field_0x1c;
    undefined4 m_field_0x20;
    undefined4 *m_field_0x24;
    undefined4 m_field_0x28;
    uint32_t m_field_0x2c;
};
