#ifndef ZZ_DIAGNOSTIC_H
#define ZZ_DIAGNOSTIC_H

#include "decomp.h"

extern bool32 gDiagnostic_strings_initialized;

extern const char * gDiagnostic_messages_path;

extern const char * GetDiagnosticString(int code, bool32 param_2);

extern const char * __fastcall GetDiagnosticHelpString(int code);

#endif /* ZZ_DIAGNOSTIC_HPP */
