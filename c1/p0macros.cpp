#include "p0macros.h"

#include "zz_unknown.h"

#include <stddef.h>

// GLOBAL: MSVC5_C1 0x00000020
// ?Current_actual_limit@@3PAEA
// unsigned char *Current_actual_limit

// GLOBAL: MSVC5_C1 0x00000024
// ?iWhiteFound@@3HA
// int iWhiteFound

// GLOBAL: MSVC5_C1 0x00000028
// ?Current_expansion_limit@@3PAEA
// unsigned char *Current_expansion_limit

// GLOBAL: MSVC5_C1 0x0000002c
// ?pMacroDefnStart@@3PAEA
// unsigned char *pMacroDefnStart

// GLOBAL: MSVC5_C1 0x00000030
// ?Tiny_lexer_nesting@@3HA
// int Tiny_lexer_nesting

// GLOBAL: MSVC5_C1 0x00000034
// ?nFormals@@3HA
// int nFormals

// GLOBAL: MSVC5_C1 0x00000038
// ?Save_Exp_ptr@@3PAEA
// unsigned char *Save_Exp_ptr

// GLOBAL: MSVC5_C1 0x0000003c
// ?Macro_line@@3JA
// long Macro_line

// GLOBAL: MSVC5_C1 0x00000040
// ?Act_ptr@@3PAEA
// unsigned char *Act_ptr

// GLOBAL: MSVC5_C1 0x00000044
// ?Exp_ptr@@3PAEA
// unsigned char *Exp_ptr

// GLOBAL: MSVC5_C1 0x00000048
// ?nActuals@@3HA
// int nActuals

// GLOBAL: MSVC5_C1 0x0000004c
// ?pActuals@@3PAEA
// unsigned char *pActuals

// GLOBAL: MSVC5_C1 0x00000050
// ?Macro_expansion@@3PAUs_expstr@@A
// struct s_expstr *Macro_expansion

// GLOBAL: MSVC5_C1 0x00000f98
// ??_C@_01FCOA@?5?$AA@
// " "

// GLOBAL: MSVC5_C1 0x00000f9c
// ??_C@_01BJG@?6?$AA@
// "\n"

// GLOBAL: MSVC5_C1 0x00000fa0
// ??_C@_01FBAH@1?$AA@
// "1"

// GLOBAL: MSVC5_C1 0x00000fa4
// ??_C@_0N@KADK@?4?2p0macros?4c?$AA@
// ".\\p0macros.c"

// GLOBAL: MSVC5_C1 0x00000fb4
// ??_C@_08FPFK@Brepro?4c?$AA@
// "Brepro.c"

// GLOBAL: MSVC5_C1 0x00000fc0
// ??_C@_0BB@BNBC@?$CDpragma?5hdrstop?6?$AA@
// "#pragma hdrstop\n"

// GLOBAL: MSVC5_C1 0x00001850
// ?pMacroActBase@@3PAEA
// C1: DATA 0x0045e3e8
unsigned char *pMacroActBase = NULL;

// GLOBAL: MSVC5_C1 0x00001854
// ?pMacroExpBase@@3PAEA
// C1: DATA 0x0045e3ec
unsigned char *pMacroExpBase = NULL;

// FUNCTION: MSVC5_C1 0x000066f0
// ?ReserveMacroBuffers@@YAXXZ
// C1: FUNCTION 0x0041bab0
void ReserveMacroBuffers()
{
    pMacroActBase = PreAllocateMemory(5 * 1024 * 1024, 1024);
    pMacroActEnd = pMacroActBase + 4096 - 5;
    pMacroExpBase = PreAllocateMemory(5 * 1024 * 1024, 1024);
    pMacroExpEnd = pMacroExpBase + 4096 - 5;
}

// FUNCTION: MSVC5_C1 0x00006740
// ?ReleaseMacroBuffers@@YAXXZ
// void __cdecl ReleaseMacroBuffers(void)

// FUNCTION: MSVC5_C1 0x00006790
// ?InitMacroBuffer@@YAXXZ
// void __cdecl InitMacroBuffer(void)

// FUNCTION: MSVC5_C1 0x000067c0
// ?AllocateMacroBuffer@@YAPAEHH@Z
// unsigned char * __cdecl AllocateMacroBuffer(int, int)

// FUNCTION: MSVC5_C1 0x00006810
// ?undefine@@YAXXZ
// void __cdecl undefine(void)

// FUNCTION: MSVC5_C1 0x000068c0
// ?define@@YAXH@Z
// void __cdecl define(int)

