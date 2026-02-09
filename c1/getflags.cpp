#include "getflags.h"

#include "error.h"
#include "globals.h"
#include "initmain.h"
#include "p0chrmap.h"

// GLOBAL: MSVC5_C1 0x00000390
// ?NewArgv@@3PAPADA
// GLOBAL: C1 0x0045b530
char **NewArgv = NULL;

// GLOBAL: C1 0x0045f4b8
const char *ErrString = NULL;

// GLOBAL: MSVC5_C1 0x000011a4
// ??_C@_02HPLL@?9?1?$AA@
// "-/"

// FUNCTION: MSVC5_C1 0x000142f0
// ?crack_cmd@@YAHPBUcmdtab@@PADP6APADXZH@Z
// FUNCTION: C1 0x0041b2c7
int __fastcall crack_cmd(const cmdtab_s *cmds, const char *argument, const char * (* get_next_argument)(), int state)
{ bool checksum_arg = true;
    int i;
    const char *arg_value = NULL;

    if (argument == NULL) {
        return 0;
    }
    ErrString = argument;
    for (i = 0;; i++) {
        const cmdtab_s *spec = &cmds[i];
        const char *ptr_arg = argument;
        const char *ptr_format = cmds[i].format;
        bool match = false;

        if (!cmds[i].type) {
            return 0;
        }
        for (;;) {
            if (*ptr_format == '\0') {
                if (*ptr_arg != '\0') {
                    break; // next argument spec
                }
                if (spec->type & 0x20) {
                    arg_value = get_next_argument();
                } else {
                    arg_value = NULL;
                }
                substr(cmds, arg_value, state);
                match = true;
                break;
            } else if (*ptr_format == '#' || *ptr_format == '$') {
                if (*ptr_format == '$') {
                    checksum_arg = false;
                }
                if (*ptr_arg != '\0') {
                    substr(spec, ptr_arg, state);
                } else {
                    arg_value = get_next_argument();
                    substr(spec, arg_value, state);
                    if (!checksum_arg) {
                        return cmds[i].retval;
                    }
                }
                match = true;
                break;
            } else if (*ptr_format == '%') {
                checksum_arg = false;
                ptr_format++;
            } else if (*ptr_format == '*') {
                if (*ptr_arg != '\0' && tailmatch(ptr_format, ptr_arg)) {
                    substr(spec, ptr_arg, state);
                    match = true;
                    break;
                } else {
                    break;
                }
            } else if (*ptr_format == '-') {
                const char *opt_start = "-/";
                if (strchr(opt_start, *ptr_arg) == NULL) {
                    break;
                }
                ptr_arg++;
                ptr_format++;
            } else {
                if (*ptr_arg != *ptr_format) {
                    break;
                }
                ptr_arg++;
                ptr_format++;
            }
        }
        if (match) {
            break;
        }
    }
    if (arg_value != NULL) {
        crc32ClCmd.Update(arg_value);
    }
    if (checksum_arg) {
        crc32ClCmd.Update(argument);
    }
    return cmds[i].retval;
}

// FUNCTION: MSVC5_C1 0x000144f0
// ?substr@@YAXPBUcmdtab@@PADH@Z
// FUNCTION: C1 0x0041af4c
void __fastcall substr(cmdtab_s const *cmds, const char *value, bool32 dupe)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00014690
// ?getnumber@@YAHPAD@Z
// int __cdecl getnumber(char *)

// FUNCTION: MSVC5_C1 0x00014700
// ?tailmatch@@YAHPAD0H@Z
bool32 tailmatch(const char *str, const char *tail)
{
    NOT_IMPLEMENTED();
}

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
