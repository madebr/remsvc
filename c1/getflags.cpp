#include "getflags.h"

#include "error.h"
#include "globals.h"
#include "initmain.h"
#include "p0chrmap.h"

#include <ctype.h>

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
int __fastcall crack_cmd(const cmdtab_s *cmds, char *argument, char * (* get_next_argument)(), int state)
{
    bool checksum_arg = true;
    char *arg_value = NULL;
    const cmdtab_s *cmd;

    if (argument == NULL) {
        return 0;
    }
    ErrString = argument;
    for (cmd = cmds; ; cmd++) {
        char *ptr_arg = argument;
        const char *ptr_format = cmd->format;
        bool match = false;

        if (!cmd->type) {
            return 0;
        }
        for (;;) {
            if (*ptr_format == '\0') {
                if (*ptr_arg != '\0') {
                    break; // next argument cmd
                }
                if (cmd->type & 0x20) {
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
                    substr(cmd, ptr_arg, state);
                } else {
                    arg_value = get_next_argument();
                    substr(cmd, arg_value, state);
                    if (!checksum_arg) {
                        return cmd->retval;
                    }
                }
                match = true;
                break;
            } else if (*ptr_format == '%') {
                checksum_arg = false;
                ptr_format++;
            } else if (*ptr_format == '*') {
                if (*ptr_arg != '\0' && tailmatch(ptr_format, ptr_arg)) {
                    substr(cmd, ptr_arg, state);
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
    return cmd->retval;
}

// FUNCTION: MSVC5_C1 0x000144f0
// ?substr@@YAXPBUcmdtab@@PADH@Z
// FUNCTION: C1 0x0041af4c
void __fastcall substr(const cmdtab_s *cmd, char *value, bool32 dupe)
{
    switch (cmd->type) {
    case 0x1:
        *cmd->ptr_bool = TRUE;
        break;
    case 0x5:
        *cmd->ptr_bool = FALSE;
        break;
    case 0x23:
        for (; *value != '\0'; value++) {
            const subtab *sub;
            for (sub = cmd->ptr_subtab; sub->flag != NULL; sub++) {
                if (sub->letter == '\0') {
                    fatal_varargs(C1048, *value, ErrString);
                }
                if (sub->letter == *value) {
                    if (sub->type == 0x1) {
                        *sub->flag = TRUE;
                    } else if (sub->type == 0x5) {
                        *sub->flag = FALSE;
                    }
                    break;
                }
            }
        }
        break;
    case 0x24:
        *cmd->ptr_int = getnumber(value);
        break;
    case 0x26:
        ListAppend(*cmd->ptr_list, dupe ? strdup(value) : value);
        break;
    case 0x27:
        if (*cmd->ptr_str != NULL) {
            char *dup_format = strdup(cmd->format);
            dup_format[strlen(dup_format) - 1] = '\0';
            fatal_varargs(C1046, dup_format, *cmd->ptr_str, value);
        }
        /* Fall through */
    case 0x22:
        *cmd->ptr_cstr = dupe ? strdup(value) : value;
        break;
    }
}

// FUNCTION: MSVC5_C1 0x00014690
// ?getnumber@@YAHPAD@Z
// FUNCTION: C1 0x0041aeb2
int getnumber(const char *const str)
{
    const char *strint = str;
    while (isspace(*strint)) {
        strint++;
    }
    if (!isdigit(*strint)) {
        fatal_varargs(C1049, str);
    }
    int l = atol(strint);
    if (l < 0 || l >= 0xffff) {
        fatal_varargs(C1049, str);
    }
    return l;
}

// FUNCTION: MSVC5_C1 0x00014700
// ?tailmatch@@YAHPAD0H@Z
// FUNCTION: C1 0x0041ae97
bool32 __fastcall tailmatch(const char *str, const char *tail) {
    if (str[1] == '\0') {
        return TRUE;
    }
    const char *str_ptr = &str[1];
    while (str_ptr[1] != '\0') {
        str_ptr++;
    }
    const char *tail_ptr = tail;
    while (tail_ptr[1] != '\0') {
        tail_ptr++;
    }
    while (*str_ptr == *tail_ptr) {
        str_ptr++;
        tail_ptr++;
    }
    return str == str_ptr && tail <= tail_ptr;
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
