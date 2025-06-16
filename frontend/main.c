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

#ifdef WITH_MSPDB
# include <mspdb41.h>
#else
typedef struct MRState {
    int und;
} MRState;
#endif

extern const char *ExtractImpliedSpec(const char *spec, char *buffer, const char *key);
extern char *FormatParsedOptionValue(char *buffer, const char *value, tApp_data *app_data);
extern int FUN_00405c21(int inheritEnv, const char *cmdName, const char *cmd_env_name, char **argv);
extern char *EscapePath(char *dest, const char *path);
extern void FatalError(int code, ...);
extern const char *SkipSpaces(const char *text);
extern void ParseResponseFile(const char *path);
extern size_t LengthOfEscapedPath(const char *path);

tApp_data app_data = {0};

// GLOBAL: CL 0x0040afc4
BOOL gConsoleInterrupted;

// GLOBAL: CL 0x0040afc8
BOOL gDisableControlHandler;

// GLOBAL: CL 0x0040a01c
BOOL gShouldPrintLogoString = TRUE;

// GLOBAL: CL 0x0040a030
tApp_data *gApp_data = &app_data;

// GLOBAL: CL 0x0040a068
int gResponseFileDepth = 0;

// GLOBAL: CL 0x0040a06c
BOOL gShould_print_cl = TRUE;

// GLOBAL: CL 0x0040a770
int gCount_compiler_file_inputs = 0;

// GLOBAL: CL 0x0040a774
tParsed_option *gUnknown_options = NULL;

// GLOBAL: CL 0x0040a77c
BOOL gPrinted_cl = FALSE;

// GLOBAL: CL 0x0040a018
BOOL gConsider_hat_options = TRUE;

// GLOBAL: CL 0x0040a054
tParsed_option *gUnused_parsed_options = NULL;

// GLOBAL: CL 0x0040a200
char gImplied_argval[1024];

// GLOBAL: CL 0x0040afa8
struct timeb gChronoAfter;

// GLOBAL: CL 0x0040afb8
struct timeb gChronoBefore;

// GLOBAL: CL 0x0040a080
const char *gBuiltInCompileOptions[] = {
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
const char *gBuiltInCompileDefinitions[] = {
    "-D_MSC_VER=1020",
    "-D_WIN32",
    NULL,
};

// GLOBAL: CL 0x00408510
const tSingle_arg_spec gSingle_arg_specs[] = {
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
tFiletype_compiler_spec gFiletype_c_compiler_specs[] = {
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
tFiletype_compiler_spec gFiletype_cpp_compiler_specs[] = {
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
tFiletype_compiler_spec gFiletype_link_compiler_specs[] = {
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
tFiletype_compiler_spec gFiletype_exe_compiler_specs[] = {
    {
        NULL,
        NULL,
        NULL,
        0,
        '\0',
        '\0',
    },
};

// GLOBAL: CL 0x0040a1bc
BOOL gBOOL_0040a1bc = TRUE;

// GLOBAL: CL 0x0040a038
tFiletype_compiler_spec gFiletype_compiler_spec_0040a038 = {
    NULL,
    "cl.err",
    NULL,
    1,
    'D',
    '-',
};

const tFiletype_spec gFiletype_specs[] = {
    {
        "c",
        eInput_compiler,
        gFiletype_c_compiler_specs,
    },
    {
        "cxx",
        eInput_compiler,
        gFiletype_cpp_compiler_specs,
    },
    {
        "cpp",
        eInput_compiler,
        gFiletype_cpp_compiler_specs,
    },
    {
        "obj",
        eInput_linker,
        gFiletype_link_compiler_specs,
    },
    {
        "lib",
        eInput_linker,
        gFiletype_link_compiler_specs,
    },
    {
        "def",
        eInput_linker,
        gFiletype_link_compiler_specs,
    },
    {
        "res",
        eInput_linker,
        gFiletype_link_compiler_specs,
    },
    {
        "exp",
        eInput_linker,
        gFiletype_link_compiler_specs,
    },
    {
        "",
        eInput_linker,
        gFiletype_link_compiler_specs,
    },
    {
        "exe",
        eOutput_linker,
        gFiletype_exe_compiler_specs,
    },
    {
        NULL,
        eStage_invalid,
        NULL,
    },
};

// GLOBAL: CL 0x0040a010
BOOL gOption_coff = TRUE;

// GLOBAL: CL 0x0040a014
BOOL gOption_notX = TRUE;

// GLOBAL: CL 0x0040a020
BOOL gOption_Gm = TRUE;

// GLOBAL: CL 0x0040a024
BOOL gMRE_enabled = TRUE;

// GLOBAL: CL 0x0040a028
BOOL gOption_ZM = FALSE;

// GLOBAL: CL 0x0040a02c
BOOL gBOOL_0040a02c = TRUE;

// GLOBAL: CL 0x0040a618
BOOL gUnknownFilesAreC = FALSE;

// GLOBAL: CL 0x0040a778
char *gOption_Fm = NULL;

// GLOBAL: CL 0x0040a794
BOOL gBuildingDLL = FALSE;

// GLOBAL: CL 0x0040a798
BOOL gPrintPaginatedClMessage = FALSE;

// GLOBAL: CL 0x0040a744
BOOL gOption_Brepro = FALSE;

// GLOBAL: CL 0x0040a74c
BOOL gOption_bm = FALSE;

// GLOBAL: CL 0x0040a04c
BOOL gRedirectStdErrToStdOut = TRUE;

// GLOBAL: CL 0x0040a050
BOOL gOption_Bt = FALSE;

// GLOBAL: CL 0x0040a600
char *gOption_bt = NULL;

// GLOBAL: CL 0x0040a604
char *gOption_Fd = NULL;

// GLOBAL: CL 0x0040a60c
BOOL gOption_Bz = FALSE;

// GLOBAL: CL 0x0040a610
BOOL gOption_bv = FALSE;

// GLOBAL: CL 0x0040a614
BOOL gAction_performed = FALSE;

// GLOBAL: CL 0x0040a7a0
BOOL gOption_bk = FALSE;

// GLOBAL: CL 0x0040a608
char *gOutputObjectFilepath = NULL;

// GLOBAL: CL 0x0040a784
char *gOutputExecutableFilepath = NULL;

// GLOBAL: CL 0x0040a78c
BOOL gExit_failure = FALSE;

// GLOBAL: CL 0x0040a788
char *gOption_FR = NULL;

// GLOBAL: CL 0x00407090
tOption_action gOption_actions[] = {
    {
        "Fo",
        eAction_setString,
        {&gOutputObjectFilepath},
    },
    {
        "Fe",
        eAction_setString,
        {&gOutputExecutableFilepath},
    },
    {
        "bA",
        eAction_callback,
        {OnbAOption},
    },
    {
        "ba",
        eAction_callback,
        {OnbaOption},
    },
    {
        "bc",
        eAction_callback,
        {OnbcOption},
    },
    {
        "bd",
        eAction_callback,
        {OnbdOption},
    },
    {
        "bE",
        eAction_setTrue,
        {&gUnknownFilesAreC},
    },
    {
        "bh",
        eAction_setTrue,
        {&gPrintPaginatedClMessage},
    },
    {
        "bil",
        eAction_setString,
        {&app_data.tempPath},
    },
    {
        "bm",
        eAction_setTrue,
        {&gOption_bm},
    },
    {
        "bo",
        eAction_callback,
        {OnboOption},
    },
    {
        "bp",
        eAction_callback,
        {OnbpOption},
    },
    {
        "br",
        eAction_setFalse,
        {&gRedirectStdErrToStdOut},
    },
    {
        "bt",
        eAction_setString,
        {&gOption_bt},
    },
    {
        "bU",
        eAction_callback,
        {OnbUOption},
    },
    {
        "bu",
        eAction_callback,
        {OnbuOption},
    },
    {
        "bv",
        eAction_setTrue,
        {&gOption_bv},
    },
    {
        "Bk",
        eAction_setTrue,
        {&gOption_bk},
    },
    {
        "Brepro",
        eAction_setTrue,
        {&gOption_Brepro},
    },
    {
        "Bt",
        eAction_setTrue,
        {&gOption_Bt},
    },
    {
        "Bz",
        eAction_setTrue,
        {&gOption_Bz},
    },
    {
        "coff",
        eAction_setTrue,
        {&gOption_coff},
    },
    {
        "Fm",
        eAction_setString,
        {&gOption_Fm},
    },
    {
        "LD",
        eAction_callback,
        {OnArgumentLDorLDd},
    },
    {
        "LDd",
        eAction_callback,
        {OnArgumentLDorLDd},
    },
    {
        "omf",
        eAction_setFalse,
        {&gOption_coff},
    },
    {
        "X",
        eAction_setFalse,
        {&gOption_notX},
    },
    {
        "Fd",
        eAction_setString,
        {&gOption_Fd},
    },
    {
        "Gm",
        eAction_setTrue,
        {&gOption_Gm},
    },
    {
        "FR",
        eAction_setString,
        {&gOption_FR},
    },
    {
        "Fr",
        eAction_setString,
        {&gOption_FR},
    },
    {
        "ZM",
        eAction_setTrue,
        {&gOption_ZM},
    },
    {
        NULL,
        eAction_invalid,
        {NULL},
    },
};

// GLOBAL: CL 0x00408530
const tTemporary_file_spec gTemporary_files_00408530[] = {
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
tCompile_filetype GetCompileFileType(const char *filepath)
{
    char extension[256];
    int i;

    _splitpath(filepath, NULL, NULL, NULL, extension);
    if (extension[0] == '\0') {
        return eFiletype_none;
    }
    for (i = 0; gFiletype_specs[i].stage != eOutput_linker; i++) {
        if (_stricmp(&extension[1], gFiletype_specs[i].extension) == 0) {
            return (tCompile_filetype) i;
        }
    }
    return eFiletype_none;
}

// FUNCTION: CL 0x0040553c
void FUN_0040553c(int index)
{
    char temp_path[1024];

    if (strlen(gApp_data->tempPath) + 10 > sizeof(temp_path) - 1) {
        FatalError(0);
    }
    FormatParsedOptionValue(temp_path, "%t", gApp_data);
    strcat(temp_path, gTemporary_files_00408530[index].filename);
    _unlink(temp_path);
}

// FUNCTION: CL 0x00405483
void FUN_00405483(BOOL arg1)
{
    tParsed_filepath *original_field_0x20;
    int i;
    const tTemporary_file_spec *temp_file;
    if (gOption_bk) {
        return;
    }
    if (gApp_data->tempPath == NULL) {
        return;
    }
    original_field_0x20 = gApp_data->field_0x20;
    i = 0;
    temp_file = &gTemporary_files_00408530[i];
    for (; temp_file->filename != NULL; i++, temp_file++) {
        if (arg1) {
            if (temp_file->remove) {
                FUN_0040553c(i);
                continue;
            }
        } else {
            if (!temp_file->remove) {
                gApp_data->field_0x20 = NULL;
                FUN_0040553c(i);
                continue;
            }
            if (original_field_0x20 != NULL) {
                tCompiler_input_file *unk = gApp_data->field_0x14;
                if (unk == NULL) {
                    gApp_data->field_0x20 = original_field_0x20;
                    FUN_0040553c(i);
                    continue;
                }
                while (unk != NULL) {
                    gApp_data->field_0x20 = unk->parsed_file;
                    FUN_0040553c(i);
                    unk = unk->next;
                }
            }
        }
    }
    gApp_data->field_0x20 = original_field_0x20;
}

// FUNCTION: CL 0x004055ad
void ExitCL(int exitcode)
{
    FUN_00405483(FALSE);
    exit(exitcode);
}

// FUNCTION: CL 0x004055c5
size_t dtostr(unsigned long number, char *dest, int radix)
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
                write_ptr += dtostr(va_arg(ap, int), write_ptr,
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
        FatalError(0);
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
            ptr_text = (char *) SkipSpaces(line);
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
    start_text = SkipSpaces(ptr_text) + 1;
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
void WriteTextF(int stream, const char *format, ...)
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
void WriteTextV(int stream, const char *format, va_list ap)
{
    size_t len;
    const char *text = ErrorVSprintf(&len, format, ap);
    write(stream, text, len);
}

// FUNCTION: CL 0x00405b28
const char *GetErrorMessage(int code)
{
    return GetMessageInFile(gApp_data->errorStringPath, code);
}

// FUNCTION: CL 0x00405a6a
void FatalError(int code, ...)
{
    va_list ap;
    if (code == 0) {
        code = 2000;
    }
    WriteTextF(STDERR_FILENO, GetErrorMessage(303), code); /* "Command line error D%d : " */
    va_start(ap, code);
    WriteTextV(STDERR_FILENO, GetMessageInFile(gApp_data->errorStringPath, code), ap);
    va_end(ap);
    WriteTextF(STDERR_FILENO, "\n");
    ExitCL(2);
}

// FUNCTION: CL 0x00405ad3
void EmitWarningF(int code, ...)
{
    va_list ap;
    const char *message;

    message = GetMessageInFile(gApp_data->errorStringPath, code);
    WriteTextF(STDERR_FILENO, GetErrorMessage(302), code);
    va_start(ap, code);
    WriteTextV(STDERR_FILENO, message, ap);
    va_end(ap);
    WriteTextF(STDERR_FILENO, "\n");
}

// FUNCTION: CL 0x004030c
void PrintLogoString(void)
{
    WriteTextF(STDERR_FILENO, GetErrorMessage(306), "10.20.6166");
    WriteTextF(STDERR_FILENO, GetErrorMessage(307));
}

// FUNCTION: CL 0x00402e48
void FatalUsageError()
{
    PrintLogoString();
    WriteTextF(STDOUT_FILENO, GetErrorMessage(305));
    exit(0);
}

// FUNCTION: CL 0x00405bd5
void *SafeMalloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL) {
        FatalError(0);
    }
    return ptr;
}

// FUNCTION: CL 0x00404fcb
char *SafeStrCpyOrKeep(char *str1, const char *str2)
{
    if (str2 != NULL) {
        strcpy(str1, str2);
    }
    return &str1[strlen(str1)];
}

// FUNCTION: CL 0x00405c0a
char *SafeStrDup(const char *str)
{
    if (str == NULL) {
        return NULL;
    }
    return _strdup(str);
}

// FUNCTION: CL 0x00404ff2
char *SafeStrDupJoin(char *str1, char *str2)
{
    size_t len1 = strlen(str2);
    size_t len2 = strlen(str1);
    char *result = SafeMalloc(len1 + len2 + 1);
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

// FUNCTION: CL 0x00404f2e
char *SafeStrCat(char *str1, const char *str2)
{
    if (str2 != NULL) {
        strcat(str1, str2);
    }
    return str1 + strlen(str1);
}

// FUNCTION: CL 0x00405bf7
void SafeFree(void *ptr)
{
    if (ptr != NULL) {
        free(ptr);
    }
}

// FUNCTION: CL 0x00405db3
BOOL WINAPI ConsoleCtrlCallback(DWORD CtrlType)
{
    (void) CtrlType;
    gConsoleInterrupted = TRUE;
    if (!gDisableControlHandler) {
        SetConsoleCtrlHandler(NULL, TRUE);
        ExitCL(4);
    }
    return 1;
}

// FUNCTION: CL 0x00405da5
void InstallConsoleHandlers()
{
    SetConsoleCtrlHandler(ConsoleCtrlCallback, TRUE);
}

// FUNCTION: CL 0x00404efe
const char *SkipSpaces(const char *text)
{
    while (*text != '\0' && _ismbcspace(*text)) {
        text = (char *) _mbsinc((unsigned char *) text);
    }
    return text;
}

// FUNCTION: CL 0x00405246
char **CreateArgArray(const char *text, BOOL cleanUpSlash)
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
    src_ptr = SkipSpaces(text);
    if (src_ptr[0] == '\0') {
        return NULL;
    }
    clean_str = SafeMalloc(strlen(src_ptr) + 1);
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
        src_ptr = SkipSpaces(src_ptr);
    }
    arg_i = 0;
    args = SafeMalloc(sizeof(char *) * (count_args + 1));
    while (count_args != 0) {
        char *arg;
        count_args -= 1;
        arg = (char *) SkipSpaces(clean_str);
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
int GetArgsArraySize(const char **args)
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
char *GetExecutableFilePath()
{
#ifdef _MSC_VER
    return (char *) *__p__pgmptr();
#else
    char *buffer;
    _get_pgmptr(&buffer);
    return buffer;
#endif
}

// FUNCTION: CL 0x004031be
char *GetFileDirectory(const char *path)
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
    return SafeStrDup(drive_dir);
}

// FUNCTION: CL 0x00403248
size_t FindFileInPATH(const char *filename, char *buffer, size_t bufferSize)
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
            FatalError(0);
        }
        if (_access(buffer, R_OK) == 0) {
            return len_joined;
        }
    }
}

// FUNCTION: CL 0x004030fc
char *JoinPathInExeSearchPath(const char *dirpath, const char *filename)
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
            if (FindFileInPATH(filename, buffer, sizeof(buffer)) != 0) {
                filename = buffer;
            }
        }
    }
    return SafeStrDup(filename);
}

