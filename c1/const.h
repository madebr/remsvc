#ifndef CONST_H
#define CONST_H

#include "c1_types.h"

// ?str_type@@YAXPAUs_tree@@@Z
// void __cdecl str_type(struct s_tree *)

// ?BuildStringConstant@@YAPAUs_tree@@PAD@Z
// struct s_tree * __cdecl BuildStringConstant(char *)

// ?build_const@@YAPAUs_tree@@PAVType_t@@ABTu_value@@W4lifetime_e@@@Z
// struct s_tree * __cdecl build_const(class Type_t *, union u_value const &, enum lifetime_e)

// ?BuildBigIntNoTTZero@@YAPAUs_tree@@_JH@Z
// struct s_tree * __cdecl BuildBigIntNoTTZero(__int64, int)

// ?BuildBigInt@@YAPAUs_tree@@_JH@Z
// struct s_tree * __cdecl BuildBigInt(__int64, int)

// ?BuildCintNoTTZero@@YAPAUs_tree@@J@Z
extern s_tree * BuildCintNoTTZero(long value);

// ?BuildCint@@YAPAUs_tree@@J@Z
extern s_tree * BuildCint(long value);

// ?BuildCuint@@YAPAUs_tree@@J@Z
// struct s_tree * __cdecl BuildCuint(long)

// ?crush_bcons@@YAPAUs_tree@@PAU1@00@Z
// struct s_tree * __cdecl crush_bcons(struct s_tree *, struct s_tree *, struct s_tree *)

// ?float_op@@YAPAUs_tree@@PAU1@PAUs_realt@@1@Z
// struct s_tree * __cdecl float_op(struct s_tree *, struct s_realt *, struct s_realt *)

// ?newreal@@YAPAUrcon@@PAUs_realt@@W4lifetime_e@@@Z
// struct rcon * __cdecl newreal(struct s_realt *, enum lifetime_e)

// ?copy_real_with_life@@YAPAUrcon@@Us_realt@@W4lifetime_e@@@Z
// struct rcon * __cdecl copy_real_with_life(struct s_realt, enum lifetime_e)

#endif /* CONST_H */
