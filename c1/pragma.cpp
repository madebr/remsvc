#include "pragma.h"

#include "decomp.h"

// GLOBAL: MSVC5_C1 0x000018c4
// ?PstatOptPragMask@@3KA
// unsigned long PstatOptPragMask

// GLOBAL: MSVC5_C1 0x000018c8
// ?PstatClearOptPragMask@@3KA
// unsigned long PstatClearOptPragMask

// GLOBAL: MSVC5_C1 0x000055f8
// ?Pragma_attrs@@3PBUIL_INFO@@B
// struct IL_INFO const *Pragma_attrs

// GLOBAL: MSVC5_C1 0x00005730
// ??_C@_01PNMI@?$BI?$AA@
// "\x18"

// GLOBAL: MSVC5_C1 0x00005734
// ??_C@_01PMJF@?$BH?$AA@
// "\x17"

// GLOBAL: MSVC5_C1 0x00005738
// ??_C@_01PEMH@q?$AA@
// "q"

// GLOBAL: MSVC5_C1 0x0000573c
// ??_C@_01DCM@?$BE?$AA@
// "\x14"

// GLOBAL: MSVC5_C1 0x00005740
// ??_C@_01KCAO@b?$AA@
// "b"

// GLOBAL: MSVC5_C1 0x00005744
// ??_C@_01KLMK@?$AO?$AA@
// "\x0E"

// GLOBAL: MSVC5_C1 0x00005748
// ??_C@_01FEHD@?$AN?$AA@
// "\r"

// GLOBAL: MSVC5_C1 0x0000574c
// ??_C@_01POOE@?$AM?$AA@
// "\f"

// GLOBAL: MSVC5_C1 0x00005750
// ??_C@_01POCP@?7?$AA@
// "\t"

// GLOBAL: MSVC5_C1 0x00005754
// ??_C@_01FFOF@?$AH?$AA@
// "\a"

// GLOBAL: MSVC5_C1 0x00005758
// ??_C@_01FGMJ@?$BD?$AA@
// "\x13"

// GLOBAL: MSVC5_C1 0x0000575c
// ??_C@_01KKJH@?$AB?$AA@
// "\x01"

// GLOBAL: MSVC5_C1 0x00005760
// ??_C@_01PMFO@?$BC?$AA@
// "\x12"

// GLOBAL: MSVC5_C1 0x00007f60
// ?PstatInitState@@3KA
// GLOBAL: C1 0x00469308
unsigned int PstatInitState = 0;

// FUNCTION: MSVC5_C1 0x0003d0c0
// ?PstatGetStatus@@YAKXZ
// FUNCTION: C1 0x004082bf
unsigned int PstatGetStatus()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x0003d0f0
// ?PstatSetFlags@@YAXK@Z
// void __cdecl PstatSetFlags(unsigned long)

