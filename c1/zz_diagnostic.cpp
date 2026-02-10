#include "zz_diagnostic.h"

#include "alloc.h"
#include "error.h"

#include <ctype.h>
#include <limits.h>
#ifdef _WIN32
#include <mbctype.h>
#include <windows.h>
#endif
#include <stdio.h>


struct tDiagnostic_file_offset {
    int code;
    int offset;
};

struct tDiagnostic_code_text {
    int code;
    const char *text;
};

// GLOBAL: C1 0x0046644c
FILE *gDiagnostics_file = NULL;

// GLOBAL: C1 0x0045c7b4
bool32 gDiagnostic_strings_initialized = FALSE;

// GLOBAL: C1 0x0045c540
const char * gDiagnostic_messages_path = "c1.err";

// GLOBAL: C1 0x00469168
tDiagnostic_file_offset gDiagnostic_file_offsets[20];

// GLOBAL: C1 0x0045c7b0
int gError_message_file_pos;

// GLOBAL: C1 0x00469208
char gDiagnostic_message_buffer[256];

// GLOBAL: C1 0x0045c7b8
tDiagnostic_code_text gDiagnostic_help_strings[83] = {
    { 303, NULL, },
    { 304, NULL, },
    { 305, NULL, },
    { 306, NULL, },
    { 307, NULL, },
    { 308, NULL, },
    { 313, NULL, },
    { 314, NULL, },
    { 315, NULL, },
    { 320, NULL, },
    { 321, NULL, },
    { 322, NULL, },
    { 323, NULL, },
    { 333, NULL, },
    { 334, NULL, },
    { 335, NULL, },
    { 336, NULL, },
    { 337, NULL, },
    { 338, NULL, },
    { 339, NULL, },
    { 340, NULL, },
    { 341, NULL, },
    { 342, NULL, },
    { 343, NULL, },
    { 344, NULL, },
    { 345, NULL, },
    { 346, NULL, },
    { 347, NULL, },
    { 348, NULL, },
    { 349, NULL, },
    { 350, NULL, },
    { 351, NULL, },
    { 352, NULL, },
    { 353, NULL, },
    { 354, NULL, },
    { 355, NULL, },
    { 356, NULL, },
    { 357, NULL, },
    { 360, NULL, },
    { 361, NULL, },
    { 362, NULL, },
    { 363, NULL, },
    { 370, NULL, },
    { 371, NULL, },
    { 372, NULL, },
    { 373, NULL, },
    { 374, NULL, },
    { 375, NULL, },
    { 376, NULL, },
    { 377, NULL, },
    { 378, NULL, },
    { 379, NULL, },
    { 380, NULL, },
    { 381, NULL, },
    { 390, NULL, },
    { 391, NULL, },
    { 392, NULL, },
    { 393, NULL, },
    { 394, NULL, },
    { 395, NULL, },
    { 396, NULL, },
    { 397, NULL, },
    { 398, NULL, },
    { 399, NULL, },
    { 400, NULL, },
    { 401, NULL, },
    { 402, NULL, },
    { 403, NULL, },
    { 404, NULL, },
    { 405, NULL, },
    { 406, NULL, },
    { 407, NULL, },
    { 408, NULL, },
    { 901, NULL, },
    { 902, NULL, },
    { 903, NULL, },
    { 904, NULL, },
    { 905, NULL, },
    { 906, NULL, },
    { 907, NULL, },
    { 908, NULL, },
    { 910, NULL, },
    { 0, NULL, },
};

// FUNCTION: C1 0x00448070
static int GetBestErrorFileMessageOffset(int code)
{
    int best_index = -1;
    int best_diff = SHRT_MAX;
    int i;

    for (i = 0; i < arraysize(gDiagnostic_file_offsets); i++) {
        int current_code = gDiagnostic_file_offsets[i].code;
        if (current_code == 0) {
            break;
        }
        int current_diff = code - current_code;
        if (current_diff == 0) {
            best_index = i;
            break;
        }
        if (current_diff != 0 && current_code <= code && current_diff < best_diff && code / -1000 == current_code / -100) {
            best_diff = current_diff;
            best_index = i;
        }
    }
    if (best_index < 0) {
        return gError_message_file_pos;
    }
    return gDiagnostic_file_offsets[best_index].offset;
}

// FUNCTION: C1 0x0044802d
static void CacheDiagnosticFileOffset(int offset, int code)
{
    int i;

    for (i = 0; i < arraysize(gDiagnostic_file_offsets); i++) {
        tDiagnostic_file_offset *file_offset = &gDiagnostic_file_offsets[i];
        if (file_offset->code == 0) {
            file_offset->code = code;
            file_offset->offset = offset;
            break;
        }
        if (file_offset->code == code) {
            break;
        }
    }
}

