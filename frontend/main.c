#include "main.h"

#include "decomp.h"
#include "forms.h"
#include "os.h"
#include "util.h"

#include <io.h>
#include <mbstring.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "portable.h"

// GLOBAL: CL 0x00407090
const cmd_s Cctab[] = {
    {
        "Fo",
        CMD_STRING,
        {&Object},
    },
    {
        "Fe",
        CMD_STRING,
        {&Exefilename},
    },
    {
        "bA",
        CMD_FUNCTION,
        {configure_asmlist},
    },
    {
        "ba",
        CMD_FUNCTION,
        {activate_pass},
    },
    {
        "bc",
        CMD_FUNCTION,
        {copy_active_pass},
    },
    {
        "bd",
        CMD_FUNCTION,
        {deactivate_passes},
    },
    {
        "bE",
        CMD_TRUE,
        {&Preprocess},
    },
    {
        "bh",
        CMD_TRUE,
        {&Help},
    },
    {
        "bil",
        CMD_STRING,
        {&CX.tempPath},
    },
    {
        "bm",
        CMD_TRUE,
        {&Mapfile},
    },
    {
        "bo",
        CMD_FUNCTION,
        {check_compile_collide},
    },
    {
        "bp",
        CMD_FUNCTION,
        {alternate_pass},
    },
    {
        "br",
        CMD_FALSE,
        {&RedirStderr},
    },
    {
        "bt",
        CMD_STRING,
        {&ForceType},
    },
    {
        "bU",
        CMD_FUNCTION,
        {undef_one_stddef},
    },
    {
        "bu",
        CMD_FUNCTION,
        {undef_stddefs},
    },
    {
        "bv",
        CMD_TRUE,
        {&Verbose},
    },
    {
        "Bk",
        CMD_TRUE,
        {&Keepfiles},
    },
    {
        "Brepro",
        CMD_TRUE,
        {&Reproducable},
    },
    {
        "Bt",
        CMD_TRUE,
        {&Time},
    },
    {
        "Bz",
        CMD_TRUE,
        {&Nospawn},
    },
    {
        "coff",
        CMD_TRUE,
        {&Coff},
    },
    {
        "Fm",
        CMD_STRING,
        {&Mapfilename},
    },
    {
        "LD",
        CMD_FUNCTION,
        {link_dll},
    },
    {
        "LDd",
        CMD_FUNCTION,
        {link_dll},
    },
    {
        "omf",
        CMD_FALSE,
        {&Coff},
    },
    {
        "X",
        CMD_FALSE,
        {&DefInclude},
    },
    {
        "Fd",
        CMD_STRING,
        {&IdbFileName},
    },
    {
        "Gm",
        CMD_TRUE,
        {&MinimalRebuild},
    },
    {
        "FR",
        CMD_STRING,
        {&SbrFileName},
    },
    {
        "Fr",
        CMD_STRING,
        {&SbrFileName},
    },
    {
        "ZM",
        CMD_TRUE,
        {&BatchPasses},
    },
    {
        NULL,
        CMD_UNKNOWN,
        {NULL},
    },
};

// GLOBAL: CL 0x00409238
const sourceinfo_s Sourceinfo[] = {
    {
        "c",
        PHASE_COMPILE,
        C_passes,
    },
    {
        "cxx",
        PHASE_COMPILE,
        Cxx_passes,
    },
    {
        "cpp",
        PHASE_COMPILE,
        Cxx_passes,
    },
    {
        "obj",
        PHASE_LINK,
        Link_passes,
    },
    {
        "lib",
        PHASE_LINK,
        Link_passes,
    },
    {
        "def",
        PHASE_LINK,
        Link_passes,
    },
    {
        "res",
        PHASE_LINK,
        Link_passes,
    },
    {
        "exp",
        PHASE_LINK,
        Link_passes,
    },
    {
        "",
        PHASE_LINK,
        Link_passes,
    },
    {
        "exe",
        PHASE_POSTPROCESS,
        Post_passes,
    },
    {
        NULL,
        PHASE_NOPHASE,
        NULL,
    },
};

// GLOBAL: CL 0x0040a020
BOOL MinimalRebuild = TRUE;

// GLOBAL: CL 0x0040a02c
BOOL BatchPassOK = TRUE;

// GLOBAL: CL 0x0040a010
BOOL Coff = TRUE;

// GLOBAL: CL 0x0040a014
BOOL DefInclude = TRUE;

// GLOBAL: CL 0x0040a018
BOOL DefPhase = TRUE;

// GLOBAL: CL 0x0040a01c
BOOL Nologo = TRUE;

// GLOBAL: CL 0x0040a024
BOOL MinRebuildOK = TRUE;

// GLOBAL: CL 0x0040a028
BOOL BatchPasses = FALSE;

// GLOBAL: CL 0x0040a030
context_s *Context = &CX;

// GLOBAL: CL 0x0040a038
passinfo_s PassInfo =
{
    NULL,
    "cl.err",
    NULL,
    1,
    'D',
    '-',
};

// GLOBAL: CL 0x0040a04c
BOOL RedirStderr = TRUE;

// GLOBAL: CL 0x0040a050
BOOL Time = FALSE;

// GLOBAL: CL 0x0040a054
flag_s *Flag_freelist = NULL;

// GLOBAL: CL 0x0040a070
const char *DefaultMacros[] = {
    "-D_MSC_VER=1020",
    "-D_WIN32",
    NULL,
};

// GLOBAL: CL 0x0040a080
const char *DefaultOptions[] = {
    "-ef%e",
    "-il%t",
    "-f%f",
    "-W1",
    "-Zep8",
    "-ZB",
    "-G4s",
    "-GR-",
    "-GX-",
    "-Otb0",
    "-dos",
    "-Fo%b.obj",
    "-Fe%b.%X",
    "-pc\\:/",
    "-bLNOI",
    "-ML",
    "-coff",
    "-Fdvc40.pdb",
    "-Zn",
    "-ZM",
    NULL,
};

char VersionNumber[] = "10.20.6166";

// GLOBAL: CL 0x0040a0e8
passinfo_s C_passes[] = {
    {
        "c1.exe",
        "c1.err",
        "MSC_CMD_FLAGS=",
        1,
        '1',
        '-',
    },
    {
        "c2.exe",
        "c23.err",
        "MSC_CMD_FLAGS=",
        1,
        '2',
        '-',
    },
    {
        NULL,
        NULL,
        NULL,
        0,
        '\0',
        '\0',
    },
};

// GLOBAL: CL 0x0040a128
passinfo_s Cxx_passes[] =
{
    {
        "c1xx.exe",
        "c1.err",
        "MSC_CMD_FLAGS=",
        1,
        'P',
        '-',
    },
    {
        "c2.exe",
        "c23.err",
        "MSC_CMD_FLAGS=",
        1,
        '2',
        '-',
    },
    {
        NULL,
        NULL,
        NULL,
        0,
        '\0',
        '\0',
    },
};

// GLOBAL: CL 0x0040a168
passinfo_s Link_passes[] =
{
    {
        "link386.exe",
        NULL,
        NULL,
        0,
        'L',
        '/',
    },
    {
        "link.exe",
        NULL,
        NULL,
        1,
        'C',
        '/',
    },
    {
        NULL,
        NULL,
        NULL,
        0,
        '\0',
        '\0',
    },
};

