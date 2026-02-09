#include "decomp.h"

#include "alloc.h"
#include "browser.h"
#include "incremental.h"
#include "../pch.h"
#include "../types.h"
#include "classes.h"

#include "../msvcrt.h"

#include <io.h>
#include <locale.h>
#include <mbctype.h>
#include <mbstring.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#define CHARACTER_CLASS1(C) (Charmap[(uint8_t)(C)])
#define CHARACTER_CLASS2(C) (gCharacter_classes_2[(uint8_t)(C)])
#define CHARACTER_CLASS3(C) (Contmap[(uint8_t)(C)])

#define MAX_ARG_COUNT (200)

// GLOBAL: C1 0x0045b0b0
uint8_t Charmap[256] = {
    0x00, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x01, 0x05, 0x01, 0x01, 0x02, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x00, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x01, 0x0a, 0x16, 0x0b, 0x24, 0x0c, 0x10, 0x15,
    0x04, 0x1c, 0x08, 0x11, 0x1b, 0x12, 0x09, 0x03,
    0x1d, 0x1d, 0x1d, 0x1d, 0x1d, 0x1d, 0x1d, 0x1d,
    0x1d, 0x1d, 0x1a, 0x20, 0x13, 0x0d, 0x14, 0x00,
    0x22, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
    0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x06, 0x06,
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
    0x06, 0x06, 0x06, 0x1f, 0x00, 0x19, 0x0e, 0x06,
    0x24, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
    0x06, 0x06, 0x06, 0x1e, 0x0f, 0x18, 0x17, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
};

