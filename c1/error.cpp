#include "error.h"

#include "decomp.h"
#include "zz_diagnostic.h"
#include "globals.h"
#include "main.h"
#include "p0io.h"
#include "portable.h"
#include "Token_IO.h"
#include "zz_unknown.h"

#include <stdarg.h>
#include <string.h>

#ifdef _WIN32
#include <io.h>
#else
#include <errno.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#endif

// GLOBAL: C1 0x00469208
char gError_message_buffer[256];

// GLOBAL: C1 0x00466500
FILE *gFile_er = NULL;

// GLOBAL: C1 0x004662c0
FILE *gFile_lp = NULL;

// GLOBAL: C1 0x00460a50
bool32 gWrite_er = FALSE;

// GLOBAL: MSVC5_C1 0x000015f8
// ?__MSGTAB@@3PAU_message@@A
// struct _message *__MSGTAB

// GLOBAL: MSVC5_C1 0x00004e2c
// ??_C@_09EMHG@?4?2error?4c?$AA@
// ".\\error.c"

// GLOBAL: MSVC5_C1 0x00004e38
// ??_C@_0BF@OIHI@fatal?5error?5C1063?3?$AN?6?$AA@
// "fatal error C1063:\r\n"

// GLOBAL: MSVC5_C1 0x00004e50
// ??_C@_09HOOG@?$CFs?5?$CFc?$CFd?3?5?$AA@
// "%s %c%d: "

// GLOBAL: MSVC5_C1 0x00004e5c
// ??_C@_09BIJJ@?$CFs?$CI?$CFd?$CJ?5?3?5?$AA@
// "%s(%d) : "

// GLOBAL: MSVC5_C1 0x00007e58
// ?IOGlobalVal@@3JA
// GLOBAL: C1 0x00469160
int IOGlobalVal = 0;

// GLOBAL: MSVC5_C1 0x00007e60
// ?Errbuff@@3PADA
// char *Errbuff

// FUNCTION: MSVC5_C1 0x0003bd60
// ?__NMSG_FIND@@YAPADI@Z
// char * __cdecl __NMSG_FIND(unsigned int)

// FUNCTION: MSVC5_C1 0x0003bd90
// ?preloadMessages@@YAXXZ
// void __cdecl preloadMessages(void)

// FUNCTION: MSVC5_C1 0x0003bdf0
// ?__NMSG_TEXT@@YAPADI@Z
// char * __cdecl __NMSG_TEXT(unsigned int)

// FUNCTION: MSVC5_C1 0x0003be20
// ?error@@YAXHZZ
// void __cdecl error(int, ...)

// FUNCTION: MSVC5_C1 0x0003be50
// ?close_file@@YAHPAU_iobuf@@@Z
// int __cdecl close_file(struct _iobuf *)

// FUNCTION: MSVC5_C1 0x0003be70
// ?errorVA@@YAXHPAD@Z
// void __cdecl errorVA(int, char *)

// FUNCTION: MSVC5_C1 0x0003bee0
// ?get_err@@YGPADH@Z
// char * __stdcall get_err(int)
// static

// FUNCTION: MSVC5_C1 0x0003bf10
// ?fatal_io_CRT@@YAHHHPAE@Z
// FUNCTION: C1 0x00448160
int fatal_io_CRT(FatalNumber fatalCode, int category, const char *text)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0044810e
int __fastcall fatal_io_CRT_position(FatalNumber code,int category,const char *text, const char *file, int lineno)
{
    if (ExecutionState != CES_ErrorCleanup && ExecutionState != CES_AbortCleanup) {
        if (text == NULL) {
            text = "";
        }
        const char *msg;
#ifdef _WIN32
        msg = _strerror(NULL);
#else
        msg = strerror(errno);
#endif
        fatal_varargs(code, category,text, msg, file, lineno);
    }
    return 0;
}
// FUNCTION: MSVC5_C1 0x0003bf60
// ?fatal_io_Win32@@YAHHHPAE@Z
// int __cdecl fatal_io_Win32(int, int, unsigned char *)

// FUNCTION: MSVC5_C1 0x0003bf80
// ?fatal_io_HRESULT@@YAHKHHPAE@Z
// int __cdecl fatal_io_HRESULT(unsigned long, int, int, unsigned char *)

// FUNCTION: MSVC5_C1 0x0003bfc0
// ?fatal@@YAHH@Z
// FUNCTION: C1 0x0043f49e
void fatal(FatalNumber code) {
    fatal_varargs(code);
}

// FUNCTION: MSVC5_C1 0x0003bfd0
// ?GaspAndDie@@YAXH@Z
// FUNCTION: C1 0x0044821d
void GaspAndDie(bool32 showMessage) {
    if (showMessage) {
        // STRING: C1 0x00456fa8
        strcpy(gError_message_buffer, "fatal error C1063:\r\n");
        write(STDOUT_FILENO, gError_message_buffer, strlen("fatal error C1063:\r\n"));
    }
    CleanupMemory();
    ExitProcess(3);
}

