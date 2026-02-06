#ifndef C1_TYPES_H
#define C1_TYPES_H

#include "decomp.h"

#include <mspdb41.h>
#include <stdio.h>


typedef struct tStruct_00452860 {
    const char *name;
    int id;
} tStruct_00452860;

typedef struct tStruct_00452be0 {
    const char *name;
    undefined4 field_0x4;
    undefined4 field_0x8;
    undefined4 field_0xc;
} tStruct_00452be0;

struct tStruct_0045c0a8 {
    BOOL option_ZE;
    BOOL p_Extension;
    BOOL p_BigIntExtension;
    int32_t p_SizeOfBigInt;
    undefined4 option_Gr;
    undefined4 field_0x14;
    BOOL option_Jd;
    BOOL option_J;
    undefined4 field_0x20;
    undefined4 field_0x24;
    undefined4 field_0x28;
    undefined4 field_0x2c;
    undefined4 field_0x30;
    undefined4 field_0x34;
    BOOL option_MD;
    BOOL option_MT;
    BOOL option_Gc;
    BOOL p_Symbolic_debug_holder;
    BOOL p_PchDFlag;
    undefined2 field_0x4c;
    undefined2 field_0x4e;
    BOOL p_NoPoundLines;
    BOOL option_pf;
    BOOL option_Bd;
    uint32_t option_Bu;
    BOOL p_fReproduceable;
    undefined4 field_0x64;
    BOOL option_Oi;
    BOOL option_Gs;
    undefined4 field_0x70;
    int32_t field_0x74;
    undefined4 option_Gd;
    BOOL option_Gz;
    BOOL option_Gf;
    BOOL bool_0x84;
    BOOL option_GF;
    BOOL bool_0x8c;
    BOOL option_cbstring;
    int32_t option_G;
    BOOL option_GM;
    int32_t option_Ob;
    BOOL p_SourceBrowser;
    BOOL p_SourceBrowserExtended;
    uint32_t optimization_flags_0xa8;
    undefined4 field_0xac;
    BOOL option_C8MODE;
    BOOL bool_0xb4;
    BOOL option_Ot;
    BOOL option_Oa;
    BOOL option_Ow;
    BOOL option_Og;
    BOOL option_Op;
    BOOL option_Oy;
    BOOL p_FUseTypeServer;
    char p_FdName[256];
    char Yl_path[256];
    char local_pch_path[260];
    undefined4 option_Oq;
    BOOL bool_0x3dc;
    BOOL option_Ov;
    undefined4 field_0x3e4;
    undefined4 field_0x3e8;
    BOOL option_C9IL;
    BOOL option_Gi;
    BOOL option_GI;
    undefined4 field_0x3f8;
    BOOL p_Cmd_fICCBrowse;
    BOOL option_SplitPdbs;
    BOOL option_NoEHForNew;
};

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

typedef struct cmdtab {
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
} cmdtab;

typedef struct tTiming {
    const char *description;
    unsigned int tick;
} tTiming;

typedef struct tDefault_warning_severity {
    int warning;
    int severity;
} tDefault_warning_severity;

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

typedef struct tStruct_0045bb64 {
    struct tStruct_0045bb64 *next;
    tStruct_00401000 field_0x4;
} tStruct_0045bb64;

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

struct tStruct_0040925a {
    undefined field_0x00;
    undefined field_0x01;
    undefined field_0x02[2];
    tStruct_00401000 *field_04;
    undefined4 field_0x08[8];
    __int64 field_0x10;
};

typedef struct tStruct_0045b75c {
    uint8_t field_0x00;
    undefined field_0x01[3];
    undefined field_0x04[4];
    uint8_t field_0x08;
    undefined field_0x09[3];
    undefined field_0x0c[4];
    undefined field_0x10[4];
    undefined field_0x14[4];
    undefined field_0x18[4];
    undefined field_0x1c[4];
} tStruct_0045b75c;

typedef struct tStruct_0045b5b0_bucket {
    struct tStruct_0045b5b0_bucket *next;
    char *key;
    undefined4 hash_and_flags;
    union {
        struct {
            undefined data_field_0x0;
            undefined data_field_0x1;
            undefined data_field_0x2;
            undefined data_field_0x4;
        };
        undefined4 field_0x10;
    };
} tStruct_0045b5b0_bucket;

typedef struct tStruct_0045c6c0 {
    undefined4 id;
    void *field_0x04;
    undefined4 field_0x08;
    undefined4 field_0x0c;
    size_t capacity;
} tStruct_0045c6c0;

typedef struct tStruct_00468c10 {
    undefined4 field_0x0;
    undefined4 field_0x4;
} tStruct_00468c10;

typedef struct tStruct_FUN_00411349_arg {
    undefined2 field_0x0;
    undefined4 field_0x4;
} tStruct_FUN_00411349_arg;

typedef struct tStruct_FUN_00409fc4_arg {
    undefined2 field_0x0;
    undefined4 field_0x4;
} tStruct_FUN_00409fc4_arg;

typedef struct tStruct_0045e470 {
    undefined4 field_0x0;
    undefined4 field_0x4;
} tStruct_0045e470;

typedef struct tBucketAndIdentifier {
    tStruct_0045b5b0_bucket **ptr_bucket;
    const char *name;
} tBucketAndIdentifier;

#endif