// FUNCTION: CL 0x004024f5
void InitAppPaths(const char *exePath, tApp_data *app_data)
{
    memset(app_data, 0, sizeof(*app_data));
    app_data->exeDirectory = GetFileDirectory(exePath);
    app_data->errorStringPath = JoinPathInExeSearchPath(app_data->exeDirectory, "cl.err");
    app_data->includePaths = getenv("INCLUDE");
}

// FUNCTION: CL 0x004023c4
BOOL ArgumentsContainNologo(char **argv, int argc)
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
BOOL FUN_004010e8(tParsed_option *option, const tFiletype_compiler_spec *spec)
{
    return strchr(option->field_0x8, spec->field_0x10) != NULL;
}

// FUNCTION: CL 0x00404e41
char *GetFileBasename(char *buffer, const char *path)
{
    _splitpath(path, NULL, NULL, buffer, NULL);
    return buffer;
}

// FUNCTION: CL 0x00404eab
char *RemoveExtension(char *buffer, const char *path)
{
    char drive[4];
    char dir[256];
    char basename[256];

    _splitpath(path, drive, dir, basename, NULL);
    _makepath(buffer, drive, dir, basename, "");
    return buffer;
}

// FUNCTION: CL 0x00404a64
const char *FormatMapPath(char *buffer, const char *exePath)
{
    char drive[4];
    char dir[256];
    char basename[256];
    char extension[256];

    if (!gOption_bm) {
        return "nul.map";
    }
    if (!gOption_Fm) {
        _splitpath(exePath, drive, dir, basename, NULL);
        _makepath(buffer, drive, dir, basename, "map");
        return buffer;
    }
    _splitpath(exePath, drive, dir, basename, extension);
    if (basename[0] == '\0') {
        GetFileBasename(basename, exePath);
    }
    _makepath(buffer, drive, dir, basename, extension[0] != '\0' ? extension : "map");
    return buffer;
}