// FUNCTION: C1 0x00423a7b
static char *ExtractCodeAndTextFromLine(char *buffer, int *code)
{
    int value = 0;

    while (isdigit(*buffer)) {
        value = value * 10 + (*buffer - '0');
        buffer++;
    }
    *code = value;
    return buffer;
}

// FUNCTIN: C1 0x00423acd
char *RemoveEscapedCharactersInDiagnosticString(char *str)
{
    while (*str++ != '"') {
    }
    char *ptr_read = str;
    char *ptr_write = str;
    while (*ptr_read != '"') {
#ifdef _WIN32
        if (_ismbblead(*ptr_read)) {
            *ptr_write++ = *ptr_read++;
        }
#endif
        if (*ptr_read == '\\') {
            ptr_read++;
            if (*ptr_read == 'n') {
                *ptr_read = '\n';
            } else if (*ptr_read == 't') {
                *ptr_read = '\t';
            } else {
                *ptr_write++ = '\\';
            }
        }
        *ptr_write++ = *ptr_read++;
    }
    *ptr_write = '\0';
    return str;
}

// FUNCTION: C1 0x004239f8
static const char *ReadDiagnosticString(int code, char *buffer, size_t bufferSize, bool32 arg4)
{
    for (;;) {
        char *text_start;
        int line_code;
        int32_t offset;

        for (;;) {
            if (!arg4) {
                offset = (int32_t)ftell(gDiagnostics_file);
            }
            if (fgets(buffer, bufferSize, gDiagnostics_file) == NULL) {
                if (!arg4) {
                    fatal_io_CRT(C1083, 314, gDiagnostic_messages_path);
                    exit(68);
                }
                return NULL;
            }
            text_start = ExtractCodeAndTextFromLine(buffer, &line_code);
            if (line_code == code || line_code % 1000 == 999) {
                break;
            }
        }
        if (line_code == code) {
            if (!arg4) {
                CacheDiagnosticFileOffset(offset, code);
            }
            return RemoveEscapedCharactersInDiagnosticString(text_start);
        } else if (line_code / -1000 == code / -1000) {
            fseek(gDiagnostics_file, 0, SEEK_SET);
            return RemoveEscapedCharactersInDiagnosticString(text_start);
        }
    }
}
// FUNCTION: C1 0x004238b7
const char * GetDiagnosticString(int code, bool32 arg2)
{
    if (gDiagnostics_file == NULL) {
        if (gDiagnostic_strings_initialized || arg2) {
            if (gDiagnostic_messages_path == NULL) {
                gDiagnostics_file = (FILE *)(uintptr_t)-1;
                return "";
            }
            gDiagnostics_file = fopen(gDiagnostic_messages_path, "r");
            if (gDiagnostics_file == NULL) {
                gDiagnostics_file = (FILE *)(intptr_t)-1;
                return "";
            }
        }
        GetDiagnosticHelpString(303);
    }
    if (gDiagnostics_file == (FILE *)(uintptr_t)-1) {
        return "";
    }
    if (!arg2) {
        fseek(gDiagnostics_file, GetBestErrorFileMessageOffset(code), SEEK_SET);
    }
    return ReadDiagnosticString(code, gDiagnostic_message_buffer, sizeof(gDiagnostic_message_buffer), arg2);
}

// GLOBAL: 0x004239d8
static const char *__fastcall LookupDiagnosticHelpString(int code)
{
    tDiagnostic_code_text *diagnostic_code_text = &gDiagnostic_help_strings[0];
    for (; diagnostic_code_text->code != 0; diagnostic_code_text++) {
        if (diagnostic_code_text->code == code) {
            return diagnostic_code_text->text;
        }
    }
    return diagnostic_code_text->text;
}

// FUNCTION: C1 0x00423937
extern const char * __fastcall GetDiagnosticHelpString(int code)
{
    if (!gDiagnostic_strings_initialized) {
        tDiagnostic_code_text *diagnostic_code_text = &gDiagnostic_help_strings[0];
        for (;diagnostic_code_text->code != 0; diagnostic_code_text++) {
            const char *text = GetDiagnosticString(diagnostic_code_text->code, TRUE);
            if (text == NULL || *text == '\0') {
                if (diagnostic_code_text->code == 313) {
                    diagnostic_code_text->text = "warning";
                }
                if (diagnostic_code_text->code == 314) {
                    diagnostic_code_text->text = "error";
                }
                if (diagnostic_code_text->code == 315) {
                    diagnostic_code_text->text = "fatal error";
                }
                if (gDiagnostics_file != (FILE*)(uintptr_t)-1) {
                    fseek(gDiagnostics_file, 0, SEEK_SET);
                }
            } else {
                diagnostic_code_text->text = pstrdup(text, M_LIFETIME1);
            }
        }
        if (gDiagnostics_file != (FILE*)(uintptr_t)-1) {
            gError_message_file_pos = ftell(gDiagnostics_file);
        }
        gDiagnostic_strings_initialized = TRUE;
    }
    return LookupDiagnosticHelpString(code);
}
