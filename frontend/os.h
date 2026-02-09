#ifndef CL_OS_H
#define CL_OS_H

#include "types.h"

#include <sys/timeb.h>

#include "portable.h"

extern struct timeb Endtime;
extern struct timeb Starttime;
extern bool32 GotCtrlC;
extern bool32 Spawning;

extern int execute(driver_phases phase, const char *cmdName, const char *cmd_env_name, char **argv);
extern void OS_Init();

extern void RedirectStdErrToStdOut(void);
extern int screen_length(void);

#endif