// FUNCTION: MSVC5_C1 0x00006d50
// ?get_formals@@YAXXZ
// void __cdecl get_formals(void)

// FUNCTION: MSVC5_C1 0x00006f60
// ?InstallDefine@@YAXPAEHH@Z
// void __cdecl InstallDefine(unsigned char *, int, int)

// FUNCTION: MSVC5_C1 0x000070f0
// ?redefn@@YAHPAE0H@Z
// int __cdecl redefn(unsigned char *, unsigned char *, int)

// FUNCTION: MSVC5_C1 0x00007140
// ?get_definition@@YAHXZ
// int __cdecl get_definition(void)

// FUNCTION: MSVC5_C1 0x000079a0
// ?is_macro_arg@@YAHPAE@Z
// int __cdecl is_macro_arg(unsigned char *)

// FUNCTION: MSVC5_C1 0x00007a20
// ?chkbuf_exceeded@@YAXPAE0PAPAE@Z
// void __cdecl chkbuf_exceeded(unsigned char *, unsigned char *, unsigned char **)

// FUNCTION: MSVC5_C1 0x00007ab0
// ?gather_chars@@YAPAEPAEPAPAEE@Z
// unsigned char * __cdecl gather_chars(unsigned char *, unsigned char **, unsigned char)

// FUNCTION: MSVC5_C1 0x00007bf0
// ?can_expand@@YAHPAUs_defn@@@Z
// int __cdecl can_expand(struct s_defn *)

// FUNCTION: MSVC5_C1 0x00008440
// ?get_actuals@@YAXPAUs_defn@@H@Z
// void __cdecl get_actuals(struct s_defn *, int)

// FUNCTION: MSVC5_C1 0x00008bf0
// ?rescan_expansion@@YAHXZ
// int __cdecl rescan_expansion(void)

// FUNCTION: MSVC5_C1 0x00008ca0
// ?move_to_actual@@YAXPAE0@Z
// void __cdecl move_to_actual(unsigned char *, unsigned char *)

// FUNCTION: MSVC5_C1 0x00008d20
// ?move_to_exp_esc@@YAXEPAE@Z
// void __cdecl move_to_exp_esc(unsigned char, unsigned char *)

// FUNCTION: MSVC5_C1 0x00008e70
// ?move_to_exp@@YAXPAE@Z
// void __cdecl move_to_exp(unsigned char *)

// FUNCTION: MSVC5_C1 0x00008ec0
// ?push_macro@@YAXPAUs_defn@@@Z
// void __cdecl push_macro(struct s_defn *)

// FUNCTION: MSVC5_C1 0x00008f40
// ?expand_definition@@YAXXZ
// void __cdecl expand_definition(void)

// FUNCTION: MSVC5_C1 0x00008fa0
// ?fExpandingMacro@@YAHPAUs_defn@@@Z
// int __cdecl fExpandingMacro(struct s_defn *)

// FUNCTION: MSVC5_C1 0x00008fe0
// ?expand_macro@@YAXXZ
// void __cdecl expand_macro(void)

// FUNCTION: MSVC5_C1 0x00009040
// ?post_paste@@YAHXZ
// int __cdecl post_paste(void)

// FUNCTION: MSVC5_C1 0x00009090
// ?do_macformal@@YAPAEPAH@Z
// unsigned char * __cdecl do_macformal(int *)

// FUNCTION: MSVC5_C1 0x00009100
// ?tl_getid@@YAHE@Z
// int __cdecl tl_getid(unsigned char)

// FUNCTION: MSVC5_C1 0x00009370
// ?do_strformal@@YAPAEXZ
// unsigned char * __cdecl do_strformal(void)

// FUNCTION: MSVC5_C1 0x000093c0
// ?can_get_non_white@@YAHXZ
// int __cdecl can_get_non_white(void)

// FUNCTION: MSVC5_C1 0x000094d0
// ?fatal_in_macro@@YAXH@Z
// void __cdecl fatal_in_macro(int)

// FUNCTION: MSVC5_C1 0x000094f0
// ?HandleFileEOS@@YAXXZ
// void __cdecl HandleFileEOS(void)

// FUNCTION: MSVC5_C1 0x00009580
// ?iTrigraphEOS@@YAHXZ
// int __cdecl iTrigraphEOS(void)

// FUNCTION: MSVC5_C1 0x000096f0
// ?handle_eos@@YAHXZ
// int __cdecl handle_eos(void)

// FUNCTION: MSVC5_C1 0x00009820
// ?CurrentCharInUserSource@@YAPAEXZ
// unsigned char * __cdecl CurrentCharInUserSource(void)

