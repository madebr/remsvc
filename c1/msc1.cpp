#include "decomp.h"

#include "alloc.h"
#include "browser.h"
#include "incremental.h"
#include "pch.h"
#include "types.h"

#include "msvcrt.h"

#include <io.h>
#include <locale.h>
#include <mbctype.h>
#include <mbstring.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#define CHARACTER_CLASS1(C) (gCharacter_classes_1[(uint8_t)(C)])
#define CHARACTER_CLASS2(C) (gCharacter_classes_2[(uint8_t)(C)])
#define CHARACTER_CLASS3(C) (gCharacter_classes_3[(uint8_t)(C)])

#define MAX_ARG_COUNT (200)

// GLOBAL: C1 0x0045b0b0
uint8_t gCharacter_classes_1[256] = {
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
uint8_t gCharacter_classes_3[256] = {
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
BOOLEAN gTerminalSignalReceived = FALSE;

// GLOBAL: C1 0x00468c20
int gCountTimings = 0;

// GLOBAL: C1 0x00468c1c
DWORD gPrevTickCount = 0;

// GLOBAL: C1 0x00468c30
tTiming gTimings[20];

// GLOBAL: C1 0x0045c580
int gMain_stage = 0;

// GLOBAL: C1 0x00467040
int gArgc;

// GLOBAL: C1 0x00467044
char **gArgv = NULL;

// GLOBAL: C1 0x0045b530
char **gAllocated_argv = NULL;

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

// GLOBAL: C1 0x0045c494
BOOL gOption_C9IL = FALSE;

// GLOBAL: C1 0x0045c100
BOOL gOption_Bd = FALSE;

// GLOBAL: C1 0x0045bf98
unsigned int gUINT_0045bf98 = 0;

// GLOBAL: C1 x00045e3e8
uintptr_t gReserved_mem1_start = 0;

// GLOBAL: C1 0x0045e3ec
uintptr_t gReserved_mem2_start = 0;

// GLBOAL: C1 0x0045cbb8
uintptr_t gReserved_mem1_end = 0;

// GLOBAL: C1 0x0045cbc0
uintptr_t gReserved_mem2_end = 0;

// GLOBAL: C1 0x00466460
int gError_count = 0;

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
tPCH_allocated_chunk gPCH_allocated_chunk_00466298;

// GLOBAL: C1 0x004664a0
tPCH_allocated_chunk gPCH_allocated_chunk_004664a0;

// GLOBAL: C1 0x00466468
tPCH_allocated_chunk gPCH_allocated_chunk_00466468;

// GLOBAL: C1 0x00460a40
tPCH_allocated_chunk gPCH_allocated_chunk_00460a40;

// GLOBAL: C1 0x00460998
tPCH_allocated_chunk gPCH_allocated_chunk_00460998;

// GLOBAL: C1 0x00466170
tPCH_allocated_chunk gPCH_allocated_chunk_00466170;

// GLOBAL: C1 0x004660f8
tPCH_allocated_chunk gPCH_allocated_chunk_004660f8;

// GLOBAL: C1 0x00466040
tPCH_allocated_chunk gPCH_allocated_chunk_00466040;

// GLOBAL: C1 0x00460a18
tPCH_allocated_chunk gPCH_allocated_chunk_00460a18;

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
uint8_t gCVHash_msb_lut[256];

// GLOBAL: C1 0x0045f4c0
uint8_t gHash_permutation_lut[256];

// GLOBAL: C1 0x0045f6c0
uint8_t gCVHash_lsb_lut[256];

// GLOBAL: C1 0x00453080
const uint32_t gCVHash_shift_lut[8] = {
        0, 1, 3, 6, 8, 13, 15, UINT32_MAX,
};

// GLOBAL: C1 0x00466150
tStringVector *gArgument_macros;

// GLOBAL: C1 0x00460a84
tStringVector *gArgument_includes;

// GLOBAL: C1 0x00466118
tStringVector *gArgument_force_includes;

// GLOBAL: C1 0x004662d0
tSigPbCb gSigPbCb;

// GLOBAL: C1 0x0046714c
char *gOption_rsp_path;

// GLOBAL: C1 0x004664f4
BOOL gOption_nologo = FALSE;

// GLOBAL: C1 0x004664fc
BOOL gOption_FAT = FALSE;

// GLOBAL: C1 0x00466500
BOOL gBOOL_00466500 = FALSE;

// GLOBAL: C1 0x0045c53c
const char *gOption_pc_map = "\\:/";

// GLOBAL: C1 0x0045c0fc
BOOL gOption_pf = FALSE;

// GLOBAL: C1 0x00466450
BOOL gOption_C = FALSE;

// GLOBAL: C1 0x00466314
BOOL gOption_E = FALSE;

// GLOBAL: C1 0x0045c0f8
BOOL gOption_EP = FALSE;

// GLOBAL: C1 0x00466274
const char *gOption_Fi_path = NULL;

// GLOBAL: C1 0x00463a98
const char *gInput_filepath = NULL;

// GLOBAL: C1 0x0045c0c4
BOOL gOption_J = FALSE;

// GLOBAL: C1 0x00454e84
BOOL gOption_Jd = FALSE;

// GLOBAL: C1 0x0045c104
uint32_t gOption_Bu = 175;

// GLOBAL: C1 0x0045c4b0
int32_t gOption_Bm = 0;

// GLOBAL: C1 0x00467038
int32_t gOption_memory = 0;

// GLOBAL: C1 0x0045c108
BOOL gOption_Brepro = FALSE;

// GLOBAL: C1 0x0045c0e0
BOOL gOption_MD = FALSE;

// GLOBAL: C1 0x0045c0e4
BOOL gOption_MT = FALSE;

// GLOBAL: C1 0x004664b0
tStruct_00466458 gStruct_004664b0;

// GLOBAL: C1 0x004662a8
tStruct_00466458 gStruct_004662a8;

// GLOBAL: C1 0x00466458
tStruct_00466458 *gPTR_00466458 = NULL;

// GLOBAL: C1 0x004664c4
BOOL gOption_WX = FALSE;

// GLOBAL: C1 0x0045c514
int32_t gOption_W = 1;

// GLOBAL: C1 0x0045c548
int32_t gOption_Zp = -1;

// GLOBAL: C1 0x0045c0b0
int32_t gOption_ZBe = -1;

// GLOBAL: C1 0x0045c0b4
int32_t gOption_ZB = -1;

// GLOBAL: C1 0x0045c0a8
BOOL gOption_ZE = FALSE;

// GLOBAL: C1 0x0045c0ac
BOOL gOption_Ze = FALSE;

// GLOBAL: C1 0x0045c0ec
BOOL gOption_Zi = FALSE;

// GLOBAL: C1 0x0045c58c
BOOL gOption_Z7 = FALSE;

// GLOBAL: C1 0x00460a28
BOOL gOption_Zn = FALSE;

// GLOBAL: C1 0x0046603c
BOOL gOption_Zf = FALSE;

// GLOBAL: C1 0x00466164
BOOL gOption_Zg = FALSE;

// GLOBAL: C1 0x00460a10
BOOL gOption_ZI = FALSE;

// GLOBAL: C1 0x0045c540
const char *gError_message_path = "c1.err";

// GLOBAL: C1 0x0045c544
const char *gOption_il = "";

// GLOBAL: C1 0x00466484
BOOL gOption_xc = FALSE;

// GLOBAL: C1 0x00466484
const char *gOption_V_path = NULL;

// GLOBAL: C1 0x0045c114
BOOL gOption_Gs = TRUE;

// GLOBAL: C1 0x0045c0e8
BOOL gOption_Gc = FALSE;

// GLOBAL: C1 0x0045c0b8
BOOL gOption_Gr = FALSE;

// GLOBAL: C1 0x0045c120
BOOL gOption_Gd = FALSE;

// GLOBAL: C1 0x0045c124
BOOL gOption_Gz = FALSE;

// GLOBAL: C1 0x0045c498
BOOL gOption_Gi = FALSE;

// GLOBAL: C1 0x0045c49c
BOOL gOption_GI = FALSE;

// GLOBAL: C1 0x0045c4a4
BOOL gOption_GFR = TRUE;

// GLOBAL: C1 0x0045c4f8
const char *gOption_NV_path = NULL;

// GLOBAL: C1 0x00466318
const char *gOption_Fr_path = NULL;

// GLOBAL: C1 0x004662d8
const char *gOption_FR_path = NULL;

// GLOBAL: C1 0x0045c504
const char *gOption_Fj = FALSE;

// GLOBAL: C1 0x0045c50c
const char *gPDB_arg_path = "vc40.pdb";

// GLOBAL: C1 0x0045c508
const char *gObject_output_arg_path = NULL;

// GLOBAL: C1 0x0045c128
BOOL gOption_Gf = FALSE;

// GLOBAL: C1 0x0045c130
BOOL gOption_GF = FALSE;

// GLOBAL: C1 0x0045c138
BOOL gOption_cbstring = FALSE;

// GLOBAL: C1 0x0045c164
BOOL gOption_Oa = FALSE;

// GLOBAL: C1 0x0045c144
int32_t gOption_Ob = 0;

// GLOBAL: C1 0x0045c110
BOOL gOption_Oi = FALSE;

// GLOBAL: C1 0x0045c16c
BOOL gOption_Og = FALSE;

// GLOBAL: C1 0x0045c170
BOOL gOption_Op = FALSE;

// GLOBAL: C1 0x0045c160
BOOL gOption_Ot = TRUE;

// GLOBAL: C1 0x0045c168
BOOL gOption_Ow = FALSE;

// GLOBAL: C1 0x0045c480
BOOL gOption_Oq = FALSE;

// GLOBAL: C1 0x0045c488
BOOL gOption_Ov = FALSE;

// GLOBAL: C1 0x0045c174
BOOL gOption_Oy = FALSE;

// GLOBAL: C1 0x0045c158
BOOL gOption_C8MODE = FALSE;

// GLOBAL: C1 0x0046703c
BOOL gOption_debugBreak = FALSE;

// GLOBAL: C1 0x0045c57c
BOOL gPrint_timings = FALSE;

// GLOBAL: C1 0x0045c4b8
const char *gOption_Yu_path = NULL;

// GLOBAL: C1 0x0045c4b4
BOOL gOption_Yu = FALSE;

// GLOBAL: C1 0x0045c4c0
const char *gPCH_arg_path = NULL;

// GLOBAL: C1 0x0045c4bc
BOOL gOption_Yc = FALSE;

// GLOBAL: C1 0x0045c0f0
BOOL gOption_Yd = FALSE;

// GLOBAL: C1 0x0045c4d0
const char *gFp_arg_path = NULL;

// GLOBAL: C1 0x0045c4c8
const char *gYX_arg_path = NULL;

// GLOBAL: C1 0x0045c4c4
BOOL gOption_YX = FALSE;

// GLOBAL: C1 0x0045c4cc
const char *gYl_arg_path = NULL;

// GLOBAL: C1 0x0045c4e8
BOOL gOption_BPCH = TRUE;

// GLOBAL: C1 0x0045c568
BOOL gOption_noexpinl = FALSE;

// GLOBAL: C1 0x0045c140
BOOL gOption_GM = FALSE;

// GLOBAL: C1 0x0045c13c
int32_t gOption_G = 0;

// GLOBAL: C1 0x0045cb28
BOOL gOption_BMOVE = FALSE;

// GLOBAL: C1 0x0045c4a8
BOOL gOption_SplitPdbs = TRUE;

// GLOBAL: C1 0x0045c4ac
BOOL gOption_NoEHForNew = FALSE;

// GLOBAL: C1 0x0046611c
BOOL gOption_BShowIncl = FALSE;

// GLOBAL: C1 0x0045c588
const char *gUnknown_argument = NULL;

// GLOBAL: C1 0x0045f4b8
const char *gCurrent_arg = NULL;

// GLOBAL: C1 0x0045b56c
ISourceBrowser *gCurrent_source_browser;

// GLOBAL: C1 0x00454d50
const tArgument_char_spec gDebug_info_arg_specs[11] = {
    { 'a', 0x5, { &gOption_Ze, }, },
    { 'e', 0x1, { &gOption_Ze, }, },
    { 'E', 0x1, { &gOption_ZE, }, },
    { 'i', 0x1, { &gOption_Zi, }, },
    { '7', 0x1, { &gOption_Z7, }, },
    { 'n', 0x1, { &gOption_Zn, }, },
    { 'f', 0x1, { &gOption_Zf, }, },
    { 'g', 0x1, { &gOption_Zg, }, },
    { 'p', 0x1, { &gOption_Zp, }, },
    { 'I', 0x1, { &gOption_ZI, }, },
    { 0 },
};

// GLOBAL: C1 0x00454dd8
tArgument_spec gArgument_specs[89] = {
    { "@$", { &gOption_rsp_path }, true, 0x22, },
    { "-nologo", { &gOption_nologo }, true, 0x01, },
    { "-FAT", { &gOption_FAT }, true, 0x01, },
    { "-pc#", { &gOption_pc_map }, true, 0x22, },
    { "-pf", { &gOption_pf }, true, 0x01, },
    { "-C", { &gOption_C }, true, 0x01, },
    { "-D#", { &gArgument_macros }, true, 0x26, },
    { "-E", { &gOption_E }, true, 0x01, },
    { "-I#", { &gArgument_includes }, true, 0x26, },
    { "-FI#", { &gArgument_force_includes }, true, 0x26, },
    { "-EP", { &gOption_EP }, true, 0x01, },
    { "-Fi#", { &gOption_Fi_path }, true, 0x22, },
    { "-f", { &gInput_filepath }, true, 0x22, },
    { "-J", { &gOption_J }, true, 0x01, },
    { "-Jd", { &gOption_Jd }, true, 0x01, },
    { "-Bd%", { &gOption_Bd }, true, 0x01, },
    { "-Bu#", { &gOption_Bu }, true, 0x24, },
    { "-Bm#", { &gOption_Bm }, true, 0x24, },
    { "-Bvb#", { &gOption_memory }, true, 0x24, },
    { "-Bvm#", { &gOption_memory }, true, 0x24, },
    { "-Zm#", { &gOption_memory }, true, 0x24, },
    { "-Brepro", { &gOption_Brepro }, true, 0x01, },
    { "-MT", { &gOption_MT }, true, 0x01, },
    { "-MD", { &gOption_MD }, true, 0x01, },
    { "-WX", { &gOption_WX }, true, 0x01, },
    { "-W#", { &gOption_W }, true, 0x24, },
    { "-Zp", { &gOption_Zp }, true, 0x01, },
    { "-Zp#", { &gOption_Zp }, true, 0x24, },
    { "-ZBe", { &gOption_ZBe }, true, 0x01, },
    { "-ZB", { &gOption_ZB }, true, 0x01, },
    { "-ZB*", { &gOption_ZB }, true, 0x24, },
    { "-Z*", { &gDebug_info_arg_specs }, true, 0x23, },
    { "-ef#", { &gError_message_path }, true, 0x22, },
    { "-il$", { &gOption_il }, true, 0x22, },
    { "-xc", { &gOption_xc }, true, 0x01, },
    { "-V#", { &gOption_V_path }, true, 0x22, },
    { "-Gs", { &gOption_Gs }, true, 0x05, },
    { "-Gc", { &gOption_Gc }, true, 0x01, },
    { "-Gr", { &gOption_Gr }, true, 0x01, },
    { "-Gd", { &gOption_Gd }, true, 0x01, },
    { "-Gz", { &gOption_Gz }, true, 0x01, },
    { "-Gi", { &gOption_Gi }, true, 0x01, },
    { "-GI", { &gOption_GI }, true, 0x01, },
    { "-GFR", { &gOption_GFR }, true, 0x01, },
    { "-GFR-", { &gOption_GFR }, true, 0x05, },
    { "-NV#", { &gOption_NV_path }, true, 0x22, },
    { "-Fr#", { &gOption_Fr_path }, true, 0x22, },
    { "-FR#", { &gOption_FR_path }, true, 0x22, },
    { "-Fj", { &gOption_Fj }, true, 0x01, },
    { "-Fd#", { &gPDB_arg_path }, true, 0x22, },
    { "-Fo*", { &gObject_output_arg_path }, true, 0x22, },
    { "-Gf", { &gOption_Gf }, true, 0x01, },
    { "-GF", { &gOption_GF }, true, 0x01, },
    { "-cbstring", { &gOption_cbstring }, true, 0x01, },
    { "-Oa", { &gOption_Oa }, true, 0x01, },
    { "-Ob#", { &gOption_Ob }, true, 0x24, },
    { "-Oi", { &gOption_Oi }, true, 0x01, },
    { "-Og", { &gOption_Og }, true, 0x01, },
    { "-Op", { &gOption_Op }, true, 0x01, },
    { "-Os", { &gOption_Ot }, true, 0x05, },
    { "-Ot", { &gOption_Ot }, true, 0x01, },
    { "-Ow", { &gOption_Ow }, true, 0x01, },
    { "-Oq", { &gOption_Oq }, true, 0x01, },
    { "-Ov", { &gOption_Ov }, true, 0x01, },
    { "-Oy", { &gOption_Oy }, true, 0x01, },
    { "-C8MODE", { &gOption_C8MODE }, true, 0x01, },
    { "-debugBreak%", { &gOption_debugBreak }, true, 0x01, },
    { "-Times%", { &gPrint_timings }, true, 0x01, },
    { "-Yu*", { &gOption_Yu_path }, true, 0x22, },
    { "-Yu", { &gOption_Yu }, true, 0x01, },
    { "-Yc*", { &gPCH_arg_path }, true, 0x22, },
    { "-Yc", { &gOption_Yc }, true, 0x01, },
    { "-Yd", { &gOption_Yd }, true, 0x01, },
    { "-Fp#", { &gFp_arg_path }, true, 0x22, },
    { "-YX*", { &gYX_arg_path }, true, 0x22, },
    { "-YX", { &gOption_YX }, true, 0x01, },
    { "-Yl*", { &gYl_arg_path }, true, 0x22, },
    { "-BNOPPCH", { &gOption_BPCH }, true, 0x05, },
    { "-noexpinl", { &gOption_noexpinl }, true, 0x01, },
    { "-GM", { &gOption_GM }, true, 0x01, },
    { "-G#", { &gOption_G }, true, 0x24, },
    { "-BMOVE", { &gOption_BMOVE }, true, 0x01, },
    { "-C9IL", { &gOption_C9IL }, true, 0x01, },
    { "-SplitPdbs", { &gOption_SplitPdbs }, true, 0x01, },
    { "-SplitPdbs-", { &gOption_SplitPdbs }, true, 0x05, },
    { "-NoEHForNew", { &gOption_NoEHForNew }, true, 0x01, },
    { "-Bshow_incl", { &gOption_BShowIncl }, true, 0x01, },
    { "*", { &gUnknown_argument }, false, 0x22, },
    { 0 },
};

// FUNCTION: C1 0x0045c17c
char gPDB_path[256];

// GLOBAL: C1 0x0045c178
BOOL gOption_Zi_and_not_Z7 = TRUE;

// GLOBAL: C1 0x0045b5b8
tPragma_stack *gPragma_stack = NULL;

// GLBOAL: C1 0x0045c27c
char gYl_path[256];

// GLOBAL: C1 0x0046644c
FILE *gError_message_file = NULL;

// GLOBAL: C1 0x00469208
char gError_message_buffer[256];

// GLOBAL: C1 0x00469168
tDiagnostic_file_offset gCached_diagnostic_file_offsets[20];

// GLOBAL: C1 0x0045c7b0
int gError_message_file_pos = 0;

// GLOBAL: C1 0x0045c7b4
BOOL gDiagnostic_help_strings_initialized = FALSE;

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
tCurrent_file_thing_0045e450 gCurrent_file_input_stream;

// GLOBAL: C1 0x00460a50
FILE *gFile_er = NULL;

// GLOBAL: C1 0x004662c0
FILE *gFile_lp = NULL;

// GLOBAL: C1 0x004663a8
IStruct_Incremental1 *gIncremental_interface1;

// GLOBAL: C1 0x0046a310
IStruct_Incremental2 *gIncremental_interface2;

// FUNCTION: C1 0x0045c15c
BOOL gBOOL_0045c15c = TRUE;

// FUNCTION: C1 0x0045c12c
BOOL gBOOL_0045c12c = FALSE;

// FUNCTION: C1 0x0045c134
BOOL gBOOL_0045c134 = FALSE;

// FUNCTION: C1 0x0045c484
BOOL gBOOL_0045c484 = FALSE;

// GLOBAL: C1 0x00466488
uint32_t gOption_G_flags = 0;

// GLOBAL: C1 0x0045c148
BOOL gBOOL_0045c148 = FALSE;

// GLOBAL: C1 0x0045c14c
BOOL gBOOL_0045c14c = FALSE;

// GLOBAL: C1 0x004662cc
const char *gSource_browser_file_path = NULL;

// GLOBAL: C1 0x004663b0
BOOL gBOOL_004663b0;

// GLOBAL: C1 0x004663bc
const char *gOriginal_option_Yu_path;

// GLOBAL: C1 0x0045f994
BOOL gReading_PCH;

// GLOBAL: C1 0x0046630c
BOOL gWriting_PCH;

// GLOBAL: C1 0x0045c4e0
BOOL gBOOL_0045c4e0;

// GLOBAL: C1 0x0045c4ec
BOOL gBOOL_0045c4ec;

// GLOBAL: C1 0x00466120
tFILESTREAM gFile_struct_sy;

// GLOBAL: C1 0x004609e0
tFILESTREAM gFile_struct_gl;

// GLOBAL: C1 0x004662e0
tFILESTREAM gFile_struct_in;

// GLOBAL: C1 0x00460a58
tFILESTREAM gFile_struct_db;

// GLOBAL: C1 0x00466010
tFILESTREAM gFile_struct_ex;

// GLOBAL: C1 0x004609b0
tFILESTREAM gFILESTREAM_004609b0;

// GLOBAL: C1 0x00465fb0
tFILESTREAM gFILESTREAM_00465fb0;

// GLOBAL: C1 0x00466454
FILE *gFi_file;

// GLOBAL: C1 0x00466294
FILE *gFile_stdout;

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
tPCH_allocated_chunk g_PCH_allocated_chunk_004664a0;

// GLOBAL: C1 0x0045b690
tStruct_0045b690 *gStruct_0045b690;

// GLOBAL: C1 0x0045b684
undefined4 gUNK_0045b684;

// GLOBAL: C1 0x0045b688
tStruct_00401000 *gUNK_0045b688;

// GLOBAL: C1 0x0045e478
tStruct_0045e478 *gPTR_0045e478;

// GLOBAL: 0x00469308
uint32_t gOptimazion_flags;


extern void __fastcall FatalErrorWithStrerror(int code, int category, const char *text);

extern const char *__fastcall GetDiagnosticHelpString(int code);

extern const char *__stdcall GetDiagnosticString(int code, BOOL arg2);

extern char *__fastcall DuplicateTextInPool(const char *text, int pool_id);

// FUNCTION: C1 0x004253ce
void __fastcall WriteStdErr(const char *text)
{
#if 0
    fwrite(text, strlen(text), 1, __p__iob() + STDERR_FILENO);
#endif
    fwrite(text, strlen(text), 1, stderr);
}

// FUNCTION: C1 0x00445a14
void ReleaseEverythingUponError()
{
    NOT_IMPLEMENTED();
}

// FUCNTION: C1 0x0041f0ca
void FUN_0041f0ca(void)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0044821d
void __fastcall FatalCompilerStackOverflowError(BOOL show_message)
{
    if (show_message) {
        strcpy(gError_message_buffer, "fatal error C1063:\r\n");
        _write(STDOUT_FILENO, gError_message_buffer, strlen(gError_message_buffer));
    }
    FUN_0041f0ca();
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
    gMain_stage = stage;
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

    for (i = 0; i < arraysize(gCached_diagnostic_file_offsets); i++) {
        tDiagnostic_file_offset *file_offset = &gCached_diagnostic_file_offsets[i];
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
                offset = (int32_t)ftell(gError_message_file);
            }
            if (fgets(buffer, bufferSize, gError_message_file) == NULL) {
                if (!arg4) {
                    FatalErrorWithStrerror(83, 314, gError_message_path);
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
            fseek(gError_message_file, 0, SEEK_SET);
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

// GLOBAL: C1 0x00423937
const char *__fastcall GetDiagnosticHelpString(int code)
{
    if (!gDiagnostic_help_strings_initialized) {
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
                if (gError_message_file != (FILE*)(uintptr_t)-1) {
                    fseek(gError_message_file, 0, SEEK_SET);
                }
            } else {
                diagnostic_code_text->text = DuplicateTextInPool(text, 1);
            }
        }
        if (gError_message_file != (FILE*)(uintptr_t)-1) {
            gError_message_file_pos = ftell(gError_message_file);
        }
        gDiagnostic_help_strings_initialized = TRUE;
    }
    return LookupDiagnosticHelpString(code);
}

// FUNCTION: C1 0x00448070
int GetBestErrorFileMessageOffset(int code)
{
    int best_index = -1;
    int best_diff = SHRT_MAX;
    int i;

    for (i = 0; i < arraysize(gCached_diagnostic_file_offsets); i++) {
        int current_code = gCached_diagnostic_file_offsets[i].code;
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
    return gCached_diagnostic_file_offsets[best_index].offset;
}

// FUNCTION: C1 0x004238b7
const char *__stdcall GetDiagnosticString(int code, BOOL arg2)
{
    if (gError_message_file == NULL) {
        if (gDiagnostic_help_strings_initialized  || arg2) {
            if (gError_message_path == NULL) {
                gError_message_file = (FILE *)(uintptr_t)-1;
                return "";
            }
            FILE * f = fopen(gError_message_path, "r");
            if (f == NULL) {
                gError_message_file = (FILE *)(uintptr_t)-1;
                return "";
            }
        }
        GetDiagnosticHelpString(303);
    }
    if (gError_message_file == (FILE *)(uintptr_t)-1) {
        return "";
    }
    if (!arg2) {
        fseek(gError_message_file, GetBestErrorFileMessageOffset(code), SEEK_SET);
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
    NOT_IMPLEMENTED();
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
int DiagnosticSprintf(char *buffer, const char *format, size_t buffer_size, ...)
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
    if (gCurrent_file_input_stream.line > 0 && gCurrent_file_input_stream.stream != NULL) {
        DiagnosticSprintf(buffer, "%Fs(%ld) : ", sizeof(buffer), GetCurrentSourceFilename(&gCurrent_file_input_stream), gCurrent_file_input_stream.line);
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
        ptr_message += DiagnosticSprintf(ptr_message, "%s %c%d: ", buffer + sizeof(buffer) - ptr_message, 'C', category + code);
    }
    DiagnosticVSprintf(ptr_message, format, buffer + sizeof(buffer) - ptr_message, ap);
    fwrite(buffer, strlen(buffer), 1, stderr);
    fwrite("\n", 1, 1, stderr);
    if (gBOOL_00466500 != 0 && gFile_er != NULL) {
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
    gError_count += 1;
    exit(gError_count);
}

// FUNCTION: C1 0x00448160
void __fastcall FatalErrorWithStrerror(int code, int category, const char *text)
{
    if (gMain_stage == 7 || gMain_stage == 6) {
        return;
    }
    if (text == NULL) {
        text = "";
    }
    FatalErrorF(code, category, text, _strerror(NULL));
}

// FUNCTION: C1 0x0043f49e
void __fastcall FatalError(int code)
{
    FatalErrorF(code);
}

// FUNCTION: C1 0x0041a6eb
uintptr_t __fastcall PreAllocateMemory(size_t reserveSize, size_t commitSize)
{
    LPVOID reserveAddr = VirtualAlloc(NULL, reserveSize, MEM_RESERVE, PAGE_READWRITE);
    if (reserveAddr == NULL) {
        FatalError(60);
    }
    LPVOID commitAddr = VirtualAlloc(reserveAddr, commitSize, MEM_COMMIT, PAGE_READWRITE);
    if (commitAddr == NULL) {
        FatalError(60);
    }
    return (uintptr_t) commitAddr;
}

// FUNCTION: C1 0x0041bab0
void ReserveMemory()
{
    gReserved_mem1_start = PreAllocateMemory(5 * 1024 * 1024, 1024);
    gReserved_mem1_end = gReserved_mem1_start + 4096 - 5;
    gReserved_mem2_start = PreAllocateMemory(5 * 1024 * 1024, 1024);
    gReserved_mem2_end = gReserved_mem2_start + 4096 - 5;
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

// FUNCTION: C1 0x0041136e
void * __fastcall StdLibSafeAlloc(size_t s)
{
    void *res = malloc(s);
    if (res == NULL) {
        FatalError(60);
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
    gTerminalSignalReceived = TRUE;
    if (gMain_stage != 8) {
        if (WaitForSingleObject(gTerminalSignalSemaphore, 4000) == WAIT_TIMEOUT) {
            int i = 0;

            WriteStdErr("Compiler terminating.  Please wait.");
            for (i = 0; i < 30; i++) {
                if (gMain_stage == 8) {
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
int __fastcall ParseEarlyArgument(const char *arg, int state)
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
void __fastcall ParseEarlyArguments(char **argv)
{
    int state = 0;
    char **arg = argv + 1;

    while (arg != NULL) {
        state = ParseEarlyArgument(*arg, state);
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
            state = ParseEarlyArgument(buffer, state);
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
char *__fastcall DuplicateTextInPool(const char *text, int pool_id)
{
    char *copy = (char *)gPCH_chunks[pool_id].Allocate(strlen(text) + 1);
    strcpy(copy, text);
    return copy;
}

// FUNCTION: C1 0x0041a2b7
tPCH_allocated_chunk::tPCH_allocated_chunk(uint32_t minSize)
{
    m_ptr_free = NULL;
    m_mem_left = 0;
    m_min_size = minSize;
    m_chunk = NULL;
}

// FUNCTION: C1 0x0041a29e
void tPCH_allocated_chunk::SelectChunk(int chunk_id)
{
    m_chunk = &gPCH_chunks[chunk_id];
    IncreaseHeapByAtLeast(1);
}

// FUNCTION: C1 0x0040c390
void tPCH_allocated_chunk::IncreaseHeapByAtLeast(size_t size)
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
        IncreaseCommitedMemoryBlock();
    }
    return (void *) result;
}

// FUNCTION: C1 0x0040c1cf
void tPCH_chunk::IncreaseCommitedMemoryBlock()
{
    if (m_mem_commited_next_free - m_address > m_maxSize) {
        FatalError(76);
    }
    size_t size = MakeMultipleOf(m_mem_commited_next_free - m_mem_commited_end, m_chunk_info->itemSize);
    if (VirtualAlloc((void *)m_mem_commited_end, size, MEM_COMMIT, PAGE_READWRITE) == NULL) {
        FatalError(60);
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

// FUNCTION: C1 0x0041a3b4
void FUN_0041a3b4()
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
                FatalError(60);
            }
        }
    }
}

// FUNCTION: C1 0x00419264
void InitPCHMemory()
{
    int i;

    FUN_004192ab();
    for (i = 0; i < arraysize(gPCH_chunks); i++) {
        if (!(gPCH_chunk_infos[i].flags & 0x1)) {
            if (!gPCH_chunks[i].Initialize(&gPCH_chunk_infos[i], NULL)) {
                FatalError(60);
            }
        }
    }
    FUN_0041a3b4();
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
void InitCVHasher()
{
    int i;

    for (i = 0; i < 256; i++) {
        int j;

        gCVHash_msb_lut[i] = 0;
        gCVHash_lsb_lut[i] = 0;
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
            gCVHash_lsb_lut[i] |= (lsb_bit & 0x1) << j;
            gCVHash_msb_lut[i] |= (msb_bit & 0x1) << j;
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
            gCharacter_classes_1[i] = 0x23;
            gCharacter_classes_3[i] |= 0x10;
        }
    }
}

// FUNCTION: C1 0x0043ee2c
void FUN_0043ee2c()
{
    int i;

    for (i = 0; i < 256; i++) {
        if (gCharacter_classes_1[i] == 0x23) {
            gCharacter_classes_1[i] = 0x21;
            gCharacter_classes_3[i] &= ~0x10;
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

    if (gAllocated_argv != NULL) {
        argv = gArgv;
        while (*argv != NULL) {
            argv++;
        }
        return argv;
    }
    char **original_argv = gArgv;
    gAllocated_argv = (char **)StdLibSafeAlloc(MAX_ARG_COUNT * sizeof(char *));
    argv = gAllocated_argv;
    for (;;) {
        *argv = *original_argv;
        if (*original_argv == NULL) {
            break;
        }
        original_argv++;
        argv++;
        if (argv - gAllocated_argv >= MAX_ARG_COUNT) {
            FatalErrorF(77, MAX_ARG_COUNT);
        }
        *argv = *original_argv;
    }
    gArgv = gAllocated_argv;
    return argv;
}

// FUNCTION: C1 0x0041adce
void __fastcall SplitAndStoreArgString(char *arg_string)
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
        if (argv_ptr - gAllocated_argv >= MAX_ARG_COUNT) {
            FatalErrorF(77, MAX_ARG_COUNT);
        }
        gArgc += 1;
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
char *GetNextArgument()
{
    gArgc -= 1;
    if (gArgc <= 0) {
        return NULL;
    }
    gArgv++;
    return *gArgv;
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
void __fastcall RunArgumentSpec(const tArgument_spec *arg_spec, const char *value, int state)
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
                    FatalErrorF(48, *value, gCurrent_arg);
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
BOOL __fastcall IdenticalEnding(const char *format, const char *arg)
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
int __fastcall ParseArgument(const tArgument_spec *arg_specs, const char *arg, char *(get_next_arg)(), int state) {
    bool checksum_arg = true;
    int i;
    const char *arg_value = NULL;

    if (arg == NULL) {
        return 0;
    }
    gCurrent_arg = arg;
    for (i = 0;; i++) {
        const tArgument_spec *spec = &arg_specs[i];
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
                RunArgumentSpec(spec, arg_value, state);
                match = true;
                break;
            } else if (*ptr_format == '#' || *ptr_format == '$') {
                if (*ptr_format == '$') {
                    checksum_arg = false;
                }
                if (*ptr_arg != '\0') {
                    RunArgumentSpec(spec, ptr_arg, state);
                } else {
                    arg_value = get_next_arg();
                    RunArgumentSpec(spec, arg_value, state);
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
                if (*ptr_arg != '\0' && IdenticalEnding(ptr_format, ptr_arg)) {
                    RunArgumentSpec(spec, ptr_arg, state);
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
        gSigPbCb.Update(arg_value, strlen(arg_value));
    }
    if (checksum_arg) {
        gSigPbCb.Update(arg, strlen(arg));
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
char *__fastcall MakeAbsolutePath(char *dest, const char *path, size_t destSize)
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
bool __fastcall PathsAreEqual(const char *p1, const char *p2)
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
void __fastcall ParseArguments(int argc, char **argv)
{
    char buffer[2048];
    int i;

    if (gPTR_0045b5bc == NULL) {
        FUN_0041c211();
    }
    InitCVHasher();
    setlocale(LC_CTYPE, "");
    InitCharacterClassesForLocale();
    InitToLowerLUT();
    if (argc > 1) {
        if (argv[1][0] == '@') {
            FILE *f = fopen(&argv[1][1], "rt");
            if (f == NULL) {
                FatalErrorWithStrerror(84, 337, &argv[1][1]);
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
                    SplitAndStoreArgString(DuplicateTextInPool(arg_start, 1));
                }
            }
            fclose(f);
        }
    }
    SplitAndStoreArgString(getenv("MSC_CMD_FLAGS"));
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
    gArgument_macros = CreateStringVector(40, 1);
    gArgument_includes = CreateStringVector(40, 1);
    gArgument_force_includes = CreateStringVector(40, 1);
    if (!gOption_C9IL) {
        gSigPbCb.Update("C", 1);
    }
    for (;;) {
        int state = 0;
        state = ParseArgument(gArgument_specs, GetNextArgument(), GetNextArgument, state);
        if (!state) {
            break;
        }
    }
    if (MakeAbsolutePath(buffer, gPDB_arg_path, sizeof(buffer)) == NULL) {
        FatalErrorF(83, 354, gPDB_arg_path, GetDiagnosticHelpString(355));
    }
    if (strlen(buffer) >= sizeof(gPDB_path)) {
        FatalError(5);
    }
    strcpy(gPDB_path, buffer);
    if (gOption_Z7) {
        gOption_Zi = TRUE;
        gOption_Zi_and_not_Z7 = FALSE;
    }
    gOption_C9IL |= !gOption_Gi;
    gOption_GFR &= gOption_Gi;
    if (gOption_SplitPdbs) {
        gPTR_00466458 = &gStruct_004664b0;
    } else {
        gPTR_00466458 = &gStruct_004662a8;
    }
    gOption_Zi_and_not_Z7 &= gOption_Zi;
    if (gOption_Jd) {
        FUN_0043ee2c();
    }
    if (gPragma_stack == NULL) {
        CreatePragmaStack();
    }
    if (gYl_arg_path != NULL) {
        if (strlen(gYl_arg_path) >= sizeof(gYl_path)) {
            FatalError(5);
        }
        strcpy(gYl_path, gYl_arg_path);
    }
    if (gUnknown_argument != NULL) {
        FatalErrorF(7, gUnknown_argument, "c1");
    }
    if (gInput_filepath == NULL) {
        FatalError(8);
    }

    if (gPCH_arg_path != NULL) {
        gOption_Yc = TRUE;
        if (gOption_Yu_path != NULL) {
            if (PathsAreEqual(gPCH_arg_path, gOption_Yu_path)) {
                gOption_Yu = FALSE;
                gOption_Yu_path = NULL;
            }
        }
    }
    if (!gOption_Yc) {
        gOption_BPCH = FALSE;
    }
    if (gOption_Yu_path != NULL) {
        gOption_Yu = TRUE;
    }
    if (gOption_YX) {
        gOption_YX = TRUE;
    }
    gOption_Yd |= gOption_YX;
    if (gOption_E || gOption_Zg) {
        gOption_YX = FALSE;
        gOption_YX = FALSE;
        gOption_Yc = FALSE;
        gPCH_arg_path = NULL;
        gOption_Yu = FALSE;
        gOption_Yu_path = NULL;
        gOption_Yd = FALSE;
        gOption_BPCH = FALSE;
    }
    if (gAllocated_argv != NULL) {
        StdFree(gAllocated_argv);
        gAllocated_argv = NULL;
    }
}

// FUNCTION: C1 0x0041ba35
void FUN_0041ba35()
{
    gOption_G_flags = 1 << gOption_G;
    if (gOption_GM) {
        gOption_G_flags |= 0x40;
    }
}

// FUNCTION: C1 0x0041b776
void FUN_0041b776()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00419771
void CreateKeywordHashmap()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041bb78
void RegisterReservedKeywords()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00448450
FILE *__fastcall OpenFileInDirectory(const char *directory, const char *filename, const char *mode)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x004193d4
void FUN_004193d4()
{
    // empty
}

// FUNCTION: C1 0x0041a66d
void FUN_0041a66d()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00401000
tStruct_00401000 *__fastcall FUN_00401000(tStruct_00401000 *arg)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041a934
void FUN_0041a934()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00419350
void FUN_00419350()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041c756
undefined4 FUN_0041c756 (undefined4 arg1, tStruct_00401000 *arg2)
{
    NOT_IMPLEMENTED();
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
void FUN_004199cc()
{
    NOT_IMPLEMENTED();
}


// FUNCTION: C1 0x00419c44
void FUN_00419c44()
{
    char buffer[20];

    if (!CreateIncrementalInterfaces(gOption_Gi && !gOption_E && !gOption_Zg, &gIncremental_interface1, &gIncremental_interface2)) {
        FatalErrorF(73, "main.c", 151);
    }
    SetHandleCount(30);
    gOption_EP = gOption_EP || !gOption_E;
    if (gOption_Zp != -1) {
        gPragma_stack->items->value = gOption_Zp;
    } else {
        gPragma_stack->items->value = 8;
    }
    gBOOL_0045c15c = gOption_Gs;
    gBOOL_0045c12c = gOption_Gf;
    gBOOL_0045c134 = gOption_GF;
    gBOOL_0045c484 = gOption_Oq;
    if (gOption_G > 4) {
        DiagnosticSprintf(buffer, "-G%d", sizeof(buffer), gOption_G);
        FatalErrorF(7, buffer, "c1");
    }
    FUN_0041ba35();
    if (gOption_E || gOption_Zg) {
        gOption_Fr_path = NULL;
        gOption_FR_path = NULL;
        gBOOL_0045c14c = FALSE;
        gBOOL_0045c148 = FALSE;
    } else {
        if (gOption_FR_path != NULL) {
            gBOOL_0045c14c = TRUE;
            gOption_Fr_path = gOption_FR_path;
        }
        gBOOL_0045c148 = gOption_Fr_path != NULL;
        gSource_browser_file_path = gOption_Fr_path;
    }
    InitializeSourceBrowser(gOption_Fr_path);
    gCurrent_source_browser = GetDummySourceBrowser();
    if (gOption_BPCH) {
        if (gPCH_arg_path == NULL && (gFp_arg_path == NULL || gOption_Yu)) {
            gOption_BPCH = FALSE;
        } else {
            if (OpenPrecompiledHeader(gPCH_arg_path)) {
                gBOOL_004663b0 = gOption_Yu;
                gOriginal_option_Yu_path = gOption_Yu_path;
                gReading_PCH = TRUE;
                if (gOption_Yu) {
                    gFp_arg_path = NULL;
                }
                gOption_Yu = TRUE;
                gOption_Yu_path = gPCH_arg_path;
                gOption_Yc = FALSE;
                gPCH_arg_path = NULL;
            } else {
                gWriting_PCH = TRUE;
                WriteMacrosAndIncludesToPCH();
            }
        }
    }
    gBOOL_0045c4e0 = gOption_Yc;
    gBOOL_0045c4ec = gOption_Zi && !gOption_Yd && gOption_Yc;
    FUN_0041b776();
    CreateKeywordHashmap();
    RegisterReservedKeywords();
    FUN_004193d4();
    if (gBOOL_00466500 && !gOption_Zg) {
        gFile_er = OpenFileInDirectory(gOption_il, "er", "w");
        gFile_lp = OpenFileInDirectory(gOption_il, "lp", "w");
    }
    if (!gOption_E && !gOption_Zg) {
        if (gOption_C9IL) {
            FUN_0041c815();
            gFile_struct_sy.Open(gOption_il, "sy", "w+");
            gFile_struct_gl.Open(gOption_il, "gl", "w+");
            gFile_struct_in.Open(gOption_il, "in", "w+");
            if (gOption_Zi != 0) {
                gFile_struct_db.Open(gOption_il, "db", "w+");
            }
        } else {
            gFile_struct_sy.set_field_0x24(1);
            gFile_struct_in.set_field_0x24(4);
            gFile_struct_ex.set_field_0x24(2);
            gFILESTREAM_004609b0.set_field_0x24(5);
            gFile_struct_gl.set_field_0x24(1);
            gFILESTREAM_00465fb0.set_field_0x24(1);
        }
    }
    if (gOption_Fi_path != NULL) {
        if (_dup(STDOUT_FILENO) == -1) {
            FatalErrorWithStrerror(83, 340, gOption_Fi_path);
        } else {
            gFi_file = freopen(gOption_Fi_path, "wt+", stdout);
            if (gFi_file == NULL) {
                FatalErrorWithStrerror(83, 340, gOption_Fi_path);
            }
        }
    }
    gFile_stdout = stdout;
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
    if (!gOption_E) {
        gUNK_0045b684 = FUN_0041c756(0, gPTR_0045b630);
        gUNK_0045b688 = FUN_0041c558(0x80);
        if (gOption_Zg == 0) {
            FUN_0041c258();
        }
        FUN_0041c5d3();
    }
    FUN_0041a4a6(gArgument_macros);
    tStruct_00456d30 *unk_stream = new tStruct_00456d30;
    gCurrent_file_input_stream.FUN_0040267e(unk_stream, 0, 0, &gCurrent_file_input_stream);
    if (gPTR_0045e478 == NULL) {
        gPTR_0045e478 = new tStruct_0045e478;
    }
    if (!gOption_Yu) {
        FUN_004199cc();
    }
}

// FUNCTION: C1 0x004082bf
uint32_t GetOptimizationArgFlags()
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x004193d6
void DoActions()
{
    FUN_00419c44();
    gOptimazion_flags = GetOptimizationArgFlags();

    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x004197a4
int main(int argc, char *argv[])
{
    gMain_stage = 1;
    ReserveMemory();
    InitTiming();
    atexit(FUN_0041f0b2);
    signal(SIGINT, OnTerminalSignal);
    signal(SIGTERM, OnTerminalSignal);
    signal(SIGBREAK, OnTerminalSignal);
    gArgc = argc;
    gArgv = argv;
    ParseEarlyArguments(argv);
    FUN_0041934f();
    GetSystemInfo(&gSystem_info);
    InitPCHMemory();
    ParseArguments(argc, argv);
    AddTiming("init1");
    if (gOption_C9IL) {
        gUINT_0045bf98 |= 0x2000;
    } else {
        gUINT_0045bf98 &= ~0x2000;
    }
    if (gOption_Bd) {
        DoActions();
    } else {
        DoActions();
    }
}

// FUNCTION: C1 0x00419195
void tFILESTREAM::Open(const char *dirpath, const char *filename, const char *mode)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041b801
tStruct_0045b690::tStruct_0045b690()
{
    NOT_IMPLEMENTED();
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
