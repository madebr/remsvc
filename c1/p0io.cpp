#include "p0io.h"

#include "nheapall.h"

// GLOBAL: C1 0x0045b5bc
s_IncludeList *IncludeList;

// GLOBAL: MSVC5_C1 0x000000b0
// ??_C@_0M@JAPN@__LINE__Var?$AA@
// "__LINE__Var"

// GLOBAL: MSVC5_C1 0x000000bc
// ??_C@_0N@LAD@__LOCAL_SIZE?$AA@
// "__LOCAL_SIZE"

// GLOBAL: MSVC5_C1 0x000000cc
// ??_C@_05HLHB@Catch?$AA@
// "Catch"

// GLOBAL: MSVC5_C1 0x000000d4
// ??_C@_07PBGM@_setjmp?$AA@
// "_setjmp"

// GLOBAL: MSVC5_C1 0x000000dc
// ??_C@_0BF@NHN@?4local?5static?5guard?4?$AA@
// ".local static guard."

// GLOBAL: MSVC5_C1 0x000000f4
// ??_C@_08BDPO@?4drectve?$AA@
// ".drectve"

// GLOBAL: MSVC5_C1 0x00000100
// ??_C@_01PILM@$?$AA@
// "$"

// GLOBAL: MSVC5_C1 0x00000104
// ??_C@_09OJNL@__unnamed?$AA@
// "__unnamed"

// GLOBAL: MSVC5_C1 0x00000110
// ??_C@_0BD@PDMB@?4alignment?5member?4?$AA@
// ".alignment member."

// GLOBAL: MSVC5_C1 0x00000124
// ??_C@_07GPHG@DllMain?$AA@
// "DllMain"

// GLOBAL: MSVC5_C1 0x0000012c
// ??_C@_07HGPI@WinMain?$AA@
// "WinMain"

// GLOBAL: MSVC5_C1 0x00000134
// ??_C@_04HBMH@main?$AA@
// "main"

// GLOBAL: MSVC5_C1 0x0000013c
// ??_C@_0BE@FMNE@abstract?5declarator?$AA@
// "abstract declarator"

// GLOBAL: MSVC5_C1 0x00000150
// ??_C@_03NAME@?4?4?4?$AA@
// "..."

// GLOBAL: MSVC5_C1 0x00000154
// ??_C@_08MADI@__formal?$AA@
// "__formal"

// GLOBAL: MSVC5_C1 0x00000160
// ??_C@_07DLLF@defined?$AA@
// "defined"

// GLOBAL: MSVC5_C1 0x00000168
// ??_C@_08PBLG@?4?2p0io?4c?$AA@
// ".\\p0io.c"

// GLOBAL: MSVC5_C1 0x00000174
// ??_C@_02NEFL@if?$AA@
// "if"

// GLOBAL: MSVC5_C1 0x00000178
// ??_C@_09OJGE@?$CDline?5?$CFd?5?$AA@
// "#line %d "

// GLOBAL: MSVC5_C1 0x00000184
// ??_C@_08GNEF@__STDC__?$AA@
// "__STDC__"

// GLOBAL: MSVC5_C1 0x00000190
// ??_C@_0O@LDDL@__TIMESTAMP__?$AA@
// "__TIMESTAMP__"

// GLOBAL: MSVC5_C1 0x000001a0
// ??_C@_08EFFP@__TIME__?$AA@
// "__TIME__"

// GLOBAL: MSVC5_C1 0x000001ac
// ??_C@_08EEJE@__DATE__?$AA@
// "__DATE__"

// GLOBAL: MSVC5_C1 0x000001b8
// ??_C@_08BBEP@__FILE__?$AA@
// "__FILE__"

// GLOBAL: MSVC5_C1 0x000001c4
// ??_C@_08NNKK@__LINE__?$AA@
// "__LINE__"

// GLOBAL: MSVC5_C1 0x000001d0
// ??_C@_00A@?$AA@
// ""

// GLOBAL: MSVC5_C1 0x00000218
// ?Ftop@@3PAUs_filelist@@A
// struct s_filelist *Ftop

// GLOBAL: MSVC5_C1 0x0000021c
// ?Fbottom@@3PAUs_filelist@@A
// struct s_filelist *Fbottom

// GLOBAL: MSVC5_C1 0x00000220
// ?Ffreelist@@3PAUs_filelist@@A
// struct s_filelist *Ffreelist

// GLOBAL: MSVC5_C1 0x00000224
// ?Fdepth@@3HA
// int Fdepth