// FUNCTION: MSVC5_C1 0x0003c020
// ?fatal_varargs@@YAHHZZ
// C1: FUNCTION 0x00448257
void fatal_varargs(FatalNumber code, ...)
{
    va_list ap;

    limit_recursion(CES_ErrorCleanup);
    va_start(ap, code);
    message(1000, code, GetDiagnosticString(1000 + code, FALSE), ap);
    va_end(ap);
    ErrorCleanup();
    Nerrors += 1;
    exit(Nerrors);
}

// FUNCTION: MSVC5_C1 0x0003c090
// ?ActualWarnLevel@@YAHHH@Z
// int __cdecl ActualWarnLevel(int, int)

// FUNCTION: MSVC5_C1 0x0003c100
// ?warning@@YAXHHZZ
// FUNCTION: C1 0x00413697
void warning(int, int, ...)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x0003c270
// ?message_continuation@@YAXHZZ
// void __cdecl message_continuation(int, ...)

// FUNCTION: MSVC5_C1 0x0003c320
// ?OutputDiagnosticString@@YAXPAD@Z
// void __cdecl OutputDiagnosticString(char *)
// static

// FUNCTION: MSVC5_C1 0x0003c380
// ?message@@YAXHHPAD0@Z
// FUNCTION: C1 0x004482a6
void message(int category, int code, const char *format_str, va_list ap)
{
    char buffer[2048];

    char *ptr_message = buffer;
    if (tokenInputStack.curPos.line > 0 && tokenInputStack.curPos.stream != NULL) {
        format(buffer, "%Fs(%ld) : ", sizeof(buffer), tokenInputStack.curPos.GetFilename());
        ptr_message = buffer + strlen(buffer);
    }
    if (category != 0) {
        const char *category_str;
        if (category == 1000) {
            category_str = GetDiagnosticHelpString(315);
        } else if (category == 2000) {
            category_str = GetDiagnosticHelpString(314);
        } else if (category == 4000) {
            category_str = GetDiagnosticHelpString(313);
        }
        ptr_message += format(ptr_message, "%s %c%d: ", buffer + sizeof(buffer) - ptr_message, category_str, 'C', category + code);
    }
    do_format(ptr_message, format_str, buffer + sizeof(buffer) - ptr_message, ap);
    fwrite(buffer, strlen(buffer), 1, stderr);
    fwrite("\n", 1, 1, stderr);
    if (gWrite_er != 0 && gFile_er != NULL) {
        fwrite(buffer, strlen(buffer), 1, stderr);
        fwrite("\n", 1, 1, stderr);
        fflush(gFile_er);
    }
}

// FUNCTION: MSVC5_C1 0x0003c4d0
// ?format@@YAHPAD0HZZ
// FUNCTION: C1 0x00415443
int format(char *buffer, const char *format_str, size_t buffer_size, ...)
{
    va_list ap;
    int result;

    va_start(ap, buffer_size);
    result = do_format(buffer, format_str, buffer_size, ap);
    va_end(ap);
    return result;
}

#include "util.h"

struct tStruct_0045c6c0 {
    undefined4 id;
    void *field_0x04;
    undefined4 field_0x08;
    undefined4 field_0x0c;
    size_t capacity;
};

// GLOBAL: C1 0x0045c6c0
tStruct_0045c6c0 *gPTR_0045c6c0;

// GLOBAL: C1 0x0045c6c4
int gINT_0045c6c4 = 0;

// GLOBAL: C1 0x0045c6c8
uint16_t gUSHORT_0045c6c8 = 100;

// GLOBAL: C1 0x0045c55c
int gINT_0045c55c = 0;

// FUNCTION: C1  0x00415461
undefined4  FUN_00415461()
{
    int i;
    int found_index = -1;
    for (i = 0; i < gINT_0045c6c4; i++) {
        if (gPTR_0045c6c0[i].id == 0) {
            found_index = i;
        }
    }
    if (found_index == -1) {
        if (gPTR_0045c6c0 == NULL) {
            gPTR_0045c6c0 = (tStruct_0045c6c0 *)xnew(64 * sizeof(tStruct_0045c6c0));
        } else {
            gPTR_0045c6c0 = (tStruct_0045c6c0 *)xrealloc(gPTR_0045c6c0, (gINT_0045c6c4 + 64) * sizeof(tStruct_0045c6c0));
        }
        if (gPTR_0045c6c0 == NULL) {
            fatal_varargs(C1060);
        }
        memset(&gPTR_0045c6c0[gINT_0045c6c4], 0, 64 * sizeof(tStruct_0045c6c0));
        found_index = gINT_0045c6c4;
        gINT_0045c6c4 += 64;
    }
    tStruct_0045c6c0 *item = &gPTR_0045c6c0[found_index];
    if (item->field_0x04 == NULL) {
        item->capacity = 128;
        item->field_0x04 = xnew(128);
    }
    item->id = gUSHORT_0045c6c8;
    gUSHORT_0045c6c8 += 1;
    item->field_0x08 = 0x40;
    item->field_0x0c = 0x41;
    memset(item->field_0x04, 0, item->capacity);
    return item->id;
}

