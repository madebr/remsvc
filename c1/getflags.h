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
        list<void> **ptr_list;
    };
    bool retval;
    undefined type;
};

// ?NewArgv@@3PAPADA
extern char **NewArgv;

extern const char *ErrString;

// ?crack_cmd@@YAHPBUcmdtab@@PADP6APADXZH@Z
extern int __fastcall crack_cmd(const cmdtab_s *cmds, const char *argument, const char * (* get_next_argument)(), int state);

// ?substr@@YAXPBUcmdtab@@PADH@Z
extern void __fastcall substr(cmdtab_s const *cmds, const char *value, bool32 dupe);

// ?getnumber@@YAHPAD@Z
// int __cdecl getnumber(char *)

// ?tailmatch@@YAHPAD0H@Z
extern bool32 tailmatch(const char *str, const char *tail);

// ?unconcat@@YAXPAE@Z
extern void __fastcall unconcat(char *argstr);

#endif /* GETFLAGS_H */
