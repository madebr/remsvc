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

// ??_C@_02HPLL@?9?1?$AA@
// "-/"

// ?crack_cmd@@YAHPBUcmdtab@@PADP6APADXZH@Z
extern int __fastcall crack_cmd(const cmdtab_s *cmd, char *argument, char * (* get_next_argument)(), int state);

// ?substr@@YAXPBUcmdtab@@PADH@Z
// void __cdecl substr(struct cmdtab const *, char *, int)

// ?getnumber@@YAHPAD@Z
// int __cdecl getnumber(char *)

// ?tailmatch@@YAHPAD0H@Z
// int __cdecl tailmatch(char *, char *, int)

// ?unconcat@@YAXPAE@Z
extern void __fastcall unconcat(char *argstr);

#endif /* GETFLAGS_H */
