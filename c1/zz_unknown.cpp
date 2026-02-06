#include "zz_unknown.h"

#include "error.h"
#include "globals.h"
#include "main.h"

#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif

#ifdef _WIN32
// GLOBAL: C1 0x0045c6fc
HANDLE gTerminalSignalSemaphore = NULL;
#endif

// GLOBAL: C1 0x0045cbb8
unsigned char *pMacroActEnd = NULL;

// GLBOAL: C1 0x0045cbc0
unsigned char *pMacroExpEnd = NULL;

// FUNCTION: C1 0x00445ac1
void OnTerminalSignal(int)
{
#ifdef _WIN32
    if (gTerminalSignalSemaphore != NULL) {
        ExitThread(0);
    }
    gTerminalSignalSemaphore = CreateSemaphoreA(NULL, 0, 1, NULL);
    if (gTerminalSignalSemaphore == NULL) {
        ExitThread(0x8000);
    }
    HandlingControlC = TRUE;
    if (ExecutionState != CES_Done) {
        if (WaitForSingleObject(gTerminalSignalSemaphore, 4000) == WAIT_TIMEOUT) {
            int i = 0;

            WriteStdErr("Compiler terminating.  Please wait.");
            for (i = 0; i < 30; i++) {
                if (ExecutionState == CES_Done) {
                    break;
                }
                if (WaitForSingleObject(gTerminalSignalSemaphore, 2000) != WAIT_TIMEOUT) {
                    break;
                }
                WriteStdErr(".");
            }
            WriteStdErr(" Abort complete.\n");
            if (i >= 30) {
                ExitProcess(0x8000);
            }
        }
    }
    CloseHandle(gTerminalSignalSemaphore);
    gTerminalSignalSemaphore = NULL;
#else
    NOT_IMPLEMENTED();
#endif
}

// FUNCTION: C1 0x0041934f
void FUN_0041934f()
{
    // empty
}

// FUNCTION: C1 0x0041f0b2
void FUN_0041f0b2()
{
    // empty
}

// FUNCTION: C1 0x004253ce
void __fastcall WriteStdErr(const char *text)
{
    fwrite(text, strlen(text), 1, stderr);
}

// FUNCTION: C1 0x0041a6eb
unsigned char * __fastcall PreAllocateMemory(size_t reserveSize, size_t commitSize)
{
#ifdef _WIN32
    LPVOID reserveAddr = VirtualAlloc(NULL, reserveSize, MEM_RESERVE, PAGE_READWRITE);
    if (reserveAddr == NULL) {
        fatal_varargs(C1060);
    }
    unsigned char *commitAddr = (unsigned char *)VirtualAlloc(reserveAddr, commitSize, MEM_COMMIT, PAGE_READWRITE);
    if (commitAddr == NULL) {
        fatal_varargs(C1060);
    }
    return commitAddr;
#else
    NOT_IMPLEMENTED();
#endif
}

// FUNCTION: C1 0x0041f0ca
void CleanupMemory() {
    NOT_IMPLEMENTED();
}
