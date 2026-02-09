#ifndef CL_UTIL_H
#define CL_UTIL_H

#include "decomp.h"

#include <stddef.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

extern char *basename(char *buffer, const char *path);
extern char *filename(char *dest, const char *path);
extern char *pathname(char *buffer, const char *path);

extern const char *gobblewhite(const char *text);
extern char *concat(char *str1, const char *str2);
extern char *concatmeta(char *dest, const char *format);
extern char *append(char *str1, const char *str2);
extern char *catinate(char *str1, char *str2);

extern size_t strqlen(const char *path);
extern char *strqcpy(char *dest, const char *path);

extern const char *strrchars(const char *text, const char *needles);

extern char **sztoszv(const char *text, bool32 cleanUpSlash);

extern void rm_il(bool32 arg1);
extern void rm_one_il(int index);

extern void done(int exitcode);

//extern size_t l2a(unsigned long number, char *dest, int radix);
extern void print(int stream, const char *format, ...);
extern char *format(size_t *len, const char *format, va_list ap);
extern void vprint(int stream, const char *format, va_list ap);
extern void echoprintf(FILE *stream, const char *format, ...);

extern void help(const char *path);

//extern const char *GetMessageInFile(const char *path, int code);
extern void cmderr(int code, ...);
extern void cmdwarn(int code, ...);
extern const char *get_message(int code);

extern void starttiming(void);
extern void endtiming(const char *description);

extern void *xnew(size_t size);
extern void xfree(void *ptr);
extern char *xstrdup(const char *str);

#endif
