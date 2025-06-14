#ifndef TYPES_H
#define TYPES_H

#include "decomp.h"
#include "types.h"

#include <windows.h>

typedef struct tParsed_option tParsed_option;
typedef struct tOption_spec tOption_spec;
typedef struct tParsed_filepath tParsed_filepath;
typedef enum tOption_action_type tOption_action_type;
typedef struct tOption_action tOption_action;
typedef struct tTemporary_file_spec tTemporary_file_spec;
typedef struct tCompiler_input_file tCompiler_input_file;
typedef struct tFiletype_compiler_spec tFiletype_compiler_spec;

typedef struct tParsed_option {
    tParsed_option *next;
    undefined4 field_0x4;
    char *field_0x8;
    char *arg_keyonly;
    char *arg_value;
    union {
        const void *void_parent;
        const tOption_spec *parent_option_spec;
        tParsed_option *parsed_option_parent;
    };
} tParsed_option;

typedef struct tOption_spec {
    const char *field_0x0;
    const char *field_0x4;
    const char *field_0x8;
    const char *field_0xc;
    union {
        const void *void_0x10;
        const char *str_0x10;
        tParsed_option *(*cb_0x10)(const char **, int *);
    };
} tOption_spec;

typedef enum {
    eFiletype_c = 0,
    eFiletype_cpp = 1,
    eFiletype_cxx = 2,
    eFiletype_obj = 3,
    eFiletype_lib = 4,
    eFiletype_def = 5,
    eFiletype_res = 6,
    eFiletype_exp = 7,
    eFiletype_none = 8,
    eFiletype_exe = 9,
} tCompile_filetype;

typedef struct tParsed_filepath {
    tParsed_filepath *next;
    char *path;
    tCompile_filetype filetype;
    short field_0xc;
    short field_0xe;
} tParsed_filepath;

typedef struct tCompiler_input_file {
    tCompiler_input_file *next;
    tParsed_filepath *parsed_file;
    undefined4 field_0x08;
    undefined4 field_0x0c;
    BOOL is_cpp;
    char *field_0x14;
    char *field_0x18;
    char *field_0x1c;
    undefined4 field_0x20;
    char *field_0x24;
} tCompiler_input_file;

typedef enum tOption_action_type {
    eAction_invalid = 0,
    eAction_setTrue = 1,
    eAction_setFalse = 2,
    eAction_setString = 3,
    eAction_callback = 4,
} tOption_action_type;

typedef struct tOption_action {
    const char *key;
    tOption_action_type action;
    union {
        void *void_pointer;
        BOOL *boolean;
        char **text;
        void (*callback)(tParsed_option *);
    };
} tOption_action;

typedef struct tTemporary_file_spec {
    const char *filename;
    BOOL remove;
} tTemporary_file_spec;

typedef struct {
    tParsed_option *field_0x0;                    // offest 0x00
    tParsed_option *field_0x4;                    // offest 0x04
    int compiler_stage;                           // offset 0x08
    tFiletype_compiler_spec *compiler_stage_spec; // offset 0x0c
    tParsed_filepath *field_0x10;                 // offest 0x10
    tCompiler_input_file *field_0x14;             // offest 0x14
    void *field_0x18;                             // offest 0x18
    void *field_0x1c;                             // offest 0x1c
    tParsed_filepath *field_0x20;                 // offset 0x20
    char *tempPath;                               // offset 0x24
    char *includePaths;                           // offset 0x28
    char *exeDirectory;                           // offset 0x2c
    char *errorStringPath;                        // offset 0x30
    char *compiler_paths[10][3];                  // offset 0x34
    char *error_paths[10][3];                     // offset 0xac
} tApp_data;

typedef struct {
    const char *key;       // offset 0x0
    const char *valuespec; // offset 0x4
} tSingle_arg_spec;

typedef struct tFiletype_compiler_spec {
    const char *compiler_filename;
    const char *error_filename;
    const char *extra_env;
    undefined4 field_0xc;
    char field_0x10;
    char field_0x11;
} tFiletype_compiler_spec;

typedef enum {
    eStage_invalid = -1,
    eInput_compiler = 0,
    eInput_linker = 1,
    eOutput_linker = 2,
} tCompile_filetype_stage;

typedef struct {
    const char *extension;
    tCompile_filetype_stage stage;
    tFiletype_compiler_spec *compiler_specs;
} tFiletype_spec;

#endif /* TYPES_H */
