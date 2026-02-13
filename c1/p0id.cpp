#include "p0id.h"

#include "decomp.h"
#include "globals.h"
#include "nheapall.h"

// GLOBAL: C1 0x0045b5c8
Id_t *pCurId = NULL;;

// FUNCTION: MSVC5_C1 0x000041d0
// ?InitIdTable@@YAXXZ
// FUNCTION: C1 0x00419771
void InitIdTable()
{
    if (PchS.rs.p_IdTable == NULL) {
        PchS.rs.p_IdTable = static_cast<Id_t **>(HeapManager::Allocate(2048 * sizeof(Id_t *), M_LIFETIME0));
    }
}

// FUNCTION: MSVC5_C1 0x00004210
// ?GetId@@YAHE@Z
// int __cdecl GetId(unsigned char)

// FUNCTION: MSVC5_C1 0x000043f0
// ?GetIdRare@@YAHPADIE@Z
// int __cdecl GetIdRare(char *, unsigned int, unsigned char)

// FUNCTION: MSVC5_C1 0x00004680
// ?GetIdForHashedString@@YAPAUId_t@@PBDIIAAH@Z
// struct Id_t * __cdecl GetIdForHashedString(char const *, unsigned int, unsigned int, int &)

// FUNCTION: MSVC5_C1 0x000047c0
// ?GetIdForString@@YAPAUId_t@@PBD@Z
// struct Id_t * __cdecl GetIdForString(char const *)

// FUNCTION: MSVC5_C1 0x00004930
// ?GetIdForKeyword@@YAXPAD@Z
// FUNCTION: C1 0x0041b16d
void GetIdForKeyword(const char *keyword)
{
    unsigned int hash = 0;
    const char *ptr = keyword;
    for (; *ptr != '\0'; ptr++) {
        hash = (hash >> 4) + static_cast<unsigned int>(*ptr) + (hash << 2);
    }
    uint16_t table_index = hash & 0x7ff;
    hash = (hash >> 16) ^ hash;
    Id_t **ptr_current_item = &PchS.rs.p_IdTable[table_index];
    Id_t *current_item = *ptr_current_item;
    Id_t *prev_item = current_item;
    while (current_item != NULL) {
        if (current_item->attr.hashval == hash && current_item->ident[ptr - keyword] == '\0') {
            if (memcmp(current_item->ident, keyword, ptr - keyword) == 0) {
                prev_item->pNext = current_item->pNext;
                current_item->pNext = PchS.rs.p_IdTable[table_index];
                PchS.rs.p_IdTable[table_index] = current_item;
                pCurId = current_item;
                return;
            }
        }
        prev_item = current_item;
        ptr_current_item = &current_item->pNext;
        current_item = *ptr_current_item;
    }
    Id_t *new_id = SAClass<Id_t>::Allocate();
    new_id->pNext = PchS.rs.p_IdTable[table_index];
    PchS.rs.p_IdTable[table_index] = new_id;
    new_id->ident = static_cast<char *>(HeapManager::Allocate((ptr - keyword + 1 + 0x3) & ~0x3, M_LIFETIME0));
    memcpy(new_id->ident, keyword, ptr - keyword);
    new_id->ident[ptr - keyword] = '\0';
    new_id->attr.hashval = hash;
    pCurId = new_id;
}

// FUNCTION: MSVC5_C1 0x00004a90
// ?GetTempIdForString@@YAPAUId_t@@PAU1@PAD@Z
// struct Id_t * __cdecl GetTempIdForString(struct Id_t *, char *)

// FUNCTION: MSVC5_C1 0x00004ab0
// ?IdHash@@YAIPAX@Z
// unsigned int __cdecl IdHash(void *)

