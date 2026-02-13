#include "const.h"

#include "alloc.h"
#include "globals.h"
#include "nheapall.h"
#include "token.h"

// FUNCTION: MSVC5_C1 0x00019f50
// ?str_type@@YAXPAUs_tree@@@Z
// void __cdecl str_type(struct s_tree *)

// FUNCTION: MSVC5_C1 0x0001a000
// ?BuildStringConstant@@YAPAUs_tree@@PAD@Z
// struct s_tree * __cdecl BuildStringConstant(char *)

// FUNCTION: MSVC5_C1 0x0001a050
// ?build_const@@YAPAUs_tree@@PAVType_t@@ABTu_value@@W4lifetime_e@@@Z
// struct s_tree * __cdecl build_const(class Type_t *, union u_value const &, enum lifetime_e)

// FUNCTION: MSVC5_C1 0x0001a0e0
// ?BuildBigIntNoTTZero@@YAPAUs_tree@@_JH@Z
// struct s_tree * __cdecl BuildBigIntNoTTZero(__int64, int)

// FUNCTION: MSVC5_C1 0x0001a1a0
// ?BuildBigInt@@YAPAUs_tree@@_JH@Z
// struct s_tree * __cdecl BuildBigInt(__int64, int)

// FUNCTION: MSVC5_C1 0x0001a1d0
// ?BuildCintNoTTZero@@YAPAUs_tree@@J@Z
// FUNCTION: C1 0x0040925a
s_tree * BuildCintNoTTZero(long value)
{
    s_tree *tree = HeapManager::Allocate<s_tree>(currentTreeLife);
    tree->tr_shape = 3;
    tree->tr_token = L_INT_CONSTANT;
    tree->tr_p1type = PchS.rs.p_ST_BTint;
    return tree;
}

// FUNCTION: MSVC5_C1 0x0001a220
// ?BuildCint@@YAPAUs_tree@@J@Z
// FUNCTION: C1 0x0040929e
s_tree * BuildCint(long value)
{
    s_tree *tree = BuildCintNoTTZero(value);
    if (value == 0) {
        tree->tr_shape |= 0x80;
    }
    return tree;
}

// FUNCTION: MSVC5_C1 0x0001a240
// ?BuildCuint@@YAPAUs_tree@@J@Z
// struct s_tree * __cdecl BuildCuint(long)

// FUNCTION: MSVC5_C1 0x0001a260
// ?crush_bcons@@YAPAUs_tree@@PAU1@00@Z
// struct s_tree * __cdecl crush_bcons(struct s_tree *, struct s_tree *, struct s_tree *)

// FUNCTION: MSVC5_C1 0x0001afe0
// ?float_op@@YAPAUs_tree@@PAU1@PAUs_realt@@1@Z
// struct s_tree * __cdecl float_op(struct s_tree *, struct s_realt *, struct s_realt *)

// FUNCTION: MSVC5_C1 0x0001b2d0
// ?newreal@@YAPAUrcon@@PAUs_realt@@W4lifetime_e@@@Z
// struct rcon * __cdecl newreal(struct s_realt *, enum lifetime_e)

// FUNCTION: MSVC5_C1 0x0001b300
// ?copy_real_with_life@@YAPAUrcon@@Us_realt@@W4lifetime_e@@@Z
// struct rcon * __cdecl copy_real_with_life(struct s_realt, enum lifetime_e)

