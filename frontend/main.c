#include "decomp.h"

#include "args.h"
#include "callbacks.h"
#include "portable.h"

#include <io.h>
#include <mbstring.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <windows.h>

extern const char *doexpand(const char *spec, char *buffer, const char *key);
extern char *replaca(char *buffer, const char *value, context_s *ctx);
extern int execute(int inheritEnv, const char *cmdName, const char *cmd_env_name, char **argv);
extern char *strqcpy(char *dest, const char *path);
extern void cmderr(int code, ...);
extern const char *gobblewhite(const char *text);
extern void response_file(const char *path);
extern size_t strqlen(const char *path);

context_s CX = {0};

// GLOBAL: CL 0x0040afc4
BOOL GotCtrlC;

// GLOBAL: CL 0x0040afc8
BOOL Spawning;

// GLOBAL: CL 0x0040a01c
BOOL Nologo = TRUE;

// GLOBAL: CL 0x0040a030
context_s *Context = &CX;

// GLOBAL: CL 0x0040a770
int SourceCount = 0;

// GLOBAL: CL 0x0040a774
flag_s *Unknown_ = NULL;

// GLOBAL: CL 0x0040a77c
BOOL RespEcho = FALSE;

// GLOBAL: CL 0x0040a018
BOOL DefPhase = TRUE;

// GLOBAL: CL 0x0040a054
flag_s *Flag_freelist = NULL;

// GLOBAL: CL 0x0040a200
char Bigbuf[1024];

// GLOBAL: CL 0x0040afa8
struct timeb Endtime;

// GLOBAL: CL 0x0040afb8
struct timeb Starttime;

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

// GLOBAL: CL 0x0040a070
const char *DefaultMacros[] = {
    "-D_MSC_VER=1020",
    "-D_WIN32",
    NULL,
};