// GLOBAL: CL 0x0040a1a8
passinfo_s Post_passes[] = {
    {
        NULL,
        NULL,
        NULL,
        0,
        '\0',
        '\0',
    },
};

// GLOBAL: CL 0x0040a200
char Bigbuf[1024];

// GLOBAL: CL 0x0040a600
char *ForceType = NULL;

// GLOBAL: CL 0x0040a604
char *IdbFileName = NULL;

// GLOBAL: CL 0x0040a608
char *Object = NULL;

// GLOBAL: CL 0x0040a60c
BOOL Nospawn = FALSE;

// GLOBAL: CL 0x0040a610
BOOL Verbose = FALSE;

// GLOBAL: CL 0x0040a614
BOOL Action = FALSE;

// GLOBAL: CL 0x0040a618
BOOL Preprocess = FALSE;

// GLOBAL: CL 0x0040a620
context_s CX = {0};

// GLOBAL: CL 0x0040a744
BOOL Reproducable = FALSE;

// GLOBAL: CL 0x0040a74c
BOOL Mapfile = FALSE;

// GLOBAL: CL 0x0040a770
int SourceCount = 0;

// GLOBAL: CL 0x0040a774
flag_s *Unknown_ = NULL;

// GLOBAL: CL 0x0040a778
char *Mapfilename = NULL;

// GLOBAL: CL 0x0040a77c
BOOL RespEcho = FALSE;

// GLOBAL: CL 0x0040a784
char *Exefilename = NULL;

// GLOBAL: CL 0x0040a788
char *SbrFileName = NULL;

// GLOBAL: CL 0x0040a78c
BOOL Nerrors = FALSE;

// GLOBAL: CL 0x0040a794
BOOL DllFlg = FALSE;

// GLOBAL: CL 0x0040a798
BOOL Help = FALSE;

// GLOBAL: CL 0x0040a7a0
BOOL Keepfiles = FALSE;

// FUNCTION: CL 0x00401000
source_type source(const char *filepath)
{
    char extension[256];
    source_type i;

    _splitpath(filepath, NULL, NULL, NULL, extension);
    if (extension[0] == '\0') {
        return SOURCE_UNKNOWN;
    }
    for (i = 0; Sourceinfo[i].phase != PHASE_POSTPROCESS; i++) {
        if (_stricmp(&extension[1], Sourceinfo[i].extension) == 0) {
            return i;
        }
    }
    return SOURCE_UNKNOWN;
}

// FUNCTION: CL 0x00401068
source_s *newsource(const char *path, source_type type)
{
    source_s *result;

    result = xnew(sizeof(*result));
    result->type = type;
    result->fixed_type = 1;
    result->path = xstrdup(path);
    result->next = NULL;
    result->batch_id = -1;
    return result;
}

// FUNCTION: CL 0x004010a1
source_s *addsource(const char *path, source_type filetype, short fixed_type)
{
    source_s *result;
    source_s **list;

    result = newsource(path, filetype);
    result->fixed_type = fixed_type;
    list = &Context->field_0x10;
    while (*list != NULL) {
        list = &(*list)->next;
    }
    *list = result;
    if (Sourceinfo[filetype].phase == PHASE_COMPILE) {
        SourceCount += 1;
    }
    return result;
}

#ifdef WITH_MSPDB
// FUNCTION: CL 0x00401108
char flag_these_pass_ids(flag_s *option, char *needles)
{
    char *pos = strpbrk(option->passes, needles);
    if (pos == NULL) {
        return '\0';
    } else {
        return *pos;
    }
}
#endif

// FUNCTION: CL 0x0040112b
void validate_arg(const char *optkey, char *optval, const char *optspec)
{
    int radix = 10;
    const char *optval_ptr = optval;
    char *end_ptr;
    unsigned long opt_intvalue;

    if (optspec[0] == 'x' && optval[0] == '0') {
        switch (optval[1]) {
            case 'D':
            case 'T':
            case 'd':
            case 't':
                optval_ptr = &optval[2];
                break;
            default:
                radix = 0;
                break;
        }
    }
    opt_intvalue = strtoul(optval_ptr, &end_ptr, radix);
    if (*end_ptr != '\0') {
        cmderr(2021, optkey, optval);
    }
    if (optspec[1] == '[') {
        unsigned long minimum;
        bool found = false;
        optspec += 2;
        while (1) {
            unsigned long maximum;
            maximum = minimum = strtoul(optspec, &end_ptr, 10);
            if (*end_ptr == '-') {
                maximum = strtoul(end_ptr + 1, &end_ptr, 10);
                if (maximum < minimum) {
                    unsigned long v = minimum;
                    minimum = maximum;
                    maximum = v;
                }
            }
            if (minimum <= opt_intvalue && opt_intvalue <= maximum) {
                found = true;
                break;
            }
            optspec = end_ptr + 1;
            if (*end_ptr != ',') {
                break;
            }
        }
        if (!found) {
            cmdwarn(4014, opt_intvalue, optkey, minimum);
            opt_intvalue = minimum;
        }
    }
    l2a(opt_intvalue, optval, 10);
}

// FUNCTION: CL 0x00401226
flag_s *domatch(const form_s *option_spec, const char **args, int *index)
{
    char optkey_buffer[32];
    char optval_buffer[1024];
    char *optkey_ptr = optkey_buffer;
    const char *arg = args[*index];
    const char *optkey_spec_ptr = option_spec->form;
    BOOL arg_is_optional;
    int optflags;
    int a1;
    int a2;
    const char *optarg = arg;
    char *optval;

    if (*optkey_spec_ptr == '^') {
        optkey_spec_ptr += 1;
    }
    for (arg += 1; *optkey_spec_ptr != '\0' && *optkey_spec_ptr != ':' && *optkey_spec_ptr != '!';
         optkey_spec_ptr += 1) {
        if (*arg != *optkey_spec_ptr) {
            cmderr(0);
        }
        *optkey_ptr++ = *arg++;
    }
    *optkey_ptr = '\0';
    if (*optkey_spec_ptr == '\0') {
        *index += 1;
        return newflag(optkey_buffer, NULL, NULL, 0);
    }
    switch (*optkey_spec_ptr) {
    case '!':
        arg_is_optional = FALSE;
        break;
    case ':':
        arg_is_optional = TRUE;
        break;
    default:
        cmderr(0);
        break;
    }
    optkey_spec_ptr++;
    optflags = 0;
    if (*optkey_spec_ptr == '?') {
        optkey_spec_ptr += 1;
        optflags = 0x2;
        memmove(optkey_buffer + 1, optkey_buffer, sizeof(optkey_buffer) - 1);
        optkey_buffer[0] = args[*index][0];
    }
    switch (*optkey_spec_ptr) {
    case '#':
        a1 = 0;
        a2 = 1;
        break;
    case '$':
        a1 = 0;
        a2 = 0;
        break;
    case '*':
        a1 = 1;
        a2 = 0;
        break;
    case '+':
        a1 = 1;
        a2 = 1;
        break;
    case '@':
        return option_spec->func_ret_2arg(args, index);
    default:
        a1 = optflags;
        a2 = optflags;
        break;
    }
    optarg = arg;
    if (a1 && *optarg == '\0') {
        optarg = args[*index + 1];
        *index += 2;
    } else {
        *index += 1;
    }
    if (optarg != NULL && optarg[0] != '\0' && (a2 || (optarg[0] != '-' && optarg[0] != '/'))) {
        optval = optval_buffer;
        strcpy(optval, arg);
    } else {
        if (!arg_is_optional) {
            cmderr(2004, optkey_buffer);
        }
        optval = NULL;
    }
    if (optval != NULL && optkey_spec_ptr[1] != '\0') {
        validate_arg(optkey_buffer, optval, &optkey_spec_ptr[1]);
    }
    return newflag(optkey_buffer, optval, NULL, optflags);
}