// FUNCTION: CL 0x00404b29
char *FormatParsedOptionValue(char *buffer, const char *format, tApp_data *app_data)
{
    char path_buffer[256];
    char *dest = buffer;
    char *ptr;
    const char *filepath;
    tCompile_filetype filetype;
    short fileprop;

    if (app_data->field_0x20 != NULL) {
        filepath = app_data->field_0x20->path;
        filetype = app_data->field_0x20->filetype;
        fileprop = app_data->field_0x20->field_0xe;
    } else {
        filepath = "";
        filetype = eFiletype_none;
        fileprop = -1;
    }
    while (*format != '\0') {
        if (*format == '%') {
            *dest = '\0';
            switch (format[1]) {
            case '%':
                *dest++ = format[1];
                break;
            case 'b':
                GetFileBasename(path_buffer, filepath);
                dest = SafeStrCat(dest, path_buffer);
                break;
            case 'B':
                GetFileBasename(path_buffer, filepath);
                _mbsupr((unsigned char *) path_buffer);
                dest = SafeStrCat(dest, path_buffer);
                break;
            case 'e':
                ptr = app_data->error_paths[filetype][app_data->compiler_stage];
                if (dest == NULL) {
                    dest = "";
                }
                dest = SafeStrCat(dest, ptr);
                break;
            case 'f':
                dest = SafeStrCat(dest, filepath);
                break;
            case 'X':
                if (gBuildingDLL) {
                    dest = SafeStrCat(dest, "dll");
                } else {
                    dest = SafeStrCat(dest, "exe");
                }
                break;
            case 'x':
                RemoveExtension(path_buffer, gOutputExecutableFilepath);
                dest = SafeStrCat(dest, path_buffer);
                break;
            case 't':
                dest = SafeStrCat(dest, app_data->tempPath);
                if (app_data->field_0x14 && fileprop != -1) {
                    dest[-6] = 'a' + fileprop / 10;
                    dest[-5] = '0' + fileprop % 10;
                }
                break;
            case 'm':
                {
                    char *exe_buffer = SafeMalloc(1024);
                    FormatParsedOptionValue(exe_buffer, gOutputExecutableFilepath, app_data);
                    FormatMapPath(dest, exe_buffer);
                    dest += strlen(dest);
                    SafeFree(exe_buffer);
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
void RunOptionActions(tApp_data *app_data)
{
    char buffer[512];
    tParsed_option *opt;

    for (opt = app_data->field_0x0; opt != NULL; opt = opt->next) {
        bool found;
        tOption_action *action;

        if (!FUN_004010e8(opt, &gFiletype_compiler_spec_0040a038)) {
            continue;
        }
        found = false;
        for (action = gOption_actions; action->key != NULL; action++) {
            if (opt->arg_keyonly[0] == action->key[0] && strcmp(opt->arg_keyonly, action->key) == 0) {
                found = true;
                switch (action->action) {
                case eAction_setTrue:
                    *action->boolean = TRUE;
                    break;
                case eAction_setFalse:
                    *action->boolean = FALSE;
                    break;
                case eAction_setString:
                    FormatParsedOptionValue(buffer, opt->arg_value, app_data);
                    *action->text = SafeStrDup(buffer);
                    break;
                case eAction_callback:
                    action->callback(opt);
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
void CreateTempDir(tApp_data *app_data)
{
    char buffer[1024];
    const char *tmp_env;

    if (app_data->tempPath != NULL) {
        gBOOL_0040a02c = FALSE;
        return;
    }
    tmp_env = getenv("TMP");
    if (tmp_env == NULL) {
        app_data->tempPath = SafeStrDup("XXXXXX");
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
        app_data->tempPath = SafeStrDupJoin(buffer, "XXXXXX");
    }
    app_data->tempPath = _mktemp(app_data->tempPath);
}

// FUNCTION: CL 0x00402387
BOOL StringStartsWith(const char *start, const char *str)
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
void EmitOptionValueDiagnostic(int code, const tParsed_option *opt1, const tParsed_option *opt2)
{
    const char *argval1;
    const char *argval2;

    if (opt1->parsed_option_parent != NULL) {
        opt1 = opt1->parsed_option_parent;
    }
    argval1 = "";
    if (opt1->arg_value != NULL) {
        argval1 = opt1->arg_value;
    }
    argval2 = "";
    if (opt2->arg_value != NULL) {
        argval2 = opt2->arg_value;
    }
    if (code >= 4000 && code < 4100) {
        EmitWarningF(code, opt1->arg_keyonly, argval1, opt2->arg_keyonly, argval2);
    } else {
        FatalError(code, opt1->arg_keyonly, argval1, opt2->arg_keyonly, argval2);
    }
}

// FUNCTION: CL 0x004021f0
const tSingle_arg_spec *FindMatchingSingleArgOption(const char *arg)
{
    int i;
    for (i = 0; gSingle_arg_specs[i].valuespec != NULL; i++) {
        if (StringStartsWith(gSingle_arg_specs[i].key, arg)) {
            return &gSingle_arg_specs[i];
        }
    }
    return NULL;
}

// FUNCTION: CL 0x00401442
int CalculateOptionMatchLength(const tOption_spec *option_spec, const char **args, int index)
{
    const char *arg_spec = option_spec->field_0x0;
    const char *arg;
    int len_match;

    if (arg_spec[0] == '^') {
        if (!gConsider_hat_options) {
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
const tOption_spec *GetBestOptionSpec(const char **args, int index)
{
    const tOption_spec *best_match = NULL;
    int best_score = 0;
    int i;

    for (i = 0; gOption_specs[i].field_0x0 != NULL; i++) {
        const tOption_spec *option_spec = &gOption_specs[i];
        if (option_spec->field_0x0[option_spec->field_0x0[0] == '^' ? 1 : 0] == args[index][1]) {
            int score = CalculateOptionMatchLength(option_spec, args, index);
            if (score > 0 && (best_score == 0 || score > best_score)) {
                best_match = option_spec;
                best_score = score;
            }
        }
    }
    return best_match;
}

// FUNCTION: CL 0x004013d7
tParsed_option *AllocateParsedOption(const char *optname, const char *optval, const char *param_3, int param_4)
{
    tParsed_option *result;

    if (gUnused_parsed_options == NULL) {
        result = SafeMalloc(sizeof(*result));
    } else {
        result = gUnused_parsed_options;
        gUnused_parsed_options = gUnused_parsed_options->next;
    }
    memset(result, 0, sizeof(*result));
    result->field_0x4 = param_4;
    result->arg_value = SafeStrDup(optval);
    result->arg_keyonly = SafeStrDup(optname);
    result->field_0x8 = SafeStrDup(param_3);
    return result;
}

// FUNCTION: CL 0x00402144
tParsed_option *DuplicateParsedOption(tParsed_option *opt)
{
    tParsed_option *r = AllocateParsedOption(opt->arg_keyonly, opt->arg_value, opt->field_0x8, opt->field_0x4);
    r->void_parent = opt->void_parent;
    return r;
}

// FUNCTION: CL 0x00402004
void FreeParsedOption(tParsed_option *opt)
{
    SafeFree((void *) opt->arg_value);
    SafeFree((void *) opt->arg_keyonly);
    opt->next = gUnused_parsed_options;
    gUnused_parsed_options = opt;
}

// FUNCTION: CL 00401fe8
void FreeParsedOptions(tParsed_option *opt)
{
    while (opt != NULL) {
        tParsed_option *next = opt->next;
        FreeParsedOption(opt);
        opt = next;
    }
}

// FUNCTION: CL 0x004016f8
void AppendParsedOption(tParsed_option **list, tParsed_option *opt)
{
    while (*list != NULL) {
        list = &(*list)->next;
    }
    *list = opt;
}

// FUNCTION: CL 0x00402165
tParsed_option *RemoveParsedOption(tParsed_option **list, tParsed_option *item)
{
    for (; *list != NULL; list = &(*list)->next) {
        if (*list == item) {
            tParsed_option *r = *list;
            *list = r->next;
            r->next = NULL;
            return r;
        }
    }
    return NULL;
}

// FUNCTION: CL 0x00401068
tParsed_filepath *AllocateParsedFilepath(const char *path, tCompile_filetype filetype)
{
    tParsed_filepath *result;

    result = SafeMalloc(sizeof(*result));
    result->filetype = filetype;
    result->field_0xc = 1;
    result->path = SafeStrDup(path);
    result->next = NULL;
    result->field_0xe = -1;
    return result;
}

// FUNCTION: CL 0x004010a1
tParsed_filepath *ParseFileArgument(const char *path, tCompile_filetype filetype, undefined2 arg3)
{
    tParsed_filepath *result;
    tParsed_filepath **list;

    result = AllocateParsedFilepath(path, filetype);
    result->field_0xc = arg3;
    list = &gApp_data->field_0x10;
    while (*list != NULL) {
        list = &(*list)->next;
    }
    *list = result;
    if (gFiletype_specs[filetype].stage == eInput_compiler) {
        gCount_compiler_file_inputs += 1;
    }
    return result;
}

// FUNCTION: CL 0x0040112b
void CheckNumericOption(const char *optkey, char *optval, const char *optspec)
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
        FatalError(2021, optkey, optval);
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
            EmitWarningF(4014, opt_intvalue, optkey, minimum);
            opt_intvalue = minimum;
        }
    }
    dtostr(opt_intvalue, optval, 10);
}

// FUNCTION: CL 0x00404f55
char *EscapeFormatString(char *dest, const char *format)
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
const char *FindLastOccurrenceOfAnyCharOf(const char *text, const char *needles)
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
const char *FUN_00401498(const char *spec, char *buffer, const char *key, const char **filename)
{
    // GLOBAL: CL 0x0040a750
    static char result_buffer[32];
    const char *result;

    *filename = '\0';
    result = ExtractImpliedSpec(&spec[1], buffer, key);
    result = ExtractImpliedSpec(&result[1], result_buffer, key);
    if (buffer[0] == '\0') {
        strcpy(buffer, result_buffer);
    }
    *filename = result_buffer;
    return &result[1];
}

// FUNCTION: CL 0x00402da5
const char *ReplaceFilenameWithExt(const char *extension_spec, char *path, const char *filename)
{
    char throwaway_buffer[256];
    char ext_c1 = *extension_spec;
    const char *path_filename;
    char *path_ptr;

    path_filename = FindLastOccurrenceOfAnyCharOf(path, "\\/");
    if (ext_c1 == '<') {
        extension_spec++;
    }
    path_filename = FindLastOccurrenceOfAnyCharOf(path, "\\/");
    if (path_filename != NULL && path_filename[1] == '\0') {
        if (filename == NULL) {
            filename = "%b";
        }
        path_ptr = SafeStrCat(path, filename);
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
const char *ExtractImpliedSpec(const char *spec, char *buffer, const char *key)
{
    char *buffer_ptr;
    const char *filename_ptr = NULL;

    buffer[0] = '\0';
    buffer_ptr = buffer;
    while (*spec != '\0') {
        if (*spec == '(') {
            *buffer_ptr = '\0';
            spec = FUN_00401498(spec, buffer_ptr, key, &filename_ptr);
            buffer_ptr = &buffer[strlen(buffer)];
        } else if (*spec == '!' || *spec == ':' || *spec == ')' || *spec == ',' || *spec == '|') {
            break;
        } else if (*spec == '*') {
            *buffer_ptr = '\0';
            if (gConsider_hat_options) {
                buffer_ptr = SafeStrCat(buffer, key);
            } else {
                buffer_ptr = EscapeFormatString(buffer, key);
            }
            spec++;
        } else if (*spec == '<') {
            spec = ReplaceFilenameWithExt(&spec[1], buffer, filename_ptr);
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
tParsed_option *CreateImpliedOptions(const char *implied_spec, const tParsed_option *option)
{
    tParsed_option *result = NULL;
    char speckey[20];

    speckey[0] = '\0';
    while (*implied_spec != '\0') {
        unsigned int specflag = 0;
        const char *implied_spec_ptr = SkipSpaces(implied_spec);
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
        implied_spec = ExtractImpliedSpec(&implied_spec_ptr[1], implied_argkey, option->arg_keyonly);
        if (*implied_spec == '!' || *implied_spec == ':') {
            if (*implied_spec == '!') {
                specflag |= 0x4;
            }
            implied_spec = ExtractImpliedSpec(&implied_spec[1], gImplied_argval, option->arg_value);
            if (strlen(gImplied_argval) != 0) {
                implied_argval = gImplied_argval;
            } else {
                implied_argval = NULL;
            }
        } else {
            implied_argval = NULL;
        }
        if (*implied_spec == ',') {
            implied_spec += 1;
        }
        AppendParsedOption(&result, AllocateParsedOption(implied_argkey, implied_argval, speckey, specflag));
    }
    return result;
}

// FUNCTION: CL 0x00401226
tParsed_option *ExtractOptionFromArgs(const tOption_spec *option_spec, const char **args, int *index)
{
    char optkey_buffer[32];
    char optval_buffer[1024];
    char *optkey_ptr = optkey_buffer;
    const char *arg = args[*index];
    const char *optkey_spec_ptr = option_spec->field_0x0;
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
            FatalError(0);
        }
        *optkey_ptr++ = *arg++;
    }
    *optkey_ptr = '\0';
    if (*optkey_spec_ptr == '\0') {
        *index += 1;
        return AllocateParsedOption(optkey_buffer, NULL, NULL, 0);
    }
    switch (*optkey_spec_ptr) {
    case '!':
        arg_is_optional = FALSE;
        break;
    case ':':
        arg_is_optional = TRUE;
        break;
    default:
        FatalError(0);
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
        return option_spec->cb_0x10(args, index);
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
            FatalError(2004, optkey_buffer);
        }
        optval = NULL;
    }
    if (optval != NULL && optkey_spec_ptr[1] != '\0') {
        CheckNumericOption(optkey_buffer, optval, &optkey_spec_ptr[1]);
    }
    return AllocateParsedOption(optkey_buffer, optval, NULL, optflags);
}

// FUNCTION: CL 0x00401711
BOOL AreOptionsSimilar(tParsed_option *opt1, tParsed_option *opt2)
{
    size_t l1;
    size_t l2;

    if (!(strcmp(opt1->arg_keyonly, "?") == 0 || strcmp(opt2->arg_keyonly, "?") == 0 ||
                strcmp(opt1->arg_keyonly, opt2->arg_keyonly) == 0)) {
        return FALSE;
    }
    if (opt1->arg_value == NULL) {
        if (opt2->arg_value == NULL || strcmp(opt2->arg_value, "?") == 0) {
            return TRUE;
        }
        return FALSE;
    }
    if (opt2->arg_value == NULL) {
        if (strcmp(opt1->arg_value, "?") == 0) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    l1 = strlen(opt1->arg_value);
    l2 = strlen(opt2->arg_value);
    if (l1 > 0 && opt1->arg_value[l1 - 1] == '?') {
        if (strncmp(opt1->arg_value, opt2->arg_value, l1 - 1) == 0) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    if (l2 > 0 && opt2->arg_value[l2 - 1] == '?') {
        if (strncmp(opt1->arg_value, opt2->arg_value, l2 - 1) == 0) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    if (strcmp(opt1->arg_value, opt2->arg_value) == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// FUNCTION: CL 0x00402d5d
BOOL FUN_00402d5d(tParsed_option *const opts1, tParsed_option *const opts2)
{
    tParsed_option *opt1;
    for (opt1 = opts1; opt1 != NULL; opt1 = opt1->next) {
        tParsed_option *opt2;
        for (opt2 = opts2; opt2 != NULL; opt2 = opt2->next) {
            if (AreOptionsSimilar(opt1, opt2) && !(opt1->field_0x4 & 0x10) && !(opt2->field_0x4 & 0x10)) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

// FUNCTION: CL 0x00402092
tParsed_option *FUN_00402092(tParsed_option **list, tParsed_option *implied_option, tParsed_option **list_arg3)
{
    tParsed_option *result = NULL;

    for (; implied_option != NULL; implied_option = implied_option->next) {
        tParsed_option *list_item;
        for (list_item = *list; list_item != NULL; list_item = list_item->next) {
            if (AreOptionsSimilar(list_item, implied_option)) {
                if (list_arg3 != NULL &&
                        (((implied_option->field_0x4 & 0x1) && !(list_item->field_0x4 & 0x21)) ||
                                ((implied_option->field_0x4 & 0x20) && !(list_item->field_0x4 & 0x20)))) {
                    tParsed_option *o;

                    if (list_item->void_parent == NULL) {
                        continue;
                    }
                    for (o = *list_arg3; o != NULL; o = o->next) {
                        if (o->parsed_option_parent == list_item) {
                            break;
                        }
                    }
                    if (o != NULL) {
                        continue;
                    }
                    AppendParsedOption(list_arg3, DuplicateParsedOption(list_item));
                } else {
                    AppendParsedOption(&result, RemoveParsedOption(list, list_item));
                }
            }
        }
    }
    return result;
}

// FUNCTION: CL 0x00402bc0
void FUN_00402bc0()
{
    tParsed_option *option;

    for (option = gApp_data->field_0x4; option != NULL; option = option->next) {
        char *parent_value;
        char *parent_ptr;
        const tOption_spec *parent;

        if (option->field_0x4 & 0x10) {
            continue;
        }
        parent = option->parent_option_spec;
        if (parent->str_0x10 == NULL) {
            continue;
        }
        if (parent->field_0x4 == NULL) {
            continue;
        }
        parent_value = SafeStrDup(parent->str_0x10);
        parent_ptr = parent_value;
        while (1) {
            char *next_ptr = (char *) _mbschr((unsigned char *) parent_ptr, ';');
            tParsed_option *implied1;
            tParsed_option *implied2;
            tParsed_option *implied3;

            if (next_ptr != NULL) {
                *next_ptr = '\0';
                next_ptr += 1;
            }
            implied1 = CreateImpliedOptions(parent_ptr, option);
            if (FUN_00402d5d(gApp_data->field_0x4, implied1)) {
                parent_ptr = next_ptr;
            } else {
                if (!(option->field_0x4 & 0x1)) {
                    char *opt1str = SafeMalloc(80);
                    char *opt2str = SafeMalloc(80);
                    tParsed_option *imp;

                    opt1str[0] = '/';
                    opt2str[0] = '\0';
                    strcpy(&opt1str[1], option->arg_keyonly);
                    for (imp = implied1; imp != NULL; imp = imp->next) {
                        if (imp != implied1) {
                            if (imp->next == NULL) {
                                strcat(opt2str, GetErrorMessage(321));
                            } else {
                                strcat(opt2str, GetErrorMessage(320));
                            }
                        }
                        strcat(opt2str, "/");
                        strcat(opt2str, imp->arg_keyonly);
                    }
                    EmitWarningF(4007, opt1str, opt2str);
                    SafeFree(opt2str);
                    SafeFree(opt1str);
                }
                implied2 = CreateImpliedOptions(parent->field_0x4, option);
                implied3 = FUN_00402092(&gApp_data->field_0x0, implied2, NULL);
                FreeParsedOptions(implied3);
                FreeParsedOptions(implied2);
                parent_ptr = NULL;
            }
            FreeParsedOptions(implied1);
            if (parent_ptr == NULL) {
                break;
            }
        }
        SafeFree(parent_value);
    }
}

// FUNCTION: CL 0x004028a3
void OnbAOption(tParsed_option *option)
{
    bool ext_cod;
    tParsed_option *opt_FA;
    tParsed_option *opt_Fa;
    tParsed_option *imp_FA;
    tParsed_option *imp_Fa;
    char *arg_extra;

    if (option->arg_value[0] == '\0') {
        return;
    }
    arg_extra = (char *) _mbschr((unsigned char *) option->arg_value, ' ');
    if (arg_extra != NULL) {
        *arg_extra = '\0';
        arg_extra += 1;
    }
    opt_FA = AllocateParsedOption("FA", "?", option->arg_value, 4);
    opt_Fa = AllocateParsedOption("Fa", "?", option->arg_value, 0);
    imp_FA = FUN_00402092(&gApp_data->field_0x0, opt_FA, NULL);
    imp_Fa = FUN_00402092(&gApp_data->field_0x0, opt_Fa, NULL);
    if (imp_FA != NULL) {
        arg_extra = imp_FA->arg_value;
        FreeParsedOption(opt_FA);
    } else {
        SafeFree(opt_FA->arg_value);
        opt_FA->arg_value = SafeStrDup(arg_extra);
        imp_FA = opt_FA;
    }
    if (imp_Fa != NULL) {
        FreeParsedOption(opt_Fa);
    } else {
        SafeFree(opt_Fa->arg_value);
        opt_Fa->arg_value = SafeStrDup("%b");
        imp_Fa = opt_Fa;
    }
    ext_cod = false;
    strcpy(gImplied_argval, imp_Fa->arg_value);
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
            EmitWarningF(4015, "/FA", &arg_extra[1]);
        }
    }
    ReplaceFilenameWithExt(ext_cod ? "cod" : "asm", gImplied_argval, NULL);
    SafeFree(imp_Fa->arg_value);
    imp_Fa->arg_value = SafeStrDup(gImplied_argval);
    AppendParsedOption(&gApp_data->field_0x0, imp_FA);
    AppendParsedOption(&gApp_data->field_0x0, imp_Fa);
    option->arg_value[0] = '\0';
}

// FUNCTION: CL 0x00401d71
BOOL ParseMultipleArgOption(const char **args, int *index)
{
    const tOption_spec *option_spec = GetBestOptionSpec(args, *index);
    tParsed_option *option;
    tParsed_option *implied_options1;

    if (option_spec == NULL) {
        AppendParsedOption(&gUnknown_options, AllocateParsedOption(args[*index], NULL, NULL, 0));
        *index += 1;
        return FALSE;
    }
    option = ExtractOptionFromArgs(option_spec, args, index);
    if (option == NULL) {
        return TRUE;
    }
    if (option->field_0x4 & 0x2) {
        AppendParsedOption(&gUnknown_options, option);
        return FALSE;
    }
    option->parent_option_spec = option_spec;
    AppendParsedOption(&gApp_data->field_0x4, option);
    implied_options1 = NULL;
    if (option_spec->field_0x4 != NULL) {
        implied_options1 = CreateImpliedOptions(option_spec->field_0x4, option);
        if (implied_options1 != NULL) {
            tParsed_option *f1 = NULL;
            tParsed_option *f2 = FUN_00402092(&gApp_data->field_0x0, implied_options1, &f1);
            tParsed_option *p;

            FreeParsedOptions(f2);
            FreeParsedOptions(f1);
            for (p = implied_options1; p != NULL; p = p->next) {
                p->parsed_option_parent = option;
            }
        }
    }
    if (option_spec->field_0xc != NULL) {
        void *prev_override;
        tParsed_option *implied_options2 = CreateImpliedOptions(option_spec->field_0xc, option);
        tParsed_option *f1 = NULL;
        tParsed_option *f2 = FUN_00402092(&gApp_data->field_0x0, implied_options2, &f1);
        tParsed_option *p;

        prev_override = NULL;
        for (p = f2; p != NULL; p = p->next) {
            if (p->parsed_option_parent != NULL) {
                p->field_0x4 |= 0x10;
            }
            if (!(p->field_0x4 & 0x21)) {
                if (prev_override == NULL || p->parsed_option_parent != prev_override) {
                    EmitOptionValueDiagnostic(4025, p, option);
                }
                prev_override = p->parsed_option_parent;
            }
        }
        FreeParsedOptions(f2);
        for (p = f1; p != NULL; p = p->next) {
            if (p->parsed_option_parent != NULL && p->parent_option_spec->field_0xc != NULL) {
                tParsed_option *g1 = NULL;
                tParsed_option *implied_opts = CreateImpliedOptions(p->parent_option_spec->field_0xc, p);
                tParsed_option *g2 = FUN_00402092(&implied_options1, implied_opts, &g1);
                FreeParsedOptions(g2);
                FreeParsedOptions(implied_opts);
                FreeParsedOptions(g1);
            }
        }
        FreeParsedOptions(f1);
    }
    if (option_spec->field_0x8 != NULL) {
        tParsed_option *implied_options3 = CreateImpliedOptions(option_spec->field_0x8, option);
        tParsed_option *f2 = FUN_00402092(&gApp_data->field_0x0, implied_options3, NULL);
        tParsed_option *p;

        if (f2 != NULL) {
            for (p = f2; p != NULL; p = p->next) {
                if (p->parsed_option_parent != NULL) {
                    p->parsed_option_parent->field_0x4 |= 0x10;
                }
                if (!(p->field_0x4 & 0x21)) {
                    EmitOptionValueDiagnostic(2016, p, option);
                }
            }
            FreeParsedOptions(f2);
        }
        FreeParsedOptions(implied_options3);
    }
    if (implied_options1 != NULL) {
        AppendParsedOption(&gApp_data->field_0x0, implied_options1);
    }
    return TRUE;
}

// FUNCTION: CL 0x0040222b
void ParseSingleArgOption(const tSingle_arg_spec *spec, const char *arg)
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
            EmitWarningF(4099, "Oy1", "Oy-");
        } else if (_mbsstr((const unsigned char *) arg_value, (const unsigned char *) "y2") != NULL) {
            EmitWarningF(4099, "Oy2", "Oy");
        }
    }
    while (*arg_value != '\0') {
        const char *valuespec = strchr(spec->valuespec, *arg_value);
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
        ParseMultipleArgOption(argv, &multi_arg);
    }
}

// FUNCTION: CL 0x00401c6d
void ParseArguments(const char **args, int count)
{
    // GLOBAL: CL 0x0040a058
    static BOOL options_are_global = FALSE;
    // GLOBAL: CL 0x0040a05c
    static BOOL warning_4026_emitted = FALSE;
    int i;

    for (i = 0; i < count;) {
        int original_count = gCount_compiler_file_inputs;
        const char *arg = args[i];
        if (arg[0] == '@') {
            ParseResponseFile(&arg[1]);
            continue;
        }
        if (arg[0] == '-' || arg[0] == '/') {
            const tSingle_arg_spec *single_arg_spec = FindMatchingSingleArgOption(&arg[1]);
            if (single_arg_spec != NULL && arg[strlen(single_arg_spec->key) + 1] != '\0') {
                ParseSingleArgOption(single_arg_spec, arg);
                i++;
            } else {
                ParseMultipleArgOption(args, &i);
            }
            if (gCount_compiler_file_inputs != 0 && original_count == gCount_compiler_file_inputs) {
                options_are_global = TRUE;
            }
        } else {
            ParseFileArgument(arg, GetCompileFileType(arg), 0);
            i++;
        }
        if (options_are_global && original_count != gCount_compiler_file_inputs && !warning_4026_emitted) {
            EmitWarningF(4026);
            warning_4026_emitted = 1;
        }
    }
}

// FUNCTION: CL 0x0040336e
void ParseResponseFile(const char *path)
{
    FILE *f;
    char *line;

    gResponseFileDepth += 1;
    if (gResponseFileDepth > 13) {
        FatalError(2035, path);
    }
    f = fopen(path, "r");
    if (f == NULL) {
        FatalError(2022, path);
    }
    line = SafeMalloc(1024);
    while (fgets(line, sizeof(line) - 1, f) != NULL) {
        size_t len_line = strlen(line);
        char **args;

        if (line[len_line - 1] == '\n') {
            line[len_line - 1] = '\0';
        }
        if (!gShouldPrintLogoString) {
            WriteTextF(STDERR_FILENO, gShould_print_cl ? "cl " : "   ");
            WriteTextF(STDERR_FILENO, "%s\n", line);
            gShould_print_cl = FALSE;
            gPrinted_cl = TRUE;
        }
        args = CreateArgArray(line, TRUE);
        if (args != NULL) {
            size_t args_count = GetArgsArraySize((const char **) args);
            ParseArguments((const char **) args, args_count);
            SafeFree(args[0]);
            SafeFree(args);
        }
    }
    if (!feof(f)) {
        FatalError(2034, path);
    }
    fclose(f);
    SafeFree(line);
    gResponseFileDepth -= 1;
}

// FUNCTION: CL 0x00402f31
int OnDCallback(const char **args, int *index)
{
    const char *macro_arg = &args[*index][2];
    char *pos_hash;
    char *pos_assign;
    char *macro_name;
    size_t macro_name_len;
    tParsed_option *opt;

    if (*macro_arg != '\0') {
        *index += 1;
    } else {
        macro_arg = args[*index + 1];
        *index += 2;
    }
    if (macro_arg == NULL || macro_arg[0] == '\0') {
        FatalError(2004, "D");
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
    macro_name = SafeMalloc(macro_name_len + 1);
    strncpy(macro_name, macro_arg, macro_name_len);
    macro_name[macro_name_len] = '\0';
    opt = AllocateParsedOption("D", macro_name, NULL, 0x0);
    OnbUOption(opt);
    FreeParsedOption(opt);
    SafeFree(macro_name);
    opt = AllocateParsedOption("D", macro_arg, "1PM", 0x4);
    AppendParsedOption(&gApp_data->field_0x0, opt);
    return 0;
}

// FUNCTION: CL 0x00402e76
int OnLinkCallback(const char **args, int *index)
{
    const char *link_arg = &args[*index][5];
    int new_index;

    if (*link_arg != '\0') {
        AppendParsedOption(&gApp_data->field_0x0, AllocateParsedOption(link_arg, NULL, "L", 0x8));
        AppendParsedOption(&gApp_data->field_0x0, AllocateParsedOption(link_arg, NULL, "C", 0x8));
    }
    new_index = *index + 1;
    while (args[new_index] != NULL) {
        const char *link_arg = args[new_index];
        AppendParsedOption(&gApp_data->field_0x0, AllocateParsedOption(link_arg, NULL, "L", 0x8));
        AppendParsedOption(&gApp_data->field_0x0, AllocateParsedOption(link_arg, NULL, "C", 0x8));
        new_index += 1;
    }
    *index = new_index;
    return 0;
}

// FUNCTION: CL 0x00403069
void FUN_00403069(const char *optionPrefix, const char **args, int *index, tCompile_filetype filetype)
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
        FatalError(2004, optionPrefix);
    }
    ParseFileArgument(path, filetype, 1);
}

// FUNCTION: CL 0x00403035
int OnTcCallback(const char **args, int *index)
{
    FUN_00403069("Tc", args, index, eFiletype_c);
    return 0;
}

// FUNCTION: CL 0x0040304f
int OnTpCallback(const char **args, int *index)
{
    FUN_00403069("Tp", args, index, eFiletype_cpp);
    return 0;
}

// FUNCTION: CL 0x0040301b
int OnToCallback(const char **args, int *index)
{
    FUN_00403069("Tp", args, index, eFiletype_obj);
    return 0;
}

// FUNCTION: CL 0x0040264e
void OnbaOption(tParsed_option *option)
{
    const tFiletype_spec *filetype_spec;

    for (filetype_spec = gFiletype_specs; filetype_spec->stage != eStage_invalid; filetype_spec++) {
        tFiletype_compiler_spec *compiler_spec;

        for (compiler_spec = filetype_spec->compiler_specs; compiler_spec->compiler_filename != NULL; compiler_spec++) {
            if (option->arg_value[0] == '.' || compiler_spec->field_0x10 == option->arg_value[0]) {
                compiler_spec->field_0xc = 1;
            }
        }
    }
}

// FUNCTION: CL 0x004026f1
void OnbcOption(tParsed_option *option)
{
    char a2 = option->arg_value[1];
    bool found = false;
    undefined4 filetype_compiler_spec_field_0xc;
    const tFiletype_spec *filetype_spec = gFiletype_specs;

    while (!found && filetype_spec->stage != eStage_invalid) {
        const tFiletype_compiler_spec *filetype_compiler_spec;
        for (filetype_compiler_spec = filetype_spec->compiler_specs;
                !found && filetype_compiler_spec->compiler_filename != NULL; filetype_compiler_spec++) {
            if (filetype_compiler_spec->field_0x10 == option->arg_value[0]) {
                filetype_compiler_spec_field_0xc = filetype_compiler_spec->field_0xc;
                found = true;
            }
        }
        filetype_spec++;
    }
    if (filetype_compiler_spec_field_0xc != 0) {
        filetype_spec = gFiletype_specs;
        while (filetype_spec->stage != eStage_invalid) {
            tFiletype_compiler_spec *filetype_compiler_spec;
            for (filetype_compiler_spec = filetype_spec->compiler_specs;
                    filetype_compiler_spec->compiler_filename != NULL; filetype_compiler_spec++) {
                if (filetype_compiler_spec->field_0x10 == a2) {
                    filetype_compiler_spec->field_0xc = filetype_compiler_spec_field_0xc;
                }
            }
            filetype_spec++;
        }
    }
}

// FUNCTION: CL 0x00402690
void OnbdOption(tParsed_option *option)
{
    char a0 = option->arg_value[0];
    const tFiletype_spec *filetype_spec;

    for (filetype_spec = gFiletype_specs; filetype_spec->stage != eStage_invalid; filetype_spec++) {
        tFiletype_compiler_spec *filetype_compiler_spec;
        for (filetype_compiler_spec = filetype_spec->compiler_specs; filetype_compiler_spec->compiler_filename != NULL;
                filetype_compiler_spec++) {
            if (a0 == '.' || _mbschr((unsigned char *) option->arg_value, filetype_compiler_spec->field_0x10) != NULL) {
                filetype_compiler_spec->field_0xc = 0;
            }
        }
    }
}

// FUNCTION: CL 0x00402808
void OnboOption(tParsed_option *option)
{
    if (option->arg_value[0] == '\0') {
        return;
    }
    if (gCount_compiler_file_inputs > 1) {
        char *arg1_space;
        char *arg2_space;
        const char *arg2;
        const char *end_arg2;

        arg1_space = (char *) _mbschr((unsigned char *) option->arg_value, ' ');
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
            FatalError(2036, &arg1_space[1], arg2);
        }
    }
    option->arg_value[0] = '\0';
}

// FUNCTION: CL 0x004025f9
void OnbpOption(tParsed_option *option)
{
    char a0 = option->arg_value[0];
    const tFiletype_spec *filetype_spec;
    for (filetype_spec = gFiletype_specs; filetype_spec->stage != eStage_invalid; filetype_spec++) {
        tFiletype_compiler_spec *filetype_compiler_spec;
        for (filetype_compiler_spec = filetype_spec->compiler_specs; filetype_compiler_spec->compiler_filename != NULL;
                filetype_compiler_spec++) {
            if (a0 == '.' || filetype_compiler_spec->field_0x10 == a0) {
                filetype_compiler_spec->compiler_filename = SafeStrDup(&option->arg_value[1]);
            }
        }
    }
}

// FUNCTION: CL 0x00402775
void OnbUOption(tParsed_option *option)
{
    tParsed_option *implied_option1 = CreateImpliedOptions("=D:*,=D:*=?", option);
    tParsed_option *implied_option2 = FUN_00402092(&gApp_data->field_0x0, implied_option1, NULL);
    FreeParsedOptions(implied_option2);
    FreeParsedOptions(implied_option1);
}

// FUNCTION: CL 0x004027ae
void OnbuOption(tParsed_option *option)
{
    // GLOBAL: CL 0x0040a060
    static BOOL macros_0x1_flags_enabled = TRUE;
    tParsed_option *p;

    (void) option;
    if (!macros_0x1_flags_enabled) {
        return;
    }
    macros_0x1_flags_enabled = FALSE;
    for (p = gApp_data->field_0x0; p != NULL; p = p->next) {
        if ((p->field_0x4 & 1) && strcmp(p->arg_keyonly, "D") == 0) {
            FreeParsedOption(RemoveParsedOption(&gApp_data->field_0x0, p));
        }
    }
}

// FUNCTION: CL 0x00402a59
void OnArgumentLDorLDd(tParsed_option *option)
{
    static BOOL ld_argument_given = TRUE;

    (void) option;

    if (ld_argument_given) {
        tParsed_filepath *filepath;

        ld_argument_given = TRUE;
        gBuildingDLL = TRUE;

        for (filepath = gApp_data->field_0x10; filepath != NULL; filepath = filepath->next) {
            if (filepath->filetype == eFiletype_exp) {
                tParsed_option *implib_option = AllocateParsedOption("implib\\:", NULL, NULL, 0x0);
                tParsed_option *implied_option1 = CreateImpliedOptions("=implib\\::?", implib_option);
                tParsed_option *implied_option2 = FUN_00402092(&gApp_data->field_0x0, implied_option1, NULL);
                FreeParsedOptions(implied_option2);
                FreeParsedOption(implib_option);
                FreeParsedOptions(implied_option1);
                break;
            }
        }
    }
}

// FUNCTION: CL 0x00405df9
int GetTerminalHeight()
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
void PrintPaginatedFileAndExit(const char *path)
{
    char buffer[84];
    int line;
    FILE *f;
    int terminal_height;

    f = fopen(path, "r");
    if (f == NULL) {
        FatalError(2022, path);
    }
    terminal_height = INT_MAX;
    if (_isatty(STDOUT_FILENO)) {
        terminal_height = GetTerminalHeight();
    }
    if (terminal_height <= 0) {
        terminal_height = 1;
    }
    for (line = 0; fgets(buffer, 81, f) != NULL; line++) {
        if (line != 0 && line % terminal_height == 0) {
            WriteTextF(STDOUT_FILENO, GetErrorMessage(313));
            while (1) {
                int ch = getchar();
                if (ch == '\n' || ch == -1) {
                    break;
                }
            }
        }
        WriteTextF(STDOUT_FILENO, buffer);
    }
    fclose(f);
    exit(0);
}

// FUNCTION: CL 0x00405de2
void RedirectStdErrToStdOut()
{
    if (gRedirectStdErrToStdOut) {
        _dup2(STDOUT_FILENO, STDERR_FILENO);
    }
}

// FUNCTION: CL 0x0040330d
void FUN_0040330d(tApp_data *app_data)
{
    tFiletype_compiler_spec *stage_spec = app_data->compiler_stage_spec;
    tCompile_filetype filetype = app_data->field_0x20->filetype;
    int stage = app_data->compiler_stage;

    if (app_data->compiler_paths[filetype][stage] == NULL) {
        char *compiler_path = JoinPathInExeSearchPath(app_data->exeDirectory, stage_spec->compiler_filename);

        app_data->compiler_paths[filetype][stage] = compiler_path;
        if (stage_spec->error_filename != NULL) {
            app_data->error_paths[filetype][stage] =
                    JoinPathInExeSearchPath(GetFileDirectory(compiler_path), stage_spec->error_filename);
        }
    }
}

// FUNCTION: CL 0x00403705
tCompiler_input_file *AllocateCompilerInputFile(tParsed_filepath *parsed_file)
{
    tCompiler_input_file *result = SafeMalloc(sizeof(tCompiler_input_file));
    result->next = NULL;
    result->parsed_file = parsed_file;
    result->field_0x08 = 0;
    return result;
}

// FUNCTION: CL 0x004036b5
tCompiler_input_file *GetCompilerInputFiles(tApp_data *app_data)
{
    tCompiler_input_file *result = NULL;
    tCompiler_input_file *last_input = NULL;
    tParsed_filepath *parsed_filepath;
    for (parsed_filepath = app_data->field_0x10; parsed_filepath != NULL; parsed_filepath = parsed_filepath->next) {
        if (gFiletype_specs[parsed_filepath->filetype].stage == eInput_compiler) {
            tCompiler_input_file *compiler_input = AllocateCompilerInputFile(parsed_filepath);
            if (result != NULL) {
                last_input->next = compiler_input;
            } else {
                result = compiler_input;
            }
            last_input = compiler_input;
        }
    }
    if (last_input == result) {
        gBOOL_0040a02c = FALSE;
    }
    return result;
}

#ifdef WITH_MSPDB

// FUNCTION: CL 0x00401108
char ParsedOptionContainsCharOf(tParsed_option *option, char *needles)
{
    char *pos = strpbrk(option->field_0x8, needles);
    if (pos == NULL) {
        return '\0';
    } else {
        return *pos;
    }
}

// FUNCTION: CL 0x00403db1
int StringCompareCbfn(const void *lhs, const void *rhs)
{
    return strcmp(*(char **) lhs, *(char **) rhs);
}

// FUNCTION: CL 0x00403b70
char *FUN_00403b70(tApp_data *app_data)
{
    char *buffer1 = SafeMalloc(1024);
    char *buffer2 = SafeMalloc(1024);
    char **argv;
    int arg_i;
    tParsed_option *option;
    char *arg_string;
    char *arg_ptr;
    int count_arguments;
    size_t len;

    count_arguments = 0;
    if (app_data->includePaths != NULL && gOption_notX) {
        count_arguments += 1;
    }
    for (option = app_data->field_0x0; option != NULL; option = option->next) {
        if (ParsedOptionContainsCharOf(option, "Mm") != '\0') {
            count_arguments += 1;
        }
    }
    len = 0;
    argv = SafeMalloc(count_arguments * sizeof(char *));
    arg_i = 0;
    for (option = app_data->field_0x0; option != NULL; option = option->next) {
        char c = ParsedOptionContainsCharOf(option, "Mm");
        if (c != '\0') {
            char *arg_ptr;
            char *arg_value_ptr;

            gImplied_argval[0] = '-';
            arg_ptr = SafeStrCpyOrKeep(&gImplied_argval[1], option->arg_keyonly);
            arg_value_ptr = option->arg_value;
            if (arg_value_ptr != NULL) {
                if (c == 'm') {
                    if (_fullpath(buffer2, arg_value_ptr, 1024) == NULL) {
                        strcpy(buffer2, option->arg_value);
                    }
                    _mbslwr((unsigned char *) buffer2);
                    arg_value_ptr = buffer2;
                }
                EscapePath(buffer1, arg_value_ptr);
                SafeStrCpyOrKeep(arg_ptr, buffer1);
            }
            argv[arg_i++] = SafeStrDup(gImplied_argval);
            len += strlen(gImplied_argval) + 1;
        }
    }
    if (app_data->includePaths != NULL && gOption_notX) {
        size_t lenInclude = LengthOfEscapedPath(app_data->includePaths);
        char *incString = SafeMalloc(lenInclude + 6);
        strcpy(incString, "-inc=");
        EscapePath(&incString[5], app_data->includePaths);
        _mbslwr((unsigned char *) incString);
        len += lenInclude + 6;
        argv[arg_i] = incString;
    }
    qsort(argv, count_arguments, sizeof(char *), StringCompareCbfn);
    arg_string = SafeMalloc(len + 1);
    arg_ptr = arg_string;
    for (arg_i = 0; arg_i < count_arguments; arg_i++) {
        arg_ptr = SafeStrCpyOrKeep(arg_ptr, argv[arg_i]);
        *arg_ptr++ = ' ';
    }
#ifdef REMSVC_RECCMP
    arg_ptr[-1] = '\0';
#else
    arg_string[len] = '\0';
#endif
    for (arg_i = 0; arg_i < count_arguments; arg_i++) {
        SafeFree(argv[arg_i]);
    }
    SafeFree(argv);
    SafeFree(buffer2);
    SafeFree(buffer1);
    return arg_string;
}

// FUNCTION: CL 00403dc6
tCompiler_input_file *FUN_00403dc6(DWORD *arg1)
{
    (void) arg1;
    NOT_IMPLEMENTED();
}
#endif

// FUNCTION: CL 0x0040371e
tCompiler_input_file *FUN_0040371e(tApp_data *app_data, tCompiler_input_file *inputs, MRState *mr_state)
{
#ifdef WITH_MSPDB
    MREngine *engine;
    MREDriver *driver;
    int result_code;
    tCompiler_input_file *input;
    void **unk;
    char *arg_string;
#endif

    if (!gOption_Gm || !gMRE_enabled) {
        gMRE_enabled = FALSE;
        return inputs;
    }
#ifdef WITH_MSPDB
    if (!MREFOpenByName(&engine, gOption_Fd, &result_code, gImplied_argval, gOption_Brepro, TRUE)) {
        EmitWarningF(4028);
        gMRE_enabled = FALSE;
        return inputs;
    }
    unk = NULL;
    MREQueryMreDrv(engine, &driver);
    MREDrvOneTimeInit(driver);
    mr_state->field_0x00 = 0;
    mr_state->field_0x04 = 0;
    mr_state->field_0x08 = 0;
    mr_state->field_0x0c = 0;
    mr_state->field_0x10 = 0;
    app_data->field_0x18 = NULL;
    app_data->field_0x1c = &app_data->field_0x18;
    arg_string = FUN_00403b70(app_data);
    for (input = inputs; input != NULL; input = input->next) {
        tParsed_filepath *parsed_file = input->parsed_file;
        app_data->field_0x20 = parsed_file;
        RunOptionActions(app_data);
        input->field_0x0c = 0;
        if (unk != NULL) {
            *unk = &input->field_0x0c;
        } else {
            mr_state->field_0x04 = (DWORD *) &input->field_0x0c;
        }
        input->is_cpp = parsed_file->filetype == eFiletype_cxx || parsed_file->filetype == eFiletype_cpp;
        input->field_0x14 = parsed_file->path;
        input->field_0x18 = gOutputObjectFilepath;
        input->field_0x1c = arg_string;
        input->field_0x24 = gOption_FR;
        unk = (void **) &input->field_0x0c;
    }
    if (gMRE_enabled && MREDrvFFilesOutOfDate(driver, mr_state)) {
        inputs = FUN_00403dc6(mr_state->field_0x00);
    } else if (gMRE_enabled) {
        EmitWarningF(4028);
        gMRE_enabled = FALSE;
    }
    if (!MREDrvFRelease(driver) && gMRE_enabled) {
        EmitWarningF(4028);
        gMRE_enabled = FALSE;
    }
    if (!MREFClose(engine, gMRE_enabled) && gMRE_enabled) {
        EmitWarningF(4028);
        gMRE_enabled = FALSE;
    }
    return inputs;
#else
    (void) app_data;
    (void) mr_state;
    EmitWarningF(4028);
    gMRE_enabled = FALSE;
    return inputs;
#endif
}

// FUNCTION: CL 0x004038f0
tCompiler_input_file *FUN_004038f0(tApp_data *app_data, MRState *mr_state)
{
#ifdef WITH_MSPDB
    int result_code;
    MREngine *engine;
    MREDriver *driver;
#endif

    if (!gOption_Gm || !gMRE_enabled) {
        return NULL;
    }
#ifdef WITH_MSPDB
    if (mr_state->field_0x00 == 0 && mr_state->field_0x04 == 0 && mr_state->field_0x08 == 0) {
        return NULL;
    }
    if (!MREFOpenByName(&engine, gOption_Fd, &result_code, gImplied_argval, gOption_Brepro, TRUE)) {
        EmitWarningF(4028);
        gMRE_enabled = FALSE;
        return FUN_00403dc6(mr_state->field_0x04);
    }
    MREQueryMreDrv(engine, &driver);
    if (mr_state->field_0x00 != NULL) {
        NOT_IMPLEMENTED();
    }
    (void) app_data;
    NOT_IMPLEMENTED();
#else
    (void) app_data;
    (void) mr_state;
    EmitWarningF(4028);
    gMRE_enabled = FALSE;
    return NULL;
#endif
}

// FUNCTION: CL 0x00404069
tCompiler_input_file *ReverseCompilerInputFile(tCompiler_input_file *input_file)
{
    tCompiler_input_file *new_head;
    tCompiler_input_file *new_next;

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
char *ExtractFilename(char *dest, const char *path)
{
    char ext[256];
    char filename[256];

    _splitpath(path, NULL, NULL, filename, ext);
    _makepath(dest, "", "", filename, ext);
    return dest;
}

// FUNCTION: CL 0x00405039
size_t LengthOfEscapedPath(const char *path)
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
size_t LengthOfFormatedArgument(const char *text, tApp_data *app_data)
{
    char buffer[256];
    size_t len = 0;
    const char *current_file;
    tCompile_filetype current_filetype;
    if (app_data->field_0x20 == NULL) {
        current_file = "";
        current_filetype = eFiletype_none;
    } else {
        current_file = app_data->field_0x20->path;
        current_filetype = app_data->field_0x20->filetype;
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
                if (app_data->error_paths[current_filetype][app_data->compiler_stage] != NULL) {
                    len += LengthOfEscapedPath(app_data->error_paths[current_filetype][app_data->compiler_stage]);
                }
                break;
            case 'f':
                len += LengthOfEscapedPath(current_file);
                break;
            case 'b':
            case 'B':
                GetFileBasename(buffer, current_file);
                len += LengthOfEscapedPath(buffer);
                break;
            case 'm':
                len += 1024;
                break;
            case 't':
                len += LengthOfEscapedPath(app_data->tempPath);
                break;
            case 'x':
                RemoveExtension(buffer, gOutputExecutableFilepath);
                len += LengthOfEscapedPath(buffer);
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
char *EscapePath(char *dest, const char *path)
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
void ChronoTimeBefore()
{
    ftime(&gChronoBefore);
}

// FUNCTION: CL 0x00405b4d
void ChronoTimeAfter(const char *description)
{
    char buffer[8];
    int time_s;
    int time_ms;
    size_t len;

    WriteTextF(STDOUT_FILENO, "time(%s)=", description);
    ftime(&gChronoAfter);
    time_s = gChronoAfter.time - gChronoBefore.time;
    time_ms = gChronoAfter.millitm - gChronoBefore.millitm;
    if (time_ms < 0) {
        time_ms += 1000;
        time_s -= 1;
    }
    strcpy(buffer, "00");
    len = dtostr(time_ms, &buffer[2], 10);
    WriteTextF(STDOUT_FILENO, "%d.%ss\n", time_s, buffer + len - 1);
}

// FUNCTION: CL 0x004040c9
int FUN_004040c9(tApp_data *app_data)
{
    char *buffer1;
    char *buffer2;
    const char *exe_filepath;
    size_t len;
    int argc;
    tParsed_option *option;
    char **argv;
    char *arg_string;
    char **argv_ptr;
    char *arg_ptr;
    tFiletype_compiler_spec *compiler_stage_spec;
    tParsed_filepath *current_filepath;
    int result;

    gAction_performed = TRUE;
    buffer1 = SafeMalloc(1024);
    buffer2 = SafeMalloc(1024);
    compiler_stage_spec = app_data->compiler_stage_spec;
    current_filepath = app_data->field_0x20;
    exe_filepath = app_data->compiler_paths[current_filepath->filetype][app_data->compiler_stage];
    len = LengthOfEscapedPath(exe_filepath);
    argc = 0;
    for (option = app_data->field_0x0; option != NULL; option = option->next) {
        if (FUN_004010e8(option, compiler_stage_spec)) {
            len += LengthOfFormatedArgument(option->arg_keyonly, app_data) + 2;
            argc += 1;
            if (option->arg_value != NULL) {
                len += LengthOfFormatedArgument(option->arg_value, app_data) + 2;
                argc += 1;
            }
        }
    }
    if (app_data->includePaths != NULL && gOption_notX) {
        const char *ptr_include;
        len += LengthOfEscapedPath(app_data->includePaths) + 6;
        ptr_include = app_data->includePaths;
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
    argv = SafeMalloc((argc + 2) * sizeof(char *));
    arg_string = SafeMalloc(len);
    argv_ptr = argv;
    *argv_ptr++ = arg_string;
    EscapePath(buffer1, exe_filepath);
    arg_ptr = SafeStrCpyOrKeep(arg_string, buffer1);
    for (option = app_data->field_0x0; option != NULL; option = option->next) {
        if (FUN_004010e8(option, compiler_stage_spec)) {
            arg_ptr++;
            *argv_ptr++ = arg_ptr;
            if (!(option->field_0x4 & 0x8)) {
                *arg_ptr++ = compiler_stage_spec->field_0x11;
            }
            arg_ptr = SafeStrCpyOrKeep(arg_ptr, FormatParsedOptionValue(buffer1, option->arg_keyonly, app_data));
            if (option->arg_value != NULL) {
                if (!(option->field_0x4 & 0x4)) {
                    arg_ptr++;
                    *argv_ptr++ = arg_ptr;
                }
                EscapePath(buffer1, FormatParsedOptionValue(buffer2, option->arg_value, app_data));
                arg_ptr = SafeStrCpyOrKeep(arg_ptr, buffer1);
            }
        }
    }
    if (app_data->includePaths != NULL && gOption_notX && strchr("1P", compiler_stage_spec->field_0x10) != NULL) {
        const char *ptr_include = app_data->includePaths;
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
                    arg_ptr = SafeStrCpyOrKeep(&arg_ptr[1], "-I");
                    *argv_ptr++ = &arg_ptr[1];
                    *ptr_end = '\0';
                    EscapePath(buffer1, ptr_include);
                    *ptr_end = ';';
                    arg_ptr = SafeStrCpyOrKeep(&arg_ptr[1], buffer1);
                }
            }
            ptr_include = &ptr_end[1];
        }
        pos_non_whitespace = _mbsspn((unsigned char *) ptr_include, (unsigned char *) " \t");
        if (pos_non_whitespace < strlen(ptr_include)) {
            *argv_ptr++ = &arg_ptr[1];
            arg_ptr = SafeStrCpyOrKeep(&arg_ptr[1], "-I");
            *argv_ptr++ = &arg_ptr[1];
            EscapePath(buffer1, ptr_include);
            SafeStrCpyOrKeep(&arg_ptr[1], buffer1);
        }
    }
    *argv_ptr = NULL;
    if (gOption_bv) {
        char **ptr;

        WriteTextF(STDERR_FILENO, "`%s", exe_filepath);
        for (ptr = &argv[1]; *ptr != NULL; ptr++) {
            WriteTextF(STDERR_FILENO, " %s", *ptr);
        }
        WriteTextF(STDERR_FILENO, "'\n");
    }
    result = 0;
    if (!gOption_Bz) {
        int inheritEnv;

        if (gOption_Bt) {
            ChronoTimeBefore();
        }
        if (current_filepath->filetype == eFiletype_exe) {
            inheritEnv = 2;
        } else {
            inheritEnv = 0;
        }
        result = FUN_00405c21(inheritEnv, exe_filepath, compiler_stage_spec->extra_env, argv);
        if (gOption_Bt) {
            ChronoTimeAfter(exe_filepath);
        }
    }
    SafeFree(argv);
    SafeFree(arg_string);
    SafeFree(buffer2);
    SafeFree(buffer1);
    return result;
}

// FUNCTION: CL 0x00404080
int FUN_00404080(tFiletype_compiler_spec *filetype_compiler_specs, tApp_data *app_data, int (*exec)(tApp_data *))
{
    int i;

    for (i = 0; filetype_compiler_specs[i].compiler_filename != NULL; i++) {
        tFiletype_compiler_spec *spec = &filetype_compiler_specs[i];
        if (spec->field_0xc) {
            app_data->compiler_stage = i;
            app_data->compiler_stage_spec = spec;
            FUN_0040330d(app_data);
            gExit_failure = exec(app_data);
            if (gExit_failure) {
                return gExit_failure;
            }
        }
    }
    return gExit_failure;
}

// FUNCTION: CL 0x00403e26
unsigned int FUN_00403e26(tApp_data *app_data, tCompiler_input_file *input_file)
{
    char buffer[1024];
    int count_failed = 0;
    tFiletype_compiler_spec *input_compiler_spec = gFiletype_specs[input_file->parsed_file->filetype].compiler_specs;
    int count_stages = 0;
    int stage;
    int message_stage;
    bool do_stage_per_stage;

    for (stage = 0; input_compiler_spec[stage].compiler_filename != NULL; stage++) {
        if (input_compiler_spec[stage].field_0xc) {
            count_stages += 1;
        }
    }
    if (gOption_ZM && gBOOL_0040a02c && count_stages >= 2) {
        do_stage_per_stage = true;
        app_data->field_0x14 = input_file;
    } else {
        do_stage_per_stage = false;
        app_data->field_0x14 = NULL;
    }
    message_stage = 0;
    for (stage = 0;; stage++) {
        tFiletype_compiler_spec *stage_compiler_spec = &input_compiler_spec[stage];
        bool run_on_file = false;
        if (do_stage_per_stage) {
            if (stage_compiler_spec->field_0xc) {
                if (message_stage > 0) {
                    input_file = ReverseCompilerInputFile(input_file);
                    app_data->field_0x14 = input_file;
                }
                message_stage += 1;
                app_data->compiler_stage = stage;
                app_data->compiler_stage_spec = stage_compiler_spec;
                app_data->field_0x20 = input_file->parsed_file;
                if (message_stage == 1) {
                    if (gBOOL_0040a1bc) {
                        gBOOL_0040a1bc = FALSE;
                    } else {
                        WriteTextF(STDERR_FILENO, GetErrorMessage(331));
                    }
                } else if (message_stage == 2 && count_stages > 2) {
                    WriteTextF(STDERR_FILENO, GetErrorMessage(332));
                } else {
                    if (message_stage == count_stages) {
                        WriteTextF(STDERR_FILENO, GetErrorMessage(333));
                    }
                }
                run_on_file = true;
            }
        }
        if (!do_stage_per_stage || run_on_file) {
            tCompiler_input_file *current_input_file;
            for (current_input_file = input_file; current_input_file != NULL;
                    current_input_file = current_input_file->next) {
                if (!do_stage_per_stage || !current_input_file->field_0x08) {
                    tParsed_filepath *current_parsed_filepath = current_input_file->parsed_file;
                    app_data->field_0x20 = current_parsed_filepath;
                    RunOptionActions(app_data);
                    if (!do_stage_per_stage || message_stage < 2) {
                        WriteTextF(STDERR_FILENO, "%s\n", ExtractFilename(buffer, current_parsed_filepath->path));
                    }
                    if (do_stage_per_stage) {
                        FUN_0040330d(app_data);
                        gExit_failure = FUN_004040c9(app_data);
                    } else {
                        gExit_failure = FUN_00404080(input_compiler_spec, app_data, FUN_004040c9);
                    }
                    if (gExit_failure) {
                        count_failed += 1;
                        current_input_file->field_0x08 = 1;
                        if (do_stage_per_stage) {
                            FUN_00405483(TRUE);
                            if (do_stage_per_stage && message_stage != count_stages) {
                                continue;
                            }
                        }
                    } else if (do_stage_per_stage && message_stage != count_stages) {
                        continue;
                    }
                    if (gOutputObjectFilepath != NULL) {
                        tParsed_filepath *obj_parsed_path =
                                AllocateParsedFilepath(gOutputObjectFilepath, eFiletype_obj);
                        obj_parsed_path->next = current_parsed_filepath->next;
                        current_input_file->parsed_file->next = obj_parsed_path;
                    }
                    FUN_00405483(TRUE);
                }
            }
            if (!do_stage_per_stage) {
                app_data->field_0x14 = NULL;
                return count_failed;
            }
        }
        if (!do_stage_per_stage || stage_compiler_spec->compiler_filename == NULL) {
            app_data->field_0x14 = NULL;
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
    if (gOption_bv) {
        _write(STDERR_FILENO, text, len);
    }
}

// FUNCTION: CL 0x00404897
void CreateCOFFLinkerResponseFile(tApp_data *app_data)
{
    char *buffer1;
    char *buffer2;
    FILE *f;
    const tFiletype_compiler_spec *compiler_stage_spec;
    tParsed_option *option;
    tParsed_filepath *filepath;

    buffer1 = SafeMalloc(1024);
    buffer2 = SafeMalloc(1024);
    compiler_stage_spec = app_data->compiler_stage_spec;
    strcpy(buffer1, app_data->tempPath);
    strcat(buffer1, "lk");
    if (!gOption_Bz) {
        f = fopen(buffer1, "w");
        if (f == NULL) {
            FatalError(2018);
        }
    } else {
        f = NULL;
    }
    for (option = app_data->field_0x0; option != NULL; option = option->next) {
        if (FUN_004010e8(option, compiler_stage_spec)) {
            if (!(option->field_0x4 & 0x8)) {
                WriteF(f, "%c", compiler_stage_spec->field_0x11);
            }
            WriteF(f, "%s", FormatParsedOptionValue(buffer1, option->arg_keyonly, app_data));
            if (option->arg_value != NULL) {
                if (!(option->field_0x4 & 0x4)) {
                    WriteF(f, " ");
                }
                EscapePath(buffer1, FormatParsedOptionValue(buffer2, option->arg_value, app_data));
                WriteF(f, "%s", buffer1);
            }
            WriteF(f, "\n");
        }
    }
    for (filepath = app_data->field_0x10; filepath != NULL; filepath = filepath->next) {
        if (filepath->filetype == eFiletype_def) {
            EscapePath(buffer1, filepath->path);
            WriteF(f, "%cdef:%s\n", compiler_stage_spec->field_0x11, buffer1);
        }
    }
    for (filepath = app_data->field_0x10; filepath != NULL; filepath = filepath->next) {
        if (gFiletype_specs[filepath->filetype].stage == eInput_linker && filepath->filetype != eFiletype_def) {
            EscapePath(buffer1, filepath->path);
            WriteF(f, "%s\n", buffer1);
        }
    }
    if (f != NULL) {
        fclose(f);
    }
    SafeFree(buffer2);
    SafeFree(buffer1);
}

// FUNCTION: CL 0x004045d8
void FUN_004045d8(tApp_data *app_data)
{
    char *buffer1;
    char *buffer2;
    FILE *f;
    const tFiletype_compiler_spec *compiler_stage_spec;
    tParsed_filepath *filepath;
    tParsed_option *option;
    bool first;
    char *exePath;

    buffer1 = SafeMalloc(1024);
    buffer2 = SafeMalloc(1024);
    compiler_stage_spec = app_data->compiler_stage_spec;
    strcpy(buffer1, app_data->tempPath);
    strcat(buffer1, "lk");
    if (!gOption_Bz) {
        f = fopen(buffer1, "w");
        if (f == NULL) {
            FatalError(2018);
        }
    } else {
        f = NULL;
    }
    first = true;
    for (filepath = app_data->field_0x10; filepath != NULL; filepath = filepath->next) {
        if (filepath->filetype == eFiletype_obj || filepath->filetype == eFiletype_none) {
            if (!first) {
                WriteF(f, "+\n");
            }
            WriteF(f, "\"%s\"", filepath->path);
            first = false;
        }
    }
    FormatParsedOptionValue(buffer1, gOutputExecutableFilepath, app_data);
    exePath = SafeStrDup(buffer1);
    WriteF(f, "\n\"%s\"", exePath);
    WriteF(f, "\n\"%s\"", FormatMapPath(buffer1, exePath));
    first = true;
    for (filepath = app_data->field_0x10; filepath != NULL; filepath = filepath->next) {
        if (filepath->filetype == eFiletype_lib) {
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
    for (option = app_data->field_0x0; option != NULL; option = option->next) {
        if (FUN_004010e8(option, compiler_stage_spec)) {
            if (!first) {
                WriteF(f, " ");
            } else {
                first = false;
            }
            if (!(option->field_0x4 & 0x8)) {
                WriteF(f, "%c", compiler_stage_spec->field_0x11);
            }
            WriteF(f, "%s", FormatParsedOptionValue(buffer1, option->arg_keyonly, app_data));
            if (option->arg_value != NULL) {
                if (!(option->field_0x4 & 0x4)) {
                    WriteF(f, " ");
                }
                EscapePath(buffer1, FormatParsedOptionValue(buffer2, option->arg_value, app_data));
                WriteF(f, "%s", buffer1);
            }
        }
    }
    if (first) {
        WriteF(f, "\n");
    }
    first = true;
    for (filepath = app_data->field_0x10; filepath != NULL; filepath = filepath->next) {
        if (filepath->filetype == eFiletype_def) {
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
    SafeFree(exePath);
    SafeFree(buffer2);
    SafeFree(buffer1);
}

// FUNCTION: CL 0x00405c21
int FUN_00405c21(int inheritEnv, const char *cmdName, const char *cmd_env_name, char **argv)
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
            env_string = SafeMalloc(len_env);
            env_ptr = SafeStrCpyOrKeep(env_string, cmd_env_name);
            for (argv_ptr = &argv[1]; *argv_ptr != NULL; argv_ptr++) {
                env_ptr = SafeStrCpyOrKeep(env_ptr, *argv_ptr);
                *env_ptr++ = ' ';
            }
            *env_ptr = '\0';
            if (_putenv(env_string) != 0) {
                FatalError(2029, cmdName);
            }
            SafeFree(env_string);
        }
        break;
    case 1:
    case 2:
        break;
    default:
        FatalError(0);
        break;
    }
    _flushall();
    *_errno() = 0;
    gDisableControlHandler = TRUE;
    gConsoleInterrupted = FALSE;
    result = (int) _spawnvp(_P_WAIT, cmdName, (const char *const *) argv);
    gDisableControlHandler = FALSE;
    if (gConsoleInterrupted || (result >> 8) == -128) {
        ExitCL(4);
    }
    if (result < 0 && *_errno() != 0) {
        FatalError(2027, cmdName);
    }
    if (result != 0) {
        if (result == 525) {
            FatalError(2030, cmdName);
        }
        result = 2;
    }
    return result;
}

// FUNCTION: CL 0x00404471
int FUN_00404471(tApp_data *app_data)
{
    char buffer[2048];
    char *argument_string;
    const char *program_exe;
    char *arguments_ptr;
    tFiletype_compiler_spec *compiler_stage_spec;
    char **argv;
    int result;

    gAction_performed = TRUE;
    argument_string = SafeMalloc(1024);
    compiler_stage_spec = app_data->compiler_stage_spec;
    program_exe = app_data->compiler_paths[app_data->field_0x20->filetype][app_data->compiler_stage];
    EscapePath(argument_string, program_exe);
    arguments_ptr = SafeStrCpyOrKeep(buffer, argument_string);
    if (gOption_coff) {
        CreateCOFFLinkerResponseFile(app_data);
        arguments_ptr = SafeStrCpyOrKeep(arguments_ptr, " -link");
    } else {
        FUN_004045d8(app_data);
    }
    arguments_ptr[0] = ' ';
    arguments_ptr[1] = '\0';
    arguments_ptr = SafeStrCpyOrKeep(&arguments_ptr[1], "@");
    arguments_ptr = SafeStrCpyOrKeep(arguments_ptr, app_data->tempPath);
    SafeStrCpyOrKeep(arguments_ptr, "lk");
    if (strlen(buffer) > sizeof(buffer) - 1) {
        FatalError(0);
    }
    argv = CreateArgArray(buffer, 0);
    if (gOption_bv) {
        WriteTextF(STDERR_FILENO, "`%s'\n", buffer);
    }
    result = 0;
    if (!gOption_Bz) {
        if (gOption_Bt) {
            ChronoTimeBefore();
        }
        result = FUN_00405c21(1, program_exe, compiler_stage_spec->extra_env, argv);
        if (gOption_Bt) {
            ChronoTimeAfter(program_exe);
        }
    }
    SafeFree(argv);
    SafeFree(argument_string);
    return result;
}

// FUNCTION: CL 0x004034c2
void FUN_004034c2(tApp_data *app_data)
{
    unsigned int mre_result = 0;
    MRState mr_state;
    tCompiler_input_file *remaining_inputs;
    tParsed_filepath *next_linker_output;

    remaining_inputs = GetCompilerInputFiles(app_data);
    remaining_inputs = FUN_0040371e(app_data, remaining_inputs, &mr_state);
    for (;;) {
        if (remaining_inputs != NULL) {
            for (;;) {
                while (remaining_inputs != NULL) {
                    tFiletype_compiler_spec *filetype_compiler_spec;
                    tCompiler_input_file *next_input;
                    tCompiler_input_file *current_input;

                    filetype_compiler_spec = gFiletype_specs[remaining_inputs->parsed_file->filetype].compiler_specs;
                    remaining_inputs->parsed_file->field_0xe = 0;
                    next_input = remaining_inputs->next;
                    current_input = remaining_inputs;
                    while (next_input != NULL &&
                            gFiletype_specs[next_input->parsed_file->filetype].compiler_specs ==
                                    filetype_compiler_spec &&
                            current_input->parsed_file->field_0xe < 259) {
                        next_input->parsed_file->field_0xe = current_input->parsed_file->field_0xe + 1;
                        current_input = next_input;
                        next_input = next_input->next;
                    }
                    current_input->next = NULL;
                    mre_result |= FUN_00403e26(app_data, remaining_inputs);
                    remaining_inputs = next_input;
                }
                remaining_inputs = FUN_004038f0(app_data, &mr_state);
                if (remaining_inputs == NULL) {
                    break;
                }
            }
        }
        remaining_inputs = FUN_004038f0(app_data, &mr_state);
        if (remaining_inputs == NULL) {
            break;
        }
    }
    if (app_data->field_0x18 != NULL) {
        WriteTextF(STDERR_FILENO, GetErrorMessage(330));
        NOT_IMPLEMENTED();
#if 0
        item_0x18 = app_data->field_0x18;
        while (item_0x18 != NULL) {
            char buffer[1024];
            next_0x18 = NULL;
            if (item_0x18 != NULL) {
                next_0x18 = item_0x18->next;;
            }
            WriteTextF(STDERR_FILENO, "%s\n", ExtractFilename(buffer, GET_HEAD(item_0x18)->path));
            item_0x18->next = mr_state.field_0x0c;
            mr_state.field_0x0c = item_0x18;
            item_0x18 = next_0x18;
        }
#endif
    }
    if (mre_result != 0) {
        gExit_failure = mre_result;
        return;
    }

    app_data->field_0x20 = app_data->field_0x10;
    if (app_data->field_0x10 != NULL) {
        tParsed_filepath *parsed_filepath = app_data->field_0x10;
        while (parsed_filepath != NULL) {
            if (parsed_filepath->filetype == eFiletype_obj) {
                break;
            }
            parsed_filepath = parsed_filepath->next;
        }
        if (parsed_filepath != NULL) {
            app_data->field_0x20 = parsed_filepath;
        }
    }
    RunOptionActions(app_data);
    gExit_failure = FUN_00404080(gFiletype_link_compiler_specs, app_data, FUN_00404471);
    if (gExit_failure) {
        return;
    }
    if (gOutputExecutableFilepath != NULL) {
        tParsed_filepath *exe_path = AllocateParsedFilepath(gOutputExecutableFilepath, eFiletype_exe);
        exe_path->next = app_data->field_0x10->next;
        app_data->field_0x10->next = exe_path;
    }
    next_linker_output = app_data->field_0x10;
    for (;;) {
        tParsed_filepath *linker_output;
        for (;;) {
            linker_output = next_linker_output;
            if (linker_output == NULL) {
                return;
            }
            next_linker_output = linker_output->next;
            if (gFiletype_specs[linker_output->filetype].stage == eOutput_linker) {
                break;
            }
        }
        app_data->field_0x20 = linker_output;
        gExit_failure = FUN_00404080(gFiletype_specs[linker_output->filetype].compiler_specs, app_data, FUN_004040c9);
        if (gExit_failure) {
            return;
        }
    }
}

// #define DEBUG_CL
#ifdef DEBUG_CL
void DumpAppData()
{
    tParsed_option *opt;
    fflush(stderr);
    fflush(stdout);
    printf("gApp_data->field_0x0 = {\n");
    opt = gApp_data->field_0x0;
    for (int i = 0; opt != NULL; i++, opt = opt->next) {
        const char *q = opt->arg_value ? "'" : "";
        printf(" [%2d] = { key='%s', value=%s%s%s, field_0x8=%s},\n", i, opt->arg_keyonly, q, opt->arg_value, q,
                opt->field_0x8);
    }
    printf("}\n");
    printf("gApp_data->field_0x4 = {\n");
    opt = gApp_data->field_0x4;
    for (int i = 0; opt != NULL; i++, opt = opt->next) {
        const char *q = opt->arg_value ? "'" : "";
        printf(" [%2d] = { key='%s', value=%s%s%s, field_0x8=%s},\n", i, opt->arg_keyonly, q, opt->arg_value, q,
                opt->field_0x8);
    }
    printf("}\n");
}
#else
# define DumpAppData() \
     do { \
     } while (0)
#endif

// FUNCTION: CL 0x004017ff
int main(int argc, char *argv[])
{
#if 0
    setbuf(_p__iob() + 1, NULL);
    setbuf(_p__iob() + 2, NULL);
#endif
    const char *msc_ide_flags;
    const char *cl;
    const char *cl_;
    char **msc_ide_flags_args;
    int count_msc_ide_flags_args;
    char **cl_args;
    int count_cl_args;
    char **cl__args;
    int count_cl__args;
    tParsed_option *opt;
    tParsed_option *unkopt;
    tParsed_filepath *input_path;
    tCompile_filetype default_filetype;

    InstallConsoleHandlers();
    msc_ide_flags = getenv("_MSC_IDE_FLAGS");
    cl = getenv("CL");
    cl_ = getenv("_CL_");
    msc_ide_flags_args = CreateArgArray(msc_ide_flags, TRUE);
    count_msc_ide_flags_args = GetArgsArraySize((const char **) msc_ide_flags_args);
    cl_args = CreateArgArray(cl, TRUE);
    count_cl_args = GetArgsArraySize((const char **) cl_args);
    cl__args = CreateArgArray(cl_, TRUE);
    count_cl__args = GetArgsArraySize((const char **) cl__args);
    argv[0] = GetExecutableFilePath();
    InitAppPaths(argv[0], gApp_data);
    if (argc == 1 && count_cl_args == 0) {
        FatalUsageError();
    }
    if (!ArgumentsContainNologo(argv + 1, argc - 1) && !ArgumentsContainNologo(cl_args, count_cl_args) &&
            !ArgumentsContainNologo(cl__args, count_cl__args)) {
        gShouldPrintLogoString = FALSE;
        PrintLogoString();
    }
    ParseArguments(gBuiltInCompileOptions, GetArgsArraySize(gBuiltInCompileOptions));
    ParseArguments(gBuiltInCompileDefinitions, GetArgsArraySize(gBuiltInCompileDefinitions));
    for (opt = gApp_data->field_0x0; opt != NULL; opt = opt->next) {
        opt->field_0x4 |= 0x1;
    }
    for (opt = gApp_data->field_0x4; opt != NULL; opt = opt->next) {
        opt->field_0x4 |= 0x1;
    }
    gConsider_hat_options = FALSE;
    if (count_msc_ide_flags_args) {
        ParseArguments((const char **) msc_ide_flags_args, count_msc_ide_flags_args);
    }
    if (count_cl_args > 0) {
        ParseArguments((const char **) cl_args, count_cl_args);
    }
    if (argc > 1) {
        ParseArguments((const char **) &argv[1], argc - 1);
    }
    if (count_cl__args > 0) {
        ParseArguments((const char **) cl__args, count_cl__args);
    }
    if (gPrinted_cl) {
        WriteTextF(STDERR_FILENO, "\n");
    }
    FUN_00402bc0();
    DumpAppData();
    RunOptionActions(gApp_data);
    CreateTempDir(gApp_data);
    if (gPrintPaginatedClMessage) {
        PrintPaginatedFileAndExit(JoinPathInExeSearchPath(gApp_data->exeDirectory, "cl32.msg"));
    }
    for (unkopt = gUnknown_options; unkopt != NULL; unkopt = unkopt->next) {
        if (unkopt->arg_value != NULL) {
            char *joinedstr = SafeMalloc(strlen(unkopt->arg_keyonly) + 1 + strlen(unkopt->arg_value) + 1);
            SafeStrCpyOrKeep(SafeStrCpyOrKeep(joinedstr, unkopt->arg_keyonly), unkopt->arg_value);
            EmitWarningF(4002, joinedstr);
            SafeFree(joinedstr);
        } else {
            EmitWarningF(4002, unkopt->arg_keyonly);
        }
    }
    if (gApp_data->field_0x10 == NULL) {
        FatalError(2003);
    }
    if (gOption_bt == NULL) {
        default_filetype = eFiletype_none;
    } else {
        switch (*gOption_bt) {
        case 'C':
            default_filetype = eFiletype_c;
            break;
        case 'O':
            default_filetype = eFiletype_obj;
            break;
        case 'P':
            default_filetype = eFiletype_cpp;
            break;
        default:
            default_filetype = eFiletype_obj;
            break;
        }
    }
    for (input_path = gApp_data->field_0x10; input_path != NULL; input_path = input_path->next) {
        const tFiletype_compiler_spec *cspec;

        if (default_filetype != eFiletype_none && !input_path->field_0xc) {
            input_path->filetype = default_filetype;
            input_path->field_0xc = 1;
        } else if (input_path->filetype == eFiletype_none) {
            if (gUnknownFilesAreC) {
                input_path->filetype = eFiletype_c;
            } else {
                input_path->filetype = eFiletype_obj;
                EmitWarningF(4024, input_path->path);
            }
        }
        for (cspec = gFiletype_specs[input_path->filetype].compiler_specs; cspec->compiler_filename != NULL; cspec++) {
            if (cspec->field_0xc) {
                break;
            }
        }
        if (!cspec->field_0xc) {
            EmitWarningF(4027, input_path->path);
        }
    }
    RedirectStdErrToStdOut();
    FUN_004034c2(gApp_data);
    gApp_data->field_0x20 = NULL;
    if (!gAction_performed) {
        EmitWarningF(4021);
    }
    ExitCL(gExit_failure ? 2 : 0);
}
