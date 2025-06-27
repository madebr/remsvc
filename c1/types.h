#ifndef C1_TYPES_H
#define C1_TYPES_H

#include "decomp.h"

#include <mspdb41.h>
#include <stdio.h>

extern void __fastcall StdFree(void *p);

typedef struct tStringVector {
    undefined2 size;
    undefined2 capacity;
    int chunk_id;
    const char **data;
} tStringVector;

typedef struct tArgument_char_spec {
    char c;
    int32_t field_0x4;
    BOOL *ptr_bool;
} tArgument_char_spec;

typedef struct tArgument_spec {
    const char *format;
    union {
        const void *ptr_cvoid;
        BOOL *ptr_bool;
        char **ptr_str;
        const char **ptr_cstr;
        int32_t *ptr_int;
        const tArgument_char_spec *ptr_char_spec;
        tStringVector **ptr_string_vector;
    };
    bool field_0x8;
    undefined field_0x9;
} tArgument_spec;

typedef struct tTiming {
    const char *description;
    unsigned int tick;
} tTiming;

typedef struct tDefault_warning_severity {
    int warning;
    int severity;
} tDefault_warning_severity;

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

class tStruct_00466458 {
public:
    tStruct_00466458();
    ~tStruct_00466458();
private:
    char *field_0x0;        // offset 0x00
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

    inline void set_field_0x24(undefined v) { m_field_0x24 = v; }
private:
    undefined *m_write_left;     // offset 0x00
    void *m_write_end;           // offset 0x04
    size_t m_buffer_size;        // offset 0x08
    undefined4 m_field_0x0c;     // offset 0x0c
    undefined4 m_field_0x10;     // offset 0x10
    FILE *m_file;                // offset 0x14
    undefined4 m_field_0x18;     // offset 0x18
    int m_field_0x1c;            // offset 0x1c
    undefined4 m_field_0x20;     // offset 0x20
    undefined m_field_0x24;      // offset 0x24
    undefined field_0x25[3];     // offset 0x28
    void *m_field_0x28;          // offset 0x2c
};

typedef struct tPragma_stack_item {
    struct tPragma_stack_item *next;
    undefined4 value;
    undefined4 field_0x8;
} tPragma_stack_item;

typedef struct tPragma_stack {
    tPragma_stack_item *items;
    tPragma_stack_item *free_items;
} tPragma_stack;

typedef struct tDiagnostic_file_offset {
    int code;
    int offset;
} tDiagnostic_file_offset;

typedef struct tDiagnostic_code_text {
    int code;
    const char *text;
} tDiagnostic_code_text;

typedef struct tStruct_00401000 {
    undefined2 field_0x00;
    undefined2 field_0x02;
    undefined4 field_0x04;
    undefined4 field_0x08;
    undefined4 field_0x0c;
} tStruct_00401000;

class tStruct_0045b690_field_0x0_parent {
    virtual void vtable_0x00();
    virtual void vtable_0x04(undefined4) = 0;
    virtual undefined4 vtable_0x08(undefined4, undefined4);
    virtual undefined4 vtable_0x0c(undefined4);
    virtual undefined4 vtable_0x10(undefined4);
    virtual void vtable_0x14(undefined4,undefined4) = 0;
    virtual undefined4 vtable_0x18(undefined4,undefined4) = 0;
    virtual void vtable_0x1c();
    virtual void vtable_0x20();
    virtual void vtable_0x24(undefined4);
};

class tStruct_0045b690_field_0x0 : public tStruct_0045b690_field_0x0_parent {
    void vtable_0x00() override;
    void vtable_0x04(undefined4) override;
    undefined4 vtable_0x08(undefined4, undefined4) override;
    undefined4 vtable_0x0c(undefined4) override;
    undefined4 vtable_0x10(undefined4) override;
    void vtable_0x14(undefined4,undefined4) override;
    undefined4 vtable_0x18(undefined4,undefined4) override;
    void vtable_0x1c() override;
    void vtable_0x20() override;
    void vtable_0x24(undefined4) override;
};

#include "alloc.h"
extern tPCH_allocated_chunk g_PCH_allocated_chunk_004664a0;
extern tPCH_chunk gPCH_chunks[6];

class tStruct_0045b690 {
public:
    tStruct_0045b690();

    void *operator new (size_t size) {
        return g_PCH_allocated_chunk_004664a0.Allocate(size);
    }
private:
    tStruct_0045b690_field_0x0 *m_field_0x00;
    tStruct_0045b690_field_0x0 *m_field_0x04;
    tStruct_0045b690_field_0x0 *m_field_0x08;
    undefined m_field_0x0c[512];
    undefined4 m_field_0x20c;
    undefined4 m_field_0x210;
    undefined4 m_field_0x214;
    undefined4 m_field_0x218;
};

struct tStruct_00402c9_item {
    undefined4 m_field_0x00;
    undefined4 m_field_0x04;
    undefined4 m_field_0x08;
    undefined4 m_field_0x0c;
};

struct tStruct_00402c9a {
    tStruct_00402c9_item *field_0x00;
    undefined4 m_field_0x04;
    int m_chunk_id;
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

struct tCurrent_file_thing_0045e450 {
    void FUN_0040267e(tStruct_00456d30 *arg1, undefined4 arg2, undefined4 arg3, tCurrent_file_thing_0045e450 *arg4);

    undefined4 *stream;
    int line;
    tCurrent_file_thing_0045e450_offset_0x8 *m_field_0x08;
};

extern ISourceBrowser *gCurrent_source_browser;
extern const char *gSource_browser_file_path;

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

#endif
