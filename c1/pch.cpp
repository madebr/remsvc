#include "pch.h"

#include "classes.h"
#include "decomp.h"

extern BOOL gOption_Yc;
extern BOOL gOption_E;
extern BOOL gOption_Yu;
extern BOOL gOption_WX;
extern const char *gPCH_arg_path;
extern const char *gFp_arg_path;
extern const char *gOption_il_path;
extern tFILESTREAM gFile_struct_ex;
extern int gILSINK_ErrorCode;

extern tStruct_0040925a * __fastcall FUN_0040929e(int arg1);
extern void __fastcall FUN_0041402e(undefined4 arg1, tStruct_0040925a *arg2);

// GLOBAL: C1 0x0045c4e4
BOOL gBOOL_0045c4e4;

// FUNCTION: C1 0x004236b2
void __fastcall FUN_004236b2(const char *path)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x0041c815
void FUN_0041c815()
{
    if (gOption_Yc && (gPCH_arg_path != NULL || gFp_arg_path != NULL) && !gOption_Yu) {
        FUN_004236b2(gPCH_arg_path);
        gFile_struct_ex.Open(gFp_arg_path, "", "w");
        gBOOL_0045c4e4 = TRUE;
    } else {
        gFile_struct_ex.Open(gOption_il_path, "ex", "w+");
    }
    if (!gOption_Yu) {
        FUN_0041402e(91, FUN_0040929e(1136));
        gFile_struct_ex.FlushWrite();
        gFile_struct_ex.Flush();
        gILSINK_ErrorCode = gFile_struct_ex.Seek(1135);
        if (gILSINK_ErrorCode != 0) {
            FUN_0044810e(86, 339, NULL, "pch.c", 1818);
        }
        gFile_struct_ex.Write("\0", 1);

        gFile_struct_ex.FlushWrite();
    }
}

// FUNCTION: C1 0x00426f37
BOOL __fastcall OpenPrecompiledHeader(const char *path)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00426e1b
void WriteMacrosAndIncludesToPCH()
{
    NOT_IMPLEMENTED();
}
