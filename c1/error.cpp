#include "error.h"

#include "decomp.h"
#include "zz_diagnostic.h"
#include "globals.h"
#include "main.h"
#include "portable.h"
#include "zz_unknown.h"

#include <stdarg.h>
#include <string.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

// GLOBAL: C1 0x00469208
char gError_message_buffer[256];

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
// long IOGlobalVal

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
// int __cdecl fatal_io_CRT(int, int, unsigned char *)

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
    ReleaseEverythingUponError();
    Nerrors += 1;
    exit(Nerrors);
}

// FUNCTION: MSVC5_C1 0x0003c090
// ?ActualWarnLevel@@YAHHH@Z
// int __cdecl ActualWarnLevel(int, int)

// FUNCTION: MSVC5_C1 0x0003c100
// ?warning@@YAXHHZZ
// void __cdecl warning(int, int, ...)

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
void message(int category, int code, char *format, va_list ap)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x0003c4d0
// ?format@@YAHPAD0HZZ
// int __cdecl format(char *, char *, int, ...)

// FUNCTION: MSVC5_C1 0x0003c4f0
// ?do_format@@YAHPADPBDH0@Z
// int __cdecl do_format(char *, char const *, int, char *)

// FUNCTION: MSVC5_C1 0x0003ca50
// ?GetWarnLevel@@YA?AW4warn_t@@I@Z
// enum warn_t __cdecl GetWarnLevel(unsigned int)