// FUNCTION: CL 0x004013d7
flag_s *newflag(const char *base, const char *arg, const char *passes, int info)
{
    flag_s *result;

    if (Flag_freelist == NULL) {
        result = xnew(sizeof(*result));
    } else {
        result = Flag_freelist;
        Flag_freelist = Flag_freelist->next;
    }
    memset(result, 0, sizeof(*result));
    result->info = info;
    result->arg = xstrdup(arg);
    result->base = xstrdup(base);
    result->passes = xstrdup(passes);
    return result;
}

// FUNCTION: CL 0x004010e8
BOOL flag_this_pass(flag_s *option, const passinfo_s *spec)
{
    return strchr(option->passes, spec->id) != NULL;
}

// FUNCTION: CL 0x00401442
int trymatch(const form_s *option_spec, const char **args, int index)
{
    const char *arg_spec = option_spec->form;
    const char *arg;
    int len_match;

    if (arg_spec[0] == '^') {
        if (!DefPhase) {
            return 0;
        }
        arg_spec += 1;
    }
    arg = args[index] + 1;
    while (*arg_spec != ':' && *arg_spec != '!') {
        if (*arg_spec != *arg) {
            return 0;
        }
        if (*arg_spec == '\0') {
            break;
        }
        arg++;
        arg_spec++;
    }
    len_match = arg - args[index];
    if (*arg_spec != '\0') {
        return len_match;
    }
    if (*arg == ' ') {
        return len_match;
    }
    if (*arg == '\0') {
        return len_match;
    }
    return 0;
}

// FUNCTION: CL 0x00401498
const char *xoption(const char *spec, char *buffer, const char *key, const char **filename)
{
    // GLOBAL: CL 0x0040a750
    static char defbase[32];
    const char *result;

    *filename = '\0';
    result = doexpand(&spec[1], buffer, key);
    result = doexpand(&result[1], defbase, key);
    if (buffer[0] == '\0') {
        strcpy(buffer, defbase);
    }
    *filename = defbase;
    return &result[1];
}

// FUNCTION: CL 0x004014ea
const char *doexpand(const char *spec, char *buffer, const char *key)
{
    char *buffer_ptr;
    const char *filename_ptr = NULL;

    buffer[0] = '\0';
    buffer_ptr = buffer;
    while (*spec != '\0') {
        if (*spec == '(') {
            *buffer_ptr = '\0';
            spec = xoption(spec, buffer_ptr, key, &filename_ptr);
            buffer_ptr = &buffer[strlen(buffer)];
        } else if (*spec == '!' || *spec == ':' || *spec == ')' || *spec == ',' || *spec == '|') {
            break;
        } else if (*spec == '*') {
            *buffer_ptr = '\0';
            if (DefPhase) {
                buffer_ptr = concat(buffer, key);
            } else {
                buffer_ptr = concatmeta(buffer, key);
            }
            spec++;
        } else if (*spec == '<') {
            spec = complete_filename(&spec[1], buffer, filename_ptr);
            buffer_ptr = &buffer[strlen(buffer)];
            break;
        } else if (*spec == '@') {
            spec++;
        } else if (*spec == '\\') {
            spec++;
            *buffer_ptr++ = *spec++;
        } else {
            *buffer_ptr++ = *spec++;
        }
    }
    *buffer_ptr = '\0';
    return spec;
}

// FUNCTION: CL 0x004015d3
flag_s *expand(const char *implied_spec, const flag_s *option)
{
    flag_s *result = NULL;
    char speckey[20];

    speckey[0] = '\0';
    while (*implied_spec != '\0') {
        unsigned int specflag = 0;
        const char *implied_spec_ptr = gobblewhite(implied_spec);
        char implied_argkey[32];
        const char *implied_argval;

        if (*implied_spec_ptr == '\0') {
            break;
        }
        if (*implied_spec_ptr != '=' && *implied_spec_ptr != '#' && *implied_spec_ptr != '-' &&
            *implied_spec_ptr != '~') {
            char *speckey_ptr = speckey;
            while (*implied_spec_ptr != '=' && *implied_spec_ptr != '#' && *implied_spec_ptr != '-' &&
                   *implied_spec_ptr != '~') {
                *speckey_ptr++ = *implied_spec_ptr++;
            }
            *speckey_ptr = '\0';
        }
        switch (*implied_spec_ptr) {
            case '#':
                specflag = 0x8;
                break;
            case '-':
                specflag = 0x1;
                break;
            case '~':
                specflag = 0x20;
                break;
        }
        implied_spec = doexpand(&implied_spec_ptr[1], implied_argkey, option->base);
        if (*implied_spec == '!' || *implied_spec == ':') {
            if (*implied_spec == '!') {
                specflag |= 0x4;
            }
            implied_spec = doexpand(&implied_spec[1], Bigbuf, option->arg);
            if (strlen(Bigbuf) != 0) {
                implied_argval = Bigbuf;
            } else {
                implied_argval = NULL;
            }
        } else {
            implied_argval = NULL;
        }
        if (*implied_spec == ',') {
            implied_spec += 1;
        }
        appendflag(&result, newflag(implied_argkey, implied_argval, speckey, specflag));
    }
    return result;
}

// FUNCTION: CL 0x004016f8
void appendflag(flag_s **list, flag_s *opt)
{
    while (*list != NULL) {
        list = &(*list)->next;
    }
    *list = opt;
}

