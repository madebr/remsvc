#pragma once

#ifdef _WIN32
#include <io.h>
#include <process.h>
#endif
#include <stdio.h>

#ifndef STDOUT_FILENO
# define STDOUT_FILENO 1
#endif

#ifndef STDERR_FILENO
# define STDERR_FILENO 2
#endif

#ifndef R_OK
# define R_OK 4
#endif

#ifndef _P_WAIT
# define _P_WAIT 0
#endif

#ifndef REMSVC_RECCMP
#include <sys/timeb.h>

#define timeb __timeb32
#define ftime _ftime32
#endif