// GLOBAL: C1 0x0045b1b0
uint8_t gCharacter_classes_2[256] = {
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x40, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
    0x1d, 0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
    0x00, 0x19, 0x39, 0x19, 0x39, 0x19, 0x19, 0x11,
    0x31, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x31,
    0x11, 0x31, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
    0x11, 0x11, 0x11, 0x00, 0x80, 0x00, 0x00, 0x11,
    0x00, 0x19, 0x39, 0x19, 0x39, 0x19, 0x19, 0x11,
    0x31, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x31,
    0x11, 0x31, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
    0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// GLOBAL: C1 0x0045b2b0
uint8_t Contmap[256] = {
    0x10, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x05, 0x06, 0x11, 0x06, 0x06, 0x06, 0x05, 0x05,
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x05, 0x05, 0x10, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x16, 0x05, 0x15, 0x05, 0x05, 0x05, 0x05, 0x15,
    0x05, 0x05, 0x01, 0x05, 0x05, 0x05, 0x05, 0x14,
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x11,
    0x05, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d,
    0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d,
    0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d,
    0x0d, 0x0d, 0x0d, 0x05, 0x10, 0x05, 0x05, 0x0d,
    0x05, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d,
    0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d,
    0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d,
    0x0d, 0x0d, 0x0d, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// GLOBAL: C1 0x0045c6cc
BOOLEAN HandlingControlC = FALSE;

// GLOBAL: C1 0x00468c20
int gCountTimings = 0;

// GLOBAL: C1 0x00468c1c
DWORD gPrevTickCount = 0;

// GLOBAL: C1 0x00468c30
tTiming gTimings[20];

// GLOBAL: C1 0x0045c580
int ExecutionState = 0;

// GLOBAL: C1 0x00467040
int Argc;

// GLOBAL: C1 0x00467044
char **Argv = NULL;

// GLOBAL: C1 0x0045b530
char **NewArgv = NULL;

// GLOBAL: C1 0x0045c6d8
SYSTEM_INFO gSystem_info = {
    {0},
    4096,    // dwPageSize
    NULL,    // lpMinimumApplicationAddress
    NULL,    // lpMaximumApplicationAddress
    0,       // dwActiveProcessorMask
    0,       // dwNumberOfProcessors
    0,       // dwProcessorType
    0x10000, // dwAllocationGranularity
    0,       // wProcessorLevel
    0,       // wProcessorRevision
};

// GLOBAL: C1 0x0045bf94
unsigned int gUINT_0045bf94 = 0;

// GLOBAL: C1 0x0045bf98
unsigned int gUINT_0045bf98 = 0;

// GLOBAL: C1 x00045e3e8
uintptr_t pMacroActBase = 0;

// GLOBAL: C1 0x0045e3ec
uintptr_t pMacroExpBase = 0;

// GLBOAL: C1 0x0045cbb8
uintptr_t pMacroActEnd = 0;

// GLOBAL: C1 0x0045cbc0
uintptr_t pMacroExpEnd = 0;

// GLOBAL: C1 0x00466460
int Nerrors = 0;

// GLOBAL: C1 0x0045c6fc
HANDLE gTerminalSignalSemaphore = NULL;

// GLOBAL: C1 0x0045c4b0
int gBm_value = 0;

// GLOBAL: C1 0x0045c0b4
int gZB_value = 0;

// GLOBAL: C1 0x0045cb2c
int gPCH_memory_scaling_factor = 100;

// GLOBAL: C1 0x00457ec0
tPCH_chunk_info gPCH_chunk_infos[6] = {
        {
                0, 50 * 1024 * 1024, 64 * 1024, 0x21, 1,
        },
        {
                1, 10 * 1024 * 1024, 32 * 1024, 0x10, 4,
        },
        {
                2, 10 * 1024 * 1024, 32 * 1024, 0x18, 4,
        },
        {
                3, 5 * 1024 * 1024, 16 * 1024, 0x18, 4,
        },
        {
                4, 5 * 1024 * 1024, 32 * 1024, 0x18, 4,
        },
        {
                5, 5 * 1024 * 1024, 32 * 1024, 0x18, 4,
        },
};

// GLOBAL: C1 0x0046a378
tPCH_chunk gPCH_chunks[6];

// GLOBAL: C1 0x00466298
VirtualHeap gPCH_allocated_chunk_00466298;

// GLOBAL: C1 0x004664a0
VirtualHeap gPCH_allocated_chunk_004664a0;

// GLOBAL: C1 0x00466468
VirtualHeap gPCH_allocated_chunk_00466468;

// GLOBAL: C1 0x00460a40
VirtualHeap gPCH_allocated_chunk_00460a40;

// GLOBAL: C1 0x00460998
VirtualHeap gPCH_allocated_chunk_00460998;

// GLOBAL: C1 0x00466170
VirtualHeap gPCH_allocated_chunk_00466170;

// GLOBAL: C1 0x004660f8
VirtualHeap gPCH_allocated_chunk_004660f8;

// GLOBAL: C1 0x00466040
VirtualHeap gPCH_allocated_chunk_00466040;

// GLOBAL: C1 0x00460a18
VirtualHeap gPCH_allocated_chunk_00460a18;

// GLOBAL: C1 0x00466e38
int32_t gTo_lower_lut[256];

// GLOBAL: C1 0x00455230
tDefault_warning_severity gDefault_warning_severities[] = {
    { 1, 5 },
    { 49, 5 },
    { 69, 5 },
    { 611, 5 },
    { 226, 14 },
    { 233, 14 },
    { 234, 14 },
    { 235, 14 },
    { 168, 5 },
    { 169, 5 },
    { 0, 0 },
};

// GLOBAL: C1 0x0045bf88
int gMin_pragma_warning = 1000;

// GLOBAL: C1 0x0045bf8c
int gMax_pragma_warning = 700;

// GLOBAL: C1 0x0045bba0
uint8_t gWarning_severities[1000];

// GLOBAL: C1 0x0045b5bc
tStruct_0045b5bc *gPTR_0045b5bc;

// GLOBAL: C1 0x0045f5c0
uint8_t crcTh[256];

// GLOBAL: C1 0x0045f4c0
uint8_t gHash_permutation_lut[256];

// GLOBAL: C1 0x0045f6c0
uint8_t crcTl[256];

// GLOBAL: C1 0x00453080
const uint32_t gCVHash_shift_lut[8] = {
        0, 1, 3, 6, 8, 13, 15, UINT32_MAX,
};

// GLOBAL: C1 0x00466150
tStringVector *listDefs;

// GLOBAL: C1 0x00460a84
tStringVector *listIncludes;

// GLOBAL: C1 0x00466118
tStringVector *listForcedIncludes;

// GLOBAL: C1 0x004662d0
tSigPbCb crc32ClCmd;

// GLOBAL: C1 0x0046714c
char *gOption_rsp_path;

// GLOBAL: C1 0x004664f4
BOOL gOption_nologo = FALSE;

// GLOBAL: C1 0x004664fc
BOOL gOption_FAT = FALSE;

// GLOBAL: C1 0x00466500
BOOL gWrite_er = FALSE;

// GLOBAL: C1 0x0045c53c
const char *gOption_pc_map = "\\:/";

// GLOBAL: C1 0x00466450
BOOL Cflag = FALSE;

// GLOBAL: C1 0x00466314
BOOL Prep = FALSE;

// GLOBAL: C1 0x00466274
const char *gOption_Fi_path = NULL;

// GLOBAL: C1 0x00463a98
const char *Input_file = NULL;

// GLOBAL: C1 0x0045c4b0
int32_t MemoryStatsLevel = 0;

// GLOBAL: C1 0x00467038
int32_t gOption_memory = 0;
// GLOBAL: C1 0x004664b0
tStruct_00466458 gStruct_004664b0;

// GLOBAL: C1 0x004662a8
tStruct_00466458 gStruct_004662a8;

// GLOBAL: C1 0x00466458
tStruct_00466458 *gPTR_00466458 = NULL;

// GLOBAL: C1 0x004664c4
BOOL WarnIsError = FALSE;

// GLOBAL: C1 0x0045c514
int32_t gOption_W = 1;

// GLOBAL: C1 0x0045c548
int32_t gOption_Zp = -1;

// GLOBAL: C1 0x0045c0a8
tStruct_0045c0a8 PchC = {
    FALSE,  /* ZE */
    FALSE,  /* Ze */
    FALSE,  /* ZBe */
    -1,     /* ZB */
    FALSE,  /* Gr */
    TRUE,   /* field_0x14 */
    FALSE,  /* Jd */
    FALSE,  /* J */
    FALSE,  /* field_0x20 */
    FALSE,  /* field_0x24 */
    FALSE,  /* field_0x28 */
    FALSE,  /* field_0x2c */
    FALSE,  /* field_0x30 */
    TRUE,   /* field_0x34 */
    FALSE,  /* MD */
    FALSE,  /* MT */
    FALSE,  /* Gc */
    FALSE,  /* Zi */
    FALSE,  /* Yd */
    0,      /* field_0x4c */
    0,      /* field_0x4e */
    FALSE,  /* EP */
    FALSE,  /* pf */
    FALSE,  /* Bd */
    175,    /* Bu */
    FALSE,  /* Brepro */
    FALSE,  /* field_0x64 */
    FALSE,  /* Oi */
    TRUE,   /* Gs */
    0,      /* field_0x74 */
    -1,     /* field_0x78 */
    FALSE,  /* Gd */
    FALSE,  /* Gz */
    FALSE,  /* Gf */
    FALSE,  /* field_0x84 */
    FALSE,  /* GF */
    FALSE,  /* field_0x8c */
    FALSE,  /* cbstring */
    0,      /* G */
    FALSE,  /* GM */
    0,      /* Ob */
    FALSE,  /* field_0xa0 */
    FALSE,  /* field_0xa4 */
    0,      /* optimization_flags_0xa8 */
    0,      /* field_0xac */
    FALSE,  /* C8MODE */
    TRUE,   /* bool_0xb4 */
    TRUE,   /* Ot */
    FALSE,  /* Oa */
    FALSE,  /* Ow */
    FALSE,  /* Og */
    FALSE,  /* Op */
    FALSE,  /* Oy */
    TRUE,   /* p_FUseTypeServer */
    "",     /* p_FdName */
    "",     /* Yl_path */
    "",     /* local_pch_path */
    FALSE,  /* Oq */
    FALSE,  /* bool_0x3dc */
    FALSE,  /* Ov */
    0,      /* field_0x3e4 */
    0,      /* field_0x3e8 */
    FALSE,  /* C9IL */
    FALSE,  /* Gi */
    FALSE,  /* GI */
    0,      /* field_0x3f8 */
    TRUE,   /* GFR */
    TRUE,   /* splitPdbs */
    FALSE,  /* NoEHForNew */
};

// GLOBAL: C1 0x0045c0a8
BOOL gOption_ZE = FALSE;

// GLOBAL: C1 0x0045c0ac
BOOL gOption_Ze = FALSE;

// GLOBAL: C1 0x0045c58c
BOOL gOption_Z7 = FALSE;

// GLOBAL: C1 0x00460a28
BOOL gOption_Zn = FALSE;

// GLOBAL: C1 0x0046603c
BOOL gOption_Zf = FALSE;

// GLOBAL: C1 0x00466164
BOOL Out_funcdef = FALSE;

// GLOBAL: C1 0x00460a10
BOOL gOption_ZI = FALSE;

// GLOBAL: C1 0x0045c540
const char *gDiagnostic_messages_path = "c1.err";

// GLOBAL: C1 0x0045c544
const char *Basename = "";

// GLOBAL: C1 0x00466484
BOOL gOption_xc = FALSE;

// GLOBAL: C1 0x00466484
const char *gOption_V_path = NULL;

// GLOBAL: C1 0x0045c4f8
const char *gOption_NV_path = NULL;

// GLOBAL: C1 0x00466318
const char *SourceBrowserNamFlg = NULL;

// GLOBAL: C1 0x004662d8
const char *SourceBrowserExt = NULL;

// GLOBAL: C1 0x0045c504
const char *gOption_Fj = FALSE;

// GLOBAL: C1 0x0045c50c
const char *gPDB_arg_path = "vc40.pdb";

// GLOBAL: C1 0x0045c508
const char *gObject_output_arg_path = NULL;

// GLOBAL: C1 0x0045c144
int32_t gOption_Ob = 0;

// GLOBAL: C1 0x0046703c
BOOL gOption_debugBreak = FALSE;

// GLOBAL: C1 0x0045c57c
BOOL gPrint_timings = FALSE;

// GLOBAL: C1 0x0045c4b8
const char *PchUFile = NULL;

// GLOBAL: C1 0x0045c4b4
BOOL PchUFlag = FALSE;

// GLOBAL: C1 0x0045c4c0
const char *PchCFile = NULL;

// GLOBAL: C1 0x0045c4bc
BOOL PchCFlag = FALSE;

// GLOBAL: C1 0x0045c4d0
const char *PchPFile = NULL;

// GLOBAL: C1 0x0045c4c8
const char *gYX_arg_path = NULL;

// GLOBAL: C1 0x0045c4c4
BOOL gOption_YX = FALSE;

// GLOBAL: C1 0x0045c4cc
const char *gYl_arg_path = NULL;

// GLOBAL: C1 0x0045c4e8
BOOL fPersistentPch = TRUE;

// GLOBAL: C1 0x0045c568
BOOL gOption_noexpinl = FALSE;

// GLOBAL: C1 0x0045cb28
BOOL gOption_BMOVE = FALSE;

// GLOBAL: C1 0x0046611c
BOOL gOption_BShowIncl = FALSE;

// GLOBAL: C1 0x0045c588
const char *Unknown_ = NULL;

// GLOBAL: C1 0x0045f4b8
const char *ErrString = NULL;

// GLOBAL: C1 0x0045b56c
ISourceBrowser *pSbr;

// GLOBAL: C1 0x00454d50
const subtab Ztab[11] = {
    { 'a', 0x5, { &gOption_Ze, }, },
    { 'e', 0x1, { &gOption_Ze, }, },
    { 'E', 0x1, { &PchC.option_ZE, }, },
    { 'i', 0x1, { &PchC.p_Symbolic_debug_holder, }, },
    { '7', 0x1, { &gOption_Z7, }, },
    { 'n', 0x1, { &gOption_Zn, }, },
    { 'f', 0x1, { &gOption_Zf, }, },
    { 'g', 0x1, { &Out_funcdef, }, },
    { 'p', 0x1, { &gOption_Zp, }, },
    { 'I', 0x1, { &gOption_ZI, }, },
    { 0 },
};

// GLOBAL: C1 0x00454dd8
cmdtab cmdtab[89] = {
    { "@$", { &gOption_rsp_path }, true, 0x22, },
    { "-nologo", { &gOption_nologo }, true, 0x01, },
    { "-FAT", { &gOption_FAT }, true, 0x01, },
    { "-pc#", { &gOption_pc_map }, true, 0x22, },
    { "-pf", { &PchC.option_pf }, true, 0x01, },
    { "-C", { &Cflag }, true, 0x01, },
    { "-D#", { &listDefs }, true, 0x26, },
    { "-E", { &Prep }, true, 0x01, },
    { "-I#", { &listIncludes }, true, 0x26, },
    { "-FI#", { &listForcedIncludes }, true, 0x26, },
    { "-EP", { &PchC.p_NoPoundLines }, true, 0x01, },
    { "-Fi#", { &gOption_Fi_path }, true, 0x22, },
    { "-f", { &Input_file }, true, 0x22, },
    { "-J", { &PchC.option_J }, true, 0x01, },
    { "-Jd", { &PchC.option_Jd }, true, 0x01, },
    { "-Bd%", { &PchC.option_Bd }, true, 0x01, },
    { "-Bu#", { &PchC.option_Bu }, true, 0x24, },
    { "-Bm#", { &MemoryStatsLevel }, true, 0x24, },
    { "-Bvb#", { &gOption_memory }, true, 0x24, },
    { "-Bvm#", { &gOption_memory }, true, 0x24, },
    { "-Zm#", { &gOption_memory }, true, 0x24, },
    { "-Brepro", { &PchC.p_fReproduceable }, true, 0x01, },
    { "-MT", { &PchC.option_MT }, true, 0x01, },
    { "-MD", { &PchC.option_MD }, true, 0x01, },
    { "-WX", { &WarnIsError }, true, 0x01, },
    { "-W#", { &gOption_W }, true, 0x24, },
    { "-Zp", { &gOption_Zp }, true, 0x01, },
    { "-Zp#", { &gOption_Zp }, true, 0x24, },
    { "-ZBe", { &PchC.p_BigIntExtension }, true, 0x01, },
    { "-ZB", { &PchC.p_SizeOfBigInt }, true, 0x01, },
    { "-ZB*", { &PchC.p_SizeOfBigInt }, true, 0x24, },
    { "-Z*", { &Ztab }, true, 0x23, },
    { "-ef#", { &gDiagnostic_messages_path }, true, 0x22, },
    { "-il$", { &Basename }, true, 0x22, },
    { "-xc", { &gOption_xc }, true, 0x01, },
    { "-V#", { &gOption_V_path }, true, 0x22, },
    { "-Gs", { &PchC.option_Gs }, true, 0x05, },
    { "-Gc", { &PchC.option_Gc }, true, 0x01, },
    { "-Gr", { &PchC.option_Gr }, true, 0x01, },
    { "-Gd", { &PchC.option_Gd }, true, 0x01, },
    { "-Gz", { &PchC.option_Gz }, true, 0x01, },
    { "-Gi", { &PchC.option_Gi }, true, 0x01, },
    { "-GI", { &PchC.option_GI }, true, 0x01, },
    { "-GFR", { &PchC.p_Cmd_fICCBrowse }, true, 0x01, },
    { "-GFR-", { &PchC.p_Cmd_fICCBrowse }, true, 0x05, },
    { "-NV#", { &gOption_NV_path }, true, 0x22, },
    { "-Fr#", { &SourceBrowserNamFlg }, true, 0x22, },
    { "-FR#", { &SourceBrowserExt }, true, 0x22, },
    { "-Fj", { &gOption_Fj }, true, 0x01, },
    { "-Fd#", { &gPDB_arg_path }, true, 0x22, },
    { "-Fo*", { &gObject_output_arg_path }, true, 0x22, },
    { "-Gf", { &PchC.option_Gf }, true, 0x01, },
    { "-GF", { &PchC.option_GF }, true, 0x01, },
    { "-cbstring", { &PchC.option_cbstring }, true, 0x01, },
    { "-Oa", { &PchC.option_Oa }, true, 0x01, },
    { "-Ob#", { &gOption_Ob }, true, 0x24, },
    { "-Oi", { &PchC.option_Oi }, true, 0x01, },
    { "-Og", { &PchC.option_Og }, true, 0x01, },
    { "-Op", { &PchC.option_Op }, true, 0x01, },
    { "-Os", { &PchC.option_Ot }, true, 0x05, },
    { "-Ot", { &PchC.option_Ot }, true, 0x01, },
    { "-Ow", { &PchC.option_Ow }, true, 0x01, },
    { "-Oq", { &PchC.option_Oq }, true, 0x01, },
    { "-Ov", { &PchC.option_Ov }, true, 0x01, },
    { "-Oy", { &PchC.option_Oy }, true, 0x01, },
    { "-C8MODE", { &PchC.option_C8MODE }, true, 0x01, },
    { "-debugBreak%", { &gOption_debugBreak }, true, 0x01, },
    { "-Times%", { &gPrint_timings }, true, 0x01, },
    { "-Yu*", { &PchUFile }, true, 0x22, },
    { "-Yu", { &PchUFlag }, true, 0x01, },
    { "-Yc*", { &PchCFile }, true, 0x22, },
    { "-Yc", { &PchCFlag }, true, 0x01, },
    { "-Yd", { &PchC.p_PchDFlag }, true, 0x01, },
    { "-Fp#", { &PchPFile }, true, 0x22, },
    { "-YX*", { &gYX_arg_path }, true, 0x22, },
    { "-YX", { &gOption_YX }, true, 0x01, },
    { "-Yl*", { &gYl_arg_path }, true, 0x22, },
    { "-BNOPPCH", { &fPersistentPch }, true, 0x05, },
    { "-noexpinl", { &gOption_noexpinl }, true, 0x01, },
    { "-GM", { &PchC.option_GM }, true, 0x01, },
    { "-G#", { &PchC.option_G }, true, 0x24, },
    { "-BMOVE", { &gOption_BMOVE }, true, 0x01, },
    { "-C9IL", { &PchC.option_C9IL }, true, 0x01, },
    { "-SplitPdbs", { &PchC.p_Cmd_splitPdbs }, true, 0x01, },
    { "-SplitPdbs-", { &PchC.p_Cmd_splitPdbs }, true, 0x05, },
    { "-NoEHForNew", { &PchC.option_NoEHForNew }, true, 0x01, },
    { "-Bshow_incl", { &gOption_BShowIncl }, true, 0x01, },
    { "*", { &Unknown_ }, false, 0x22, },
    { 0 },
};

// GLOBAL: C1 0x0045b5b8
tPragma_stack *gPragma_stack = NULL;

// GLOBAL: C1 0x0046644c
FILE *gDiagnostics_file = NULL;

// GLOBAL: C1 0x00469208
char gError_message_buffer[256];

// GLOBAL: C1 0x00469168
tDiagnostic_file_offset gDiagnostic_file_offsets[20];

// GLOBAL: C1 0x0045c7b0
int gError_message_file_pos = 0;

// GLOBAL: C1 0x0045c7b4
BOOL gDiagnostic_strings_initialized = FALSE;

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

// GLOBAL: C1 0x0045e450
tCurrent_file_thing_0045e450 tokenInputStack;

// GLOBAL: C1 0x00460a50
FILE *gFile_er = NULL;

// GLOBAL: C1 0x004662c0
FILE *gFile_lp = NULL;

// GLOBAL: C1 0x004663a8
IStruct_Incremental1 *gIncremental_interface1;

// GLOBAL: C1 0x0046a310
IStruct_Incremental2 *gIncremental_interface2;

// GLOBAL: C1 0x004664d0
IStruct_Incremental3 *gIncremental_interface3;

// GLOBAL: C1 0x00466488
uint32_t gOption_G_flags = 0;

// GLOBAL: C1 0x004662cc
const char *SourceBrowserNam = NULL;

// GLOBAL: C1 0x004663b0
BOOL PchOldUFlag;

// GLOBAL: C1 0x004663bc
const char *gOriginal_option_Yu_path;

// GLOBAL: C1 0x0045f994
BOOL fReusePersistPch;

// GLOBAL: C1 0x0046630c
BOOL fGenPersistPch;

// GLOBAL: C1 0x0045c4e0
BOOL gBOOL_0045c4e0;

// GLOBAL: C1 0x0045c4ec
BOOL PchReuseCVTypes;

// GLOBAL: C1 0x00466120
tFILESTREAM ilsLSym;

// GLOBAL: C1 0x004609e0
tFILESTREAM ilsGSym;

// GLOBAL: C1 0x004662e0
tFILESTREAM ilsInit;

// GLOBAL: C1 0x00460a58
tFILESTREAM ildsDB;

// GLOBAL: C1 0x00466010
tFILESTREAM ilsExp;

// GLOBAL: C1 0x004609b0
tFILESTREAM gFILESTREAM_004609b0;

// GLOBAL: C1 0x00465fb0
tFILESTREAM gFILESTREAM_00465fb0;

// GLOBAL: C1 0x00466454
FILE *gFi_file;

// GLOBAL: C1 0x00466294
FILE *I_Eoutput;

// GLOBAL: C1 0x0045b67c
tStruct_00401000 *gPTR_0045b67c;

// GLOBAL: C1 0x0045b670
tStruct_00401000 *gPTR_0045b670;

// GLOBAL: C1 0x0045b630
tStruct_00401000 *gPTR_0045b630;

// GLOBAL: C1 0x0045b674
tStruct_00401000 *gPTR_0045b674;

// GLOBAL: C1 0x0045b634
tStruct_00401000 *gPTR_0045b634;

// GLOBAL: C1 0x0045b638
tStruct_00401000 *gPTR_0045b638;

// GLOBAL: C1 0x0045b63c
tStruct_00401000 *gPTR_0045b63c;

// GLOBAL: C1 0x0045b640
tStruct_00401000 *gPTR_0045b640;

// GLOBAL: C1 0x0045b644
tStruct_00401000 *gPTR_0045b644;

// GLOBAL: C1 0x0045b648
tStruct_00401000 *gPTR_0045b648;

// GLOBAL: C1 0x0045b64c
tStruct_00401000 *gPTR_0045b64c;

// GLOBAL: C1 0x0045b650
tStruct_00401000 *gPTR_0045b650;

// GLOBAL: C1 0x0045b678
tStruct_00401000 *gPTR_0045b678;

// GLOBAL: C1 0x0045b668
tStruct_00401000 *gPTR_0045b668;

// GLOBAL: C1 0x0045b66c
tStruct_00401000 *gPTR_0045b66c;

// GLOBAL: C1 0x0045b65c
tStruct_00401000 *gPTR_0045b65c;

// GLOBAL: C1 0x0045b660
tStruct_00401000 *gPTR_0045b660;

// GLOBAL: C1 0x0045b62c
tStruct_00401000 *gPTR_0045b62c;

// GLOBAL: C1 0x0045b664
tStruct_00401000 *gPTR_0045b664;

// GLOBAL: C1 0x0045b680
tStruct_00401000 *gPTR_0045b680;

// GLOBAL: C1 0x0045b620
tStruct_00401000 *gPTR_0045b620;

// GLOBAL: C1 0x0045b628
tStruct_00401000 *gPTR_0045b628;

// GLOBAL: C1 0x0045b624
tStruct_00401000 *gPTR_0045b624;

// GLOBAL: C1 0x004664a0
VirtualHeap g_PCH_allocated_chunk_004664a0;

// GLOBAL: C1 0x0045b690
tStruct_0045b690 *gStruct_0045b690;

// GLOBAL: C1 0x0045b684
undefined4 gUNK_0045b684;

// GLOBAL: C1 0x0045b688
tStruct_00401000 *gUNK_0045b688;

// GLOBAL: C1 0x0045e478
tStruct_0045e478 *gPTR_0045e478;

// GLOBAL: 0x00469308
uint32_t gOptimization_flags_00469308;

// GLOBAL: C1 0x00469158
int gINT_00469158; // 0, 1, or 2

// GLOBAL: C1 0x00468d50
tStruct_0045c0a8 gOptions_PCH_00468d50;

// GLOBAL: C1 0x0045c6d0
BOOL gBOOL_0045c6d0;

// GLOBAL: C1 0xgBOOL_0045f98c
BOOL gBOOL_0045f98c;

// GLOBAL: C1 0x00465fe0
tFILESTREAM gFILESTREAM_00465fe0;

// GLOBAL: C1 0x004565d0
const bool gBOOL_ARRAY_004565d0[254] = {
        false, true,  true,  true,
        true,  true,  false, false,
        false, false, false, false,
        false, false, false, true,
        true,  true,  true,  true,
        true,  true,  true,  true,
        true,  true,  true,  true,
        true,  true,  false, true,
        true,  true,  true,  true,
        true,  false, false, false,
        false, false, false, false,
        true,  true,  true,  false,
        true,  true,  true,  true,
        true,  false, true,  true,
        true,  true,  true,  true,
        false, true,  true,  true,
        true,  true,  true,  true,
        false, true,  true,  true,
        true,  true,  true,  true,
        true,  true,  true,  true,
        true,  true,  true,  true,
        true,  true,  true,  true,
        true,  true,  true,  true,
        true,  true,  true,  true,
        true,  true,  true,  true,
        false, true,  false, false,
        false, true,  true,  false,
        false, true,  true,  false,
        true,  true,  true,  false,
        true,  false, true,  false,
        true,  true,  false, false,
        true,  true,  false, false,
        true,  true,  true,  false,
        true,  true,  true,  false,
        true,  true,  false, true,
        false, true,  true,  true,
        true,  true,  true,  true,
        true,  false, false, true,
        false, true,  true,  false,
        true,  false, true,  false,
        false, false, false, false,
        false, false, false, false,
        false, false, false, false,
        false, false, true,  true,
        true,  false, false, true,
        false, true,  true,  true,
        true,  true,  true,  true,
        true,  false, false, true,
        true,  true,  false, false,
        false, true,  true,  true,
        true,  false, false, true,
        false, false, false, false,
        false, false, true,  false,
        true,  false, false, true,
        true,  true,  true,  true,
        true,  true,  true,  true,
        false, false, false, false,
        false, false, false, false,
        false, false, true,  false,
        true,  false, true,  true,
        true,  false, false, true,
        true,  true,  true,  false,
        false, false, false, true,
        true,  false,
};

// GLOBAL: C1 0x00452860
tStruct_00452860 gReserved_keyword_token_values[112] = {
    { "auto", 15 },
    { "break", 105 },
    { "case", 106 },
    { "char", 23 },
    { "const", 54 },
    { "continue", 109 },
    { "default", 110 },
    { "do", 112 },
    { "double", 26 },
    { "else", 114 },
    { "enum", 34 },
    { "extern", 17 },
    { "float", 25 },
    { "for", 118 },
    { "goto", 120 },
    { "if", 121 },
    { "int", 24 },
    { "long", 28 },
    { "register", 18 },
    { "return", 132 },
    { "short", 27 },
    { "signed", 31 },
    { "sizeof", 136 },
    { "static", 16 },
    { "struct", 35 },
    { "switch", 139 },
    { "typedef", 19 },
    { "union", 36 },
    { "unsigned", 32 },
    { "void", 29 },
    { "volatile", 55 },
    { "while", 142 },
    { "__inline", 21 },
    { "__cdecl", 44 },
    { "__based", 51 },
    { "__stdcall", 137 },
    { "__declspec", 199 },
    { "asm", 182 },
    { "catch", 183 },
    { "class", 33 },
    { "const_cast", 245 },
    { "delete", 148 },
    { "dynamic_cast", 246 },
    { "friend", 20 },
    { "inline", 21 },
    { "new", 147 },
    { "operator", 158 },
    { "private", 144 },
    { "protected", 145 },
    { "public", 146 },
    { "reinterpret_cast", 238 },
    { "static_cast", 212 },
    { "template", 184 },
    { "this", 151 },
    { "throw", 185 },
    { "try", 186 },
    { "typeid", 128 },
    { "virtual", 22 },
    { "namespace", 243 },
    { "using", 244 },
    { "__single_inheritance", 191 },
    { "__multiple_inheritance", 192 },
    { "__virtual_inheritance", 193 },
    { "__novtordisp", 181 },
    { "__resume", 251 },
    { "__nounwind", 251 },
    { "__syscall", 251 },
    { "__near", 251 },
    { "__far", 251 },
    { "__far16", 251 },
    { "__huge", 251 },
    { "__fortran", 251 },
    { "__export", 251 },
    { "__interrupt", 251 },
    { "__loadds", 251 },
    { "__saveregs", 251 },
    { "__segment", 251 },
    { "__segname", 251 },
    { "__self", 251 },
    { "__thiscall", 198 },
    { "cdecl", 44 },
    { "far", 251 },
    { "fortran", 251 },
    { "huge", 251 },
    { "near", 251 },
    { "pascal", 239 },
    { "__pascal", 240 },
    { "__try", 174 },
    { "__except", 175 },
    { "__finally", 176 },
    { "__leave", 188 },
    { "__asm", 49 },
    { "__fastcall", 45 },
    { "__unaligned", 200 },
    { "__builtin_alignof", 187 },
    { "__sysapi", 197 },
    { "__builtin_isfloat", 236 },
    { "__wchar_t", 234 },
    { "__restrict", 46 },
    { "__int8", 219 },
    { "__int16", 220 },
    { "__int32", 221 },
    { "__int64", 222 },
    { "__int128", 223 },
    { "wchar_t", 234 },
    { "bool", 251 },
    { "true", 251 },
    { "false", 251 },
    { "mutable", 251 },
    { "explicit", 251 },
    { "typename", 251 },
    { NULL, 0 },
};

tStruct_00452be0 gExtendedDeclModifiers[7] = {
    { "dllimport", 6, 2, 0},
    { "dllexport", 7, 3, 0 },
    { "inline", 3, 1, 0 },
    { "naked", 4, 1, 0 },
    { "thread", 5, 1, 0 },
    { "allocate", 8, 1, 1 },
    { NULL, 0, 0, 0 },
};

// GLOBAL: C1 0x0045b5c8
tStruct_0045b5b0_bucket *gCurrent_bucket;

// GLOBAL: C1 0x0045b75c
tStruct_0045b75c *gPTR_ARRAY_0045b75c[254];

// GLOBAL: C1 0x0045b5b0
tStruct_0045b5b0_bucket **gKeywordHashmap;

// GLOBAL: C1 0x00469160
int gILSINK_ErrorCode;

// GLOBAL: C1 0x0045bb64
tStruct_0045bb64 **gPTR_0045bb64;

// GLOBAL: C1 0x0045b5ac
undefined4 **gPTR_0045b5ac;

// GLOBAL: C1 0x0045b5b4
undefined4 **gPTR_0045b5b4;

// GLOBAL: C1 0x0045c6c0
tStruct_0045c6c0 *gPTR_0045c6c0;

// GLOBAL: C1 0x0045c6c4
int gINT_0045c6c4;

// GLOBAL: C1 0x0045c6c8
uint16_t gUSHORT_0045c6c8 = 100;

// GLOBAL: C1 0x0045b5e0
tStruct_0045b5b0_bucket *gPTR_0045b5e0;

// GLOBAL: C1 0x0045b5f4
tStruct_0045b5b0_bucket *gPTR_0045b5f4;

// GLOBAL: C1 0x0045b5f0
tStruct_0045b5b0_bucket *gPTR_0045b5f0;

// GLOBAL: C1 0x0045b5dc
tStruct_0045b5b0_bucket *gPTR_0045b5dc;

// GLOBAL: C1 0x0045b5fc
tStruct_0045b5b0_bucket *gPTR_0045b5fc;

// GLOBAL: C1 0x0045b608
tStruct_0045b5b0_bucket *gPTR_0045b608;

// GLOBAL: C1 0x0045b60c
tStruct_0045b5b0_bucket *gPTR_0045b60c;

// GLOBAL: C1 0x0045b5d4
tStruct_0045b5b0_bucket *gPTR_0045b5d4;

// GLOBAL: C1 0x0045b610
tStruct_0045b5b0_bucket *gPTR_0045b610;

// GLOBAL: C1 0x0045b5e4
tStruct_0045b5b0_bucket *gPTR_0045b5e4;

// GLOBAL: C1 0x0045b5e8
tStruct_0045b5b0_bucket *gPTR_0045b5e8;

// GLOBAL: C1 0x0045b5f8
tStruct_0045b5b0_bucket *gPTR_0045b5f8;

// GLOBAL: C1 0x0045b600
tStruct_0045b5b0_bucket *gPTR_0045b600;

// GLOBAL: C1 0x0045b604
tStruct_0045b5b0_bucket *gPTR_0045b604;

// GLOBAL: C1 0x0045b5ec
tStruct_0045b5b0_bucket *gPTR_0045b5ec;

// GLOBAL: C1 0x0045bb54
tStruct_0045b5b0_bucket *gPTR_0045bb54;

// GLOBAL: C1 0x004520f8
tBucketAndIdentifier gSpecial_identifiers_and_buckets[17] = {
        { &gPTR_0045b5e0, "defined" },
        { &gPTR_0045b5f4, "__formal" },
        { &gPTR_0045b5f0, "..." },
        { &gPTR_0045b5dc, "abstract declarator" },
        { &gPTR_0045b5fc, "main" },
        { &gPTR_0045b608, "WinMain" },
        { &gPTR_0045b60c, "DllMain" },
        { &gPTR_0045b5d4, ".alignment member." },
        { &gPTR_0045b610, "__unnamed" },
        { &gPTR_0045b5e4, "$" },
        { &gPTR_0045b5e8, ".drectve" },
        { &gPTR_0045b5f8, ".local static guard." },
        { &gPTR_0045b600, "_setjmp" },
        { &gPTR_0045b604, "Catch" },
        { &gPTR_0045b5ec, "__LOCAL_SIZE" },
        { &gPTR_0045bb54, "__LINE__Var" },
        { NULL, NULL },
};

BOOL *const PstatFlagMap[21] = {
    &PchC.bool_0xb4,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &PchC.option_Oa,
    &PchC.option_Ow,
    &PchC.option_Ot,
    NULL,
    &PchC.option_Og,
    NULL,
    NULL,
    &PchC.option_Op,
    NULL,
    NULL,
    NULL,
    &PchC.bool_0x3dc,
    &PchC.option_Ov,
    NULL,
    &PchC.option_Oy,
};

// GLOBAL: C1 0x00468c10
tStruct_00468c10 gStruct_00468c10;

// GLOBAL: C1 0xgStruct_0045e470
tStruct_0045e470 gStruct_0045e470;


extern void __fastcall fatal_io_CRT(int code, int category, const char *text);

extern const char *__fastcall GetDiagnosticHelpString(int code);

extern const char *__stdcall GetDiagnosticString(int code, BOOL arg2);

extern char *__fastcall pstrdup(const char *text, int pool_id);

extern void FUN_0041f15f();

extern void OKToHandleCtrlC();

extern void * __fastcall xnew(size_t s);

extern void * __fastcall xrealloc(void *mem, size_t s);

extern void __fastcall fatal_varargs(int code);

// FUNCTION: C1 0x004253ce
void __fastcall WriteStdErr(const char *text)
{
#if 0
    fwrite(text, strlen(text), 1, __p__iob() + STDERR_FILENO);
#endif
    fwrite(text, strlen(text), 1, stderr);
}

// FUNCTION: C1 0x0043f132
void FUN_0043f132()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00442a47
void FUN_00442a47()
{
    NOT_IMPLEMENTED();
}

// FUCNTION: C1 0x0041f0ca
void CleanupMemory()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0044e8b0
void __fastcall FUN_0044e8b0(tStruct_00466458 *arg)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00445a14
void ReleaseEverythingUponError()
{
    FUN_0043f132();
    FUN_0041f15f();
    FUN_00442a47();
    FUN_0044e8b0(&gStruct_004662a8);
    if (gPTR_00466458 != NULL) {
        FUN_0044e8b0(gPTR_00466458);
    }
    CleanupMemory();
    ExecutionState = 8;
    if (HandlingControlC) {
        OKToHandleCtrlC();
    }
}

// FUNCTION: C1 0x0044821d
void __fastcall FatalCompilerStackOverflowError(BOOL show_message)
{
    if (show_message) {
        strcpy(gError_message_buffer, "fatal error C1063:\r\n");
        _write(STDOUT_FILENO, gError_message_buffer, strlen(gError_message_buffer));
    }
    CleanupMemory();
    ExitProcess(3);
}

// FUNCTION: C1 0x00445a9b
void __fastcall AvoidRecursiveFatalError(int stage)
{
    // GLOBAL: C1 0x00468c18
    static int depth = 0;

    int prev_depth = depth;
    depth++;

    if (prev_depth > 0) {
        FatalCompilerStackOverflowError(TRUE);
    }
    ExecutionState = stage;
}

// FUNCTIN: C1 0x00423acd
char *RemoveEscapedCharactersInDiagnosticString(char *str)
{
    str++;
    while (*str != '"') {
        str++;
    }
    char *ptr_read = str;
    char *ptr_write = str;
    while (*ptr_read != '"') {
        if (__p__mbctype()[1 + (unsigned char)*ptr_read] & 0x4) {
            *ptr_write++ = *ptr_read++;
        }
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

// FUNCTION: C1 0x00423a7b
char *ExtractCodeAndTextFromLine(char *buffer, int *code)
{
    int value = 0;

    while (isdigit(*buffer)) {
        value = value * 10 + (*buffer - '0');
        buffer++;
    }
    *code = value;
    return buffer;
}

void CacheDiagnosticFileOFfset(int offset, int code)
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

// FUNCTION: C1 0x004239f8
char *ReadDiagnosticString(int code, char *buffer, size_t bufferSize, BOOL arg4)
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
                    fatal_io_CRT(83, 314, gDiagnostic_messages_path);
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
                CacheDiagnosticFileOFfset(offset, code);
            }
            return RemoveEscapedCharactersInDiagnosticString(text_start);
        } else if (line_code / -1000 == code / -1000) {
            fseek(gDiagnostics_file, 0, SEEK_SET);
            return RemoveEscapedCharactersInDiagnosticString(text_start);
        }
    }
}

