#include "getflags.h"

#include "error.h"
#include "initmain.h"
#include "p0chrmap.h"

// GLOBAL: MSVC5_C1 0x00000390
// ?NewArgv@@3PAPADA
// GLOBAL: C1 0x0045b530
char **NewArgv = NULL;

// GLOBAL: MSVC5_C1 0x000011a4
// ??_C@_02HPLL@?9?1?$AA@
// "-/"

// FUNCTION: MSVC5_C1 0x000142f0
// ?crack_cmd@@YAHPBUcmdtab@@PADP6APADXZH@Z
// FUNCTION: C1 0x0041b2c7
int __fastcall crack_cmd(const cmdtab_s *cmd, char *argument, char * (* get_next_argument)(), int state)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x000144f0
// ?substr@@YAXPBUcmdtab@@PADH@Z
// void __cdecl substr(struct cmdtab const *, char *, int)

// FUNCTION: MSVC5_C1 0x00014690
// ?getnumber@@YAHPAD@Z
// int __cdecl getnumber(char *)

// FUNCTION: MSVC5_C1 0x00014700
// ?tailmatch@@YAHPAD0H@Z
// int __cdecl tailmatch(char *, char *, int)

// FUNCTION: MSVC5_C1 0x000148d0
// ?copyover@@YAPAPADXZ
// FUNCTION: C1 0x0041ad63
static char ** copyover()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00014780
// ?unconcat@@YAXPAE@Z
// FUNCTION: C1 0x0041adce
void __fastcall unconcat(char *argstr)
{
    bool in_quotes = false;

    if (argstr == NULL) {
        return;
    }
    char **argv_ptr = copyover();
    while (*argstr != '\0') {
        while (*argstr == ' ') {
            argstr++;
        }
        if (*argstr == '\0') {
            continue;
        }
        *argv_ptr++ = argstr;
        if (argv_ptr - NewArgv >= MAX_ARG_COUNT) {
            fatal_varargs(C1077, MAX_ARG_COUNT);
        }
        Argc += 1;
        char *arg_ptr = argstr;
        while (*argstr != '\0') {
            if (*argstr == ' ' && !in_quotes) {
                break;
            }
            uint8_t cls = Charmap[*argstr];
            if (cls == 0) {
                if (*argstr == '?') {
                    *arg_ptr++ = *argstr++;
                    continue;
                }
                argstr++;
                if (*argstr == '"') {
                    *arg_ptr++  = *argstr++;
                    continue;
                }
                *arg_ptr++ = '\\';
                if (*argstr != '\0' && (*argstr != ' ' || in_quotes)) {
                    *arg_ptr++ = *argstr++;
                    continue;
                }
            } else if (cls == 0x16) {
                in_quotes = !in_quotes;
                argstr++;
            } else if (cls == 0x23) {
                *arg_ptr++ = *argstr++;
                *arg_ptr++ = *argstr++;
            } else {
                *arg_ptr++ = *argstr++;
            }
        }
        if (*argstr != '\0') {
            argstr++;
        }
        *arg_ptr = '\0';
    }
    *argv_ptr = NULL;
}
