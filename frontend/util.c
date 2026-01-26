#include "util.h"

#include "forms.h"
#include "main.h"
#include "os.h"
#include "types.h"

#include <limits.h>
#include <mbstring.h>
#include <stdbool.h>
#include <string.h>

#include "portable.h"

// FUNCTION: CL 0x00404e41
char *basename(char *buffer, const char *path)
{
    _splitpath(path, NULL, NULL, buffer, NULL);
    return buffer;
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

// FUNCTION: CL 0x00404efe
const char *gobblewhite(const char *text)
{
    while (*text != '\0' && _ismbcspace(*text)) {
        text = (char *) _mbsinc((unsigned char *) text);
    }
    return text;
}

// FUNCTION: CL 0x00404f2e
char *concat(char *str1, const char *str2)
{
    if (str2 != NULL) {
        strcat(str1, str2);
    }
    return str1 + strlen(str1);
}

// FUNCTION: CL 0x00404f55
char *concatmeta(char *dest, const char *fmt)
{
    dest = dest + strlen(dest);
    if (fmt != NULL) {
        while (*fmt != '\0') {
            _mbccpy((unsigned char *) dest, (unsigned char *) fmt);
            dest = (char *) _mbsinc((unsigned char *) dest);
            if (_mbsncmp((unsigned char *) fmt, (unsigned char *) "%", 1) == 0) {
                _mbccpy((unsigned char *) dest, (unsigned char *) fmt);
                dest = (char *) _mbsinc((unsigned char *) dest);
            }
            fmt = (char *) _mbsinc((unsigned char *) fmt);
        }
        *dest = '\0';
    }
    return dest;
}

// FUNCTION: CL 0x00404fcb
char *append(char *str1, const char *str2)
{
    if (str2 != NULL) {
        strcpy(str1, str2);
    }
    return &str1[strlen(str1)];
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

// FUNCTION: CL 0x00405483
void rm_il(BOOL arg1)
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

// FUNCTION: CL 0x004055ad
void done(int exitcode)
{
    rm_il(FALSE);
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

// FUNCTION: CL 0x00405647
void print(int stream, const char *fmt, ...)
{
    char *text;
    size_t len;
    va_list ap;
    va_start(ap, fmt);
    text = format(&len, fmt, ap);
    va_end(ap);
    write(stream, text, len);
}

// FUNCTION: CL 0x00405672
char *format(size_t *len, const char *fmt, va_list ap)
{
    static char buffer[2048];
    char *write_ptr = buffer;
    const char *src;
    while (*fmt != '\0') {
        if (_mbsncmp((unsigned char *) fmt, (unsigned char *) "%", 1) == 0) {
            fmt = _mbsinc((unsigned char *) fmt);
            switch (*fmt) {
            case 'c':
                *write_ptr = (char) va_arg(ap, int);
                write_ptr = (char *) _mbsinc((unsigned char *) write_ptr);
                break;
            case 'd':
            case 'x':
                write_ptr += l2a(va_arg(ap, int), write_ptr,
                _mbsncmp((unsigned char *) fmt, (unsigned char *) "d", 1) == 0 ? 10 : 0);
                break;
            case 's':
                src = va_arg(ap, const char *);
                strcpy(write_ptr, src);
                write_ptr += strlen(src);
                break;
            default:
                _mbccpy((unsigned char *) write_ptr, (unsigned char *) "%");
                _mbccpy(_mbsinc((unsigned char *) write_ptr), (unsigned char *) fmt);
                write_ptr = (char *) _mbsinc((unsigned char *) write_ptr);
                break;
            }
        } else {
            _mbccpy((unsigned char *) write_ptr, (unsigned char *) fmt);
            write_ptr = (char *) _mbsinc((unsigned char *) write_ptr);
        }
        fmt = _mbsinc((unsigned char *) fmt);
    }
    *write_ptr = '\0';
    *len = write_ptr - buffer;
    if (*len >= sizeof(buffer)) {
        cmderr(0);
    }
    return buffer;
}

// FUNCTION: CL 0x004057b4
void vprint(int stream, const char *fmt, va_list ap)
{
    size_t len;
    const char *text = format(&len, fmt, ap);
    write(stream, text, len);
}

// FUNCTION: CL 0x004057dd
void echoprintf(FILE *stream, const char *fmt, ...)
{
    size_t len;
    va_list ap;
    const char *text;

    va_start(ap, fmt);
    text = format(&len, fmt, ap);
    va_end(ap);
    if (stream != NULL) {
        _write(_fileno(stream), text, len);
    }
    if (Verbose) {
        _write(STDERR_FILENO, text, len);
    }
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

// FUNCTION: CL 0x00405b28
const char *get_message(int code)
{
    return GetMessageInFile(Context->errorpath, code);
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

// FUNCTION: CL 0x00405bd5
void *xnew(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL) {
        cmderr(0);
    }
    return ptr;
}

// FUNCTION: CL 0x00405bf7
void xfree(void *ptr)
{
    if (ptr != NULL) {
        free(ptr);
    }
}

// FUNCTION: CL 0x00405c0a
char *xstrdup(const char *str)
{
    if (str == NULL) {
        return NULL;
    }
    return _strdup(str);
}
