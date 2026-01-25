#ifndef TYPES_H
#define TYPES_H

#include "decomp.h"
#include "types.h"

#include <windows.h>
#include <mspdb41.h>

typedef struct flag_s flag_s;
typedef struct form_s form_s;
typedef struct source_s source_s;
typedef enum tOption_action_type tOption_action_type;
typedef struct cmd_s cmd_s;
typedef struct ilsuffix_s ilsuffix_s;
typedef struct worklist_s worklist_s;
typedef struct passinfo_s passinfo_s;

typedef struct flag_s {
    flag_s *next;
    int info;
    char *passes;
    char *base;
    char *arg;
    union {
        const form_s *form;
        flag_s *swtch;
    };
} flag_s;

typedef struct form_s {
    const char *form;
    const char *tmpl;
    const char *conflict;
    const char *override;
    union {
        const void *void_u;
        const char *required;
        flag_s *(*func_ret_2arg)(const char **, int *);
    };
} form_s;

typedef enum {
    SOURCE_C = 0,
    SOURCE_CPP = 1,
    SOURCE_CXX = 2,
    SOURCE_OBJ = 3,
    SOURCE_LIB = 4,
    SOURCE_DEF = 5,
    SOURCE_RES = 6,
    SOURCE_EXP = 7,
    SOURCE_UNKNOWN = 8,
    SOURCE_EXE = 9,
} source_type;

typedef struct source_s {
    source_s *next;
    char *path;
    source_type type;
    short fixed_type;
    short batch_id;
} source_s;

typedef struct worklist_s {
    worklist_s *next;
    source_s *parsed_file;
    BOOL had_error;
    SRCTARG srctarg;
    char *sbrfile;
} worklist_s;

typedef enum cmd_type {
    CMD_UNKNOWN = 0,
    CMD_TRUE = 1,
    CMD_FALSE = 2,
    CMD_STRING = 3,
    CMD_FUNCTION = 4,
} cmd_type;

typedef struct cmd_s {
    const char *form;
    cmd_type type;
    union {
        void *dummy;
        BOOL *flag;
        char **string;
        void (*function)(flag_s *);
    };
} cmd_s;

typedef struct ilsuffix_s {
    const char *suffix;
    BOOL compile_il;
} ilsuffix_s;

typedef struct {
    flag_s *flags;
    flag_s *switches;
    int current_pass;
    passinfo_s *compiler_stage_spec;
    source_s *field_0x10;
    worklist_s *batchlist;
    SRCTARG *skiplist;
    SRCTARG **skiplistend;
    source_s *current_source;
    char *tempPath;
    char *include;
    char *exedir;
    char *errorpath;
    char *exepaths[10][3];
    char *errorpaths[10][3];
} context_s;

typedef struct {
    const char *key;       // offset 0x0
    const char *valuespec; // offset 0x4
} tSingle_arg_spec;

typedef struct passinfo_s {
    const char *pass_filename;
    const char *error_filename;
    const char *environment_variable;
    BOOL is_active;
    char id;
    char swchar;
} passinfo_s;

typedef enum {
    PHASE_NOPHASE = -1,
    PHASE_COMPILE = 0,
    PHASE_LINK = 1,
    PHASE_POSTPROCESS = 2,
} driver_phases;

typedef struct {
    const char *extension;
    driver_phases phase;
    passinfo_s *passes;
} sourceinfo_s;

#endif /* TYPES_H */
