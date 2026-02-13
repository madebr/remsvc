#ifndef ERROR_H
#define ERROR_H

#include "decomp.h"

#include <stdarg.h>
#include <stdio.h>

#define ERROR_OCCURRED() (((WarnIsError > 1) ? 1 : 0) + Nerrors)

typedef enum {
    C1000 = 0,
    FATAL_NONE= 0 ,
    C1001 = 1,
    C1002 = 2,
    C1003 = 3,
    C1004 = 4,
    C1005 = 5,
    C1006 = 6,
    C1007 = 7,
    C1008 = 8,
    C1009 = 9,
    C1010 = 10,
    C1012 = 12,
    C1013 = 13,
    C1014 = 14,
    C1016 = 16,
    C1017 = 17,
    C1018 = 18,
    C1019 = 19,
    C1020 = 20,
    C1021 = 21,
    C1022 = 22,
    C1023 = 23,
    C1026 = 26,
    C1027 = 27,
    C1033 = 33,
    C1034 = 34,
    C1035 = 35,
    C1036 = 36,
    C1037 = 37,
    C1038 = 38,
    C1042 = 42,
    C1043 = 43,
    C1044 = 44,
    C1045 = 45,
    C1046 = 46,
    C1047 = 47,
    C1048 = 48,
    C1049 = 49,
    C1051 = 51,
    C1053 = 53,
    C1054 = 54,
    C1055 = 55,
    C1057 = 57,
    C1059 = 59,
    C1060 = 60,
    C1061 = 61,
    C1063 = 63,
    C1064 = 64,
    C1065 = 65,
    C1067 = 67,
    C1068 = 68,
    C1070 = 70,
    C1071 = 71,
    C1073 = 73,
    C1074 = 74,
    C1075 = 75,
    C1076 = 76,
    C1077 = 77,
    C1079 = 79,
    C1080 = 80,
    C1081 = 81,
    C1082 = 82,
    C1083 = 83,
    C1084 = 84,
    C1085 = 85,
    C1086 = 86,
    C1087 = 87,
    C1088 = 88,
    C1089 = 89,
    C1090 = 90,
    C1091 = 91,
    C1092 = 92,
    C1093 = 93,
    C1094 = 94,
    C1098 = 98,
    C1099 = 99,
    C1100 = 100,
    C1101 = 101,
    C1102 = 102,
    C1103 = 103,
    C1104 = 104,
    C1105 = 105,
    C1107 = 107,
    C1108 = 108,
    C1109 = 109,
    C1110 = 110,
    C1111 = 111,
    C1112 = 112,
    C1113 = 113,
    C1120 = 120,
    C1121 = 121,
    C1126 = 126,
    C1128 = 128,
    C1189 = 189,
    C1190 = 190,
    C1191 = 191,
    C1192 = 192,
    C1193 = 193,
    C1194 = 194,
    C1195 = 195,
    C1196 = 196,
    C1197 = 197,
    C1201 = 201,
    C1202 = 202,
    C1205 = 205,
    C1206 = 206,
    C1207 = 207,
    C1208 = 208,
    C1209 = 209,
    C1210 = 210,
    C1211 = 211,
    C1300 = 300,
    C1301 = 301,
    C1302 = 302,
    C1303 = 303,
    C1304 = 304,
    C1305 = 305,
    C1306 = 306,
    C1307 = 307,
    C1308 = 308,
    C1309 = 309,
    C1310 = 310,
    C1311 = 311,
    C1312 = 312,
    C1313 = 313,
    C1350 = 350,
    C1351 = 351,
    C1352 = 352,
    C1353 = 353,
    C1382 = 382,
    C1383 = 383,
    C1384 = 384,
    C1505 = 505,
    C1506 = 506,
    C1507 = 507,
    C1508 = 508,
    C1509 = 509,
    C1510 = 510,
    C1600 = 600,
    C1601 = 601,
    C1602 = 602,
    C1603 = 603,
    C1852 = 852,
    C1853 = 853,
    C1854 = 854,
    C1859 = 859,
    C1900 = 900,
    C1901 = 901,
    C1902 = 902,
    C1903 = 903,
    C1904 = 904,
    C1905 = 905,
    C1999 = 999
} FatalNumber;

extern FILE *gFile_er;

extern FILE *gFile_lp;

extern bool32 gWrite_er;

// ?__MSGTAB@@3PAU_message@@A
// struct _message *__MSGTAB

// ??_C@_09EMHG@?4?2error?4c?$AA@
// ".\\error.c"

// ??_C@_0BF@OIHI@fatal?5error?5C1063?3?$AN?6?$AA@
// "fatal error C1063:\r\n"

// ??_C@_09HOOG@?$CFs?5?$CFc?$CFd?3?5?$AA@
// "%s %c%d: "

// ??_C@_09BIJJ@?$CFs?$CI?$CFd?$CJ?5?3?5?$AA@
// "%s(%d) : "

// ?IOGlobalVal@@3JA
extern int IOGlobalVal;

// ?Errbuff@@3PADA
// char *Errbuff

// ?__NMSG_FIND@@YAPADI@Z
// char * __cdecl __NMSG_FIND(unsigned int)

// ?preloadMessages@@YAXXZ
// void __cdecl preloadMessages(void)

// ?__NMSG_TEXT@@YAPADI@Z
// char * __cdecl __NMSG_TEXT(unsigned int)

// ?error@@YAXHZZ
// void __cdecl error(int, ...)

// ?close_file@@YAHPAU_iobuf@@@Z
// int __cdecl close_file(struct _iobuf *)

// ?errorVA@@YAXHPAD@Z
// void __cdecl errorVA(int, char *)

// ?get_err@@YGPADH@Z
// char * __stdcall get_err(int)

extern int __fastcall fatal_io_CRT_position(FatalNumber code,int category,const char *text, const char *file, int lineno);

// ?fatal_io_CRT@@YAHHHPAE@Z
extern int fatal_io_CRT(FatalNumber fatalCode, int category, const char *text);

// ?fatal_io_Win32@@YAHHHPAE@Z
// int __cdecl fatal_io_Win32(int, int, unsigned char *)

// ?fatal_io_HRESULT@@YAHKHHPAE@Z
// int __cdecl fatal_io_HRESULT(unsigned long, int, int, unsigned char *)

// ?fatal@@YAHH@Z
extern void fatal(FatalNumber error);

// ?GaspAndDie@@YAXH@Z
extern void GaspAndDie(bool32 showMessage);

// ?fatal_varargs@@YAHHZZ
extern void fatal_varargs(FatalNumber code, ...);

// ?ActualWarnLevel@@YAHHH@Z
// int __cdecl ActualWarnLevel(int, int)

// ?warning@@YAXHHZZ
extern void warning(int, int, ...);

// ?message_continuation@@YAXHZZ
// void __cdecl message_continuation(int, ...)

// ?OutputDiagnosticString@@YAXPAD@Z
// void __cdecl OutputDiagnosticString(char *)

// ?message@@YAXHHPAD0@Z
extern void message(int category, int code, const char *format_str, va_list ap);

// ?format@@YAHPAD0HZZ
extern int format(char *buffer, const char *format_str, size_t buffer_size, ...);

// ?do_format@@YAHPADPBDH0@Z
extern int do_format(char *buffer, char const *format_str, size_t buffer_size, va_list ap);

// ?GetWarnLevel@@YA?AW4warn_t@@I@Z
// enum warn_t __cdecl GetWarnLevel(unsigned int)

#endif /* ERROR_H */
