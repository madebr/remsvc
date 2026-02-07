#ifndef P0IO_H
#define P0IO_H

#include "decomp.h"

struct s_IncludeList {
    undefined4 field_0x0;
};


extern s_IncludeList *IncludeList;

// ??_C@_0M@JAPN@__LINE__Var?$AA@
// "__LINE__Var"

// ??_C@_0N@LAD@__LOCAL_SIZE?$AA@
// "__LOCAL_SIZE"

// ??_C@_05HLHB@Catch?$AA@
// "Catch"

// ??_C@_07PBGM@_setjmp?$AA@
// "_setjmp"

// ??_C@_0BF@NHN@?4local?5static?5guard?4?$AA@
// ".local static guard."

// ??_C@_08BDPO@?4drectve?$AA@
// ".drectve"

// ??_C@_01PILM@$?$AA@
// "$"

// ??_C@_09OJNL@__unnamed?$AA@
// "__unnamed"

// ??_C@_0BD@PDMB@?4alignment?5member?4?$AA@
// ".alignment member."

// ??_C@_07GPHG@DllMain?$AA@
// "DllMain"

// ??_C@_07HGPI@WinMain?$AA@
// "WinMain"

// ??_C@_04HBMH@main?$AA@
// "main"

// ??_C@_0BE@FMNE@abstract?5declarator?$AA@
// "abstract declarator"

// ??_C@_03NAME@?4?4?4?$AA@
// "..."

// ??_C@_08MADI@__formal?$AA@
// "__formal"

// ??_C@_07DLLF@defined?$AA@
// "defined"

// ??_C@_08PBLG@?4?2p0io?4c?$AA@
// ".\\p0io.c"

// ??_C@_02NEFL@if?$AA@
// "if"

// ??_C@_09OJGE@?$CDline?5?$CFd?5?$AA@
// "#line %d "

// ??_C@_08GNEF@__STDC__?$AA@
// "__STDC__"

// ??_C@_0O@LDDL@__TIMESTAMP__?$AA@
// "__TIMESTAMP__"

// ??_C@_08EFFP@__TIME__?$AA@
// "__TIME__"

// ??_C@_08EEJE@__DATE__?$AA@
// "__DATE__"

// ??_C@_08BBEP@__FILE__?$AA@
// "__FILE__"

// ??_C@_08NNKK@__LINE__?$AA@
// "__LINE__"

// ??_C@_00A@?$AA@
// ""

// ?Ftop@@3PAUs_filelist@@A
// struct s_filelist *Ftop

// ?Fbottom@@3PAUs_filelist@@A
// struct s_filelist *Fbottom

// ?Ffreelist@@3PAUs_filelist@@A
// struct s_filelist *Ffreelist

// ?Fdepth@@3HA
// int Fdepth

// ?curFileNo@@3HA
// int curFileNo

// ?FtopIsMemInline@@YAHXZ
// int __cdecl FtopIsMemInline(void)

// ?GetTimeStamp@@YAKXZ
// unsigned long __cdecl GetTimeStamp(void)

// ?GetFileOffset@@YAJXZ
// long __cdecl GetFileOffset(void)

// ?CloseIncludeFile@@YAHXZ
// int __cdecl CloseIncludeFile(void)

// ?RewindSourceFile@@YAXXZ
// void __cdecl RewindSourceFile(void)

// ?PushNewOpenFile@@YAXPAVFilename@@HHH@Z
// void __cdecl PushNewOpenFile(class Filename *, int, int, int)

// ?OpenFile@@YAHPAEIHHH@Z
// int __cdecl OpenFile(unsigned char *, unsigned int, int, int, int)

// ?UseInlineFile@@YAXH@Z
// void __cdecl UseInlineFile(int)

// ?CloseAllSources@@YAXXZ
// void __cdecl CloseAllSources(void)

// ?fpop@@YAHXZ
// int __cdecl fpop(void)

// ?NestedInclude@@YAHPAEH0@Z
// int __cdecl NestedInclude(unsigned char *, int, unsigned char *)

// ?esc_sequence@@YAPAEPAE0@Z
// unsigned char * __cdecl esc_sequence(unsigned char *, unsigned char *)

// ?emit_line@@YAXXZ
// void __cdecl emit_line(void)

// ?io_eob@@YAHXZ
// int __cdecl io_eob(void)

// ?InitializeStandardIdentifiers@@YAXXZ
// void __cdecl InitializeStandardIdentifiers(void)

// ?pbStartOfCurBuf@@YAPAEXZ
// unsigned char * __cdecl pbStartOfCurBuf(void)

// ?cbRemainingInBuffer@@YAJXZ
// long __cdecl cbRemainingInBuffer(void)

// ?fEOF@@YAHXZ
// int __cdecl fEOF(void)

// ?fICCSkipFn@@YAHJG@Z
// int __cdecl fICCSkipFn(long, unsigned short)

// ?p0_init@@YAXPAUlist@@@Z
// void __cdecl p0_init(struct list *)

// ?CommandDef@@YAXPAD@Z
// void __cdecl CommandDef(char *)

// ?WriteMessage@@YAXPAD@Z
// void __cdecl WriteMessage(char *)

// ?FixFileNamePointers@@YAXXZ
// void __cdecl FixFileNamePointers(void)

// ?PrevCharWasInitialNewLine@@YAHXZ
// int __cdecl PrevCharWasInitialNewLine(void)

// ?getFileName@Position@@QBEPAEXZ
// public: unsigned char * __thiscall Position::getFileName(void) const

extern void InitIncludeList();

#endif /* P0IO_H */