// GLOBAL: MSVC5_C1 0x00000228
// ?curFileNo@@3HA
// int curFileNo

// FUNCTION: MSVC5_C1 0x00004ac0
// ?FtopIsMemInline@@YAHXZ
// int __cdecl FtopIsMemInline(void)

// FUNCTION: MSVC5_C1 0x00004ad0
// ?GetTimeStamp@@YAKXZ
// unsigned long __cdecl GetTimeStamp(void)

// FUNCTION: MSVC5_C1 0x00004af0
// ?GetFileOffset@@YAJXZ
// long __cdecl GetFileOffset(void)

// FUNCTION: MSVC5_C1 0x00004b10
// ?CloseIncludeFile@@YAHXZ
// int __cdecl CloseIncludeFile(void)

// FUNCTION: MSVC5_C1 0x00004b60
// ?RewindSourceFile@@YAXXZ
// void __cdecl RewindSourceFile(void)

// FUNCTION: MSVC5_C1 0x00004be0
// ?PushNewOpenFile@@YAXPAVFilename@@HHH@Z
// void __cdecl PushNewOpenFile(class Filename *, int, int, int)

// FUNCTION: MSVC5_C1 0x00004e80
// ?OpenFile@@YAHPAEIHHH@Z
// int __cdecl OpenFile(unsigned char *, unsigned int, int, int, int)

// FUNCTION: MSVC5_C1 0x00004f60
// ?UseInlineFile@@YAXH@Z
// void __cdecl UseInlineFile(int)

// FUNCTION: MSVC5_C1 0x00005010
// ?CloseAllSources@@YAXXZ
// void __cdecl CloseAllSources(void)

// FUNCTION: MSVC5_C1 0x00005040
// ?fpop@@YAHXZ
// int __cdecl fpop(void)

// FUNCTION: MSVC5_C1 0x000052a0
// ?NestedInclude@@YAHPAEH0@Z
// int __cdecl NestedInclude(unsigned char *, int, unsigned char *)

// FUNCTION: MSVC5_C1 0x00005480
// ?esc_sequence@@YAPAEPAE0@Z
// unsigned char * __cdecl esc_sequence(unsigned char *, unsigned char *)

// FUNCTION: MSVC5_C1 0x000054d0
// ?emit_line@@YAXXZ
// void __cdecl emit_line(void)

// FUNCTION: MSVC5_C1 0x00005560
// ?io_eob@@YAHXZ
// int __cdecl io_eob(void)

// FUNCTION: MSVC5_C1 0x00005700
// ?InitializeStandardIdentifiers@@YAXXZ
// void __cdecl InitializeStandardIdentifiers(void)

// FUNCTION: MSVC5_C1 0x00005730
// ?pbStartOfCurBuf@@YAPAEXZ
// unsigned char * __cdecl pbStartOfCurBuf(void)

// FUNCTION: MSVC5_C1 0x00005750
// ?cbRemainingInBuffer@@YAJXZ
// long __cdecl cbRemainingInBuffer(void)

// FUNCTION: MSVC5_C1 0x00005770
// ?fEOF@@YAHXZ
// int __cdecl fEOF(void)

// FUNCTION: MSVC5_C1 0x00005780
// ?fICCSkipFn@@YAHJG@Z
// int __cdecl fICCSkipFn(long, unsigned short)

// FUNCTION: MSVC5_C1 0x000058f0
// ?p0_init@@YAXPAUlist@@@Z
// void __cdecl p0_init(struct list *)

// FUNCTION: MSVC5_C1 0x00005ae0
// ?CommandDef@@YAXPAD@Z
// void __cdecl CommandDef(char *)

// FUNCTION: MSVC5_C1 0x00005c20
// ?WriteMessage@@YAXPAD@Z
// void __cdecl WriteMessage(char *)

// FUNCTION: MSVC5_C1 0x00005c50
// ?FixFileNamePointers@@YAXXZ
// void __cdecl FixFileNamePointers(void)

// FUNCTION: MSVC5_C1 0x00005ca0
// ?PrevCharWasInitialNewLine@@YAHXZ
// int __cdecl PrevCharWasInitialNewLine(void)

// FUNCTION: MSVC5_C1 0x00005cc0
// ?getFileName@Position@@QBEPAEXZ
// public: unsigned char * __thiscall Position::getFileName(void) const

// GLOBAL: C1 0x0041c211
void InitIncludeList()
{
    IncludeList = HeapManager::Allocate<s_IncludeList>(M_LIFETIME0);
}