// GLOBAL: CL 0x00408510
const tSingle_arg_spec Combos[] = {
    {
        "G",
        "3:4:5:d:e:f:h*:i-:m-:p#:r:s*:t#:x-:y:z:A:B:D:E*:M:R-:X-",
    },
    {
        "O",
        "1:2:a-:b#:d:g-:i-:p-:s:t:w-:x:y-:V#",
    },
    {
        "Z",
        "7:a:d:e:g:i:l:m#:n:p#:s:B*:M-",
    },
    {
        NULL,
        NULL,
    },
};

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
passinfo_s Cxx_passes[] = {
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
passinfo_s Link_passes[] = {
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

// GLOBAL: CL 0x0040a038
passinfo_s PassInfo = {
    NULL,
    "cl.err",
    NULL,
    1,
    'D',
    '-',
};

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

// GLOBAL: CL 0x0040a010
BOOL Coff = TRUE;

// GLOBAL: CL 0x0040a014
BOOL DefInclude = TRUE;

// GLOBAL: CL 0x0040a020
BOOL MinimalRebuild = TRUE;

// GLOBAL: CL 0x0040a024
BOOL MinRebuildOK = TRUE;

// GLOBAL: CL 0x0040a028
BOOL BatchPasses = FALSE;

// GLOBAL: CL 0x0040a02c
BOOL BatchPassOK = TRUE;

// GLOBAL: CL 0x0040a618
BOOL Preprocess = FALSE;

// GLOBAL: CL 0x0040a778
char *Mapfilename = NULL;

// GLOBAL: CL 0x0040a794
BOOL DllFlg = FALSE;

// GLOBAL: CL 0x0040a798
BOOL Help = FALSE;

// GLOBAL: CL 0x0040a744
BOOL Reproducable = FALSE;

// GLOBAL: CL 0x0040a74c
BOOL Mapfile = FALSE;

// GLOBAL: CL 0x0040a04c
BOOL RedirStderr = TRUE;

// GLOBAL: CL 0x0040a050
BOOL Time = FALSE;

// GLOBAL: CL 0x0040a600
char *ForceType = NULL;

// GLOBAL: CL 0x0040a604
char *IdbFileName = NULL;

// GLOBAL: CL 0x0040a60c
BOOL Nospawn = FALSE;

// GLOBAL: CL 0x0040a610
BOOL Verbose = FALSE;

// GLOBAL: CL 0x0040a614
BOOL Action = FALSE;

// GLOBAL: CL 0x0040a7a0
BOOL Keepfiles = FALSE;

// GLOBAL: CL 0x0040a608
char *Object = NULL;

// GLOBAL: CL 0x0040a784
char *Exefilename = NULL;

// GLOBAL: CL 0x0040a78c
BOOL Nerrors = FALSE;

// GLOBAL: CL 0x0040a788
char *SbrFileName = NULL;

// GLOBAL: CL 0x00407090
cmd_s Cctab[] = {
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

// GLOBAL: CL 0x00408530
const ilsuffix_s Il_suffix[] = {
    {
        "ex",
        TRUE,
    },
    {
        "sy",
        TRUE,
    },
    {
        "gl",
        TRUE,
    },
    {
        "in",
        TRUE,
    },
    {
        "st",
        TRUE,
    },
    {
        "db",
        TRUE,
    },
    {
        "lk",
        FALSE,
    },
    {
        "df.def",
        FALSE,
    },
    {NULL, FALSE},
};

// FUNCTION: CL 0x00401000
source_type source(const char *filepath)
{
    char extension[256];
    int i;

    _splitpath(filepath, NULL, NULL, NULL, extension);
    if (extension[0] == '\0') {
        return SOURCE_UNKNOWN;
    }
    for (i = 0; Sourceinfo[i].phase != PHASE_POSTPROCESS; i++) {
        if (_stricmp(&extension[1], Sourceinfo[i].extension) == 0) {
            return (source_type) i;
        }
    }
    return SOURCE_UNKNOWN;
}

// FUNCTION: CL 0x0040553c
void rm_one_il(int index)
{
    char temp_path[1024];

    if (strlen(Context->tempPath) + 10 > sizeof(temp_path) - 1) {
        cmderr(0);
    }
    replaca(temp_path, "%t", Context);
    strcat(temp_path, Il_suffix[index].suffix);
    _unlink(temp_path);
}

// FUNCTION: CL 0x00405483
void do_rm_il(BOOL arg1)
{
    source_s *original_field_0x20;
    int i;
    const ilsuffix_s *temp_file;
    if (Keepfiles) {
        return;
    }
    if (Context->tempPath == NULL) {
        return;
    }
    original_field_0x20 = Context->current_source;
    i = 0;
    temp_file = &Il_suffix[i];
    for (; temp_file->suffix != NULL; i++, temp_file++) {
        if (arg1) {
            if (temp_file->compile_il) {
                rm_one_il(i);
                continue;
            }
        } else {
            if (!temp_file->compile_il) {
                Context->current_source = NULL;
                rm_one_il(i);
                continue;
            }
            if (original_field_0x20 != NULL) {
                worklist_s *unk = Context->batchlist;
                if (unk == NULL) {
                    Context->current_source = original_field_0x20;
                    rm_one_il(i);
                    continue;
                }
                while (unk != NULL) {
                    Context->current_source = unk->parsed_file;
                    rm_one_il(i);
                    unk = unk->next;
                }
            }
        }
    }
    Context->current_source = original_field_0x20;
}

// FUNCTION: CL 0x004055ad
void done(int exitcode)
{
    do_rm_il(FALSE);
    exit(exitcode);
}

// FUNCTION: CL 0x004055c5
size_t l2a(unsigned long number, char *dest, int radix)
{
    char buffer[36];
    char *str;
    size_t len;
    buffer[0] = '\0';
    str = &buffer[1];
    len = 0;
    while (1) {
        _mbccpy((unsigned char *) str, (unsigned char *) &"0123456789abcdef"[number % radix]);
        str = (char *) _mbsinc((unsigned char *) str);
        number /= radix;
        if (number == 0) {
            break;
        }
    }
    while (1) {
        str = (char *) _mbsdec((unsigned char *) buffer, (unsigned char *) str);
        _mbccpy((unsigned char *) dest, (unsigned char *) str);
        dest = (char *) _mbsinc((unsigned char *) dest);
        if (*str == '\0') {
            break;
        }
        len += 1;
    }
    return len;
}

// FUNCTION: CL 0x00405672
char *ErrorVSprintf(size_t *len, const char *format, va_list ap)
{
    static char buffer[2048];
    char *write_ptr = buffer;
    const char *src;
    while (*format != '\0') {
        if (_mbsncmp((unsigned char *) format, (unsigned char *) "%", 1) == 0) {
            format = _mbsinc((unsigned char *) format);
            switch (*format) {
            case 'c':
                *write_ptr = (char) va_arg(ap, int);
                write_ptr = (char *) _mbsinc((unsigned char *) write_ptr);
                break;
            case 'd':
            case 'x':
                write_ptr += l2a(va_arg(ap, int), write_ptr,
                        _mbsncmp((unsigned char *) format, (unsigned char *) "d", 1) == 0 ? 10 : 0);
                break;
            case 's':
                src = va_arg(ap, const char *);
                strcpy(write_ptr, src);
                write_ptr += strlen(src);
                break;
            default:
                _mbccpy((unsigned char *) write_ptr, (unsigned char *) "%");
                _mbccpy(_mbsinc((unsigned char *) write_ptr), (unsigned char *) format);
                write_ptr = (char *) _mbsinc((unsigned char *) write_ptr);
                break;
            }
        } else {
            _mbccpy((unsigned char *) write_ptr, (unsigned char *) format);
            write_ptr = (char *) _mbsinc((unsigned char *) write_ptr);
        }
        format = _mbsinc((unsigned char *) format);
    }
    *write_ptr = '\0';
    *len = write_ptr - buffer;
    if (*len >= sizeof(buffer)) {
        cmderr(0);
    }
    return buffer;
}

// FUNCTION: CL 0x00405916
const char *GetMessageInFile(const char *path, int code)
{
    char line[256];
    char digits[12];
    char *ptr_text;
    const char *start_text;

    FILE *f = fopen(path, "r");
    if (f == NULL) {
        return "";
    }
    while (1) {
        char *ptr_digits;
        while (1) {
            if (fgets(line, sizeof(line), f) == NULL) {
                fclose(f);
                return "";
            }
            ptr_text = (char *) gobblewhite(line);
            if (_ismbcdigit(*ptr_text)) {
                break;
            }
        }
        ptr_digits = digits;
        while (_ismbcdigit(*ptr_text)) {
            *ptr_digits++ = *ptr_text++;
        }
        *ptr_digits = '\0';
        if (atoi(digits) == code) {
            break;
        }
    }
    start_text = gobblewhite(ptr_text) + 1;
    ptr_text = (char *) start_text; /* Skip first '"' */

    while (_mbsncmp((unsigned char *) ptr_text, (unsigned char *) "\"", 1) != 0) {
        if (_mbsncmp((unsigned char *) ptr_text, (unsigned char *) "\\", 1) == 0) {
            switch (*_mbsinc((unsigned char *) ptr_text)) {
            case 'n':
                *ptr_text = '\n';
                strcpy(ptr_text + 1, ptr_text + 2);
                break;
            case 't':
                *ptr_text = '\t';
                strcpy(ptr_text + 1, ptr_text + 2);
                break;
            }
        }
        ptr_text = (char *) _mbsinc((unsigned char *) ptr_text);
    }
    *ptr_text = '\0';
    fclose(f);
    return strdup(start_text);
}

// FUNCTION: CL 0x00405647
void print(int stream, const char *format, ...)
{
    char *text;
    size_t len;
    va_list ap;
    va_start(ap, format);
    text = ErrorVSprintf(&len, format, ap);
    va_end(ap);
    write(stream, text, len);
}

// FUNCTION: CL 0x004057b4
void vprint(int stream, const char *format, va_list ap)
{
    size_t len;
    const char *text = ErrorVSprintf(&len, format, ap);
    write(stream, text, len);
}

// FUNCTION: CL 0x00405b28
const char *get_message(int code)
{
    return GetMessageInFile(Context->errorpath, code);
}

// FUNCTION: CL 0x00405a6a
void cmderr(int code, ...)
{
    va_list ap;
    if (code == 0) {
        code = 2000;
    }
    print(STDERR_FILENO, get_message(303), code); /* "Command line error D%d : " */
    va_start(ap, code);
    vprint(STDERR_FILENO, GetMessageInFile(Context->errorpath, code), ap);
    va_end(ap);
    print(STDERR_FILENO, "\n");
    done(2);
}

// FUNCTION: CL 0x00405ad3
void cmdwarn(int code, ...)
{
    va_list ap;
    const char *message;

    message = GetMessageInFile(Context->errorpath, code);
    print(STDERR_FILENO, get_message(302), code);
    va_start(ap, code);
    vprint(STDERR_FILENO, message, ap);
    va_end(ap);
    print(STDERR_FILENO, "\n");
}

// FUNCTION: CL 0x004030c
void LOGO(void)
{
    print(STDERR_FILENO, get_message(306), "10.20.6166");
    print(STDERR_FILENO, get_message(307));
}

// FUNCTION: CL 0x00402e48
void usage()
{
    LOGO();
    print(STDOUT_FILENO, get_message(305));
    exit(0);
}

// FUNCTION: CL 0x00405bd5
void *xnew(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL) {
        cmderr(0);
    }
    return ptr;
}

// FUNCTION: CL 0x00404fcb
char *append(char *str1, const char *str2)
{
    if (str2 != NULL) {
        strcpy(str1, str2);
    }
    return &str1[strlen(str1)];
}

// FUNCTION: CL 0x00405c0a
char *xstrdup(const char *str)
{
    if (str == NULL) {
        return NULL;
    }
    return _strdup(str);
}

// FUNCTION: CL 0x00404ff2
char *catinate(char *str1, char *str2)
{
    size_t len1 = strlen(str2);
    size_t len2 = strlen(str1);
    char *result = xnew(len1 + len2 + 1);
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

// FUNCTION: CL 0x00404f2e
char *concat(char *str1, const char *str2)
{
    if (str2 != NULL) {
        strcat(str1, str2);
    }
    return str1 + strlen(str1);
}

// FUNCTION: CL 0x00405bf7
void xfree(void *ptr)
{
    if (ptr != NULL) {
        free(ptr);
    }
}

// FUNCTION: CL 0x00405db3
BOOL WINAPI NT_handling_function(DWORD CtrlType)
{
    (void) CtrlType;
    GotCtrlC = TRUE;
    if (!Spawning) {
        SetConsoleCtrlHandler(NULL, TRUE);
        done(4);
    }
    return 1;
}

// FUNCTION: CL 0x00405da5
void OS_Init()
{
    SetConsoleCtrlHandler(NT_handling_function, TRUE);
}

// FUNCTION: CL 0x00404efe
const char *gobblewhite(const char *text)
{
    while (*text != '\0' && _ismbcspace(*text)) {
        text = (char *) _mbsinc((unsigned char *) text);
    }
    return text;
}

// FUNCTION: CL 0x00405246
char **sztoszv(const char *text, BOOL cleanUpSlash)
{
    const char *src_ptr;
    char *clean_str;
    char *dst_ptr;
    bool in_quotes;
    int count_args;
    int arg_i;
    char **args;

    if (text == NULL) {
        return NULL;
    }
    src_ptr = gobblewhite(text);
    if (src_ptr[0] == '\0') {
        return NULL;
    }
    clean_str = xnew(strlen(src_ptr) + 1);
    dst_ptr = clean_str;
    in_quotes = false;
    count_args = 0;
    while (*src_ptr != '\0') {
        while (1) {
            bool copy_src = true;
            int nb_quotes = 0;
            int count_slash = 0;
            while (_mbsncmp((unsigned char *) src_ptr, (unsigned char *) "\\", 1) == 0) {
                src_ptr = (char *) _mbsinc((unsigned char *) src_ptr);
                count_slash += 1;
            }
            if (_mbsncmp((unsigned char *) src_ptr, (unsigned char *) "\"", 1) == 0) {
                if (count_slash % 2 == 0) {
                    if (in_quotes) {
                        if (_mbsncmp(_mbsinc((unsigned char *) src_ptr), (unsigned char *) "\"", 1) == 0) {
                            src_ptr = (char *) _mbsinc((unsigned char *) src_ptr);
                            if (!cleanUpSlash) {
                                nb_quotes = 1;
                            }
                        } else {
                            copy_src = !cleanUpSlash;
                        }
                    } else {
                        copy_src = !cleanUpSlash;
                    }
                    in_quotes = !in_quotes;
                }
                if (cleanUpSlash) {
                    count_slash /= 2;
                }
            }
            while (count_slash != 0) {
                count_slash -= 1;
                _mbccpy((unsigned char *) dst_ptr, (unsigned char *) "\\");
                dst_ptr = (char *) _mbsinc((unsigned char *) dst_ptr);
            }
            while (nb_quotes != 0) {
                nb_quotes -= 1;
                _mbccpy((unsigned char *) dst_ptr, (unsigned char *) "\"");
                dst_ptr = (char *) _mbsinc((unsigned char *) dst_ptr);
            }
            if (src_ptr[0] == '\0' || (!in_quotes && _ismbcspace(src_ptr[0]))) {
                break;
            }
            if (copy_src) {
                _mbccpy((unsigned char *) dst_ptr, (unsigned char *) src_ptr);
                dst_ptr = (char *) _mbsinc((unsigned char *) dst_ptr);
            }
            src_ptr = (char *) _mbsinc((unsigned char *) src_ptr);
        }
        dst_ptr[0] = '\0';
        dst_ptr += 1;
        count_args += 1;
        src_ptr = gobblewhite(src_ptr);
    }
    arg_i = 0;
    args = xnew(sizeof(char *) * (count_args + 1));
    while (count_args != 0) {
        char *arg;
        count_args -= 1;
        arg = (char *) gobblewhite(clean_str);
        if (arg[0] != '\0') {
            args[arg_i] = arg;
            arg_i += 1;
        }
        clean_str = arg + strlen(clean_str) + 1;
    }
    args[arg_i] = NULL;
    return args;
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

// FUNCTION: CL 0x004025f0
char *fullccpath()
{
    return _pgmptr;
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

// FUNCTION: CL 0x004024f5
void build_context(const char *exePath, context_s *ctx)
{
    memset(ctx, 0, sizeof(*ctx));
    ctx->exedir = extract_path(exePath);
    ctx->errorpath = findpass(ctx->exedir, "cl.err");
    ctx->include = getenv("INCLUDE");
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
                            (pos_nologo == line + 1 || _mbschr((unsigned char *) " \t\"", pos_nologo[-2]) != NULL) &&
                            (pos_nologo[6] == '\0' || _mbschr((unsigned char *) " \t\"\n", pos_nologo[6]))) {
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

// FUNCTION: CL 0x004010e8
BOOL flag_this_pass(flag_s *option, const passinfo_s *spec)
{
    return strchr(option->passes, spec->id) != NULL;
}

// FUNCTION: CL 0x00404e41
char *basename(char *buffer, const char *path)
{
    _splitpath(path, NULL, NULL, buffer, NULL);
    return buffer;
}

// FUNCTION: CL 0x00404eab
char *pathname(char *buffer, const char *path)
{
    char drive[4];
    char dir[256];
    char basename[256];

    _splitpath(path, drive, dir, basename, NULL);
    _makepath(buffer, drive, dir, basename, "");
    return buffer;
}

// FUNCTION: CL 0x00404a64
const char *mapfile(char *buffer, const char *exePath)
{
    char drive[4];
    char dir[256];
    char filename[256];
    char extension[256];

    if (!Mapfile) {
        return "nul.map";
    }
    if (!Mapfilename) {
        _splitpath(exePath, drive, dir, filename, NULL);
        _makepath(buffer, drive, dir, filename, "map");
        return buffer;
    }
    _splitpath(exePath, drive, dir, filename, extension);
    if (filename[0] == '\0') {
        basename(filename, exePath);
    }
    _makepath(buffer, drive, dir, filename, extension[0] != '\0' ? extension : "map");
    return buffer;
}

// FUNCTION: CL 0x00404b29
char *replaca(char *buffer, const char *format, context_s *ctx)
{
    char path_buffer[256];
    char *dest = buffer;
    char *ptr;
    const char *filepath;
    source_type filetype;
    short batch_id;

    if (ctx->current_source != NULL) {
        filepath = ctx->current_source->path;
        filetype = ctx->current_source->type;
        batch_id = ctx->current_source->batch_id;
    } else {
        filepath = "";
        filetype = SOURCE_UNKNOWN;
        batch_id = -1;
    }
    while (*format != '\0') {
        if (*format == '%') {
            *dest = '\0';
            switch (format[1]) {
            case '%':
                *dest++ = format[1];
                break;
            case 'b':
                basename(path_buffer, filepath);
                dest = concat(dest, path_buffer);
                break;
            case 'B':
                basename(path_buffer, filepath);
                _mbsupr((unsigned char *) path_buffer);
                dest = concat(dest, path_buffer);
                break;
            case 'e':
                ptr = ctx->errorpaths[filetype][ctx->current_pass];
                if (dest == NULL) {
                    dest = "";
                }
                dest = concat(dest, ptr);
                break;
            case 'f':
                dest = concat(dest, filepath);
                break;
            case 'X':
                if (DllFlg) {
                    dest = concat(dest, "dll");
                } else {
                    dest = concat(dest, "exe");
                }
                break;
            case 'x':
                pathname(path_buffer, Exefilename);
                dest = concat(dest, path_buffer);
                break;
            case 't':
                dest = concat(dest, ctx->tempPath);
                if (ctx->batchlist && batch_id != -1) {
                    dest[-6] = 'a' + batch_id / 10;
                    dest[-5] = '0' + batch_id % 10;
                }
                break;
            case 'm':
                {
                    char *exe_buffer = xnew(1024);
                    replaca(exe_buffer, Exefilename, ctx);
                    mapfile(dest, exe_buffer);
                    dest += strlen(dest);
                    xfree(exe_buffer);
                }
                break;
            }
            format += 2;
        } else {
            *dest++ = *format++;
        }
    }
    *dest = '\0';
    return buffer;
}

// FUNCTION: CL 0x00402ae2
void cc_switches(context_s *ctx)
{
    char buffer[512];
    flag_s *opt;

    for (opt = ctx->flags; opt != NULL; opt = opt->next) {
        bool found;
        cmd_s *action;

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
const tSingle_arg_spec *is_combo(const char *arg)
{
    int i;
    for (i = 0; Combos[i].valuespec != NULL; i++) {
        if (prefix(Combos[i].key, arg)) {
            return &Combos[i];
        }
    }
    return NULL;
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

// FUNCTION: CL 0x00402144
flag_s *dupflag(flag_s *opt)
{
    flag_s *r = newflag(opt->base, opt->arg, opt->passes, opt->info);
    r->swtch = opt->swtch;
    return r;
}

// FUNCTION: CL 0x00402004
void freeflag(flag_s *opt)
{
    xfree((void *) opt->arg);
    xfree((void *) opt->base);
    opt->next = Flag_freelist;
    Flag_freelist = opt;
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

// FUNCTION: CL 0x004016f8
void appendflag(flag_s **list, flag_s *opt)
{
    while (*list != NULL) {
        list = &(*list)->next;
    }
    *list = opt;
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

// FUNCTION: CL 0x00404f55
char *concatmeta(char *dest, const char *format)
{
    dest = dest + strlen(dest);
    if (format != NULL) {
        while (*format != '\0') {
            _mbccpy((unsigned char *) dest, (unsigned char *) format);
            dest = (char *) _mbsinc((unsigned char *) dest);
            if (_mbsncmp((unsigned char *) format, (unsigned char *) "%", 1) == 0) {
                _mbccpy((unsigned char *) dest, (unsigned char *) format);
                dest = (char *) _mbsinc((unsigned char *) dest);
            }
            format = (char *) _mbsinc((unsigned char *) format);
        }
        *dest = '\0';
    }
    return dest;
}

// FUNCION: CL 0x00405204
const char *strrchars(const char *text, const char *needles)
{
    const char *last_pos = NULL;

    while (*needles != '\0') {
        const char *pos = (char *) _mbsrchr((unsigned char *) text, *needles);
        if (pos != NULL) {
            if (last_pos == NULL || last_pos < pos) {
                last_pos = pos;
            }
        }
        needles = (char *) _mbsinc((unsigned char *) needles);
    }
    return last_pos;
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
        path_ptr = (char *) _mbsrchr((unsigned char *) path_filename, '.');
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
            char *next_ptr = (char *) _mbschr((unsigned char *) parent_ptr, ';');
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
    arg_extra = (char *) _mbschr((unsigned char *) option->arg, ' ');
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

// FUNCTION: CL 0x0040222b
void crack_combo(const tSingle_arg_spec *spec, const char *arg)
{
    char buffer[32];
    const char *argv[2];
    size_t buffer_pos;
    const char *arg_value;

    argv[0] = buffer;
    argv[1] = NULL;
    buffer[0] = arg[0];
    buffer_pos = strlen(spec->key);
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
        const char *valuespec = strchr(spec->valuespec, *arg);
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
            const tSingle_arg_spec *single_arg_spec = is_combo(&arg[1]);
            if (single_arg_spec != NULL && arg[strlen(single_arg_spec->key) + 1] != '\0') {
                crack_combo(single_arg_spec, arg);
                i++;
            } else {
                handlematch(args, &i);
            }
            if (SourceCount != 0 && original_count == SourceCount) {
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

// FUNCTION: CL 0x0040336e
void response_file(const char *path)
{
    FILE *f;
    char *line;

    // GLOBAL: CL 0x0040a06c
    static BOOL first = TRUE;

    // GLOBAL: CL 0x0040a068
    int nesting = 0;

    nesting += 1;
    if (nesting > 13) {
        cmderr(2035, path);
    }
    f = fopen(path, "r");
    if (f == NULL) {
        cmderr(2022, path);
    }
    line = xnew(1024);
    while (fgets(line, sizeof(line) - 1, f) != NULL) {
        size_t len_line = strlen(line);
        char **args;

        if (line[len_line - 1] == '\n') {
            line[len_line - 1] = '\0';
        }
        if (!Nologo) {
            print(STDERR_FILENO, first ? "cl " : "   ");
            print(STDERR_FILENO, "%s\n", line);
            first = FALSE;
            RespEcho = TRUE;
        }
        args = sztoszv(line, TRUE);
        if (args != NULL) {
            size_t args_count = argcount((const char **) args);
            templates((const char **) args, args_count);
            xfree(args[0]);
            xfree(args);
        }
    }
    if (!feof(f)) {
        cmderr(2034, path);
    }
    fclose(f);
    xfree(line);
    nesting -= 1;
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
    pos_hash = (char *) _mbschr((unsigned char *) macro_arg, '#');
    if (pos_hash != NULL) {
        /* FIXME/BUG: this function modifies args ! */
        *pos_hash = '=';
    }
    pos_assign = (char *) _mbschr((unsigned char *) macro_arg, '=');
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

// FUNCTION: CL 0x00403035
int tcargs(const char **args, int *index)
{
    other_sources("Tc", args, index, SOURCE_C);
    return 0;
}

// FUNCTION: CL 0x0040304f
int tpargs(const char **args, int *index)
{
    other_sources("Tp", args, index, SOURCE_CPP);
    return 0;
}

// FUNCTION: CL 0x0040301b
int toargs(const char **args, int *index)
{
    other_sources("To", args, index, SOURCE_OBJ);
    return 0;
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

// FUNCTION: CL 0x00402690
void deactivate_passes(flag_s *option)
{
    char a0 = option->arg[0];
    const sourceinfo_s *filetype_spec;

    for (filetype_spec = Sourceinfo; filetype_spec->phase != PHASE_NOPHASE; filetype_spec++) {
        passinfo_s *filetype_compiler_spec;
        for (filetype_compiler_spec = filetype_spec->passes; filetype_compiler_spec->pass_filename != NULL;
                filetype_compiler_spec++) {
            if (a0 == '.' || _mbschr((unsigned char *) option->arg, filetype_compiler_spec->id) != NULL) {
                filetype_compiler_spec->is_active = 0;
            }
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

        arg1_space = (char *) _mbschr((unsigned char *) option->arg, ' ');
        arg2_space = (char *) _mbschr((unsigned char *) arg1_space + 1, ' ');
        *arg2_space = '\0';
        arg2 = arg2_space + 1;
        end_arg2 = arg2;
        for (;;) {
            char *next_end_arg2 = (char *) _mbsinc((unsigned char *) end_arg2);
            if (next_end_arg2 == NULL || *next_end_arg2 == '\0') {
                break;
            }
            end_arg2 = next_end_arg2;
        }
        if (_mbsstr((unsigned char *) arg2, (unsigned char *) "%b") == NULL &&
                _mbschr((unsigned char *) "\\/", *end_arg2) == NULL) {
            cmderr(2036, &arg1_space[1], arg2);
        }
    }
    option->arg[0] = '\0';
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
    static BOOL macros_0x1_flags_enabled = TRUE;
    flag_s *p;

    (void) option;
    if (!macros_0x1_flags_enabled) {
        return;
    }
    macros_0x1_flags_enabled = FALSE;
    for (p = Context->flags; p != NULL; p = p->next) {
        if ((p->info & 1) && strcmp(p->base, "D") == 0) {
            freeflag(rmflag(&Context->flags, p));
        }
    }
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

// FUNCTION: CL 0x00405df9
int screen_length()
{
    HANDLE conHandle;
    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
    BOOL success;
    int height;

    conHandle =
            CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, 0, NULL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, NULL);
    if (conHandle == INVALID_HANDLE_VALUE) {
        return 25;
    }
    success = GetConsoleScreenBufferInfo(conHandle, &consoleScreenBufferInfo);
    CloseHandle(conHandle);
    if (!success) {
        return 25;
    }
    height = consoleScreenBufferInfo.srWindow.Bottom - consoleScreenBufferInfo.srWindow.Top + 1;
    if (height <= 0) {
        return 1;
    }
    return height;
}

// FUNCTION: CL 0x00405836
void help(const char *path)
{
    char buffer[84];
    int line;
    FILE *f;
    int terminal_height;

    f = fopen(path, "r");
    if (f == NULL) {
        cmderr(2022, path);
    }
    terminal_height = INT_MAX;
    if (_isatty(STDOUT_FILENO)) {
        terminal_height = screen_length();
    }
    if (terminal_height <= 0) {
        terminal_height = 1;
    }
    for (line = 0; fgets(buffer, 81, f) != NULL; line++) {
        if (line != 0 && line % terminal_height == 0) {
            print(STDOUT_FILENO, get_message(313));
            while (1) {
                int ch = getchar();
                if (ch == '\n' || ch == -1) {
                    break;
                }
            }
        }
        print(STDOUT_FILENO, buffer);
    }
    fclose(f);
    exit(0);
}

// FUNCTION: CL 0x00405de2
void RedirectStdErrToStdOut()
{
    if (RedirStderr) {
        _dup2(STDOUT_FILENO, STDERR_FILENO);
    }
}

// FUNCTION: CL 0x0040330d
void acquire_pass(context_s *ctx)
{
    passinfo_s *stage_spec = ctx->compiler_stage_spec;
    source_type filetype = ctx->current_source->type;
    int stage = ctx->current_pass;

    if (ctx->exepaths[filetype][stage] == NULL) {
        char *compiler_path = findpass(ctx->exedir, stage_spec->pass_filename);

        ctx->exepaths[filetype][stage] = compiler_path;
        if (stage_spec->error_filename != NULL) {
            ctx->errorpaths[filetype][stage] =
                    findpass(extract_path(compiler_path), stage_spec->error_filename);
        }
    }
}

// FUNCTION: CL 0x00403705
worklist_s *new_worklist_item(source_s *parsed_file)
{
    worklist_s *result = xnew(sizeof(worklist_s));
    result->next = NULL;
    result->parsed_file = parsed_file;
    result->had_error = 0;
    return result;
}

// FUNCTION: CL 0x004036b5
worklist_s *build_full_worklist(context_s *ctx)
{
    worklist_s *result = NULL;
    worklist_s *last_input = NULL;
    source_s *parsed_filepath;
    for (parsed_filepath = ctx->field_0x10; parsed_filepath != NULL; parsed_filepath = parsed_filepath->next) {
        if (Sourceinfo[parsed_filepath->type].phase == PHASE_COMPILE) {
            worklist_s *compiler_input = new_worklist_item(parsed_filepath);
            if (result != NULL) {
                last_input->next = compiler_input;
            } else {
                result = compiler_input;
            }
            last_input = compiler_input;
        }
    }
    if (last_input == result) {
        BatchPassOK = FALSE;
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

// FUNCTION: CL 0x00403db1
int strcmp_proxy(const void *lhs, const void *rhs)
{
    return strcmp(*(char **) lhs, *(char **) rhs);
}

// FUNCTION: CL 0x00403b70
char *get_minrebuild_options(context_s *ctx)
{
    char *buffer1 = xnew(1024);
    char *buffer2 = xnew(1024);
    char **argv;
    int arg_i;
    flag_s *option;
    char *arg_string;
    char *arg_ptr;
    int count_arguments;
    size_t len;

    count_arguments = 0;
    if (ctx->include != NULL && DefInclude) {
        count_arguments += 1;
    }
    for (option = ctx->flags; option != NULL; option = option->next) {
        if (flag_these_pass_ids(option, "Mm") != '\0') {
            count_arguments += 1;
        }
    }
    len = 0;
    argv = xnew(count_arguments * sizeof(char *));
    arg_i = 0;
    for (option = ctx->flags; option != NULL; option = option->next) {
        char c = flag_these_pass_ids(option, "Mm");
        if (c != '\0') {
            char *arg_ptr;
            char *arg_value_ptr;

            Bigbuf[0] = '-';
            arg_ptr = append(&Bigbuf[1], option->base);
            arg_value_ptr = option->arg;
            if (arg_value_ptr != NULL) {
                if (c == 'm') {
                    if (_fullpath(buffer2, arg_value_ptr, 1024) == NULL) {
                        strcpy(buffer2, option->arg);
                    }
                    _mbslwr((unsigned char *) buffer2);
                    arg_value_ptr = buffer2;
                }
                strqcpy(buffer1, arg_value_ptr);
                append(arg_ptr, buffer1);
            }
            argv[arg_i++] = xstrdup(Bigbuf);
            len += strlen(Bigbuf) + 1;
        }
    }
    if (ctx->include != NULL && DefInclude) {
        size_t lenInclude = strqlen(ctx->include);
        char *incString = xnew(lenInclude + 6);
        strcpy(incString, "-inc=");
        strqcpy(&incString[5], ctx->include);
        _mbslwr((unsigned char *) incString);
        len += lenInclude + 6;
        argv[arg_i] = incString;
    }
    qsort(argv, count_arguments, sizeof(char *), strcmp_proxy);
    arg_string = xnew(len + 1);
    arg_ptr = arg_string;
    for (arg_i = 0; arg_i < count_arguments; arg_i++) {
        arg_ptr = append(arg_ptr, argv[arg_i]);
        *arg_ptr++ = ' ';
    }
#ifdef REMSVC_RECCMP
    arg_ptr[-1] = '\0';
#else
    arg_string[len] = '\0';
#endif
    for (arg_i = 0; arg_i < count_arguments; arg_i++) {
        xfree(argv[arg_i]);
    }
    xfree(argv);
    xfree(buffer2);
    xfree(buffer1);
    return arg_string;
}

// FUNCTION: CL 00403dc6
worklist_s *rethread_worklist_by_srctargs(SRCTARG *arg1)
{
    (void) arg1;
    NOT_IMPLEMENTED();
}
#endif

// FUNCTION: CL 0x0040371e
worklist_s *init_minrebuild(context_s *ctx, worklist_s *inputs, CAList *mr_state)
{
#ifdef WITH_MSPDB
    MREngine *engine;
    MREDriver *driver;
    int result_code;
    worklist_s *input;
    SRCTARG *unk;
    char *arg_string;
#endif

    if (!MinimalRebuild || !MinRebuildOK) {
        MinRebuildOK = FALSE;
        return inputs;
    }
#ifdef WITH_MSPDB
    if (!MREFOpenByName(&engine, IdbFileName, &result_code, Bigbuf, Reproducable, TRUE)) {
        cmdwarn(4028);
        MinRebuildOK = FALSE;
        return inputs;
    }
    unk = NULL;
    MREQueryMreDrv(engine, &driver);
    MREDrvOneTimeInit(driver);
    mr_state->pstDoCompile = NULL;
    mr_state->pstMaybeCompile = NULL;
    mr_state->pstDontCompile = NULL;
    mr_state->pstDone = NULL;
    mr_state->pstError = NULL;
    ctx->skiplist = NULL;
    ctx->skiplistend = &ctx->skiplist;
    arg_string = get_minrebuild_options(ctx);
    for (input = inputs; input != NULL; input = input->next) {
        source_s *parsed_file = input->parsed_file;
        SRCTARG* srctarg;

        ctx->current_source = parsed_file;
        cc_switches(ctx);
        srctarg = &input->srctarg;
        srctarg->psrctargNext = NULL;
        if (unk != NULL) {
            unk->psrctargNext = srctarg;
        } else {
            mr_state->pstMaybeCompile = srctarg;
        }
        srctarg->fCpp = parsed_file->type == SOURCE_CXX || parsed_file->type == SOURCE_CPP;
        srctarg->szSrc = parsed_file->path;
        srctarg->szTarg = Object;
        srctarg->szOptions = arg_string;
        input->sbrfile = SbrFileName;
        unk = srctarg;
    }
    if (MinRebuildOK && MREDrvFFilesOutOfDate(driver, mr_state)) {
        inputs = rethread_worklist_by_srctargs(mr_state->pstDoCompile);
    } else if (MinRebuildOK) {
        cmdwarn(4028);
        MinRebuildOK = FALSE;
    }
    if (!MREDrvFRelease(driver) && MinRebuildOK) {
        cmdwarn(4028);
        MinRebuildOK = FALSE;
    }
    if (!MREFClose(engine, MinRebuildOK) && MinRebuildOK) {
        cmdwarn(4028);
        MinRebuildOK = FALSE;
    }
    return inputs;
#else
    (void) ctx;
    (void) mr_state;
    cmdwarn(4028);
    MinRebuildOK = FALSE;
    return inputs;
#endif
}

// FUNCTION: CL 0x004038f0
worklist_s *iterate_minrebuild(context_s *ctx, CAList *mr_state)
{
#ifdef WITH_MSPDB
    int result_code;
    MREngine *engine;
    MREDriver *driver;
#endif

    if (!MinimalRebuild || !MinRebuildOK) {
        return NULL;
    }
#ifdef WITH_MSPDB
    if (mr_state->pstDoCompile == NULL && mr_state->pstMaybeCompile == NULL && mr_state->pstDontCompile == NULL) {
        return NULL;
    }
    if (!MREFOpenByName(&engine, IdbFileName, &result_code, Bigbuf, Reproducable, TRUE)) {
        cmdwarn(4028);
        MinRebuildOK = FALSE;
        return rethread_worklist_by_srctargs(mr_state->pstMaybeCompile);
    }
    MREQueryMreDrv(engine, &driver);
    if (mr_state->pstDoCompile != NULL) {
        NOT_IMPLEMENTED();
    }
    (void) ctx;
    NOT_IMPLEMENTED();
#else
    (void) ctx;
    (void) mr_state;
    cmdwarn(4028);
    MinRebuildOK = FALSE;
    return NULL;
#endif
}

// FUNCTION: CL 0x00404069
worklist_s *reverse_worklist(worklist_s *input_file)
{
    worklist_s *new_head;
    worklist_s *new_next;

    new_next = new_head = NULL;
    while (input_file != NULL) {
        new_head = input_file;
        input_file = new_head->next;
        new_head->next = new_next;
        new_next = new_head;
    }
    return new_head;
}

// FUNCTION: CL 0x00404e5c
char *filename(char *dest, const char *path)
{
    char ext[256];
    char filename[256];

    _splitpath(path, NULL, NULL, filename, ext);
    _makepath(dest, "", "", filename, ext);
    return dest;
}

// FUNCTION: CL 0x00405039
size_t strqlen(const char *path)
{
    int count_backslash = 0;
    size_t len = 0;
    bool space = false;
    while (*path != '\0') {
        if (_ismbcspace(*path)) {
            space = true;
        }
        if (_mbsncmp((unsigned char *) path, (unsigned char *) "\"", 1) == 0) {
            len += count_backslash + 1;
        }
        if (_mbsncmp((unsigned char *) path, (unsigned char *) "\\", 1) == 0) {
            count_backslash += 1;
        } else {
            count_backslash = 0;
        }
        len += _mbclen((unsigned char *) path);
        path = (char *) _mbsinc((unsigned char *) path);
    }
    if (space) {
        len += count_backslash + 2;
    }
    return len;
}

// FUNCTION: CL 0x00404d26
size_t replaca_strlen(const char *text, context_s *ctx)
{
    char buffer[256];
    size_t len = 0;
    const char *current_file;
    source_type current_filetype;
    if (ctx->current_source == NULL) {
        current_file = "";
        current_filetype = SOURCE_UNKNOWN;
    } else {
        current_file = ctx->current_source->path;
        current_filetype = ctx->current_source->type;
    }
    while (*text != '\0') {
        switch (*text) {
        case '"':
        case '\\':
            len += 2;
            text++;
            break;
        case '%':
            switch (text[1]) {
            case '%':
                len += 1;
                break;
            case 'X':
                len += 3;
                break;
            case 'e':
                if (ctx->errorpaths[current_filetype][ctx->current_pass] != NULL) {
                    len += strqlen(ctx->errorpaths[current_filetype][ctx->current_pass]);
                }
                break;
            case 'f':
                len += strqlen(current_file);
                break;
            case 'b':
            case 'B':
                basename(buffer, current_file);
                len += strqlen(buffer);
                break;
            case 'm':
                len += 1024;
                break;
            case 't':
                len += strqlen(ctx->tempPath);
                break;
            case 'x':
                pathname(buffer, Exefilename);
                len += strqlen(buffer);
                break;
            }
            text += 2;
            break;
        default:
            len += 1;
            text++;
            break;
        }
    }
    return len;
}

// FUNCTION: CL 0x004050c0
char *strqcpy(char *dest, const char *path)
{
    int count_backslash = 0;
    bool space = false;
    char *write_ptr = dest;
    while (*path != '\0') {
        if (_ismbcspace(*path)) {
            space = true;
        }
        if (_mbsncmp((unsigned char *) path, (unsigned char *) "\"", 1) == 0) {
            while (count_backslash-- >= 0) {
                _mbccpy((unsigned char *) write_ptr, (unsigned char *) "\\");
                write_ptr = (char *) _mbsinc((unsigned char *) write_ptr);
            }
        }
        if (_mbsncmp((unsigned char *) path, (unsigned char *) "\\", 1) == 0) {
            count_backslash += 1;
        } else {
            count_backslash = 0;
        }
        _mbccpy((unsigned char *) write_ptr, (unsigned char *) path);
        write_ptr = (char *) _mbsinc((unsigned char *) write_ptr);
        path = (char *) _mbsinc((unsigned char *) path);
    }
    if (space) {
        memmove(&dest[1], dest, write_ptr - dest);
        _mbccpy((unsigned char *) dest, (unsigned char *) "\"");
        write_ptr = (char *) _mbsinc((unsigned char *) write_ptr);
        while (count_backslash > 0) {
            _mbccpy((unsigned char *) write_ptr, (unsigned char *) "\\");
            write_ptr = (char *) _mbsinc((unsigned char *) write_ptr);
            count_backslash -= 1;
        }
        _mbccpy((unsigned char *) write_ptr, (unsigned char *) "\"");
        write_ptr = (char *) _mbsinc((unsigned char *) write_ptr);
    }
    *write_ptr = '\0';
    return dest;
}

// FUNCTION: CL 0x00405b3e
void starttiming()
{
    ftime(&Starttime);
}

// FUNCTION: CL 0x00405b4d
void endtiming(const char *description)
{
    char buffer[8];
    int time_s;
    int time_ms;
    size_t len;

    print(STDOUT_FILENO, "time(%s)=", description);
    ftime(&Endtime);
    time_s = Endtime.time - Starttime.time;
    time_ms = Endtime.millitm - Starttime.millitm;
    if (time_ms < 0) {
        time_ms += 1000;
        time_s -= 1;
    }
    strcpy(buffer, "00");
    len = l2a(time_ms, &buffer[2], 10);
    print(STDOUT_FILENO, "%d.%ss\n", time_s, buffer + len - 1);
}

// FUNCTION: CL 0x004040c9
int dopass(context_s *ctx)
{
    char *buffer1;
    char *buffer2;
    const char *exe_filepath;
    size_t len;
    int argc;
    flag_s *option;
    char **argv;
    char *arg_string;
    char **argv_ptr;
    char *arg_ptr;
    passinfo_s *compiler_stage_spec;
    source_s *current_filepath;
    int result;

    Action = TRUE;
    buffer1 = xnew(1024);
    buffer2 = xnew(1024);
    compiler_stage_spec = ctx->compiler_stage_spec;
    current_filepath = ctx->current_source;
    exe_filepath = ctx->exepaths[current_filepath->type][ctx->current_pass];
    len = strqlen(exe_filepath);
    argc = 0;
    for (option = ctx->flags; option != NULL; option = option->next) {
        if (flag_this_pass(option, compiler_stage_spec)) {
            len += replaca_strlen(option->base, ctx) + 2;
            argc += 1;
            if (option->arg != NULL) {
                len += replaca_strlen(option->arg, ctx) + 2;
                argc += 1;
            }
        }
    }
    if (ctx->include != NULL && DefInclude) {
        const char *ptr_include;
        len += strqlen(ctx->include) + 6;
        ptr_include = ctx->include;
        for (;;) {
            argc += 2;
            ptr_include = (char *) _mbschr((unsigned char *) ptr_include, ';');
            if (ptr_include == NULL) {
                break;
            }
            len += 6;
            ptr_include += 1;
        }
    }
    argv = xnew((argc + 2) * sizeof(char *));
    arg_string = xnew(len);
    argv_ptr = argv;
    *argv_ptr++ = arg_string;
    strqcpy(buffer1, exe_filepath);
    arg_ptr = append(arg_string, buffer1);
    for (option = ctx->flags; option != NULL; option = option->next) {
        if (flag_this_pass(option, compiler_stage_spec)) {
            arg_ptr++;
            *argv_ptr++ = arg_ptr;
            if (!(option->info & 0x8)) {
                *arg_ptr++ = compiler_stage_spec->swchar;
            }
            arg_ptr = append(arg_ptr, replaca(buffer1, option->base, ctx));
            if (option->arg != NULL) {
                if (!(option->info & 0x4)) {
                    arg_ptr++;
                    *argv_ptr++ = arg_ptr;
                }
                strqcpy(buffer1, replaca(buffer2, option->arg, ctx));
                arg_ptr = append(arg_ptr, buffer1);
            }
        }
    }
    if (ctx->include != NULL && DefInclude && strchr("1P", compiler_stage_spec->id) != NULL) {
        const char *ptr_include = ctx->include;
        size_t pos_non_whitespace;

        for (;;) {
            char *ptr_end;

            ptr_end = (char *) _mbschr((unsigned char *) ptr_include, ';');
            if (ptr_end == NULL) {
                break;
            }
            if (ptr_include != ptr_end) {
                int pos_non_whitespace = (int) _mbsspn((unsigned char *) ptr_include, (unsigned char *) " \t");
                if (pos_non_whitespace < ptr_end - ptr_include) {
                    *argv_ptr++ = &arg_ptr[1];
                    arg_ptr = append(&arg_ptr[1], "-I");
                    *argv_ptr++ = &arg_ptr[1];
                    *ptr_end = '\0';
                    strqcpy(buffer1, ptr_include);
                    *ptr_end = ';';
                    arg_ptr = append(&arg_ptr[1], buffer1);
                }
            }
            ptr_include = &ptr_end[1];
        }
        pos_non_whitespace = _mbsspn((unsigned char *) ptr_include, (unsigned char *) " \t");
        if (pos_non_whitespace < strlen(ptr_include)) {
            *argv_ptr++ = &arg_ptr[1];
            arg_ptr = append(&arg_ptr[1], "-I");
            *argv_ptr++ = &arg_ptr[1];
            strqcpy(buffer1, ptr_include);
            append(&arg_ptr[1], buffer1);
        }
    }
    *argv_ptr = NULL;
    if (Verbose) {
        char **ptr;

        print(STDERR_FILENO, "`%s", exe_filepath);
        for (ptr = &argv[1]; *ptr != NULL; ptr++) {
            print(STDERR_FILENO, " %s", *ptr);
        }
        print(STDERR_FILENO, "'\n");
    }
    result = 0;
    if (!Nospawn) {
        int inheritEnv;

        if (Time) {
            starttiming();
        }
        if (current_filepath->type == SOURCE_EXE) {
            inheritEnv = 2;
        } else {
            inheritEnv = 0;
        }
        result = execute(inheritEnv, exe_filepath, compiler_stage_spec->environment_variable, argv);
        if (Time) {
            endtiming(exe_filepath);
        }
    }
    xfree(argv);
    xfree(arg_string);
    xfree(buffer2);
    xfree(buffer1);
    return result;
}

// FUNCTION: CL 0x00404080
int passes(passinfo_s *passes, context_s *ctx, int (*exec)(context_s *))
{
    int i;

    for (i = 0; passes[i].pass_filename != NULL; i++) {
        passinfo_s *pass = &passes[i];
        if (pass->is_active) {
            ctx->current_pass = i;
            ctx->compiler_stage_spec = pass;
            acquire_pass(ctx);
            Nerrors = exec(ctx);
            if (Nerrors) {
                return Nerrors;
            }
        }
    }
    return Nerrors;
}

// FUNCTION: CL 0x00403e26
unsigned int compile_worklist(context_s *ctx, worklist_s *input_file)
{
    char buffer[1024];
    int count_failed = 0;
    passinfo_s *input_compiler_spec = Sourceinfo[input_file->parsed_file->type].passes;
    int count_stages = 0;
    int stage;
    int message_stage;
    bool do_stage_per_stage;

    // GLOBAL: CL 0x0040a1bc
    BOOL first = TRUE;

    for (stage = 0; input_compiler_spec[stage].pass_filename != NULL; stage++) {
        if (input_compiler_spec[stage].is_active) {
            count_stages += 1;
        }
    }
    if (BatchPasses && BatchPassOK && count_stages >= 2) {
        do_stage_per_stage = true;
        ctx->batchlist = input_file;
    } else {
        do_stage_per_stage = false;
        ctx->batchlist = NULL;
    }
    message_stage = 0;
    for (stage = 0;; stage++) {
        passinfo_s *stage_compiler_spec = &input_compiler_spec[stage];
        bool run_on_file = false;
        if (do_stage_per_stage) {
            if (stage_compiler_spec->is_active) {
                if (message_stage > 0) {
                    input_file = reverse_worklist(input_file);
                    ctx->batchlist = input_file;
                }
                message_stage += 1;
                ctx->current_pass = stage;
                ctx->compiler_stage_spec = stage_compiler_spec;
                ctx->current_source = input_file->parsed_file;
                if (message_stage == 1) {
                    if (first) {
                        first = FALSE;
                    } else {
                        print(STDERR_FILENO, get_message(331));
                    }
                } else if (message_stage == 2 && count_stages > 2) {
                    print(STDERR_FILENO, get_message(332));
                } else {
                    if (message_stage == count_stages) {
                        print(STDERR_FILENO, get_message(333));
                    }
                }
                run_on_file = true;
            }
        }
        if (!do_stage_per_stage || run_on_file) {
            worklist_s *current_input_file;
            for (current_input_file = input_file; current_input_file != NULL;
                    current_input_file = current_input_file->next) {
                if (!do_stage_per_stage || !current_input_file->had_error) {
                    source_s *current_parsed_filepath = current_input_file->parsed_file;
                    ctx->current_source = current_parsed_filepath;
                    cc_switches(ctx);
                    if (!do_stage_per_stage || message_stage < 2) {
                        print(STDERR_FILENO, "%s\n", filename(buffer, current_parsed_filepath->path));
                    }
                    if (do_stage_per_stage) {
                        acquire_pass(ctx);
                        Nerrors = dopass(ctx);
                    } else {
                        Nerrors = passes(input_compiler_spec, ctx, dopass);
                    }
                    if (Nerrors) {
                        count_failed += 1;
                        current_input_file->had_error = 1;
                        if (do_stage_per_stage) {
                            do_rm_il(TRUE);
                            if (do_stage_per_stage && message_stage != count_stages) {
                                continue;
                            }
                        }
                    } else if (do_stage_per_stage && message_stage != count_stages) {
                        continue;
                    }
                    if (Object != NULL) {
                        source_s *obj_parsed_path =
                                newsource(Object, SOURCE_OBJ);
                        obj_parsed_path->next = current_parsed_filepath->next;
                        current_input_file->parsed_file->next = obj_parsed_path;
                    }
                    do_rm_il(TRUE);
                }
            }
            if (!do_stage_per_stage) {
                ctx->batchlist = NULL;
                return count_failed;
            }
        }
        if (!do_stage_per_stage || stage_compiler_spec->pass_filename == NULL) {
            ctx->batchlist = NULL;
            return count_failed;
        }
    }
}

// FUNCTION: CL 0x004057dd
void WriteF(FILE *stream, const char *format, ...)
{
    size_t len;
    va_list ap;
    const char *text;

    va_start(ap, format);
    text = ErrorVSprintf(&len, format, ap);
    va_end(ap);
    if (stream != NULL) {
        _write(_fileno(stream), text, len);
    }
    if (Verbose) {
        _write(STDERR_FILENO, text, len);
    }
}

// FUNCTION: CL 0x00404897
void CoffResponseFile(context_s *ctx)
{
    char *buffer1;
    char *buffer2;
    FILE *f;
    const passinfo_s *compiler_stage_spec;
    flag_s *option;
    source_s *filepath;

    buffer1 = xnew(1024);
    buffer2 = xnew(1024);
    compiler_stage_spec = ctx->compiler_stage_spec;
    strcpy(buffer1, ctx->tempPath);
    strcat(buffer1, "lk");
    if (!Nospawn) {
        f = fopen(buffer1, "w");
        if (f == NULL) {
            cmderr(2018);
        }
    } else {
        f = NULL;
    }
    for (option = ctx->flags; option != NULL; option = option->next) {
        if (flag_this_pass(option, compiler_stage_spec)) {
            if (!(option->info & 0x8)) {
                WriteF(f, "%c", compiler_stage_spec->swchar);
            }
            WriteF(f, "%s", replaca(buffer1, option->base, ctx));
            if (option->arg != NULL) {
                if (!(option->info & 0x4)) {
                    WriteF(f, " ");
                }
                strqcpy(buffer1, replaca(buffer2, option->arg, ctx));
                WriteF(f, "%s", buffer1);
            }
            WriteF(f, "\n");
        }
    }
    for (filepath = ctx->field_0x10; filepath != NULL; filepath = filepath->next) {
        if (filepath->type == SOURCE_DEF) {
            strqcpy(buffer1, filepath->path);
            WriteF(f, "%cdef:%s\n", compiler_stage_spec->swchar, buffer1);
        }
    }
    for (filepath = ctx->field_0x10; filepath != NULL; filepath = filepath->next) {
        if (Sourceinfo[filepath->type].phase == PHASE_LINK && filepath->type != SOURCE_DEF) {
            strqcpy(buffer1, filepath->path);
            WriteF(f, "%s\n", buffer1);
        }
    }
    if (f != NULL) {
        fclose(f);
    }
    xfree(buffer2);
    xfree(buffer1);
}

// FUNCTION: CL 0x004045d8
void OmfResponseFile(context_s *ctx)
{
    char *buffer1;
    char *buffer2;
    FILE *f;
    const passinfo_s *compiler_stage_spec;
    source_s *filepath;
    flag_s *option;
    bool first;
    char *exePath;

    buffer1 = xnew(1024);
    buffer2 = xnew(1024);
    compiler_stage_spec = ctx->compiler_stage_spec;
    strcpy(buffer1, ctx->tempPath);
    strcat(buffer1, "lk");
    if (!Nospawn) {
        f = fopen(buffer1, "w");
        if (f == NULL) {
            cmderr(2018);
        }
    } else {
        f = NULL;
    }
    first = true;
    for (filepath = ctx->field_0x10; filepath != NULL; filepath = filepath->next) {
        if (filepath->type == SOURCE_OBJ || filepath->type == SOURCE_UNKNOWN) {
            if (!first) {
                WriteF(f, "+\n");
            }
            WriteF(f, "\"%s\"", filepath->path);
            first = false;
        }
    }
    replaca(buffer1, Exefilename, ctx);
    exePath = xstrdup(buffer1);
    WriteF(f, "\n\"%s\"", exePath);
    WriteF(f, "\n\"%s\"", mapfile(buffer1, exePath));
    first = true;
    for (filepath = ctx->field_0x10; filepath != NULL; filepath = filepath->next) {
        if (filepath->type == SOURCE_LIB) {
            if (!first) {
                WriteF(f, "+");
            }
            WriteF(f, "\n\"%s\"", filepath->path);
            first = false;
        }
    }
    if (first) {
        WriteF(f, "\n");
    }
    first = true;
    for (option = ctx->flags; option != NULL; option = option->next) {
        if (flag_this_pass(option, compiler_stage_spec)) {
            if (!first) {
                WriteF(f, " ");
            } else {
                first = false;
            }
            if (!(option->info & 0x8)) {
                WriteF(f, "%c", compiler_stage_spec->swchar);
            }
            WriteF(f, "%s", replaca(buffer1, option->base, ctx));
            if (option->arg != NULL) {
                if (!(option->info & 0x4)) {
                    WriteF(f, " ");
                }
                strqcpy(buffer1, replaca(buffer2, option->arg, ctx));
                WriteF(f, "%s", buffer1);
            }
        }
    }
    if (first) {
        WriteF(f, "\n");
    }
    first = true;
    for (filepath = ctx->field_0x10; filepath != NULL; filepath = filepath->next) {
        if (filepath->type == SOURCE_DEF) {
            if (!first) {
                WriteF(f, "+\n");
            }
            WriteF(f, "\n\"%s\"", filepath->path);
            first = false;
        }
    }
    WriteF(f, ";\n");
    if (f != NULL) {
        fclose(f);
    }
    xfree(exePath);
    xfree(buffer2);
    xfree(buffer1);
}

// FUNCTION: CL 0x00405c21
int execute(int inheritEnv, const char *cmdName, const char *cmd_env_name, char **argv)
{
    int result;

    switch (inheritEnv) {
    case 0:
        if (cmd_env_name != NULL) {
            size_t len_env;
            char **argv_ptr;
            char *env_string;
            char *env_ptr;

            len_env = strlen(cmd_env_name) + 2;
            ;
            for (argv_ptr = &argv[1]; *argv_ptr != NULL; argv_ptr++) {
                len_env += 1 + strlen(*argv_ptr);
            }
            env_string = xnew(len_env);
            env_ptr = append(env_string, cmd_env_name);
            for (argv_ptr = &argv[1]; *argv_ptr != NULL; argv_ptr++) {
                env_ptr = append(env_ptr, *argv_ptr);
                *env_ptr++ = ' ';
            }
            *env_ptr = '\0';
            if (_putenv(env_string) != 0) {
                cmderr(2029, cmdName);
            }
            xfree(env_string);
        }
        break;
    case 1:
    case 2:
        break;
    default:
        cmderr(0);
        break;
    }
    _flushall();
    *_errno() = 0;
    Spawning = TRUE;
    GotCtrlC = FALSE;
    result = (int) _spawnvp(_P_WAIT, cmdName, (const char *const *) argv);
    Spawning = FALSE;
    if (GotCtrlC || (result >> 8) == -128) {
        done(4);
    }
    if (result < 0 && *_errno() != 0) {
        cmderr(2027, cmdName);
    }
    if (result != 0) {
        if (result == 525) {
            cmderr(2030, cmdName);
        }
        result = 2;
    }
    return result;
}

// FUNCTION: CL 0x00404471
int link(context_s *ctx)
{
    char buffer[2048];
    char *argument_string;
    const char *program_exe;
    char *arguments_ptr;
    passinfo_s *compiler_stage_spec;
    char **argv;
    int result;

    Action = TRUE;
    argument_string = xnew(1024);
    compiler_stage_spec = ctx->compiler_stage_spec;
    program_exe = ctx->exepaths[ctx->current_source->type][ctx->current_pass];
    strqcpy(argument_string, program_exe);
    arguments_ptr = append(buffer, argument_string);
    if (Coff) {
        CoffResponseFile(ctx);
        arguments_ptr = append(arguments_ptr, " -link");
    } else {
        OmfResponseFile(ctx);
    }
    arguments_ptr[0] = ' ';
    arguments_ptr[1] = '\0';
    arguments_ptr = append(&arguments_ptr[1], "@");
    arguments_ptr = append(arguments_ptr, ctx->tempPath);
    append(arguments_ptr, "lk");
    if (strlen(buffer) > sizeof(buffer) - 1) {
        cmderr(0);
    }
    argv = sztoszv(buffer, 0);
    if (Verbose) {
        print(STDERR_FILENO, "`%s'\n", buffer);
    }
    result = 0;
    if (!Nospawn) {
        if (Time) {
            starttiming();
        }
        result = execute(1, program_exe, compiler_stage_spec->environment_variable, argv);
        if (Time) {
            endtiming(program_exe);
        }
    }
    xfree(argv);
    xfree(argument_string);
    return result;
}

// FUNCTION: CL 0x004034c2
void compile(context_s *ctx)
{
    unsigned int mre_result = 0;
    CAList mr_state;
    worklist_s *remaining_inputs;
    source_s *next_linker_output;

    remaining_inputs = build_full_worklist(ctx);
    remaining_inputs = init_minrebuild(ctx, remaining_inputs, &mr_state);
    for (;;) {
        if (remaining_inputs != NULL) {
            for (;;) {
                while (remaining_inputs != NULL) {
                    passinfo_s *filetype_compiler_spec;
                    worklist_s *next_input;
                    worklist_s *current_input;

                    filetype_compiler_spec = Sourceinfo[remaining_inputs->parsed_file->type].passes;
                    remaining_inputs->parsed_file->batch_id = 0;
                    next_input = remaining_inputs->next;
                    current_input = remaining_inputs;
                    while (next_input != NULL &&
                            Sourceinfo[next_input->parsed_file->type].passes ==
                                    filetype_compiler_spec &&
                            current_input->parsed_file->batch_id < 259) {
                        next_input->parsed_file->batch_id = current_input->parsed_file->batch_id + 1;
                        current_input = next_input;
                        next_input = next_input->next;
                    }
                    current_input->next = NULL;
                    mre_result |= compile_worklist(ctx, remaining_inputs);
                    remaining_inputs = next_input;
                }
                remaining_inputs = iterate_minrebuild(ctx, &mr_state);
                if (remaining_inputs == NULL) {
                    break;
                }
            }
        }
        remaining_inputs = iterate_minrebuild(ctx, &mr_state);
        if (remaining_inputs == NULL) {
            break;
        }
    }
    if (ctx->skiplist != NULL) {
        print(STDERR_FILENO, get_message(330));
        NOT_IMPLEMENTED();
#if 0
        item_0x18 = ctx->field_0x18;
        while (item_0x18 != NULL) {
            char buffer[1024];
            next_0x18 = NULL;
            if (item_0x18 != NULL) {
                next_0x18 = item_0x18->next;;
            }
            print(STDERR_FILENO, "%s\n", filename(buffer, GET_HEAD(item_0x18)->path));
            item_0x18->next = mr_state.field_0x0c;
            mr_state.field_0x0c = item_0x18;
            item_0x18 = next_0x18;
        }
#endif
    }
    if (mre_result != 0) {
        Nerrors = mre_result;
        return;
    }

    ctx->current_source = ctx->field_0x10;
    if (ctx->field_0x10 != NULL) {
        source_s *parsed_filepath = ctx->field_0x10;
        while (parsed_filepath != NULL) {
            if (parsed_filepath->type == SOURCE_OBJ) {
                break;
            }
            parsed_filepath = parsed_filepath->next;
        }
        if (parsed_filepath != NULL) {
            ctx->current_source = parsed_filepath;
        }
    }
    cc_switches(ctx);
    Nerrors = passes(Link_passes, ctx, link);
    if (Nerrors) {
        return;
    }
    if (Exefilename != NULL) {
        source_s *exe_path = newsource(Exefilename, SOURCE_EXE);
        exe_path->next = ctx->field_0x10->next;
        ctx->field_0x10->next = exe_path;
    }
    next_linker_output = ctx->field_0x10;
    for (;;) {
        source_s *linker_output;
        for (;;) {
            linker_output = next_linker_output;
            if (linker_output == NULL) {
                return;
            }
            next_linker_output = linker_output->next;
            if (Sourceinfo[linker_output->type].phase == PHASE_POSTPROCESS) {
                break;
            }
        }
        ctx->current_source = linker_output;
        Nerrors = passes(Sourceinfo[linker_output->type].passes, ctx, dopass);
        if (Nerrors) {
            return;
        }
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
            default_filetype = SOURCE_CPP;
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
    done(Nerrors ? 2 : 0);
}
