#include "os.h"

#include "main.h"
#include "util.h"

#ifdef _WIN32
#include <io.h>
#else
#include <limits.h>
#endif

// GLOBAL: CL 0x0040afa8
struct timeb Endtime;

// GLOBAL: CL 0x0040afb8
struct timeb Starttime;

// GLOBAL: CL 0x0040afc4
bool32 GotCtrlC;

// GLOBAL: CL 0x0040afc8
bool32 Spawning;

// FUNCTION: CL 0x00405c21
int execute(driver_phases phase, const char *cmdName, const char *cmd_env_name, char **argv)
{
    int result;

    switch (phase) {
    case PHASE_COMPILE:
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
    case PHASE_LINK:
    case PHASE_POSTPROCESS:
        break;
    default:
        cmderr(0);
        break;
    }
#ifdef _WIN32
    _flushall();
#else
    fflush(stdout);
#endif
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

#ifdef _WIN32
// FUNCTION: CL 0x00405db3
static bool32 WINAPI NT_handling_function(DWORD CtrlType)
{
    (void) CtrlType;
    GotCtrlC = TRUE;
    if (!Spawning) {
        SetConsoleCtrlHandler(NULL, TRUE);
        done(4);
    }
    return 1;
}
#endif

// FUNCTION: CL 0x00405da5
void OS_Init()
{
#ifdef _WIN32
    SetConsoleCtrlHandler(NT_handling_function, TRUE);
#endif
}

// FUNCTION: CL 0x00405de2
void RedirectStdErrToStdOut()
{
    if (RedirStderr) {
        _dup2(STDOUT_FILENO, STDERR_FILENO);
    }
}

// FUNCTION: CL 0x00405df9
int screen_length()
{
#ifdef _WIN32
    HANDLE conHandle;
    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
    bool32 success;
    int height;

    conHandle = CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, 0, NULL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, NULL);
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
#else
    return INT_MAX;
#endif
}
