#include "../pch.h"

#include "classes.h"
#include "decomp.h"

extern BOOL PchCFlag;
extern BOOL Prep;
extern BOOL PchUFlag;
extern BOOL WarnIsError;
extern const char *PchCFile;
extern const char *PchPFile;
extern const char *Basename;
extern tFILESTREAM ilsExp;
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
    if (PchCFlag && (PchCFile != NULL || PchPFile != NULL) && !PchUFlag) {
        FUN_004236b2(PchCFile);
        ilsExp.Open(PchPFile, "", "w");
        gBOOL_0045c4e4 = TRUE;
    } else {
        ilsExp.Open(Basename, "ex", "w+");
    }
    if (!PchUFlag) {
        FUN_0041402e(91, FUN_0040929e(1136));
        ilsExp.FlushWrite();
        ilsExp.Flush();
        gILSINK_ErrorCode = ilsExp.Seek(1135);
        if (gILSINK_ErrorCode != 0) {
            FUN_0044810e(86, 339, NULL, "pch.c", 1818);
        }
        ilsExp.Write("\0", 1);

        ilsExp.FlushWrite();
    }
}

// FUNCTION: C1 0x00426f37
BOOL __fastcall ValidatePersistentPch(const char *path)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: C1 0x00426e1b
void WriteMacrosAndIncludesToPCH()
{
    NOT_IMPLEMENTED();
}
