#ifndef P0ID_H
#define P0ID_H

#include "decomp.h"

struct idAttr_t {
    unsigned int hashval: 16;
    bool32 isKeyword: 1;
    // bool32 isType: 1;
    // bool32 isMember: 1;
    // bool32 isMacroDefn: 1;
    // bool32 isVirtualMF: 1;
    // bool32 isBrowserRefDisabled: 1;
    // bool32 isUnnamed: 1;
    // bool32 isDeclSpecKey: 1;
    // bool32 _padding_: 3;
};

// SIZE: C1 0x14
struct Id_t {
    Id_t *pNext;
    char *ident;
    idAttr_t attr;
    undefined4 field_0xc;
    int token;
};

extern Id_t *pCurId;

// ?InitIdTable@@YAXXZ
extern void InitIdTable();

// ?GetId@@YAHE@Z
// int __cdecl GetId(unsigned char)

// ?GetIdRare@@YAHPADIE@Z
// int __cdecl GetIdRare(char *, unsigned int, unsigned char)

// ?GetIdForHashedString@@YAPAUId_t@@PBDIIAAH@Z
// struct Id_t * __cdecl GetIdForHashedString(char const *, unsigned int, unsigned int, int &)

// ?GetIdForString@@YAPAUId_t@@PBD@Z
// struct Id_t * __cdecl GetIdForString(char const *)

// ?GetIdForKeyword@@YAXPAD@Z
extern void GetIdForKeyword(const char *keyword);

// ?GetTempIdForString@@YAPAUId_t@@PAU1@PAD@Z
// struct Id_t * __cdecl GetTempIdForString(struct Id_t *, char *)

// ?IdHash@@YAIPAX@Z
// unsigned int __cdecl IdHash(void *)

#endif /* P0ID_H */