// FUNCTION: C1 0x00415414
void FUN_00415414()
{
    gINT_0045c55c -= 0;
    if (gINT_0045c55c == 0) {
        int i;
        for (i = 0; i < gINT_0045c6c4; i++) {
            gPTR_0045c6c0[i].id = 0;
        }
    }
}

// FUNCTION: C1 0x0041545b
undefined4 FUN_0041545b()
{
    gINT_0045c55c += 1;
    return FUN_00415461();
}

// FUNCTION: MSVC5_C1 0x0003c4f0
// ?do_format@@YAHPADPBDH0@Z
// FUNCTION: C1 0x0041517d
int do_format(char *buffer, char const *format_str, size_t buffer_size, va_list ap)
{
    if (format_str == NULL) {
        return 0;
    }
    size_t buffer_size_left = buffer_size;
    if (buffer_size == (size_t)-1) {
        buffer_size_left = SIZE_MAX;
    }
    FUN_0041545b();
    char *ptr_write = buffer;
    const char *ptr_format = format_str;
    while (*ptr_format != '\0') {
        if (*ptr_format == '%') {
            int radix;
            int format_long = 0;
            bool32 format_continue = TRUE;
            char local_buffer[64];
            const char *str;
            size_t len;
            ptr_format++;
            while (format_continue) {
                switch (*ptr_format) {
                case '$':
                    NOT_IMPLEMENTED();
                    break;
                case 'D':
                case 'U':
                case 'X':
                    radix = *ptr_format == 'X' ? 16 : 10;
                    if (*ptr_format == 'U') {
                        uint64_t u64 = va_arg(ap, uint64_t);
#ifdef _WIN32
                        _ui64toa(u64, local_buffer, radix);
#else
                        sprintf(local_buffer, "%" PRIu64, u64);
#endif
                    } else {
                        int64_t i64 = va_arg(ap, int64_t);
#ifdef _WIN32
                        _i64toa(i64, local_buffer, radix);
#else
                        sprintf(local_buffer, "%" PRId64, i64);
#endif
                    }
                    len = strlen(local_buffer);
                    strncpy(ptr_write, local_buffer, len + 1);
                    ptr_write += len;
                    ptr_format++;
                    format_continue = FALSE;
                    break;
                case 'F':
                    ptr_format++;
                    break;
                case 'c':
                    *ptr_write++ = va_arg(ap, int);
                    ptr_format++;
                    format_continue = FALSE;
                    break;
                case 'd':
                case 'u':
                case 'x':
                    radix = *ptr_format == 'X' ? 16 : 10;
                    if (*ptr_format == 'U') {
                        unsigned int u32 = va_arg(ap, unsigned int);
#ifdef _WIN32
                        _ui64toa(u32, local_buffer, radix);
#else
                        sprintf(local_buffer, "%" PRIu32, u32);
#endif
                    } else {
                        int i32 = va_arg(ap, int);
#ifdef _WIN32
                        _i64toa(i32, local_buffer, radix);
#else
                        sprintf(local_buffer, "%" PRId32, i32);
#endif
                    }
                    len = strlen(local_buffer);
                    strncpy(ptr_write, local_buffer, len + 1);
                    ptr_write += len;
                    ptr_format++;
                    format_continue = FALSE;
                    break;
                case 'l':
                    format_long = 1;
                    ptr_format++;
                    break;
                case 's':
                    str = va_arg(ap, const char *);
                    len = strlen(str);
                    strncpy(ptr_write, str, len + 1);
                    ptr_write += len;
                    ptr_format++;
                    format_continue = FALSE;
                    break;
                default:
                    *ptr_write = *ptr_format++;
                    format_continue = FALSE;
                    break;
                }
            }
        } else {
            *ptr_write++ = *ptr_format++;
        }
    }
    FUN_00415414();
    if (buffer_size_left <= 0 && buffer_size > 0) {
        strcpy(ptr_write - 4, "...");
    } else {
        *ptr_write = '\0';
    }
    return ptr_write - buffer;
}

// FUNCTION: MSVC5_C1 0x0003ca50
// ?GetWarnLevel@@YA?AW4warn_t@@I@Z
// enum warn_t __cdecl GetWarnLevel(unsigned int)

