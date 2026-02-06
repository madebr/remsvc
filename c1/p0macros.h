#ifndef P0MACROS_H
#define P0MACROS_H
// ?Current_actual_limit@@3PAEA
// unsigned char *Current_actual_limit

// ?iWhiteFound@@3HA
// int iWhiteFound

// ?Current_expansion_limit@@3PAEA
// unsigned char *Current_expansion_limit

// ?pMacroDefnStart@@3PAEA
// unsigned char *pMacroDefnStart

// ?Tiny_lexer_nesting@@3HA
// int Tiny_lexer_nesting

// ?nFormals@@3HA
// int nFormals

// ?Save_Exp_ptr@@3PAEA
// unsigned char *Save_Exp_ptr

// ?Macro_line@@3JA
// long Macro_line

// ?Act_ptr@@3PAEA
// unsigned char *Act_ptr

// ?Exp_ptr@@3PAEA
// unsigned char *Exp_ptr

// ?nActuals@@3HA
// int nActuals

// ?pActuals@@3PAEA
// unsigned char *pActuals

// ?Macro_expansion@@3PAUs_expstr@@A
// struct s_expstr *Macro_expansion

// ??_C@_01FCOA@?5?$AA@
// " "

// ??_C@_01BJG@?6?$AA@
// "\n"

// ??_C@_01FBAH@1?$AA@
// "1"

// ??_C@_0N@KADK@?4?2p0macros?4c?$AA@
// ".\\p0macros.c"

// ??_C@_08FPFK@Brepro?4c?$AA@
// "Brepro.c"

// ??_C@_0BB@BNBC@?$CDpragma?5hdrstop?6?$AA@
// "#pragma hdrstop\n"

// ?pMacroActBase@@3PAEA
extern unsigned char *pMacroActBase;

// ?pMacroExpBase@@3PAEA
extern unsigned char *pMacroExpBase;

// ?ReserveMacroBuffers@@YAXXZ
// void __cdecl ReserveMacroBuffers(void)
extern void ReserveMacroBuffers(void);

// ?ReleaseMacroBuffers@@YAXXZ
// void __cdecl ReleaseMacroBuffers(void)

// ?InitMacroBuffer@@YAXXZ
// void __cdecl InitMacroBuffer(void)

// ?AllocateMacroBuffer@@YAPAEHH@Z
// unsigned char * __cdecl AllocateMacroBuffer(int, int)

// ?undefine@@YAXXZ
// void __cdecl undefine(void)

// ?define@@YAXH@Z
// void __cdecl define(int)

// ?get_formals@@YAXXZ
// void __cdecl get_formals(void)

// ?InstallDefine@@YAXPAEHH@Z
// void __cdecl InstallDefine(unsigned char *, int, int)

// ?redefn@@YAHPAE0H@Z
// int __cdecl redefn(unsigned char *, unsigned char *, int)

// ?get_definition@@YAHXZ
// int __cdecl get_definition(void)

// ?is_macro_arg@@YAHPAE@Z
// int __cdecl is_macro_arg(unsigned char *)

// ?chkbuf_exceeded@@YAXPAE0PAPAE@Z
// void __cdecl chkbuf_exceeded(unsigned char *, unsigned char *, unsigned char **)

// ?gather_chars@@YAPAEPAEPAPAEE@Z
// unsigned char * __cdecl gather_chars(unsigned char *, unsigned char **, unsigned char)

// ?can_expand@@YAHPAUs_defn@@@Z
// int __cdecl can_expand(struct s_defn *)

// ?get_actuals@@YAXPAUs_defn@@H@Z
// void __cdecl get_actuals(struct s_defn *, int)

// ?rescan_expansion@@YAHXZ
// int __cdecl rescan_expansion(void)

// ?move_to_actual@@YAXPAE0@Z
// void __cdecl move_to_actual(unsigned char *, unsigned char *)

// ?move_to_exp_esc@@YAXEPAE@Z
// void __cdecl move_to_exp_esc(unsigned char, unsigned char *)

// ?move_to_exp@@YAXPAE@Z
// void __cdecl move_to_exp(unsigned char *)

// ?push_macro@@YAXPAUs_defn@@@Z
// void __cdecl push_macro(struct s_defn *)

// ?expand_definition@@YAXXZ
// void __cdecl expand_definition(void)

// ?fExpandingMacro@@YAHPAUs_defn@@@Z
// int __cdecl fExpandingMacro(struct s_defn *)

// ?expand_macro@@YAXXZ
// void __cdecl expand_macro(void)

// ?post_paste@@YAHXZ
// int __cdecl post_paste(void)

// ?do_macformal@@YAPAEPAH@Z
// unsigned char * __cdecl do_macformal(int *)

// ?tl_getid@@YAHE@Z
// int __cdecl tl_getid(unsigned char)

// ?do_strformal@@YAPAEXZ
// unsigned char * __cdecl do_strformal(void)

// ?can_get_non_white@@YAHXZ
// int __cdecl can_get_non_white(void)

// ?fatal_in_macro@@YAXH@Z
// void __cdecl fatal_in_macro(int)

// ?HandleFileEOS@@YAXXZ
// void __cdecl HandleFileEOS(void)

// ?iTrigraphEOS@@YAHXZ
// int __cdecl iTrigraphEOS(void)

// ?handle_eos@@YAHXZ
// int __cdecl handle_eos(void)

// ?CurrentCharInUserSource@@YAPAEXZ
// unsigned char * __cdecl CurrentCharInUserSource(void)

#endif /* P0MACROS_H */