// FUNCTION: CL 0x00401711
BOOL flagmatch(flag_s *opt1, flag_s *opt2)
{
    size_t l1;
    size_t l2;

    if (!(strcmp(opt1->base, "?") == 0 || strcmp(opt2->base, "?") == 0 ||
          strcmp(opt1->base, opt2->base) == 0)) {
        return FALSE;
    }
    if (opt1->arg == NULL) {
        if (opt2->arg == NULL || strcmp(opt2->arg, "?") == 0) {
            return TRUE;
        }
        return FALSE;
    }
    if (opt2->arg == NULL) {
        if (strcmp(opt1->arg, "?") == 0) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    l1 = strlen(opt1->arg);
    l2 = strlen(opt2->arg);
    if (l1 > 0 && opt1->arg[l1 - 1] == '?') {
        if (strncmp(opt1->arg, opt2->arg, l1 - 1) == 0) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    if (l2 > 0 && opt2->arg[l2 - 1] == '?') {
        if (strncmp(opt1->arg, opt2->arg, l2 - 1) == 0) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    if (strcmp(opt1->arg, opt2->arg) == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// #define DEBUG_CL
#ifdef DEBUG_CL
void dump_context()
{
    flag_s *opt;
    fflush(stderr);
    fflush(stdout);
    printf("Context->flags = {\n");
    opt = Context->flags;
    for (int i = 0; opt != NULL; i++, opt = opt->next) {
        const char *q = opt->arg ? "'" : "";
        printf(" [%2d] = { base='%s', arg=%s%s%s, opt=%s},\n", i, opt->base, q, opt->arg, q,
                opt->field_0x8);
    }
    printf("}\n");
    printf("Context->switches = {\n");
    opt = Context->switches;
    for (int i = 0; opt != NULL; i++, opt = opt->next) {
        const char *q = opt->arg ? "'" : "";
        printf(" [%2d] = { opt='%s', arg=%s%s%s, base=%s},\n", i, opt->base, q, opt->arg, q,
                opt->base);
    }
    printf("}\n");
}
#else
# define dump_context() \
     do { \
     } while (0)
#endif

// FUNCTION: CL 0x004017ff
int main(int argc, char *argv[])
{
    const char *msc_ide_flags;
    const char *cl;
    const char *cl_;
    char **msc_ide_flags_args;
    int count_msc_ide_flags_args;
    char **cl_args;
    int count_cl_args;
    char **cl__args;
    int count_cl__args;
    flag_s *opt;
    flag_s *unkopt;
    source_s *input_path;
    source_type default_filetype;

#ifdef _MSC_VER
    __try {
#endif

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    OS_Init();
    msc_ide_flags = getenv("_MSC_IDE_FLAGS");
    cl = getenv("CL");
    cl_ = getenv("_CL_");
    msc_ide_flags_args = sztoszv(msc_ide_flags, TRUE);
    count_msc_ide_flags_args = argcount((const char **) msc_ide_flags_args);
    cl_args = sztoszv(cl, TRUE);
    count_cl_args = argcount((const char **) cl_args);
    cl__args = sztoszv(cl_, TRUE);
    count_cl__args = argcount((const char **) cl__args);
    argv[0] = fullccpath();
    build_context(argv[0], Context);
    if (argc == 1 && count_cl_args == 0) {
        usage();
    }
    if (!early_switch_scan(argv + 1, argc - 1) && !early_switch_scan(cl_args, count_cl_args) &&
        !early_switch_scan(cl__args, count_cl__args)) {
        Nologo = FALSE;
        LOGO();
    }
    templates(DefaultOptions, argcount(DefaultOptions));
    templates(DefaultMacros, argcount(DefaultMacros));
    /* mark as defaults */
    for (opt = Context->flags; opt != NULL; opt = opt->next) {
        opt->info |= 0x1;
    }
    for (opt = Context->switches; opt != NULL; opt = opt->next) {
        opt->info |= 0x1;
    }
    DefPhase = FALSE;
    if (count_msc_ide_flags_args) {
        templates((const char **) msc_ide_flags_args, count_msc_ide_flags_args);
    }
    if (count_cl_args > 0) {
        templates((const char **) cl_args, count_cl_args);
    }
    if (argc > 1) {
        templates((const char **) &argv[1], argc - 1);
    }
    if (count_cl__args > 0) {
        templates((const char **) cl__args, count_cl__args);
    }
    if (RespEcho) {
        print(STDERR_FILENO, "\n");
    }
    check_required();
    dump_context();
    cc_switches(Context);
    maketempdir(Context);
    if (Help) {
        help(findpass(Context->exedir, "cl32.msg"));
    }
    Help = 0;
    for (unkopt = Unknown_; unkopt != NULL; unkopt = unkopt->next) {
        if (unkopt->arg != NULL) {
            char *joinedstr = xnew(strlen(unkopt->base) + 1 + strlen(unkopt->arg) + 1);
            append(append(joinedstr, unkopt->base), unkopt->arg);
            cmdwarn(4002, joinedstr);
            xfree(joinedstr);
        } else {
            cmdwarn(4002, unkopt->base);
        }
    }
    if (Context->field_0x10 == NULL) {
        cmderr(2003);
    }
    if (ForceType == NULL) {
        default_filetype = SOURCE_UNKNOWN;
    } else {
        switch (*ForceType) {
            case 'C':
                default_filetype = SOURCE_C;
                break;
            case 'O':
                default_filetype = SOURCE_OBJ;
                break;
            case 'P':
                default_filetype = SOURCE_CXX;
                break;
            default:
                default_filetype = SOURCE_OBJ;
                break;
        }
    }
    for (input_path = Context->field_0x10; input_path != NULL; input_path = input_path->next) {
        const passinfo_s *cspec;

        if (default_filetype != SOURCE_UNKNOWN && !input_path->fixed_type) {
            input_path->type = default_filetype;
            input_path->fixed_type = 1;
        } else if (input_path->type == SOURCE_UNKNOWN) {
            if (Preprocess) {
                input_path->type = SOURCE_C;
            } else {
                input_path->type = SOURCE_OBJ;
                cmdwarn(4024, input_path->path);
            }
        }
        for (cspec = Sourceinfo[input_path->type].passes; cspec->pass_filename != NULL; cspec++) {
            if (cspec->is_active) {
                break;
            }
        }
        if (!cspec->is_active) {
            cmdwarn(4027, input_path->path);
        }
    }
    RedirectStdErrToStdOut();
    compile(Context);
    Context->current_source = NULL;
    if (!Action) {
        cmdwarn(4021);
    }
#ifdef _MSC_VER
    } __finally {
    }
#endif
    done(Nerrors ? 2 : 0);
}

// FUNCTION: CL 0x00401c6d
void templates(const char **args, int count)
{
    // GLOBAL: CL 0x0040a058
    static BOOL seen_src_flag = FALSE;
    // GLOBAL: CL 0x0040a05c
    static BOOL already_warned = FALSE;
    int i;

    for (i = 0; i < count;) {
        int original_count = SourceCount;
        const char *arg = args[i];
        if (arg[0] == '@') {
            response_file(&arg[1]);
            continue;
        }
        if (arg[0] == '-' || arg[0] == '/') {
            const combo_s *single_arg_spec = is_combo(&arg[1]);
            if (SourceCount != 0 && original_count == SourceCount) {
                if (single_arg_spec != NULL && arg[strlen(single_arg_spec->combo) + 1] != '\0') {
                    crack_combo(single_arg_spec, arg);
                    i++;
                } else {
                    handlematch(args, &i);
                }
                seen_src_flag = TRUE;
            }
        } else {
            addsource(arg, source(arg), 0);
            i++;
        }
        if (seen_src_flag && original_count != SourceCount && !already_warned) {
            cmdwarn(4026);
            already_warned = 1;
        }
    }
}

// FUNCTION: CL 0x00401d71
BOOL handlematch(const char **args, int *index)
{
    const form_s *option_spec = findmatch(args, *index);
    flag_s *option;
    flag_s *implied_options1;

    if (option_spec == NULL) {
        appendflag(&Unknown_, newflag(args[*index], NULL, NULL, 0));
        *index += 1;
        return FALSE;
    }
    option = domatch(option_spec, args, index);
    if (option == NULL) {
        return TRUE;
    }
    if (option->info & 0x2) {
        appendflag(&Unknown_, option);
        return FALSE;
    }
    option->form = option_spec;
    appendflag(&Context->switches, option);
    implied_options1 = NULL;
    if (option_spec->tmpl != NULL) {
        implied_options1 = expand(option_spec->tmpl, option);
        if (implied_options1 != NULL) {
            flag_s *f1 = NULL;
            flag_s *f2 = conflict(&Context->flags, implied_options1, &f1);
            flag_s *p;

            freeflaglist(f2);
            freeflaglist(f1);
            for (p = implied_options1; p != NULL; p = p->next) {
                p->swtch = option;
            }
        }
    }
    if (option_spec->override != NULL) {
        void *prev_override;
        flag_s *implied_options2 = expand(option_spec->override, option);
        flag_s *f1 = NULL;
        flag_s *f2 = conflict(&Context->flags, implied_options2, &f1);
        flag_s *p;

        prev_override = NULL;
        for (p = f2; p != NULL; p = p->next) {
            if (p->swtch != NULL) {
                p->info |= 0x10;
            }
            if (!(p->info & 0x21)) {
                if (prev_override == NULL || p->swtch != prev_override) {
                    switcherr(4025, p, option);
                }
                prev_override = p->swtch;
            }
        }
        freeflaglist(f2);
        for (p = f1; p != NULL; p = p->next) {
            if (p->swtch != NULL && p->form->override != NULL) {
                flag_s *g1 = NULL;
                flag_s *implied_opts = expand(p->form->override, p);
                flag_s *g2 = conflict(&implied_options1, implied_opts, &g1);
                freeflaglist(g2);
                freeflaglist(implied_opts);
                freeflaglist(g1);
            }
        }
        freeflaglist(f1);
    }
    if (option_spec->conflict != NULL) {
        flag_s *implied_options3 = expand(option_spec->conflict, option);
        flag_s *f2 = conflict(&Context->flags, implied_options3, NULL);
        flag_s *p;

        if (f2 != NULL) {
            for (p = f2; p != NULL; p = p->next) {
                if (p->swtch != NULL) {
                    p->swtch->info |= 0x10;
                }
                if (!(p->info & 0x21)) {
                    switcherr(2016, p, option);
                }
            }
            freeflaglist(f2);
        }
        freeflaglist(implied_options3);
    }
    if (implied_options1 != NULL) {
        appendflag(&Context->flags, implied_options1);
    }
    return TRUE;
}

// FUNCTION: CL 00401fe8
void freeflaglist(flag_s *opt)
{
    while (opt != NULL) {
        flag_s *next = opt->next;
        freeflag(opt);
        opt = next;
    }
}

// FUNCTION: CL 0x00402004
void freeflag(flag_s *opt)
{
    xfree((void *) opt->arg);
    xfree((void *) opt->base);
    opt->next = Flag_freelist;
    Flag_freelist = opt;
}

// FUNCTION: CL 0040202e
const form_s *findmatch(const char **args, int index)
{
    const form_s *best_match = NULL;
    int best_score = 0;
    int i;

    for (i = 0; Forms[i].form != NULL; i++) {
        const form_s *option_spec = &Forms[i];
        if (option_spec->form[option_spec->form[0] == '^' ? 1 : 0] == args[index][1]) {
            int score = trymatch(option_spec, args, index);
            if (score > 0 && (best_score == 0 || score > best_score)) {
                best_match = option_spec;
                best_score = score;
            }
        }
    }
    return best_match;
}

// FUNCTION: CL 0x00402092
flag_s *conflict(flag_s **list, flag_s *implied_option, flag_s **list_arg3)
{
    flag_s *result = NULL;

    for (; implied_option != NULL; implied_option = implied_option->next) {
        flag_s *list_item;
        for (list_item = *list; list_item != NULL; list_item = list_item->next) {
            if (flagmatch(list_item, implied_option)) {
                if (list_arg3 != NULL &&
                    (((implied_option->info & 0x1) && !(list_item->info & 0x21)) ||
                     ((implied_option->info & 0x20) && !(list_item->info & 0x20)))) {
                    flag_s *o;

                    if (list_item->swtch == NULL) {
                        continue;
                    }
                    for (o = *list_arg3; o != NULL; o = o->next) {
                        if (o->swtch == list_item) {
                            break;
                        }
                    }
                    if (o != NULL) {
                        continue;
                    }
                    appendflag(list_arg3, dupflag(list_item));
                } else {
                    appendflag(&result, rmflag(list, list_item));
                }
            }
        }
    }
    return result;
}

// FUNCTION: CL 0x00402144
flag_s *dupflag(flag_s *opt)
{
    flag_s *r = newflag(opt->base, opt->arg, opt->passes, opt->info);
    r->swtch = opt->swtch;
    return r;
}

// FUNCTION: CL 0x00402165
flag_s *rmflag(flag_s **list, flag_s *item)
{
    for (; *list != NULL; list = &(*list)->next) {
        if (*list == item) {
            flag_s *r = *list;
            *list = r->next;
            r->next = NULL;
            return r;
        }
    }
    return NULL;
}

// FUNCTION: CL 0x0040218e
void switcherr(int code, const flag_s *opt1, const flag_s *opt2)
{
    const char *argval1;
    const char *argval2;

    if (opt1->swtch != NULL) {
        opt1 = opt1->swtch;
    }
    argval1 = "";
    if (opt1->arg != NULL) {
        argval1 = opt1->arg;
    }
    argval2 = "";
    if (opt2->arg != NULL) {
        argval2 = opt2->arg;
    }
    if (code >= 4000 && code < 4100) {
        cmdwarn(code, opt1->base, argval1, opt2->base, argval2);
    } else {
        cmderr(code, opt1->base, argval1, opt2->base, argval2);
    }
}

// FUNCTION: CL 0x004021f0
const combo_s *is_combo(const char *arg)
{
    int i;
    for (i = 0; Combos[i].combo != NULL; i++) {
        if (prefix(Combos[i].combo, arg)) {
            return &Combos[i];
        }
    }
    return NULL;
}

// FUNCTION: CL 0x0040222b
void crack_combo(const combo_s *spec, const char *arg)
{
    char buffer[32];
    const char *argv[2];
    size_t buffer_pos;
    const char *arg_value;

    argv[0] = buffer;
    argv[1] = NULL;
    buffer[0] = arg[0];
    buffer_pos = strlen(spec->combo);
    memcpy(&buffer[1], &arg[1], buffer_pos);
    arg_value = arg + 1 + buffer_pos;
    buffer_pos += 1;
    if (buffer[1] == 'O') {
        if (_mbsstr((const unsigned char *) arg_value, (const unsigned char *) "y1") != NULL) {
            cmdwarn(4099, "Oy1", "Oy-");
        } else if (_mbsstr((const unsigned char *) arg_value, (const unsigned char *) "y2") != NULL) {
            cmdwarn(4099, "Oy2", "Oy");
        }
    }
    while (*arg_value != '\0') {
        const char *valuespec = strchr(spec->buddies, *arg);
        char *buffer_ptr;
        int multi_arg;

        buffer[buffer_pos] = *arg_value++;
        buffer_ptr = &buffer[buffer_pos + 1];
        if (valuespec != NULL) {
            valuespec++;
            for (; *valuespec != ':' && *valuespec != '\0'; valuespec++) {
                if (*valuespec == '#') {
                    while (isdigit(*arg_value)) {
                        *buffer_ptr++ = *arg_value++;
                    }
                } else if (*valuespec == '*') {
                    while (*arg_value != '\0') {
                        *buffer_ptr++ = *arg_value++;
                    }
                    break;
                } else if (*arg_value == *valuespec) {
                    *buffer_ptr++ = *arg_value++;
                    continue;
                }
            }
        }
        *buffer_ptr = '\0';
        multi_arg = 0;
        handlematch(argv, &multi_arg);
    }
}

// FUNCTION: CL 0x00402387
BOOL prefix(const char *start, const char *str)
{
    while (1) {
        if (*start == '\0') {
            return TRUE;
        }
        if (*start != *str) {
            return FALSE;
        }
        start++;
        str++;
    }
}

// FUNCTION: CL 0x004023a8
int argcount(const char **args)
{
    int i;
    if (args == NULL) {
        return 0;
    }
    for (i = 0; *args != NULL; i++) {
        args++;
    }
    return i;
}

// FUNCTION: CL 0x004023c4
BOOL early_switch_scan(char **argv, int argc)
{
    char line[1024];
    int i;

    for (i = 0; i < argc; i++) {
        const char *arg = argv[i];
        if ((*arg == '-' || *arg == '/') && strcmp(arg + 1, "nologo") == 0) {
            return TRUE;
        }
        if (*arg == '@') {
            BOOL found = FALSE;
            FILE *f = fopen(&arg[1], "r");
            if (f != NULL) {
                if (fgets(line, sizeof(line) - 1, f) != NULL) {
                    char *pos_nologo = strstr(line, "nologo");
                    if (pos_nologo != NULL && pos_nologo > line && (pos_nologo[-1] == '-' || pos_nologo[-1] == '/') &&
                        (pos_nologo == line + 1 || _mbschr(" \t\"", pos_nologo[-2]) != NULL) &&
                        (pos_nologo[6] == '\0' || _mbschr(" \t\"\n", pos_nologo[6]))) {
                        found = TRUE;
                    }
                }
                fclose(f);
            }
            if (found) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

// FUNCTION: CL 0x004024f5
void build_context(const char *exePath, context_s *ctx)
{
    memset(ctx, 0, sizeof(*ctx));
    ctx->exedir = extract_path(exePath);
    ctx->errorpath = findpass(ctx->exedir, "cl.err");
    ctx->include = getenv("INCLUDE");
}

// FUNCTION: CL 0x0040253d
void maketempdir(context_s *ctx)
{
    char buffer[1024];
    const char *tmp_env;

    if (ctx->tempPath != NULL) {
        BatchPassOK = FALSE;
        return;
    }
    tmp_env = getenv("TMP");
    if (tmp_env == NULL) {
        ctx->tempPath = xstrdup("XXXXXX");
    } else {
        size_t len_buffer;
        char final_c;

        strcpy(buffer, tmp_env);
        len_buffer = strlen(buffer);
        final_c = buffer[len_buffer - 1];
        if (final_c != '\\' && final_c != ':' && final_c != '/') {
            buffer[len_buffer + 0] = '\\';
            buffer[len_buffer + 1] = '\0';
        }
        ctx->tempPath = catinate(buffer, "XXXXXX");
    }
    ctx->tempPath = _mktemp(ctx->tempPath);
}

// FUNCTION: CL 0x004025f0
char *fullccpath()
{
    return _pgmptr;
}

// FUNCTION: CL 0x004025f9
void alternate_pass(flag_s *option)
{
    char a0 = option->arg[0];
    const sourceinfo_s *filetype_spec;
    for (filetype_spec = Sourceinfo; filetype_spec->phase != PHASE_NOPHASE; filetype_spec++) {
        passinfo_s *filetype_compiler_spec;
        for (filetype_compiler_spec = filetype_spec->passes; filetype_compiler_spec->pass_filename != NULL;
             filetype_compiler_spec++) {
            if (a0 == '.' || filetype_compiler_spec->id == a0) {
                filetype_compiler_spec->pass_filename = xstrdup(&option->arg[1]);
            }
        }
    }
}

// FUNCTION: CL 0x0040264e
void activate_pass(flag_s *option)
{
    const sourceinfo_s *filetype_spec;

    for (filetype_spec = Sourceinfo; filetype_spec->phase != PHASE_NOPHASE; filetype_spec++) {
        passinfo_s *compiler_spec;

        for (compiler_spec = filetype_spec->passes; compiler_spec->pass_filename != NULL; compiler_spec++) {
            if (option->arg[0] == '.' || compiler_spec->id == option->arg[0]) {
                compiler_spec->is_active = TRUE;
            }
        }
    }
}

// FUNCTION: CL 0x00402690
void deactivate_passes(flag_s *option)
{
    char a0 = option->arg[0];
    const sourceinfo_s *filetype_spec;

    for (filetype_spec = Sourceinfo; filetype_spec->phase != PHASE_NOPHASE; filetype_spec++) {
        passinfo_s *filetype_compiler_spec;
        for (filetype_compiler_spec = filetype_spec->passes; filetype_compiler_spec->pass_filename != NULL;
             filetype_compiler_spec++) {
            if (a0 == '.' || _mbschr(option->arg, filetype_compiler_spec->id) != NULL) {
                filetype_compiler_spec->is_active = 0;
            }
        }
    }
}

// FUNCTION: CL 0x004026f1
void copy_active_pass(flag_s *option)
{
    char a2 = option->arg[1];
    bool found = false;
    BOOL active;
    const sourceinfo_s *filetype_spec = Sourceinfo;

    while (!found && filetype_spec->phase != PHASE_NOPHASE) {
        const passinfo_s *filetype_compiler_spec;
        for (filetype_compiler_spec = filetype_spec->passes;
             !found && filetype_compiler_spec->pass_filename != NULL; filetype_compiler_spec++) {
            if (filetype_compiler_spec->id == option->arg[0]) {
                active = filetype_compiler_spec->is_active;
                found = true;
            }
        }
        filetype_spec++;
    }
    if (active) {
        filetype_spec = Sourceinfo;
        while (filetype_spec->phase != PHASE_NOPHASE) {
            passinfo_s *filetype_compiler_spec;
            for (filetype_compiler_spec = filetype_spec->passes;
                 filetype_compiler_spec->pass_filename != NULL; filetype_compiler_spec++) {
                if (filetype_compiler_spec->id == a2) {
                    filetype_compiler_spec->is_active = active;
                }
            }
            filetype_spec++;
        }
    }
}

// FUNCTION: CL 0x00402775
void undef_one_stddef(flag_s *option)
{
    flag_s *implied_option1 = expand("=D:*,=D:*=?", option);
    flag_s *implied_option2 = conflict(&Context->flags, implied_option1, NULL);
    freeflaglist(implied_option2);
    freeflaglist(implied_option1);
}

// FUNCTION: CL 0x004027ae
void undef_stddefs(flag_s *option)
{
    // GLOBAL: CL 0x0040a060
    static BOOL first = TRUE;
    flag_s *p;

    (void) option;
    if (!first) {
        return;
    }
    first = FALSE;
    for (p = Context->flags; p != NULL; p = p->next) {
        if ((p->info & 1) && strcmp(p->base, "D") == 0) {
            freeflag(rmflag(&Context->flags, p));
        }
    }
}

// FUNCTION: CL 0x00402808
void check_compile_collide(flag_s *option)
{
    if (option->arg[0] == '\0') {
        return;
    }
    if (SourceCount > 1) {
        char *arg1_space;
        char *arg2_space;
        const char *arg2;
        const char *end_arg2;

        arg1_space = (char *) _mbschr(option->arg, ' ');
        arg2_space = (char *) _mbschr(arg1_space + 1, ' ');
        *arg2_space = '\0';
        arg2 = arg2_space + 1;
        end_arg2 = arg2;
        for (;;) {
            char *next_end_arg2 = (char *) _mbsinc(end_arg2);
            if (next_end_arg2 == NULL || *next_end_arg2 == '\0') {
                break;
            }
            end_arg2 = next_end_arg2;
        }
        if (_mbsstr(arg2, "%b") == NULL &&
            _mbschr("\\/", *end_arg2) == NULL) {
            cmderr(2036, &arg1_space[1], arg2);
        }
    }
    option->arg[0] = '\0';
}

// FUNCTION: CL 0x004028a3
void configure_asmlist(flag_s *option)
{
    bool ext_cod;
    flag_s *opt_FA;
    flag_s *opt_Fa;
    flag_s *imp_FA;
    flag_s *imp_Fa;
    char *arg_extra;

    if (option->arg[0] == '\0') {
        return;
    }
    arg_extra = (char *) _mbschr(option->arg, ' ');
    if (arg_extra != NULL) {
        *arg_extra = '\0';
        arg_extra += 1;
    }
    opt_FA = newflag("FA", "?", option->arg, 4);
    opt_Fa = newflag("Fa", "?", option->arg, 0);
    imp_FA = conflict(&Context->flags, opt_FA, NULL);
    imp_Fa = conflict(&Context->flags, opt_Fa, NULL);
    if (imp_FA != NULL) {
        arg_extra = imp_FA->arg;
        freeflag(opt_FA);
    } else {
        xfree(opt_FA->arg);
        opt_FA->arg = xstrdup(arg_extra);
        imp_FA = opt_FA;
    }
    if (imp_Fa != NULL) {
        freeflag(opt_Fa);
    } else {
        xfree(opt_Fa->arg);
        opt_Fa->arg = xstrdup("%b");
        imp_Fa = opt_Fa;
    }
    ext_cod = false;
    strcpy(Bigbuf, imp_Fa->arg);
    if (arg_extra != NULL) {
        bool invalid = false;
        char *ptr;
        for (ptr = arg_extra; *ptr != '\0'; ptr++) {
            switch (*ptr) {
            case 'a':
            case 'b':
            case 's':
                break;
            case 'c':
                ext_cod = true;
                break;
            default:
                invalid = true;
                break;
            }
        }
        if (invalid) {
            cmdwarn(4015, "/FA", &arg_extra[1]);
        }
    }
    complete_filename(ext_cod ? "cod" : "asm", Bigbuf, NULL);
    xfree(imp_Fa->arg);
    imp_Fa->arg = xstrdup(Bigbuf);
    appendflag(&Context->flags, imp_FA);
    appendflag(&Context->flags, imp_Fa);
    option->arg[0] = '\0';
}

// FUNCTION: CL 0x00402a59
void link_dll(flag_s *option)
{
    static BOOL first = TRUE;

    (void) option;

    if (first) {
        source_s *filepath;

        first = TRUE;
        DllFlg = TRUE;

        for (filepath = Context->field_0x10; filepath != NULL; filepath = filepath->next) {
            if (filepath->type == SOURCE_EXP) {
                flag_s *implib_option = newflag("implib\\:", NULL, NULL, 0x0);
                flag_s *implied_option1 = expand("=implib\\::?", implib_option);
                flag_s *implied_option2 = conflict(&Context->flags, implied_option1, NULL);
                freeflaglist(implied_option2);
                freeflag(implib_option);
                freeflaglist(implied_option1);
                break;
            }
        }
    }
}

// FUNCTION: CL 0x00402ae2
void cc_switches(context_s *ctx)
{
    char buffer[512];
    flag_s *opt;

    for (opt = ctx->flags; opt != NULL; opt = opt->next) {
        bool found;
        const cmd_s *action;

        if (!flag_this_pass(opt, &PassInfo)) {
            continue;
        }
        found = false;
        for (action = Cctab; action->form != NULL; action++) {
            if (opt->base[0] == action->form[0] && strcmp(opt->base, action->form) == 0) {
                found = true;
                switch (action->type) {
                    case CMD_TRUE:
                        *action->flag = TRUE;
                        break;
                    case CMD_FALSE:
                        *action->flag = FALSE;
                        break;
                    case CMD_STRING:
                        replaca(buffer, opt->arg, ctx);
                        *action->string = xstrdup(buffer);
                        break;
                    case CMD_FUNCTION:
                        action->function(opt);
                        break;
                    default:
                        break;
                }
            }
            if (found) {
                break;
            }
        }
    }
}

// FUNCTION: CL 0x00402bc0
void check_required()
{
    flag_s *option;

    for (option = Context->switches; option != NULL; option = option->next) {
        char *parent_value;
        char *parent_ptr;
        const form_s *parent;

        if (option->info & 0x10) {
            continue;
        }
        parent = option->form;
        if (parent->required == NULL) {
            continue;
        }
        if (parent->tmpl == NULL) {
            continue;
        }
        parent_value = xstrdup(parent->required);
        parent_ptr = parent_value;
        while (1) {
            char *next_ptr = (char *) _mbschr(parent_ptr, ';');
            flag_s *implied1;
            flag_s *implied2;
            flag_s *implied3;

            if (next_ptr != NULL) {
                *next_ptr = '\0';
                next_ptr += 1;
            }
            implied1 = expand(parent_ptr, option);
            if (find_any_match(Context->switches, implied1)) {
                parent_ptr = next_ptr;
            } else {
                if (!(option->info & 0x1)) {
                    char *opt1str = xnew(80);
                    char *opt2str = xnew(80);
                    flag_s *imp;

                    opt1str[0] = '/';
                    opt2str[0] = '\0';
                    strcpy(&opt1str[1], option->base);
                    for (imp = implied1; imp != NULL; imp = imp->next) {
                        if (imp != implied1) {
                            if (imp->next == NULL) {
                                strcat(opt2str, get_message(321));
                            } else {
                                strcat(opt2str, get_message(320));
                            }
                        }
                        strcat(opt2str, "/");
                        strcat(opt2str, imp->base);
                    }
                    cmdwarn(4007, opt1str, opt2str);
                    xfree(opt2str);
                    xfree(opt1str);
                }
                implied2 = expand(parent->tmpl, option);
                implied3 = conflict(&Context->flags, implied2, NULL);
                freeflaglist(implied3);
                freeflaglist(implied2);
                parent_ptr = NULL;
            }
            freeflaglist(implied1);
            if (parent_ptr == NULL) {
                break;
            }
        }
        xfree(parent_value);
    }
}

// FUNCTION: CL 0x00402d5d
BOOL find_any_match(flag_s *const opts1, flag_s *const opts2)
{
    flag_s *opt1;
    for (opt1 = opts1; opt1 != NULL; opt1 = opt1->next) {
        flag_s *opt2;
        for (opt2 = opts2; opt2 != NULL; opt2 = opt2->next) {
            if (flagmatch(opt1, opt2) && !(opt1->info & 0x10) && !(opt2->info & 0x10)) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

// FUNCTION: CL 0x00402da5
const char *complete_filename(const char *extension_spec, char *path, const char *filename)
{
    char throwaway_buffer[256];
    char ext_c1 = *extension_spec;
    const char *path_filename;
    char *path_ptr;

    path_filename = strrchars(path, "\\/");
    if (ext_c1 == '<') {
        extension_spec++;
    }
    path_filename = strrchars(path, "\\/");
    if (path_filename != NULL && path_filename[1] == '\0') {
        if (filename == NULL) {
            filename = "%b";
        }
        path_ptr = concat(path, filename);
    } else {
        path_filename = path;
        path_ptr = (char *) _mbsrchr(path_filename, '.');
        if (path_ptr == NULL) {
            path_ptr = &path[strlen(path)];
        } else if (ext_c1 != '<') {
            path_ptr = throwaway_buffer;
        }
    }
    *path_ptr++ = '.';
    for (;;) {
        if (*extension_spec == '\0' || *extension_spec == ',') {
            break;
        }
        *path_ptr++ = *extension_spec++;
    }
    *path_ptr = '\0';
    return extension_spec;
}

// FUNCTION: CL 0x00402e48
void usage()
{
    LOGO();
    print(STDOUT_FILENO, get_message(305));
    exit(0);
}

// FUNCTION: CL 0x00402e76
int ldargs(const char **args, int *index)
{
    const char *link_arg = &args[*index][5];
    int new_index;

    if (*link_arg != '\0') {
        appendflag(&Context->flags, newflag(link_arg, NULL, "L", 0x8));
        appendflag(&Context->flags, newflag(link_arg, NULL, "C", 0x8));
    }
    new_index = *index + 1;
    while (args[new_index] != NULL) {
        const char *link_arg = args[new_index];
        appendflag(&Context->flags, newflag(link_arg, NULL, "L", 0x8));
        appendflag(&Context->flags, newflag(link_arg, NULL, "C", 0x8));
        new_index += 1;
    }
    *index = new_index;
    return 0;
}

// FUNCTION: CL 0x00402f31
int Dargs(const char **args, int *index)
{
    const char *macro_arg = &args[*index][2];
    char *pos_hash;
    char *pos_assign;
    char *macro_name;
    size_t macro_name_len;
    flag_s *opt;

    if (*macro_arg != '\0') {
        *index += 1;
    } else {
        macro_arg = args[*index + 1];
        *index += 2;
    }
    if (macro_arg == NULL || macro_arg[0] == '\0') {
        cmderr(2004, "D");
    }
    pos_hash = (char *) _mbschr(macro_arg, '#');
    if (pos_hash != NULL) {
        /* FIXME/BUG: this function modifies args ! */
        *pos_hash = '=';
    }
    pos_assign = (char *) _mbschr(macro_arg, '=');
    if (pos_assign == NULL) {
        macro_name_len = strlen(macro_arg);
    } else {
        macro_name_len = pos_assign - macro_arg;
    }
    macro_name = xnew(macro_name_len + 1);
    strncpy(macro_name, macro_arg, macro_name_len);
    macro_name[macro_name_len] = '\0';
    opt = newflag("D", macro_name, NULL, 0x0);
    undef_one_stddef(opt);
    freeflag(opt);
    xfree(macro_name);
    opt = newflag("D", macro_arg, "1PM", 0x4);
    appendflag(&Context->flags, opt);
    return 0;
}

// FUNCTION: CL 0x0040301b
int toargs(const char **args, int *index)
{
    other_sources("To", args, index, SOURCE_OBJ);
    return 0;
}

// FUNCTION: CL 0x00403035
int tcargs(const char **args, int *index)
{
    other_sources("Tc", args, index, SOURCE_C);
    return 0;
}

// FUNCTION: CL 0x0040304f
int tpargs(const char **args, int *index)
{
    other_sources("Tp", args, index, SOURCE_CXX);
    return 0;
}

// FUNCTION: CL 0x00403069
void other_sources(const char *optionPrefix, const char **args, int *index, source_type filetype)
{
    const char *path = &args[*index][1];
    const char *prefix = optionPrefix;

    while (*prefix != '\0') {
        prefix++;
        path++;
    }
    if (*path != '\0') {
        *index += 1;
    } else {
        path = args[*index + 1];
        *index += 2;
    }
    if (path == NULL || path[0] == '\0') {
        cmderr(2004, optionPrefix);
    }
    addsource(path, filetype, 1);
}

// FUNCTION: CL 0x004030c
void LOGO(void)
{
    print(STDERR_FILENO, get_message(306), VersionNumber);
    print(STDERR_FILENO, get_message(307));
}

// FUNCTION: CL 0x004030fc
char *findpass(const char *dirpath, const char *filename)
{
    char buffer[1024];

    strcpy(buffer, dirpath);
    strcat(buffer, filename);
    if (_access(buffer, R_OK) == 0) {
        filename = buffer;
    } else {
        buffer[0] = '.';
        buffer[1] = '\\';
        buffer[2] = '\0';
        strcat(buffer, filename);
        if (_access(buffer, R_OK) == 0) {
            filename = buffer;
        } else {
            if (walkpath(filename, buffer, sizeof(buffer)) != 0) {
                filename = buffer;
            }
        }
    }
    return xstrdup(filename);
}

// FUNCTION: CL 0x004031be
char *extract_path(const char *path)
{
    char drive[256];
    char dir[256];
    char basename[256];
    char ext[256];
    size_t len_dir;
    char *drive_dir;

    _splitpath(path, drive, dir, basename, ext);
    len_dir = strlen(dir);
    if (len_dir > 0 && dir[len_dir - 1] != '\\' && dir[len_dir - 1] != ';' && dir[len_dir - 1] != '/') {
        dir[len_dir + 0] = '\\';
        dir[len_dir + 1] = '\0';
    }
    drive_dir = strcat(drive, dir);
    return xstrdup(drive_dir);
}

// FUNCTION: CL 0x00403248
size_t walkpath(const char *filename, char *buffer, size_t bufferSize)
{
    const char *path_env = getenv("PATH");
    if (path_env == NULL) {
        buffer[0] = '\0';
        return 0;
    }
    while (1) {
        char *write_ptr;
        size_t len_path_item;
        size_t len_joined;

        while (1) {
            if (*path_env == '\0') {
                buffer[0] = '\0';
                return 0;
            }
            while (*path_env == ' ' || *path_env == ';') {
                path_env++;
            }
            write_ptr = buffer;
            if (*path_env == '\0') {
                buffer[0] = '\0';
                return FALSE;
            }
            while (*path_env != '\0' && *path_env != ';') {
                *write_ptr++ = *path_env++;
            }
            if (*buffer != '\0') {
                break;
            }
        }
        len_path_item = strlen(buffer);
        if (buffer[len_path_item - 1] != '\\' && buffer[len_path_item - 1] != ';' && buffer[len_path_item - 1] != '/') {
            buffer[len_path_item + 0] = '\\';
            buffer[len_path_item + 1] = '\0';
        }
        strcat(buffer, filename);
        len_joined = strlen(buffer);
        if (len_joined >= bufferSize) {
            cmderr(0);
        }
        if (_access(buffer, R_OK) == 0) {
            return len_joined;
        }
    }
}
