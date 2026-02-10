#ifndef GETFLAGS_H
#define GETFLAGS_H

#include "decomp.h"
#include "list.h"

#define MAX_ARG_COUNT (200)

struct subtab {
    int letter;
    int type;
    bool32 *flag;
};

struct cmdtab_s {
    const char *format;
    union {
        const void *ptr_cvoid;
        bool32 *ptr_bool;
        char **ptr_str;
        const char **ptr_cstr;
        int32_t *ptr_int;
        const subtab *ptr_subtab;
        list<void *> **ptr_list;
    };
    bool retval;
    undefined type;
};

// ?NewArgv@@3PAPADA
extern char **NewArgv;

extern const char *ErrString;

// ?crack_cmd@@YAHPBUcmdtab@@PADP6APADXZH@Z
extern bool32 __fastcall crack_cmd(const cmdtab_s *cmds, char *argument, char * (* get_next_argument)(), bool32 dupe);

// ?substr@@YAXPBUcmdtab@@PADH@Z
extern void __fastcall substr(const cmdtab_s *cmd, char *value, bool32 dupe);

// ?getnumber@@YAHPAD@Z
extern int getnumber(const char *const str);

// ?tailmatch@@YAHPAD0H@Z
extern bool32 __fastcall tailmatch(const char *str, const char *tail);

// ?unconcat@@YAXPAE@Z
extern void __fastcall unconcat(char *argstr);

#endif /* GETFLAGS_H */