// GLOBAL: 0x004239d8
const char *__fastcall LookupDiagnosticHelpString(int code)
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
const char *__fastcall GetDiagnosticHelpString(int code)
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
                diagnostic_code_text->text = pstrdup(text, 1);
            }
        }
        if (gDiagnostics_file != (FILE*)(uintptr_t)-1) {
            gError_message_file_pos = ftell(gDiagnostics_file);
        }
        gDiagnostic_strings_initialized = TRUE;
    }
    return LookupDiagnosticHelpString(code);
}

// FUNCTION: C1 0x00448070
int GetBestErrorFileMessageOffset(int code)
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

// FUNCTION: C1 0x004238b7
const char *__stdcall GetDiagnosticString(int code, BOOL arg2)
{
    if (gDiagnostics_file == NULL) {
        if (gDiagnostic_strings_initialized  || arg2) {
            if (gDiagnostic_messages_path == NULL) {
                gDiagnostics_file = (FILE *)(uintptr_t)-1;
                return "";
            }
            FILE * f = fopen(gDiagnostic_messages_path, "r");
            if (f == NULL) {
                gDiagnostics_file = (FILE *)(uintptr_t)-1;
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
    return ReadDiagnosticString(code, gError_message_buffer, sizeof(gError_message_buffer), arg2);
}

// FUNCTION: C1 0x0040551c
const char *__fastcall GetCurrentSourceFilename(tCurrent_file_thing_0045e450 *arg1)
{
    (void) arg1;
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041545b
undefined4 FUN_0041545b()
{
    int i;
    int found_index = -1;
    for (i = 0; i < gINT_0045c6c4; i++) {
        if (gPTR_0045c6c0[i].id == 0) {
            found_index = i;
        }
    }
    if (found_index == -1) {
        if (gPTR_0045c6c0 == NULL) {
            gPTR_0045c6c0 = (tStruct_0045c6c0 *)xnew(64 * sizeof(tStruct_0045c6c0));
        } else {
            gPTR_0045c6c0 = (tStruct_0045c6c0 *)xrealloc(gPTR_0045c6c0, (gINT_0045c6c4 + 64) * sizeof(tStruct_0045c6c0));
        }
        if (gPTR_0045c6c0 == NULL) {
            fatal_varargs(60);
        }
        memset(&gPTR_0045c6c0[gINT_0045c6c4], 0, 64 * sizeof(tStruct_0045c6c0));
        found_index = gINT_0045c6c4;
        gINT_0045c6c4 += 64;
    }
    tStruct_0045c6c0 *item = &gPTR_0045c6c0[found_index];
    if (item->field_0x04 == NULL) {
        item->capacity = 128;
        item->field_0x04 = xnew(128);
    }
    item->id = gUSHORT_0045c6c8;
    gUSHORT_0045c6c8 += 1;
    item->field_0x08 = 0x40;
    item->field_0x0c = 0x41;
    memset(item->field_0x04, 0, item->capacity);
    return item->id;
}

// FUNCTION: C1 0x00415414
undefined4 FUN_00415414()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041517d
int __fastcall DiagnosticVSprintf(char *buffer, const char *format, size_t buffer_size, va_list ap)
{
    if (format == NULL) {
        return 0;
    }
    size_t buffer_size_left = buffer_size;
    if (buffer_size == (size_t)-1) {
        buffer_size_left = SIZE_MAX;
    }
    FUN_0041545b();
    char *ptr_write = buffer;
    const char *ptr_format = format;
    while (*ptr_format != '\0') {
        if (*ptr_format == '%') {
            int radix;
            int format_long = 0;
            int format_continue = 1;
            char local_buffer[64];
            const char *str;
            size_t len;
            ptr_format++;
            while (format_continue) {
                switch (*ptr_format) {
                case '$':
                    NOT_IMPLEMENTED();
                    break;
                case 'D':
                case 'U':
                case 'X':
                    radix = *ptr_format == 'X' ? 16 : 10;
                    if (*ptr_format == 'U') {
                        unsigned __int64 u64 = va_arg(ap, unsigned __int64);
                        _ui64toa(u64, local_buffer, radix);
                    } else {
                        __int64 i64 = va_arg(ap, __int64);
                        _i64toa(i64, local_buffer, radix);
                    }
                    len = strlen(local_buffer);
                    strncpy(ptr_write, local_buffer, len + 1);
                    ptr_write += len;
                    ptr_format++;
                    format_continue = 0;
                    break;
                case 'F':
                    ptr_format++;
                    break;
                case 'c':
                    *ptr_write++ = va_arg(ap, int);
                    ptr_format++;
                    break;
                case 'd':
                case 'u':
                case 'x':
                    radix = *ptr_format == 'X' ? 16 : 10;
                    if (*ptr_format == 'U') {
                        unsigned int u32 = va_arg(ap, unsigned int);
                        _ultoa(u32, local_buffer, radix);
                    } else {
                        int i32 = va_arg(ap, int);
                        _ltoa(i32, local_buffer, radix);
                    }
                    len = strlen(local_buffer);
                    strncpy(ptr_write, local_buffer, len + 1);
                    ptr_write += len;
                    ptr_format++;
                    format_continue = 0;
                    break;
                case 'l':
                    format_long = 1;
                    ptr_format++;
                    break;
                case 's':
                    str = va_arg(ap, const char *);
                    len = strlen(str);
                    strncpy(ptr_write, str, len + 1);
                    ptr_write += len;
                    ptr_format++;
                    format_continue = 0;
                    break;
                default:
                    *ptr_write = *ptr_format++;
                    format_continue = 0;
                    break;
                }
            }
        } else {
            *ptr_write++ = *ptr_format++;
        }
    }
    FUN_00415414();
    if (buffer_size_left <= 0 && buffer_size > 0) {
        strcpy(ptr_write - 4, "...");
    } else {
        *ptr_write = '\0';
    }
    return ptr_write - buffer;
}

// FUNCTION: C1 0x00415443
int format(char *buffer, const char *format, size_t buffer_size, ...)
{
    va_list ap;
    int result;

    va_start(ap, buffer_size);
    result = DiagnosticVSprintf(buffer, format, buffer_size, ap);
    va_end(ap);
    return result;
}

// FUNCTION: C1 0x004482a6
void __fastcall PrintDiagnosticV(int category, int code, const char *format, va_list ap)
{
    char buffer[2048];

    char *ptr_message = buffer;
    if (tokenInputStack.line > 0 && tokenInputStack.stream != NULL) {
        format(buffer, "%Fs(%ld) : ", sizeof(buffer), GetCurrentSourceFilename(&tokenInputStack), tokenInputStack.line);
        ptr_message = buffer + strlen(buffer);
    }
    if (category != 0) {
        const char *category_str;
        if (category == 1000) {
            category_str = GetDiagnosticHelpString(315);
        } else if (category == 2000) {
            category_str = GetDiagnosticHelpString(314);
        } else if (category == 4000) {
            category_str = GetDiagnosticHelpString(313);
        }
        ptr_message += format(ptr_message, "%s %c%d: ", buffer + sizeof(buffer) - ptr_message, 'C', category + code);
    }
    DiagnosticVSprintf(ptr_message, format, buffer + sizeof(buffer) - ptr_message, ap);
    fwrite(buffer, strlen(buffer), 1, stderr);
    fwrite("\n", 1, 1, stderr);
    if (gWrite_er != 0 && gFile_er != NULL) {
        fwrite(buffer, strlen(buffer), 1, stderr);
        fwrite("\n", 1, 1, stderr);
        fflush(gFile_er);
    }
}

// FUNCTION: C1 0x00448257
void FatalErrorF(int code, ...)
{
    va_list ap;

    AvoidRecursiveFatalError(7);
    va_start(ap, code);
    PrintDiagnosticV(1000, code, GetDiagnosticString(1000 + code, FALSE), ap);
    va_end(ap);
    ReleaseEverythingUponError();
    Nerrors += 1;
    exit(Nerrors);
}

// FUNCTION: C1 0x00413697
void Emit4000Warning(int warning_level, int code, ...)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x004233bc
void __cdecl Error2000F(int warning_level, int code, ...)
{
    va_list ap;

    if (PchC.p_Extension) {
        Emit4000Warning(4, warning_level);
        return;
    }
    va_start(ap, code);
    PrintDiagnosticV(2000,code,GetDiagnosticString(2000 + code, 0), ap);
    va_end(ap);
    Nerrors += 1;
    if (Nerrors > 100) {
        FatalErrorF(3, 100);
    }
    if (gIncremental_interface3 != NULL) {
        if (!gIncremental_interface3->vmethod_inc3_0x44()) {
            FatalErrorF(73, "error.c", 352);
        }
    }
}

// FUNCTION: C1 0x004480f7
void EmitError(int code, ...)
{
    va_list ap;

    if (gUINT_0045bf94 & 0x200) {
        return;
    }
    va_start(ap, code);
    PrintDiagnosticV(2000, code, GetDiagnosticString(2000 + code, 0), ap);
    va_end(ap);
    Nerrors += 1;
    if (Nerrors > 100) {
        FatalErrorF(3, 100);
    }
    if (gIncremental_interface3 != NULL) {
        if (!gIncremental_interface3->vmethod_inc3_0x44()) {
            FatalErrorF(73, "error.c", 352);
        }
    }
}

// FUNCTION: C1 0x0044810e
int __fastcall FUN_0044810e(int code, int category, const char *arg3, const char *file, int line)
{
    if (ExecutionState == 7 || ExecutionState == 6) {
        return 0;
    }
    if (arg3 == NULL) {
        arg3 = "";
    }
    FatalErrorF(code, category, arg3, _strerror(NULL), file, line);
    return 0;
}

// FUNCTION: C1 0x00448160
void __fastcall fatal_io_CRT(int code, int category, const char *text)
{
    if (ExecutionState == 7 || ExecutionState == 6) {
        return;
    }
    if (text == NULL) {
        text = "";
    }
    FatalErrorF(code, category, text, _strerror(NULL));
}

// FUNCTION: C1 0x0043f49e
void __fastcall fatal_varargs(int code)
{
    FatalErrorF(code);
}

// FUNCTION: C1 0x0041a6eb
uintptr_t __fastcall PreAllocateMemory(size_t reserveSize, size_t commitSize)
{
    LPVOID reserveAddr = VirtualAlloc(NULL, reserveSize, MEM_RESERVE, PAGE_READWRITE);
    if (reserveAddr == NULL) {
        fatal_varargs(60);
    }
    LPVOID commitAddr = VirtualAlloc(reserveAddr, commitSize, MEM_COMMIT, PAGE_READWRITE);
    if (commitAddr == NULL) {
        fatal_varargs(60);
    }
    return (uintptr_t) commitAddr;
}

// FUNCTION: C1 0x0041bab0
void ReserveMacroBuffers()
{
    pMacroActBase = PreAllocateMemory(5 * 1024 * 1024, 1024);
    pMacroActEnd = gReserved_mem1_start + 4096 - 5;
    pMacroExpBase = PreAllocateMemory(5 * 1024 * 1024, 1024);
    pMacroExpEnd = pMacroExpBase + 4096 - 5;
}

// FUNCTION: C1 0x00419396
void InitTiming()
{
    gCountTimings = 0;
    gPrevTickCount = GetTickCount();
}

// FUNCTION: C1 0x00408275
void __fastcall AddTiming(const char *description)
{
    DWORD tick = GetTickCount();
    gTimings[gCountTimings].description = description;
    gTimings[gCountTimings].tick = tick - gPrevTickCount;
    DWORD next_count = gCountTimings + 1;
    if (next_count >= arraysize(gTimings)) {
        next_count = 0;
    }
    gPrevTickCount = tick;
}

// FUNCTION: C1 0x0041f0f6
void PrintTimings()
{
    if (gPrint_timings) {
        int i;
        int total = 0;

        for (i = 0; i < gCountTimings; i++) {
            total += gTimings[i].tick;
            printf("%8d in %s.\n", gTimings[i].tick, gTimings[i].description);
        }
        printf("%d ms total time.\n", total);
    }
}

// FUNCTION: C1 0x0041136e
void * __fastcall xnew(size_t s)
{
    void *res = malloc(s);
    if (res == NULL) {
        fatal_varargs(60);
    }
    return res;
}

// FUNCTION: C1 0x00447fc2
void * __fastcall xrealloc(void *mem, size_t s)
{
    void *res = realloc(mem, s);
    if (res == NULL) {
        fatal_varargs(60);
    }
    return res;
}

// FUNCTION: C1 0x00411f38
void __fastcall StdFree(void *p) {
    free(p);
}

// FUNCTION: C1 0x0041f0b2
void FUN_0041f0b2()
{
    // empty
}

// FUNCTION: C1 0x00445ac1
void OnTerminalSignal(int)
{
    if (gTerminalSignalSemaphore != NULL) {
        ExitThread(0);
    }
    gTerminalSignalSemaphore = CreateSemaphoreA(NULL, 0, 1, NULL);
    if (gTerminalSignalSemaphore == NULL) {
        ExitThread(0x8000);
    }
    HandlingControlC = TRUE;
    if (ExecutionState != 8) {
        if (WaitForSingleObject(gTerminalSignalSemaphore, 4000) == WAIT_TIMEOUT) {
            int i = 0;

            WriteStdErr("Compiler terminating.  Please wait.");
            for (i = 0; i < 30; i++) {
                if (ExecutionState == 8) {
                    break;
                }
                if (WaitForSingleObject(gTerminalSignalSemaphore, 2000) != WAIT_TIMEOUT) {
                    break;
                }
                WriteStdErr(".");
            }
            WriteStdErr(" Abort complete.\n");
            if (i >= 30) {
                ExitProcess(0x8000);
            }
        }
    }
    CloseHandle(gTerminalSignalSemaphore);
    gTerminalSignalSemaphore = NULL;
}

// FUNCTION: C1 0x00419928
int __fastcall gatherOneCommandLineNugget(const char *arg, int state)
{
    if (arg == NULL) {
        return 0;
    }
    for (;;) {
        switch (state) {
        case 0:
            if (strncmp(arg, "-Bm", 3) == 0) {
                arg += 3;
                state = 1;
            } else if (strncmp(arg, "-ZB", 3) == 0) {
                arg += 3;
                state = 2;
            } else if (strncmp(arg, "-ZM", 3) == 0) {
                arg += 3;
                state = 3;
            }
            break;
        case 1:
            gBm_value = atoi(arg);
            return 0;
        case 2:
            gZB_value = atoi(arg);
            return 0;
        case 3:
            gPCH_memory_scaling_factor = atoi(arg);
            if (gPCH_memory_scaling_factor == 0) {
                gPCH_memory_scaling_factor = 100;
            }
            return 0;
        }
        if (*arg == '\0') {
            return 0;
        }
        if (state == 0) {
            return 0;
        }
    }
}

// FUNCTION: C1 0x00419862
void __fastcall PreParseArgs(char **argv)
{
    int state = 0;
    char **arg = argv + 1;

    while (arg != NULL) {
        state = gatherOneCommandLineNugget(*arg, state);
        arg++;
    }

    bool in_quotes = false;
    state = 0;
    char *envstr = getenv("MSC_CMD_FLAGS");
    if (envstr != NULL) {
        char buffer[512];
        char *ptr_write = buffer;
        while (*envstr != '\0') {
            while (*envstr == ' ') {
                envstr++;
            }
            if (*envstr == '\0') {
                break;
            }
            for (;;) {
                if (*envstr == ' ' && !in_quotes) {
                    break;
                }
                uint8_t cls1 = CHARACTER_CLASS1(*envstr);
                if (cls1 == 0) {
                    if (*envstr == '?') {
                        *ptr_write++ = *envstr;
                    } else if (envstr[1] == '"') {
                        *ptr_write++ = *envstr++;
                    } else {
                        *ptr_write++ = '\\';
                        envstr++;
                        if (*envstr != '\0' && (*envstr != ' ' || in_quotes)) {
                            *ptr_write++ = *envstr++;
                        }
                    }
                } else if (cls1 == 0x16) {
                    in_quotes = !in_quotes;  // '"'
                    envstr++;
                } else {
                    *ptr_write++ = *envstr++;
                    if (cls1 == 0x23) {
                        // ???
                        NOT_IMPLEMENTED();
                    }
                }
                if (*envstr == '\0') {
                    break;
                }
            }
            if (*envstr != '\0') {
                envstr++;
            }
            *ptr_write = '\0';
            state = gatherOneCommandLineNugget(buffer, state);
        }
    }
}

// FUNCTION: C1 0x0041934f
void FUN_0041934f()
{
    // empty
}

// FUNCTION: C1 0x0040c1af
size_t __fastcall MakeMultipleOf(size_t size, size_t itemSize)
{
    size_t result = (size / itemSize) * itemSize;
    if (size % itemSize > 0) {
        result += itemSize;
    }
    return result;
}

// FUNCTION: C1 0x0041a383
size_t __fastcall GetMaximumChunkSize(tPCH_chunk_info *chunk_info)
{
    size_t size = (int)((float)chunk_info->maxSize * (float)gPCH_memory_scaling_factor / 100.f);
    size = MakeMultipleOf(size, chunk_info->itemSize);
    if (size == 0) {
        return chunk_info->itemSize;
    }
    return size;
}

// FUNCTION: C1 0x00423857
char *__fastcall pstrdup(const char *text, int pool_id)
{
    char *copy = (char *)gPCH_chunks[pool_id].Allocate(strlen(text) + 1);
    strcpy(copy, text);
    return copy;
}

// FUNCTION: C1 0x0041a2b7
VirtualHeap::VirtualHeap(uint32_t minSize)
{
    m_ptr_free = NULL;
    m_mem_left = 0;
    m_min_size = minSize;
    m_chunk = NULL;
}

// FUNCTION: C1 0x0041a29e
void VirtualHeap::SelectChunk(int chunk_id)
{
    m_chunk = &gPCH_chunks[chunk_id];
    IncreaseHeapByAtLeast(1);
}

// FUNCTION: C1 0x0040c390
void VirtualHeap::IncreaseHeapByAtLeast(size_t size)
{
    size_t count_pages = (size - 1) / gSystem_info.dwPageSize + 1;
    if (count_pages <= m_min_size) {
        count_pages = m_min_size;
    }
    m_ptr_free = m_chunk->AllocatePages(count_pages, &m_mem_left);
}

// FUNCTION: C1 0x0041a2f3
BOOL tPCH_chunk::Initialize(tPCH_chunk_info *chunk_info, void *startAddress)
{
    m_chunk_info = chunk_info;
    m_maxSize = GetMaximumChunkSize(chunk_info);
    m_address = (uintptr_t)VirtualAlloc(startAddress, m_maxSize, MEM_RESERVE, PAGE_READWRITE);
    if (m_address == 0) {
        return FALSE;
    }
    Reset();
    m_field_0x1c = 0;
    return TRUE;
}

// FUNCTION: C1 0x0040c3bd
void * tPCH_chunk::AllocatePages(size_t count_pages, size_t *actualSize)
{
    uintptr_t result = m_mem_commited_next_free;
    *actualSize = MakeMultipleOf(count_pages * gSystem_info.dwPageSize + m_mem_commited_next_free - m_address, gSystem_info.dwPageSize) + (m_mem_commited_next_free - m_address);
    m_mem_commited_next_free += *actualSize;
    if (m_mem_commited_next_free > m_mem_commited_end) {
        HeapExtend();
    }
    return (void *) result;
}

// FUNCTION: C1 0x0040c1cf
void VirtualHeap::HeapExtend()
{
    if (m_mem_commited_next_free - m_address > m_maxSize) {
        fatal_varargs(76);
    }
    size_t size = MakeMultipleOf(m_mem_commited_next_free - m_mem_commited_end, m_chunk_info->itemSize);
    if (VirtualAlloc((void *)m_mem_commited_end, size, MEM_COMMIT, PAGE_READWRITE) == NULL) {
        fatal_varargs(60);
    }
    m_mem_commited_end += size;
    m_commited_size += size;
}

// FUNCTION: C1 0x0041a372
void tPCH_chunk::Reset()
{
    m_commited_size = 0;
    m_mem_commited_next_free = (uintptr_t)m_address;
    m_mem_commited_end = (uintptr_t)m_address;
    m_field_0x18 = 0;
}

tStruct_00466458::tStruct_00466458()
{
    field_0x0 = NULL;
    field_0x4 = 0;
    field_0x8 = 0;
    field_0xc = 0;
    field_0x10 = 0;
}

tStruct_00466458::~tStruct_00466458()
{
    // empty
}

// FUNCTION: C1 0x0041f2db
void tStruct_00466458::FUN_0041f2db()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041a3b4
void AllSAClasses::Initialize()
{
    gPCH_allocated_chunk_00466298.SelectChunk(0);
    gPCH_allocated_chunk_004664a0.SelectChunk(0);
    gPCH_allocated_chunk_00466468.SelectChunk(0);
    gPCH_allocated_chunk_00460a40.SelectChunk(0);
    gPCH_allocated_chunk_00460998.SelectChunk(0);
    gPCH_allocated_chunk_00466170.SelectChunk(0);
    gPCH_allocated_chunk_004660f8.SelectChunk(0);
    gPCH_allocated_chunk_00466040.SelectChunk(0);
    gPCH_allocated_chunk_00460a18.SelectChunk(0);
}

// FUNCTION: C1 0x004192ab
void FUN_004192ab()
{
    int i;

    for (i = 0; i < arraysize(gPCH_chunks); i++) {
        if (gPCH_chunk_infos[i].flags & 0x1) {
            if (!gPCH_chunks[i].Initialize(&gPCH_chunk_infos[i], NULL)) {
                fatal_varargs(60);
            }
        }
    }
}

// FUNCTION: C1 0x00419264
void HeapManager::InitGlobalHeaps()
{
    int i;

    FUN_004192ab();
    for (i = 0; i < arraysize(gPCH_chunks); i++) {
        if (!(gPCH_chunk_infos[i].flags & 0x1)) {
            if (!gPCH_chunks[i].Initialize(&gPCH_chunk_infos[i], NULL)) {
                fatal_varargs(60);
            }
        }
    }
    AllSAClasses::Initialize();
}

// GLOBAL: 0x0041c211
void FUN_0041c211()
{
    tStruct_0045b5bc *ptr = (tStruct_0045b5bc *)gPCH_chunks[0].Allocate(sizeof(tStruct_0045b5bc));
    if (ptr == NULL) {
        gPTR_0045b5bc = NULL;
    } else {
        gPTR_0045b5bc = ptr;
    }
}

// FUNCTION: C1 0x0041aae2
void InitCrc()
{
    int i;

    for (i = 0; i < 256; i++) {
        int j;

        crcTh[i] = 0;
        crcTl[i] = 0;
        for (j = 0; j < 8; j++) {
            int shift_lut_index = 0;
            uint8_t msb_bit = 0;
            uint8_t lsb_bit = 0;
            int shift;

            for (;;) {
                for (;;) {
                    shift = gCVHash_shift_lut[shift_lut_index] + j;
                    if (shift > 7) {
                        break;
                    }
                    shift_lut_index++;
                    lsb_bit ^= i >> shift;
                }
                if (shift > 15) {
                    break;
                }
                msb_bit ^= i >> (shift - 8);
                shift_lut_index++;
            }
            crcTl[i] |= (lsb_bit & 0x1) << j;
            crcTh[i] |= (msb_bit & 0x1) << j;
        }
    }
    for (i = 0; i < 256; i++) {
        int j;
        uint8_t new_index = i;
        uint8_t lsb_bit = 0x2;

        for (j = 1; j < 8; j++) {
            new_index ^= (2 * new_index) & lsb_bit;
            if (j > 2) {
                new_index ^= (8 * new_index) & lsb_bit;
            }
            lsb_bit <<= 1;
        }
        gHash_permutation_lut[i] = new_index;
    }
}
// FUNCTION: C1 0x0041a33a
void InitCharacterClassesForLocale()
{
    int i;
    const uint8_t *mbtype = __p__mbctype();
    _setmbcp(_MB_CP_LOCALE);

    for (i = 0; i < 256; i++) {
        if (mbtype[i + 1] & 0x4) {
            Charmap[i] = 0x23;
            Contmap[i] |= 0x10;
        }
    }
}

// FUNCTION: C1 0x0043ee2c
void FUN_0043ee2c()
{
    int i;

    for (i = 0; i < 256; i++) {
        if (Charmap[i] == 0x23) {
            Charmap[i] = 0x21;
            Contmap[i] &= ~0x10;
        }
    }
}

// FUNCTION: C1 0x0041b0b2
void InitToLowerLUT()
{
    int i;

    for (i = 0; i < 256; i++) {
        if (CHARACTER_CLASS1(i) == 0x23) {
            gTo_lower_lut[i] = -1;
        } else {
            gTo_lower_lut[i] = _mbctolower(i);
        }
    }
    gTo_lower_lut['/'] = '\\';
}

char **GetArgvWritePointer()
{
    char **argv;

    if (NewArgv != NULL) {
        argv = Argv;
        while (*argv != NULL) {
            argv++;
        }
        return argv;
    }
    char **original_argv = Argv;
    NewArgv = (char **)xnew(MAX_ARG_COUNT * sizeof(char *));
    argv = NewArgv;
    for (;;) {
        *argv = *original_argv;
        if (*original_argv == NULL) {
            break;
        }
        original_argv++;
        argv++;
        if (argv - NewArgv >= MAX_ARG_COUNT) {
            FatalErrorF(77, MAX_ARG_COUNT);
        }
        *argv = *original_argv;
    }
    Argv = NewArgv;
    return argv;
}

// FUNCTION: C1 0x0041adce
void __fastcall unconcat(char *arg_string)
{
    bool in_quotes = false;

    if (arg_string == NULL) {
        return;
    }
    char **argv_ptr = GetArgvWritePointer();
    while (*arg_string != '\0') {
        while (*arg_string == ' ') {
            arg_string++;
        }
        if (*arg_string == '\0') {
            continue;
        }
        *argv_ptr++ = arg_string;
        if (argv_ptr - NewArgv >= MAX_ARG_COUNT) {
            FatalErrorF(77, MAX_ARG_COUNT);
        }
        Argc += 1;
        char *arg_ptr = arg_string;
        while (*arg_string != '\0') {
            if (*arg_string == ' ' && !in_quotes) {
                break;
            }
            uint8_t cls = CHARACTER_CLASS1(*arg_string);
            if (cls == 0) {
                if (*arg_string == '?') {
                    *arg_ptr++ = *arg_string++;
                    continue;
                }
                arg_string++;
                if (*arg_string == '"') {
                    *arg_ptr++  = *arg_string++;
                    continue;
                }
                *arg_ptr++ = '\\';
                if (*arg_string != '\0' && (*arg_string != ' ' || in_quotes)) {
                    *arg_ptr++ = *arg_string++;
                    continue;
                }
            } else if (cls == 0x16) {
                in_quotes = !in_quotes;
                arg_string++;
            } else if (cls == 0x23) {
                *arg_ptr++ = *arg_string++;
                *arg_ptr++ = *arg_string++;
            } else {
                *arg_ptr++ = *arg_string++;
            }
        }
        if (*arg_string != '\0') {
            arg_string++;
        }
        *arg_ptr = '\0';
    }
    *argv_ptr = NULL;
}

// FUNCTION: C1 0x0041b8af
const char *GetNextArgument()
{
    Argc -= 1;
    if (Argc <= 0) {
        return NULL;
    }
    Argv++;
    return *Argv;
}

// FUNCTION: C1 0x00411ea0
tStringVector * __fastcall CreateStringVector(undefined2 capacity, int chunk_id)
{
    tStringVector *vector = (tStringVector *)gPCH_chunks[chunk_id].Allocate(sizeof(tStringVector));
    vector->size = 0;
    vector->capacity = capacity;
    vector->chunk_id = chunk_id;
    if (vector->capacity != 0) {
        vector->data = (const char **)gPCH_chunks[chunk_id].Allocate(capacity * sizeof(void *));
    }
    return vector;
}

// FUNCTION: C1 0x0044407c
void __fastcall StringVector_IncreaseCapacity(tStringVector *vect)
{
    if (vect->capacity < 1000) {
        vect->capacity = 2 * vect->capacity + 4;
    } else {
        vect->capacity += 1000;
    }
    const char **new_data = (const char **)gPCH_chunks[vect->chunk_id].Allocate(sizeof(char *) * vect->capacity);
    memcpy(new_data, vect->data, sizeof(char *) * vect->size);
    vect->data = new_data;
}

// FUNCTION: C1 0x00411f16
void __fastcall StringVector_Append(tStringVector *vect, const char *value)
{
    if (vect->capacity == vect->size) {
        StringVector_IncreaseCapacity(vect);
    }
    vect->data[vect->size] = value;
    vect->size++;
}

// FUNCTION: C1 0x0041aeb2
int __fastcall ParseNumericalArgument(const char *strvalue)
{
    const char *strint = strvalue;
    while (isspace(*strint)) {
        strint++;
    }
    if (!isdigit(*strint)) {
        FatalErrorF(49, strvalue);
    }
    long l = atol(strint);
    if (l < 0 || l >= 0xffff) {
        FatalErrorF(49, strvalue);
    }
    return (int) l;
}

// FUNCTION: C1 0x0041af4c
void __fastcall substr(const cmdtab *arg_spec, const char *value, int state)
{
    switch (arg_spec->field_0x9) {
    case 0x1:
        *arg_spec->ptr_bool = TRUE;
        break;
    case 0x5:
        *arg_spec->ptr_bool = FALSE;
        break;
    case 0x22:
        *arg_spec->ptr_cstr = state ? strdup(value) : value;
        break;
    case 0x23:
        for (; *value != '\0'; value++) {
            const tArgument_char_spec *char_spec = arg_spec->ptr_char_spec;
            for (;;) {
                if (char_spec->c == '\0') {
                    FatalErrorF(48, *value, ErrString);
                }
                if (char_spec->c == *value) {
                    if (char_spec->field_0x4 == 0x1) {
                        *char_spec->ptr_bool = TRUE;
                    } else if (char_spec->field_0x4 == 0x5) {
                        *char_spec->ptr_bool = FALSE;
                    }
                    break;
                }
            }
        }
        break;
    case 0x24:
        *arg_spec->ptr_int = ParseNumericalArgument(value);
        break;
    case 0x26:
        StringVector_Append(*arg_spec->ptr_string_vector, state ? strdup(value) : value);
        break;
    case 0x27:
        if (*arg_spec->ptr_str != NULL) {
            char *dup_format = strdup(arg_spec->format);
            dup_format[strlen(dup_format) - 1] = '\0';
            FatalErrorF(46, dup_format, *arg_spec->ptr_str, value);
        }
        break;
    }
}

// FUNCTION: C1 0x0041ae9
BOOL __fastcall tailmatch(const char *format, const char *arg)
{
    if (format[1] == '\0') {
        return TRUE;
    }
    const char *end_format = format;
    while (end_format[1] != '\0') {
        end_format++;
    }
    const char *end_arg = arg;
    while (end_arg[1] != '\0') {
        end_arg++;
    }
    while (*end_format == *end_arg) {
        end_format--;
        end_arg--;
    }
    return end_format == format && arg <= end_arg;
}

// FUNCTION: C1 0x0041b2c7
int __fastcall crack_cmd(const cmdtab *arg_specs, const char *arg, char *(get_next_arg)(), int state) {
    bool checksum_arg = true;
    int i;
    const char *arg_value = NULL;

    if (arg == NULL) {
        return 0;
    }
    ErrString = arg;
    for (i = 0;; i++) {
        const cmdtab *spec = &arg_specs[i];
        const char *ptr_arg = arg;
        const char *ptr_format = arg_specs[i].format;
        bool match = false;

        if (!arg_specs[i].field_0x9) {
            return 0;
        }
        for (;;) {
            if (*ptr_format == '\0') {
                if (*ptr_arg != '\0') {
                    break; // next argument spec
                }
                if (spec->field_0x9 & 0x20) {
                    arg_value = get_next_arg();
                } else {
                    arg_value = NULL;
                }
                substr(spec, arg_value, state);
                match = true;
                break;
            } else if (*ptr_format == '#' || *ptr_format == '$') {
                if (*ptr_format == '$') {
                    checksum_arg = false;
                }
                if (*ptr_arg != '\0') {
                    substr(spec, ptr_arg, state);
                } else {
                    arg_value = get_next_arg();
                    substr(spec, arg_value, state);
                    if (!checksum_arg) {
                        return arg_specs[i].field_0x8;
                    }
                }
                match = true;
                break;
            } else if (*ptr_format == '%') {
                checksum_arg = false;
                ptr_format++;
            } else if (*ptr_format == '*') {
                if (*ptr_arg != '\0' && tailmatch(ptr_format, ptr_arg)) {
                    substr(spec, ptr_arg, state);
                    match = true;
                    break;
                } else {
                    break;
                }
            } else if (*ptr_format == '-') {
                const char *opt_start = "-/";
                if (strchr(opt_start, *ptr_arg) == NULL) {
                    break;
                }
                ptr_arg++;
                ptr_format++;
            } else {
                if (*ptr_arg != *ptr_format) {
                    break;
                }
                ptr_arg++;
                ptr_format++;
            }
        }
        if (match) {
            break;
        }
    }
    if (arg_value != NULL) {
        crc32ClCmd.Update(arg_value, strlen(arg_value));
    }
    if (checksum_arg) {
        crc32ClCmd.Update(arg, strlen(arg));
    }
    return arg_specs[i].field_0x8;
}

// FUNCTION: C1 0x00411f5a
char *__fastcall TransformToLower(char *str)
{
    char *ptr = str;
    while (*ptr != '\0') {
        if (gTo_lower_lut[(unsigned char)*ptr] == -1) {
            ptr++;
        } else {
            *ptr = gTo_lower_lut[(unsigned char)*ptr];
        }
        ptr++;
    }
    return str;
}

// FUNCTION: C1 0x00411f86
char *__fastcall FullPath(char *dest, const char *path, size_t destSize)
{
    char buffer[260];
    bool no_fullpath = false;

    strcpy(buffer, path);
    if (strlen(buffer) >= 3) {
        TransformToLower(buffer);
        if (!(__p__mbctype()[1 + buffer[0]] & 0x4)) {
            bool absolute = false;
            bool network = false;

            if (buffer[0] == '\\' && buffer[1] == '\\') {
                network = absolute = true;
            } else if (buffer[0] < 0x80 && buffer[1] == ':') {
                absolute = true;
            }
            if (absolute) {
                no_fullpath = _mbsstr((unsigned char *)buffer, (unsigned char *)".\\") == NULL;
                if (no_fullpath && !network) {
                    no_fullpath = _mbsstr((unsigned char *)buffer, (unsigned char *)":\\") != NULL;
                }
            }
        }
    }
    bool full_path_succes = false;
    if (!no_fullpath) {
        char *r = _fullpath(dest, path, destSize);
        full_path_succes = r != NULL;
    }
    if (!full_path_succes) {
        strcpy(dest, path);
    }
    return TransformToLower(dest);
}

// FUNCTION: C1 0x004193ac
void * __fastcall AllocateFromPool0(size_t s) {
    return gPCH_chunks[0].Allocate(s);
}

// FUNCTION: C1 0x00421c3a
void __fastcall PragmaStack_ResetItem(tPragma_stack_item *item)
{
    item->next = NULL;
    item->value = 0;
    item->field_0x8 = 0;
}

// FUNCTION: C1 0x00411702
tPragma_stack_item *__fastcall PragmaStack_PushItem(tPragma_stack *stack)
{
    tPragma_stack_item *item = stack->free_items;
    if (item != NULL) {
        stack->free_items = item->next;
        PragmaStack_ResetItem(item);
    } else {
        item = (tPragma_stack_item *)gPCH_chunks[0].Allocate(sizeof(tPragma_stack_item));
    }
    item->next = stack->items;
    stack->items = item;
    return item;
}

// FUNCTION: C1 0x0041160c
void CreatePragmaStack()
{
    tPragma_stack *stack = (tPragma_stack *)AllocateFromPool0(sizeof(tPragma_stack));
    if (stack != NULL) {
        gPragma_stack = stack;
    } else {
        gPragma_stack = NULL;
    }
    tPragma_stack_item *item = PragmaStack_PushItem(gPragma_stack);
    if (gOption_Zp != -1) {
        item->value = gOption_Zp;
    } else {
        item->value = 8;
    }
    item->field_0x8 = 0;
    undefined4 head_value = gPragma_stack->items->value;
    item = PragmaStack_PushItem(gPragma_stack);
    item->value = head_value;
    item->field_0x8 = 0;
}

// FUNCTION: C1 0x004236da
bool __fastcall fStrCleanCmp(const char *p1, const char *p2)
{
    for (;;) {
        if (*p1 == '\0' || *p2 == '\0') {
            return *p1 == *p2;
        }
        if (!(_mbctoupper(*p1) == _mbctoupper(*p1)
                || (*p1 == '/' && *p2 == '\\')
                || (*p1 == '\\' && *p2 == '/'))) {
            return false;
        }
        p1++;
        p2++;
    }
}

// FUNCTION: C1 0x0041b4b2
void __fastcall init_main1(int argc, char **argv)
{
    char buffer[2048];
    int i;

    if (gPTR_0045b5bc == NULL) {
        FUN_0041c211();
    }
    InitCrc();
    setlocale(LC_CTYPE, "");
    InitCharacterClassesForLocale();
    InitToLowerLUT();
    if (argc > 1) {
        if (argv[1][0] == '@') {
            FILE *f = fopen(&argv[1][1], "rt");
            if (f == NULL) {
                fatal_io_CRT(84, 337, &argv[1][1]);
                exit(1);
            }
            while (fgets(buffer, sizeof(buffer), f) != NULL) {
                if (buffer[0] != ';') {
                    size_t len_line = strlen(buffer);
                    if (buffer[len_line - 1] == '\n') {
                        buffer[len_line - 1] = '\0';
                    }
                    char *arg_start = buffer;
                    if (buffer[0] == 'P' && buffer[1] == '1'&& buffer[2] == ':') {
                        arg_start = &buffer[3];
                    }
                    unconcat(pstrdup(arg_start, 1));
                }
            }
            fclose(f);
        }
    }
    unconcat(getenv("MSC_CMD_FLAGS"));
    for (i = 0; gDefault_warning_severities[i].warning != 0; i++) {
        int warning = gDefault_warning_severities[i].warning;
        gWarning_severities[warning] = gDefault_warning_severities[i].severity;
        if (warning >= 700 && warning < 1000) {
            if (warning <= gMin_pragma_warning) {
                gMin_pragma_warning = warning;
            }
            if (warning >= gMax_pragma_warning) {
                gMax_pragma_warning = warning;
            }
        }
    }
    listDefs = ListNewSize<void_*>(40, 1);
    listIncludes = ListNewSize<void_*>(40, 1);
    listForcedIncludes = ListNewSize<void_*>(40, 1);
    if (!PchC.option_C9IL) {
        crc32ClCmd.Update("C", 1);
    }
    for (;;) {
        int state = 0;
        state = crack_cmd(cmdtab, GetNextArgument(), GetNextArgument, state);
        if (!state) {
            break;
        }
    }
    if (FullPath(buffer, gPDB_arg_path, sizeof(buffer)) == NULL) {
        FatalErrorF(83, 354, gPDB_arg_path, GetDiagnosticHelpString(355));
    }
    if (strlen(buffer) >= sizeof(PchC.p_FdName)) {
        fatal_varargs(5);
    }
    strcpy(PchC.p_FdName, buffer);
    if (gOption_Z7) {
        PchC.p_Symbolic_debug_holder = TRUE;
        PchC.p_FUseTypeServer = FALSE;
    }
    PchC.option_C9IL |= !PchC.option_Gi;
    PchC.p_Cmd_fICCBrowse &= PchC.option_Gi;
    if (PchC.p_Cmd_splitPdbs) {
        gPTR_00466458 = &gStruct_004664b0;
    } else {
        gPTR_00466458 = &gStruct_004662a8;
    }
    PchC.p_FUseTypeServer &= PchC.p_Symbolic_debug_holder;
    if (PchC.option_Jd) {
        FUN_0043ee2c();
    }
    if (gPragma_stack == NULL) {
        CreatePragmaStack();
    }
    if (gYl_arg_path != NULL) {
        if (strlen(gYl_arg_path) >= sizeof(PchC.Yl_path)) {
            fatal_varargs(5);
        }
        strcpy(PchC.Yl_path, PchC.Yl_path);
    }
    if (Unknown_ != NULL) {
        FatalErrorF(7, Unknown_, "c1");
    }
    if (Input_file == NULL) {
        fatal_varargs(8);
    }

    if (PchCFile != NULL) {
        PchCFlag = TRUE;
        if (PchUFile != NULL) {
            if (fStrCleanCmp(PchCFile, PchUFile)) {
                PchUFlag = FALSE;
                PchUFile = NULL;
            }
        }
    }
    if (!PchCFlag) {
        fPersistentPch = FALSE;
    }
    if (PchUFile != NULL) {
        PchUFlag = TRUE;
    }
    if (gOption_YX) {
        gOption_YX = TRUE;
    }
    PchC.p_PchDFlag |= gOption_YX;
    if (Prep || Out_funcdef) {
        gOption_YX = FALSE;
        gOption_YX = FALSE;
        PchCFlag = FALSE;
        PchCFile = NULL;
        PchUFlag = FALSE;
        PchUFile = NULL;
        PchC.p_PchDFlag = FALSE;
        fPersistentPch = FALSE;
    }
    if (NewArgv != NULL) {
        StdFree(NewArgv);
        NewArgv = NULL;
    }
}

// FUNCTION: C1 0x0041ba35
void FUN_0041ba35()
{
    gOption_G_flags = 1 << PchC.option_G;
    if (PchC.option_GM) {
        gOption_G_flags |= 0x40;
    }
}

// FUNCTION: C1 0x0041b776
void FUN_0041b776()
{
    int i;

    for (i = 1; i < 254; i++) {
        if (gBOOL_ARRAY_004565d0[i]) {
            tStruct_0045b75c *r = (tStruct_0045b75c *)gPCH_allocated_chunk_00460a18.Allocate(sizeof(tStruct_0045b75c));
            if (r == NULL) {
                gPTR_ARRAY_0045b75c[i] = NULL;
                continue;
            }
            r->field_0x00 = i;
            r->field_0x08 = i;
            gPTR_ARRAY_0045b75c[i] = r;
        } else {
            gPTR_ARRAY_0045b75c[i] = NULL;
        }
    }
}
// FUNCTION: C1 0x00419771
void CreateKeywordHashmap()
{
    if (gKeywordHashmap == NULL) {
        gKeywordHashmap = (tStruct_0045b5b0_bucket **) gPCH_chunks[0].Allocate(2048 * sizeof(tStruct_0045b5b0_bucket * ));
    }
}

// FUNCTION: C1 0x0041b16d
void __fastcall FindOrCreateBucket_0041b16d(const char *name)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041b764
void __fastcall FUN_0041b764(const char *name)
{
    FindOrCreateBucket_0041b16d(name);
    gCurrent_bucket->hash_and_flags &= ~0x10000;
}

// FUNCTION: C1 0x0041ba04
void __fastcall MarkKeywordReservedForFutureUse(const char *name)
{
    FindOrCreateBucket_0041b16d(name);
    if (gCurrent_bucket->hash_and_flags & 0x10000) {
        gCurrent_bucket->data_field_0x0 = 251;
        gCurrent_bucket->data_field_0x1 = 3;
    }
}

// FUNCTION: C1 0x0041b7e3
void __fastcall MarkKeywordAsObsolete(const char *name)
{
    FindOrCreateBucket_0041b16d(name);
    if (gCurrent_bucket->hash_and_flags & 0x10000) {
        gCurrent_bucket->data_field_0x0 = 251;
        gCurrent_bucket->data_field_0x1 = 1;
    }
}

// FUNCTION: C1 0x0041c146
void __fastcall MarkKeywordAsObsoleteUseDeclspecDllexportInstead(const char *name)
{
    FindOrCreateBucket_0041b16d(name);
    if (gCurrent_bucket->hash_and_flags & 0x10000) {
        gCurrent_bucket->data_field_0x0 = 251;
        gCurrent_bucket->data_field_0x1 = 5;
    }
}

// FUNCTION: C1 0x0041b92c
void __fastcall MarkKeywordOnlySupportedInCPP(const char *name)
{
    FindOrCreateBucket_0041b16d(name);
    if (gCurrent_bucket->hash_and_flags & 0x10000) {
        gCurrent_bucket->data_field_0x0 = 251;
        gCurrent_bucket->data_field_0x1 = 2;
    }
}

// FUNCTION: C1 0x0041c1c4
void __fastcall MarkKeywordAsNotSupportedInThisProduct(const char *name)
{
    FindOrCreateBucket_0041b16d(name);
    if (gCurrent_bucket->hash_and_flags & 0x10000) {
        gCurrent_bucket->data_field_0x0 = 251;
        gCurrent_bucket->data_field_0x1 = 4;
    }
}

// FUNCTION: C1 0x0041c0f1
void __fastcall MarkTokenAsNotYetSupported(const char *name)
{
    FindOrCreateBucket_0041b16d(name);
    if (gCurrent_bucket->hash_and_flags & 0x10000) {
        gCurrent_bucket->data_field_0x0 = 251;
        gCurrent_bucket->data_field_0x1 = 6;
    }
}

void RegisterExtendedDeclModifiers() {
    int i;

    for (i = 0; gExtendedDeclModifiers[i].name != NULL; i++) {
        FindOrCreateBucket_0041b16d(gExtendedDeclModifiers[i].name);
        gCurrent_bucket->hash_and_flags |= 0x800000;
        if (!(gCurrent_bucket->hash_and_flags & 0x10000)) {
            gCurrent_bucket->data_field_0x0 = i;
        }
    }
}

// FUNCTION: C1 0x0041bb78
void InitKeywords()
{
    int i;

    PchC.p_Extension = PchC.p_Extension || PchC.p_BigIntExtension;
    PchC.p_SizeOfBigInt /= 8;
    if (PchC.p_SizeOfBigInt == 0) {
        PchC.p_SizeOfBigInt = 4;
    } else if (PchC.p_SizeOfBigInt < 4 || PchC.p_SizeOfBigInt > 8) {
        Emit4000Warning(1, 696, PchC.p_SizeOfBigInt << 3, 32);
        PchC.p_SizeOfBigInt = 4;
    } else if (PchC.p_SizeOfBigInt != 4 && PchC.p_SizeOfBigInt != 8) {
        Emit4000Warning(1, 696, PchC.p_SizeOfBigInt << 3, 32);
        PchC.p_SizeOfBigInt = 4;
    }

    for (i = 0; gReserved_keyword_token_values[i].name != NULL; i++) {
        FindOrCreateBucket_0041b16d(gReserved_keyword_token_values[i].name);
        gCurrent_bucket->hash_and_flags |= 0x10000;
        gCurrent_bucket->data_field_0x0 = gReserved_keyword_token_values[i].id;
    }
    FUN_0041b764("asm");
    FUN_0041b764("catch");
    FUN_0041b764("class");
    FUN_0041b764("const_cast");
    FUN_0041b764("delete");
    FUN_0041b764("dynamic_cast");
    FUN_0041b764("friend");
    FUN_0041b764("inline");
    FUN_0041b764("new");
    FUN_0041b764("operator");
    FUN_0041b764("private");
    FUN_0041b764("protected");
    FUN_0041b764("public");
    FUN_0041b764("reinterpret_cast");
    FUN_0041b764("static_cast");
    FUN_0041b764("template");
    FUN_0041b764("this");
    FUN_0041b764("throw");
    FUN_0041b764("try");
    FUN_0041b764("typeid");
    FUN_0041b764("virtual");
    FUN_0041b764("namespace");
    FUN_0041b764("using");
    FUN_0041b764("__interrupt");
    FUN_0041b764("__loadds");
    FUN_0041b764("__saveregs");
    FUN_0041b764("__segment");
    FUN_0041b764("__segname");
    FUN_0041b764("__self");

    if (!PchC.p_Extension) {
        FUN_0041b764("cdecl");
    }
    if (!gOption_Zf && !PchC.p_Extension) {
        FUN_0041b764("far");
    }
    if (!gOption_Zf && !PchC.p_Extension) {
        FUN_0041b764("fortran");
    }
    if (!gOption_Zf && !PchC.p_Extension) {
        FUN_0041b764("near");
    }
    if (!gOption_Zf && !PchC.p_Extension) {
        FUN_0041b764("huge");
    }
    if (!gOption_Zf && !PchC.p_Extension) {
        FUN_0041b764("pascal");
    }
    FUN_0041b764("wchar_t");
    FUN_0041b764("bool");
    FUN_0041b764("true");
    FUN_0041b764("false");
    FUN_0041b764("mutable");
    FUN_0041b764("explicit");
    FUN_0041b764("typename");
    MarkKeywordReservedForFutureUse("namespace");
    MarkKeywordReservedForFutureUse("using");
    MarkKeywordOnlySupportedInCPP("__single_inheritance");
    MarkKeywordOnlySupportedInCPP("__multiple_inheritance");
    MarkKeywordOnlySupportedInCPP("__virtual_inheritance");
    MarkKeywordOnlySupportedInCPP("__novtordisp");
    MarkKeywordReservedForFutureUse("__resume");
    MarkKeywordReservedForFutureUse("__nounwind");
    MarkKeywordAsObsolete("__syscall");
    MarkKeywordAsObsolete("__near");
    MarkKeywordAsObsolete("__far");
    MarkKeywordAsObsolete("__far16");
    MarkKeywordAsObsolete("__huge");
    MarkKeywordAsObsolete("__fortran");
    MarkKeywordAsObsoleteUseDeclspecDllexportInstead("__export");
    MarkKeywordReservedForFutureUse("__thiscall");
    MarkKeywordAsObsolete("far");
    MarkKeywordAsObsolete("fortran");
    MarkKeywordAsObsolete("huge");
    MarkKeywordAsObsolete("near");
    MarkKeywordAsObsolete("pascal");
    MarkKeywordAsObsolete("__pascal");
    MarkKeywordAsNotSupportedInThisProduct("__unaligned");
    MarkKeywordAsNotSupportedInThisProduct("__builtin_alignof");
    MarkKeywordAsNotSupportedInThisProduct("__sysapi");
    MarkKeywordAsNotSupportedInThisProduct("__builtin_isfloat");
    MarkKeywordAsNotSupportedInThisProduct("__wchar_t");
    MarkKeywordAsNotSupportedInThisProduct("__restrict");

    if (PchC.p_SizeOfBigInt < 4) {
        MarkKeywordAsNotSupportedInThisProduct("__int8");
    }
    if (PchC.p_SizeOfBigInt < 4) {
        MarkKeywordAsNotSupportedInThisProduct("__int16");
    }
    if (PchC.p_SizeOfBigInt < 4) {
        MarkKeywordAsNotSupportedInThisProduct("__int32");
    }
    if (PchC.p_SizeOfBigInt < 8) {
        MarkKeywordAsNotSupportedInThisProduct("__int64");
    }
    if (PchC.p_SizeOfBigInt < 16) {
        MarkKeywordAsNotSupportedInThisProduct("__int128");
    }
    MarkTokenAsNotYetSupported("bool");
    MarkTokenAsNotYetSupported("true");
    MarkTokenAsNotYetSupported("false");
    MarkTokenAsNotYetSupported("mutable");
    MarkTokenAsNotYetSupported("explicit");
    MarkTokenAsNotYetSupported("typename");

    if (gOptions_0045c0a8.p_Extension || gOptions_0045c0a8.option_ZE) {
        for (i = 0; gReserved_keyword_token_values[i].name != NULL; i++) {
            if (strncmp(gReserved_keyword_token_values[i].name, "__", 2) == 0) {
                FindOrCreateBucket_0041b16d(gReserved_keyword_token_values[i].name);
                if (gCurrent_bucket->hash_and_flags & 0x10000) {
                    if (gCurrent_bucket->data_field_0x0 == 251) {
                        undefined v = gCurrent_bucket->data_field_0x1;
                        if (v == 1 || v == 5) {
                            FindOrCreateBucket_0041b16d(&gReserved_keyword_token_values[i].name[1]);
                            gCurrent_bucket->hash_and_flags |= 0x10000;
                            gCurrent_bucket->data_field_0x0 = 251;
                            gCurrent_bucket->data_field_0x1 = v;
                        }
                    } else {
                        FindOrCreateBucket_0041b16d(&gReserved_keyword_token_values[i].name[1]);
                        gCurrent_bucket->hash_and_flags |= 0x10000;
                        gCurrent_bucket->data_field_0x0 = 251;
                    }
                }
            }
        }
    }
    RegisterExtendedDeclModifiers();
}

// FUNCTION: C1 0x00448450
FILE *__fastcall OpenFileInDirectory(const char *directory, const char *filename, const char *mode)
{
    char path[260];

    strcpy(path, directory);
    if (filename != NULL) {
        strcat(path, filename);
    }
    FILE *f = fopen(path, mode);
    if (f == NULL) {
        fatal_io_CRT(83, 339, path);
    }
    setvbuf(f, NULL, 0, 4096);
    return f;
}

// FUNCTION: C1 0x004193d4
void FUN_004193d4()
{
    // empty
}

// FUNCTION: C1 0x0041a66d
void FUN_0041a66d()
{
    gPTR_0045bb64 = (tStruct_0045bb64 **) gPCH_chunks[0].Allocate(2048 * sizeof(tStruct_0045bb64 *));
    gPTR_0045b5b4 = (undefined4 **) gPCH_chunks[0].Allocate(1024 * sizeof(undefined4 *));
    gPTR_0045b5ac = (undefined4 **) gPCH_chunks[0].Allocate(1024 * sizeof(undefined4 *));
}

// FUNCTION: C1 0x00401000
tStruct_00401000 *__fastcall FUN_00401000(tStruct_00401000 *arg)
{
    tStruct_0045bb64 **ptr_first = &gPTR_0045bb64[(arg->field_0x08 / 4 + arg->field_0x04 / 4 + arg->field_0x02 + arg->field_0x00) % 0x800];
    tStruct_0045bb64 *item = *ptr_first;
    while (item != NULL) {
        if (item->field_0x4.field_0x04 == arg->field_0x04
            && item->field_0x4.field_0x08 == arg->field_0x08
            && item->field_0x4.field_0x00 == arg->field_0x00
            && item->field_0x4.field_0x02 == arg->field_0x02) {
            return &item->field_0x4;
        }
        item = item->next;
    }
    item = (tStruct_0045bb64*)gPCH_allocated_chunk_00466468.Allocate(sizeof(tStruct_0045bb64));
    item->next = *ptr_first;
    *ptr_first = item;
    item->field_0x4 = *arg;
    if (gOptions_0045c0a8.p_Symbolic_debug_holder) {
        item->field_0x4.field_0x0c = 0;
    }
    return &item->field_0x4;
}

// FUNCTION: C1 0x00407472
undefined4 * FUN_00407472()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041a934
void FUN_0041a934()
{
    gStruct_0045e470.field_0x4 = 0;
    gStruct_0045e470.field_0x0 = 2;
}

// FUNCTION: C1 0x0040c224
tStruct_0045b5b0_bucket * __fastcall CreateBucket_0040c224(const char *identifier)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00419350
void FUN_00419350()
{
    int i;

    for (i = 0; gSpecial_identifiers_and_buckets[i].ptr_bucket != NULL; i++) {
        *gSpecial_identifiers_and_buckets[i].ptr_bucket = CreateBucket_0040c224(gSpecial_identifiers_and_buckets[i].name);
    }
}

// FUNCTION: C1 0x00405f30
tStruct_00405f3 * __fastcall FUN_00405f30(undefined2 arg1, undefined2 arg2, undefined4 *arg3)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x004058d8
void tStruct_00405f3::FUN_004058d8(undefined4 *arg1, undefined4 arg2)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041e7bc
tStruct_0041e7bc::tStruct_0041e7bc(tStruct_00401000 *arg1, tStruct_00468c10* arg2)
{
    memset(this, 0, sizeof(*this));
    m_field_0x24 = FUN_00407472();
    m_field_0x1c = arg2->field_0x0;
    m_field_0x20 = arg2->field_0x4;
    m_field_0x00 = arg1;
}

// FUNCTION: C1 0x00405900
void tStruct_0041e7bc_offset_0x18::FUN_00405900()
{
    NOT_IMPLEMENTED();
#if 0
    if (m_field_0x8) {
        gStruct_0045b690->FUN_0040aedc();
    }
    if (m_field_0x4 == 6) {
        m_field_0x4 = m_field_0x0->FUN_0040afc0);
    }
#endif
}

// FUNCTION: C1 0x00409fc4
void tStruct_0041e7bc::FUN_00409fc4(tStruct_FUN_00409fc4_arg *arg1, tStruct_FUN_00409fc4_arg *arg2)
{
    if (arg1->field_0x0 & 0x70) {
        m_field_0x14 |= 0x1;
    }
    tStruct_00405f3 *v = FUN_00405f30(1, arg1->field_0x0 | arg2->field_0x0, &arg1->field_0x4);
    if (m_field_0x08 != NULL) {
        m_field_0x08->m_field_0x4 = v;
        m_field_0x08 = v;
    } else {
        m_field_0x08 = v;
        m_field_0x04 = v;
    }
}

// FUNCTION: C1 0x00405ced
void tStruct_0041e7bc::FUN_00405ced(tStruct_00405f3 *arg)
{
    m_field_0x14 |= 0x1;
    if (m_field_0x04 != NULL) {
        switch (m_field_0x08->m_field_0x0 & 0x7) {
        case 0x1:
            m_field_0x08->m_field_0x0 = (arg->m_field_0x0 & 0xc803) | 0x3;
            break;
        case 0x2:
            EmitError(92);
            m_field_0x08->m_field_0x8 = 0;
            m_field_0x08->m_field_0x0 = 1;
            break;
        case 0x4:
            {
                EmitError(92);
                tStruct_FUN_00409fc4_arg a1;
                a1.field_0x0 = 0;
                a1.field_0x4 = 0;
                tStruct_FUN_00409fc4_arg a2;
                a2.field_0x0 = 0;
                a2.field_0x4 = 0;
                FUN_00409fc4(&a1, &a2);
                m_field_0x08->m_field_0x0 = 3;
                break;
            }
        }
        if (this->m_field_0x08->m_field_0x2 & 0x300) {
            EmitError(212, m_field_0x24);
            m_field_0x2c |= 0x1;
            m_field_0x08->m_field_0x2 &= ~0x400;
        }
    }
}

// FUNCTION: C1 0x00405d36
void tStruct_0041e7bc::FUN_00405d36(tStruct_0041e7bc_offset_0x18 *arg)
{
    bool was_null = m_field_0x04 == NULL;
    m_field_0x2c |= 0x10;
    arg->FUN_00405900();
    undefined4 a;
    tStruct_00405f3 *v = FUN_00405f30(4, 0, &a);
    v->FUN_004058d8(arg->m_field_0x0, arg->m_field_0x4);
    if (was_null && (m_field_0x0c & 0x70)) {
        v->m_field_0x2 |= 0x70;
        m_field_0x0c &= ~0x70;
    }
    this->FUN_00405ced(v);
    if (m_field_0x08 != NULL) {
        m_field_0x08->m_field_0x4 = v;
        m_field_0x08 = v;
    } else {
        m_field_0x08 = v;
        m_field_0x04 = v;
    }
    if (was_null) {
        m_field_0x2c |= 0x8;
        m_field_0x18 = arg;
    }
}

// FUNCTION: C1 0x00411349
void tStruct_0041e7bc::FUN_00411349(tStruct_FUN_00411349_arg *arg)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00405faf
void tStruct_0041e7bc::FUN_00405faf()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041c756
undefined4 __fastcall FUN_0041c756 (undefined4 arg1, tStruct_00401000 *arg2)
{
    tStruct_0041e7bc data(arg2, &gStruct_00468c10);
    data.FUN_00405d36(new tStruct_0041e7bc_offset_0x18);
    tStruct_FUN_00411349_arg fun_arg;
    fun_arg.field_0x4 = 0;
    fun_arg.field_0x0 = arg1;
    data.FUN_00411349(&fun_arg);
    data.FUN_00405faf();
    return data.GetField0x28();
}

// FUNCTION: C1 0x0041c558
tStruct_00401000 *__fastcall FUN_0041c558(undefined2 flags)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041c258
void FUN_0041c258()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041c5d3
void FUN_0041c5d3()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041a4a6
void __fastcall FUN_0041a4a6(tStringVector *macros)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x004199cc
void init_main3()
{
    NOT_IMPLEMENTED();
}


// FUNCTION: C1 0x00419c44
void init_main2()
{
    char buffer[20];

    if (!FESigMgr::open(gOptions_0045c0a8.option_Gi && !Prep && !Out_funcdef, &gIncremental_interface1, &gIncremental_interface2)) {
        FatalErrorF(73, "main.c", 151);
    }
    SetHandleCount(30);
    gOptions_0045c0a8.p_NoPoundLines = gOptions_0045c0a8.p_NoPoundLines || !Prep;
    if (gOption_Zp != -1) {
        gPragma_stack->items->value = gOption_Zp;
    } else {
        gPragma_stack->items->value = 8;
    }
    gOptions_0045c0a8.bool_0xb4 = gOptions_0045c0a8.option_Gs;
    gOptions_0045c0a8.bool_0x84 = gOptions_0045c0a8.option_Gf;
    gOptions_0045c0a8.bool_0x8c = gOptions_0045c0a8.option_GF;
    gOptions_0045c0a8.bool_0x3dc = gOptions_0045c0a8.option_Oq;
    if (gOptions_0045c0a8.option_G > 4) {
        format(buffer, "-G%d", sizeof(buffer), gOptions_0045c0a8.option_G);
        FatalErrorF(7, buffer, "c1");
    }
    FUN_0041ba35();
    if (Prep || Out_funcdef) {
        SourceBrowserNamFlg = NULL;
        SourceBrowserExt = NULL;
        gOptions_0045c0a8.p_SourceBrowserExtended = FALSE;
        gOptions_0045c0a8.p_SourceBrowser = FALSE;
    } else {
        if (SourceBrowserExt != NULL) {
            gOptions_0045c0a8.p_SourceBrowserExtended = TRUE;
            SourceBrowserNamFlg = SourceBrowserExt;
        }
        gOptions_0045c0a8.p_SourceBrowser = SourceBrowserNamFlg != NULL;
        SourceBrowserNam = SourceBrowserNamFlg;
    }
    SBR::Open(SourceBrowserNamFlg);
    pSbr = GetDummySourceBrowser();
    if (fPersistentPch) {
        if (PchCFile == NULL && (PchPFile == NULL || PchUFlag)) {
            fPersistentPch = FALSE;
        } else {
            if (ValidatePersistentPch(PchCFile)) {
                PchOldUFlag = PchUFlag;
                gOriginal_option_Yu_path = PchUFile;
                fReusePersistPch = TRUE;
                if (PchUFlag) {
                    PchPFile = NULL;
                }
                PchUFlag = TRUE;
                PchUFile = PchCFile;
                PchCFlag = FALSE;
                PchCFile = NULL;
            } else {
                fGenPersistPch = TRUE;
                WriteMacrosAndIncludesToPCH();
            }
        }
    }
    gBOOL_0045c4e0 = PchCFlag;
    PchReuseCVTypes = gOptions_0045c0a8.p_Symbolic_debug_holder && !gOptions_0045c0a8.p_PchDFlag && PchCFlag;
    FUN_0041b776();
    CreateKeywordHashmap();
    InitKeywords();
    FUN_004193d4();
    if (gWrite_er && !Out_funcdef) {
        gFile_er = OpenFileInDirectory(Basename, "er", "w");
        gFile_lp = OpenFileInDirectory(Basename, "lp", "w");
    }
    if (!Prep && !Out_funcdef) {
        if (gOptions_0045c0a8.option_C9IL) {
            FUN_0041c815();
            ilsLSym.Open(Basename, "sy", "w+");
            ilsGSym.Open(Basename, "gl", "w+");
            ilsInit.Open(Basename, "in", "w+");
            if (gOptions_0045c0a8.p_Symbolic_debug_holder) {
                ildsDB.Open(Basename, "db", "w+");
            }
        } else {
            ilsLSym.set_field_0x24(1);
            ilsInit.set_field_0x24(4);
            ilsExp.set_field_0x24(2);
            gFILESTREAM_004609b0.set_field_0x24(5);
            ilsGSym.set_field_0x24(1);
            gFILESTREAM_00465fb0.set_field_0x24(1);
        }
    }
    if (gOption_Fi_path != NULL) {
        if (_dup(STDOUT_FILENO) == -1) {
            fatal_io_CRT(83, 340, gOption_Fi_path);
        } else {
            gFi_file = freopen(gOption_Fi_path, "wt+", stdout);
            if (gFi_file == NULL) {
                fatal_io_CRT(83, 340, gOption_Fi_path);
            }
        }
    }
    I_Eoutput = stdout;
    FUN_0041a66d();

    tStruct_00401000 *var = (tStruct_00401000 *)gPCH_chunks[3].Allocate(sizeof(tStruct_00401000));
    var->field_0x02 = 0;
    var->field_0x04 = 0;
    var->field_0x08 = 0;

    var->field_0x00 = 0;
    gPTR_0045b67c = FUN_00401000(var);
    var->field_0x00 = 0x4041;
    gPTR_0045b670 = FUN_00401000(var);
    var->field_0x00 = 0x63;
    gPTR_0045b630 = FUN_00401000(var);
    var->field_0x00 = 0x4063;
    gPTR_0045b674 = FUN_00401000(var);
    var->field_0x00 = 0x41;
    gPTR_0045b634 = FUN_00401000(var);
    var->field_0x00 = 0x4041;
    gPTR_0045b638 = FUN_00401000(var);
    var->field_0x00 = 0x42;
    gPTR_0045b63c = FUN_00401000(var);
    var->field_0x00 = 0x4042;
    gPTR_0045b640 = FUN_00401000(var);
    var->field_0x00 = 0x43;
    gPTR_0045b644 = FUN_00401000(var);
    var->field_0x00 = 0x4043;
    gPTR_0045b648 = FUN_00401000(var);
    var->field_0x00 = 0x4c;
    gPTR_0045b64c = FUN_00401000(var);
    var->field_0x00 = 0x404c;
    gPTR_0045b650 = FUN_00401000(var);
    var->field_0x00 = 0x4063;
    gPTR_0045b678 = FUN_00401000(var);
    var->field_0x00 = 0x42;
    gPTR_0045b668 = FUN_00401000(var);
    var->field_0x00 = 0x4042;
    gPTR_0045b66c = FUN_00401000(var);
    var->field_0x00 = 0x44;
    gPTR_0045b65c = FUN_00401000(var);
    var->field_0x00 = 0x4044;
    gPTR_0045b660 = FUN_00401000(var);
    var->field_0x00 = 0x107;
    gPTR_0045b62c = FUN_00401000(var);
    var->field_0x00 = 0x802;
    gPTR_0045b664 = FUN_00401000(var);
    var->field_0x00 = 0x80;
    gPTR_0045b680 = FUN_00401000(var);
    var->field_0x02 = 1;
    var->field_0x00 = 0x41;
    gPTR_0045b620 = FUN_00401000(var);
    var->field_0x00 = 0x4041;
    gPTR_0045b628 = FUN_00401000(var);
    var->field_0x00 = 99;
    gPTR_0045b624 = FUN_00401000(var);
    var->field_0x02 = 0;

    FUN_0041a934();
    gStruct_0045b690 = new tStruct_0045b690;
    FUN_00419350();
    if (!Prep) {
        gUNK_0045b684 = FUN_0041c756(0, gPTR_0045b630);
        gUNK_0045b688 = FUN_0041c558(0x80);
        if (Out_funcdef == 0) {
            FUN_0041c258();
        }
        FUN_0041c5d3();
    }
    FUN_0041a4a6(listDefs);
    tStruct_00456d30 *unk_stream = new tStruct_00456d30;
    tokenInputStack.FUN_0040267e(unk_stream, 0, 0, &tokenInputStack);
    if (gPTR_0045e478 == NULL) {
        gPTR_0045e478 = new tStruct_0045e478;
    }
    if (!PchUFlag) {
        init_main3();
    }
}

// FUNCTION: C1 0x004082bf
uint32_t PstatGetStatus()
{
    uint32_t result = 0;
    uint32_t flag = 0x80000000;
    int i;

    for (i = 0; i < ARRAYSIZE(PstatFlagMap); i++) {
        if (PstatFlagMap[i] != NULL && *PstatFlagMap[i]) {
            result |= flag;
        }
        flag >>= 1;
    }
    return result;
}

// FUNCTION: C1 0x00426b10
void FUN_00426b10()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041c5bf
void FUN_0041c5bf()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0043ff10
void __fastcall FUN_0043ff10(const char *path, BOOL arg2)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0044648e
void FUN_0044648e()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041e9c3
void FUN_0041e9c3()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x004495f1
void FUN_004495f1() {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x004496d8
void FUN_004496d8() {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x004445a1
void FUN_004445a1() {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041e7f1
void RunYACC_0041e7f1() {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041f45d
void __fastcall FUN_0041f45d(tStruct_0045b690 *arg1)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0040929e
tStruct_0040925a * __fastcall FUN_0040929e(int arg1) {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041402e
void __fastcall FUN_0041402e(undefined4 arg1, tStruct_0040925a *arg2)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0040872a
void FUN_0040872a()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041f3a9
void FUN_0041f3a9()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x004497c1
void __fastcall FUN_004497c1(BOOL arg1)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x004491dd
void FUN_004491dd()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00426935
int __fastcall FUN_00426935(FILE *f)
{
    if (f == NULL) {
        return -1;
    }
    return fclose(f);
}

// FUNCTION: C1 0x0041f15f
void FUN_0041f15f()
{
    NOT_IMPLEMENTED();
}

// FUCNTION: C1 0x00445a54
void OKToHandleCtrlC(void)
{
    if (ExecutionState != 8) {
        if (ExecutionState == 6) {
            return;
        }
        AvoidRecursiveFatalError(6);
        ReleaseEverythingUponError();
    }
    if (gTerminalSignalSemaphore != NULL) {
        ReleaseSemaphore(gTerminalSignalSemaphore, 1, NULL);
    }
    Sleep(0);
    ExitProcess(0x8000);
}

// FUNCTION: C1 0x004193d6
void main_compile()
{
    init_main2();
    gOptimization_flags_00469308 = PstatGetStatus();
    AddTiming("the reset of init2");
    ExecutionState = 3;
    gOptions_0045c0a8.p_PchDFlag = gOptions_0045c0a8.p_PchDFlag && !gOptions_0045c0a8.p_FUseTypeServer;
    if (Prep) {
        FUN_00426b10();
        ExecutionState = 5;
    } else {
        if (gOptions_0045c0a8.option_C9IL) {
            FUN_0041c5bf();
        }
        if (PchUFlag) {
            if (PchOldUFlag) {
                FUN_0043ff10(gOriginal_option_Yu_path, FALSE);
            }
            FUN_0043ff10(PchUFile, TRUE);
        } else {
            gOptions_0045c0a8.optimization_flags_0xa8 = PstatGetStatus();
            if (gOption_YX) {
                gOptions_0045c0a8.p_PchDFlag = !gOptions_0045c0a8.p_FUseTypeServer;
                FUN_0044648e();
            } else {
                gINT_00469158 = 0;
                if (gOptions_0045c0a8.option_C9IL && !Prep && !Out_funcdef && gOptions_0045c0a8.p_Symbolic_debug_holder) {
                    FUN_0041e9c3();
                }
            }
            gOptions_PCH_00468d50 = gOptions_0045c0a8;
        }
        AddTiming("PCH open");
        if (!gOptions_0045c0a8.option_C9IL && !gOption_YX) {
            if (gBOOL_0045c4e0) {
                FUN_004495f1();
            } else {
                FUN_004496d8();
                FUN_004445a1();
            }
        }
        RunYACC_0041e7f1();
        if (gOptions_0045c0a8.option_C9IL || gBOOL_0045c6d0) {
            AddTiming("primary parsing");
        } else {
            AddTiming("headers");
        }
        if (!Out_funcdef) {
            AddTiming("compiler generated stuff");
            FUN_0041f45d(gStruct_0045b690);
            AddTiming("global symbols");
            if (gOptions_0045c0a8.option_C9IL) {
                if (gBOOL_0045f98c) {
                    FUN_0041402e(83, NULL);
                    FUN_0041402e(84, FUN_0040929e(0));
                }
                FUN_0041402e(77, NULL);
            }
            FUN_0040872a();
        }
        AddTiming("expect nothing");
        ExecutionState = 5;
        pSbr = GetSourceBrowser();
        pSbr->vtable_0x00();
        DestroySourceBrowser();
        if ((WarnIsError > 1) + Nerrors == 0) {
            if (!gIncremental_interface3->vmethod_inc3_0x00()) {
                char buffer[260];
                EmitError(471, gPTR_00466458->field_0x0->vmethod_0x0c(buffer));
            }
        }
        if (!gIncremental_interface3->vmethod_inc3_0x04()) {
            FatalErrorF(73, "main.c", 1326);
        }
        if (!Out_funcdef) {
            if (!Prep && (gOptions_0045c0a8.p_Symbolic_debug_holder || gOptions_0045c0a8.p_FUseTypeServer)) {
                FUN_0041f3a9();
            }
            if (gOptions_0045c0a8.option_C9IL == 0) {
                FUN_004497c1(FALSE);
                FUN_004491dd();
            }
            else {
                ilsExp.Ilsink_Close();
                ilsLSym.Ilsink_Close();
                ilsGSym.Ilsink_Close();
                gFILESTREAM_00465fe0.FlushBuffer();
                ilsInit.Ilsink_Close();
                if (gOptions_0045c0a8.p_Symbolic_debug_holder) {
                    ildsDB.Ilsink_Close();
                }
            }
            gPTR_00466458->FUN_0041f2db();
        }
        gIncremental_interface1->vtable_inc1_0x10();
    }
    if (gOption_Fi_path != NULL) {
        if (FUN_00426935(gFi_file)) {
            FUN_0044810e(85, 340, gOption_Fi_path, "main.c", 1388);
        }
    }
    if (fflush(stdout) != 0) {
        FUN_0044810e(85, 340, NULL, "main.c", 1393);
    }
    FUN_0041f15f();
    AddTiming("IPM/MR/IL close and wrap-up");
    PrintTimings();
    CleanupMemory();
    ExecutionState = 8;
    if (HandlingControlC) {
        OKToHandleCtrlC();
    }
    exit(Nerrors + (1 < WarnIsError));
}

// FUNCTION: C1 0x004197a4
int main(int argc, char *argv[])
{
    ExecutionState = 1;
    ReserveMacroBuffers();
    InitTiming();
    atexit(FUN_0041f0b2);
    signal(SIGINT, OnTerminalSignal);
    signal(SIGTERM, OnTerminalSignal);
    signal(SIGBREAK, OnTerminalSignal);
    Argc = argc;
    Argv = argv;
    PreParseArgs(argv);
    FUN_0041934f();
    GetSystemInfo(&gSystem_info);
    HeapManager::InitGlobalHeaps();
    init_main1(argc, argv);
    AddTiming("init1");
    if (gOptions_0045c0a8.option_C9IL) {
        gUINT_0045bf98 |= 0x2000;
    } else {
        gUINT_0045bf98 &= ~0x2000;
    }
    if (gOptions_0045c0a8.option_Bd) {
        main_compile();
    } else {
        main_compile();
    }
}

// FUNCTION: C1 0x00419195
void tFILESTREAM::Open(const char *dirpath, const char *filename, const char *mode)
{
    const char *p;
    char buffer[260];

    if (strcmp(dirpath, "nul") == 0) {
        p = NULL;
    } else {
        p = filename;
    }
    strcpy(buffer, dirpath);
    if (p != NULL) {
        strcat(buffer, p);
    }
    m_file = fopen(buffer, mode);
    if (m_file == NULL) {
        fatal_io_CRT(83, 339, buffer);
    }
    setvbuf(m_file, NULL, _IOFBF, 4096);
}

// FUNCTION: C1 0x0041f36c
int tFILESTREAM::Close()
{
    if (m_file == NULL) {
        return ((WarnIsError > 1) + Nerrors) == 0 ? 0 : -1;
    }
    FlushWrite();
    int result = fclose(m_file);
    m_file = NULL;
    return result;
}

// FUNCTION: C1 0x0041f2f7
void tFILESTREAM::Ilsink_Close()
{
    gILSINK_ErrorCode = Close();
    if (gILSINK_ErrorCode == -1) {
        FUN_0044810e(82, 339, NULL, "ilsink.cpp", 81);
    }
}

// FUNCTION: C1 0x00411ab2
BOOL tFILESTREAM::IncreaseBuffer(size_t size)
{
    size_t increment = m_buffer_size / 2;
    if (size + 4096 >= increment) {
        increment = size + 4096;
    }
    size_t new_size = (m_buffer_size + increment + 4096 - 1) & ~(4096 - 1);
    char *new_buffer = new char[new_size];
    if (new_buffer == NULL) {
        return FALSE;
    }
    m_buffer_size = new_size;
    size_t left = m_write_end - m_write_left;
    memcpy(new_buffer, m_write_left, left);
    memset(new_buffer + left, 0, m_buffer_size - left);
    delete[] m_write_left;
    if (new_buffer != NULL) {
        void *prev_write_left = m_write_left;
        m_write_end = new_buffer + left;
        m_write_left = new_buffer;
        if (new_buffer != prev_write_left && m_field_0x0c != NULL) {
            m_field_0x0c(new_buffer);
        }
    }
    return TRUE;
}

// FUNCTION: C1 0x0041b801
tStruct_0045b690::tStruct_0045b690()
{
    m_field_0x00c[508] = 0;
    m_field_0x20c = 0;
    m_field_0x210 = 0;
    m_field_0x214 = 0;
    m_field_0x218 = 0;
    m_field_0x000 = new tStruct_0045b690_field_0x0;
    m_field_0x000->Initialize();
    m_field_0x004 = m_field_0x000;
    m_field_0x008 = m_field_0x000;
}

// FUNCTION: C1 0x0040267e
void tCurrent_file_thing_0045e450::FUN_0040267e(tStruct_00456d30 *arg1, undefined4 arg2, undefined4 arg3, tCurrent_file_thing_0045e450 *arg4)
{
    NOT_IMPLEMENTED();
}

// tStruct_00452018

// FUNCTION: C1 0x0040465f
BOOL tStruct_00452018::vtable_0x00() {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0043ee70
undefined4 tStruct_00452018::vtable_0x04() {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041915a
void tStruct_00452018::vtable_0x08(undefined4) {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x004051c0
void tStruct_00452018::vtable_0x0c(undefined4) {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0043ee4e
undefined4 tStruct_00452018::vtable_0x10() {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0040525f
void tStruct_00452018::vtable_0x14() {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0043ee51
tStruct_00452018::~tStruct_00452018() {
    NOT_IMPLEMENTED();
}

// tStruct_00456d30


// FUNCTION: C1 0x00403187
BOOL tStruct_00456d30::vtable_0x00() {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00445bb0
undefined4 tStruct_00456d30::vtable_0x04() {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x004067a3
void tStruct_00456d30::vtable_0x08(undefined4) {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00445bc7
void tStruct_00456d30::vtable_0x0c(undefined4) {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x004067b4
undefined4 tStruct_00456d30::vtable_0x10() {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00445bca
void tStruct_00456d30::vtable_0x14() {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00445bcb
tStruct_00456d30::~tStruct_00456d30() {
    NOT_IMPLEMENTED();
}

// tStruct_0045b690_field_0x0_parent

// FUNCTION: C1 0x0044e7bc
BOOL tStruct_0045b690_field_0x0_parent::vtable_0x00()
{
    return TRUE;
}

// FUNCTION: C1 0x0044e7f2
undefined4 tStruct_0045b690_field_0x0_parent::vtable_0x08(undefined4, undefined4)
{
    FatalErrorF(1, "symtable.inl", 1625);
    return 0;
}

// FUNCTION: C1 0x0044e80b
undefined4 tStruct_0045b690_field_0x0_parent::vtable_0x0c(undefined4)
{
    FatalErrorF(1, "symtable.inl", 1635);
    return 0;
}

// FUNCTION: C1 0x0044e7d9
undefined4 tStruct_0045b690_field_0x0_parent::vtable_0x10(undefined4)
{
    FatalErrorF(1, "symtable.inl", 1611);
    return 0;
}

// FUNCTION: C1 0x00448797
void tStruct_0045b690_field_0x0_parent::vtable_0x1c()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0044e824
void tStruct_0045b690_field_0x0_parent::vtable_0x20()
{
    FatalErrorF(1, "symtable.inl", 1642);
}

// FUNCTION: C1 0x0044e7c2
void tStruct_0045b690_field_0x0_parent::vtable_0x24(undefined4)
{
    FatalErrorF(1, "symtable.inl", 1595);
}

// tStruct_0045b690_field_0x0

// FUNCTION: C1 0x00413c21
BOOL tStruct_0045b690_field_0x0::vtable_0x00() {
    return m_field_0x10 != NULL;
}

// FUNCTION: C1 0x00405a13
void tStruct_0045b690_field_0x0::vtable_0x04(undefined4) {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x004070a0
undefined4 tStruct_0045b690_field_0x0::vtable_0x08(undefined4, undefined4) {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00410047
undefined4 tStruct_0045b690_field_0x0::vtable_0x0c(undefined4) {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0040a1b9
undefined4 tStruct_0045b690_field_0x0::vtable_0x10(undefined4) {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0044e548
void tStruct_0045b690_field_0x0::vtable_0x14(undefined4,undefined4) {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0044e518
undefined4 tStruct_0045b690_field_0x0::vtable_0x18(undefined4,undefined4) {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x004487b8
void tStruct_0045b690_field_0x0::vtable_0x1c() {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00408f75
void tStruct_0045b690_field_0x0::vtable_0x20() {
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00405f6f
void tStruct_0045b690_field_0x0::vtable_0x24(undefined4) {
    NOT_IMPLEMENTED();
}
