#pragma once

#ifdef _WIN32
#include <io.h>
#include <process.h>
#define PATH_JOIN_CHAR '\\'
#else
#include <errno.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#define PATH_JOIN_CHAR '/'
#endif
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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

#ifdef _WIN32
#define timeb __timeb32
#define ftime _ftime32
#else
#define timeb portable_timeb
#define ftime portable_ftime

#define _MAX_DRIVE 1
#define _MAX_PATH 260
#define _MAX_DIR 260

struct portable_timeb {
    uint64_t time;
    uint16_t millitm;
};

static int portable_ftime(struct portable_timeb *tb) {
    struct timespec ts;
    int result = clock_gettime(CLOCK_MONOTONIC, &ts);
    tb->time = ts.tv_sec;
    tb->millitm = ts.tv_nsec / 1000000;
    return result;
}

#define _access access
#define _dup2 dup2
#define _isatty isatty
#define _ismbcdigit isdigit
#define _putenv putenv
#define _unlink unlink
#define _stricmp strcasecmp

static inline void _splitpath(const char *path, char *out_drive, char *out_directory, char *out_stem, char *out_extension) {
    if (out_drive != NULL) {
        out_drive[0] = '\0';
    }
    const char *begin_filename = strrchr(path, '/');
    if (begin_filename == NULL) {
        begin_filename = path;
    } else {
        begin_filename += 1;
    }
    if (out_directory != NULL) {
        if (begin_filename == path) {
            out_directory[0] = '\0';
        } else {
            strncpy(out_directory, path, begin_filename - path - 1);
            out_directory[begin_filename - path - 1] = '\0';
        }
    }
    const char *end_stem = strrchr(begin_filename, '.');
    if (out_stem != NULL) {
        if (end_stem == NULL) {
            strcpy(out_stem, begin_filename);
        } else {
            strncpy(out_stem, begin_filename, end_stem - begin_filename);
            out_stem[end_stem - begin_filename] = '\0';
        }
    }
    if (out_extension != NULL) {
        if (end_stem == NULL) {
            out_extension[0] = '\0';
        } else {
            strcpy(out_extension, end_stem);
        }
    }
}

static inline void _makepath(char *path, const char *drive, const char *dir, const char *fname, const char *ext) {
    path[0] = '\0';
    if (drive) {
        strcpy(path, drive);
        path += strlen(drive);
    }
    if (dir) {
        strcpy(path, dir);
        path += strlen(dir);
        if (*dir && (fname || ext)) {
            *path++ = '/';
        }
    }
    if (fname) {
        strcpy(path, fname);
        path += strlen(path);
    }
    if (ext) {
        strcpy(path, ext);
    }
}

static inline size_t _mbclen(const unsigned char *c) {
    return strlen((const char *)c);
}

static inline unsigned char *_mbsrchr(unsigned char *str, unsigned int c) {
    return (unsigned char *) strrchr((char *)str, c);
}

static inline int _mbsncmp(const unsigned char *string1, const unsigned char *string2, size_t count) {
    return strncmp((const char *)string1, (const char *)string2, count);
}

static inline void _mbccpy(unsigned char *dest, const unsigned char *src) {
    strcpy((char *)dest, (const char *)src);
}

static inline size_t _mbsspn(const unsigned char *str, const unsigned char *strCharSet) {
    return strspn((const char *)str, (const char *)strCharSet);
}

static inline unsigned char *_mbsupr(unsigned char *str) {
    unsigned char *result = str;
    while (*str) {
        int c = toupper(*str);
        *str++ = c;
    }
    return result;
}

static inline int _ismbcspace(unsigned int c) {
    return isspace(c);
}

static int * _errno() {
    return &errno;
}

static unsigned char * _mbsinc(unsigned char *current) {
    current++;
    return current;
}

static unsigned char * _mbsdec(unsigned char *start, unsigned char *current) {
    current--;
    if (current < start) {
        current = start;
    }
    return current;
}

static inline unsigned char *_mbschr(unsigned char *str, unsigned int c) {
    return (unsigned char *) strchr((char *) str, c);
}

static inline char * _mktemp(char *templ) {
    int result = mkstemp(templ);
    if (result == -1) {
#if 0
        /* Always fails on my system? */
        return NULL;
#endif
    }
    return templ;
}

static inline char * _strdup(const char *str) {
    return strdup(str);
}

static inline int _ismbblead(int c) {
    return 0;
}

static inline const unsigned char *_mbsstr(const unsigned char *str, const unsigned char *strSearch) {
    return (unsigned char *)strstr((const char *)str, (const char *)strSearch);
}

static inline intptr_t _spawnvp(int mode, const char *cmdname, const char * const *argv) {
    fflush(stdout);
    pid_t p = fork();
    if (p == 0) {
        execvp(cmdname, (char * const *)argv);
        exit(0);
        abort();
    }
    int status = -1;
    if (mode == _P_WAIT) {
        int waitpid_result = waitpid(p, &status, 0);
        if (waitpid_result != p) {
            return -1;
        }
    } else {
        abort();
    }
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        int signal = WTERMSIG(status);
        return -256 - signal;
    } else {
        return -1;
    }
}

static inline intptr_t _spawnv(int mode, const char *cmdname, const char *const *argv) {
    return _spawnvp(mode, cmdname, argv);
}

static inline char *portable_pgmptr() {
    static char path[1024];
    if (readlink("/proc/self/exe", path, sizeof(path)) == -1) {
        strcpy(path, "recl");
    }
    return path;
}
#define _pgmptr portable_pgmptr()

#endif
#endif
