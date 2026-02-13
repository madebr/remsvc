#include "p0keys.h"

#include "decomp.h"
#include "error.h"
#include "globals.h"
#include "p0id.h"

struct kw_t {
    const char *szKeyword;
    e_token_t token;
};

// GLOBAL: C1 0x00452860
const kw_t keytab[] = {
    { "auto",                       L_AUTO             },
    { "break",                      L_BREAK            },
    { "case",                       L_CASE             },
    { "char",                       L_CHAR             },
    { "const",                      L_CONST            },
    { "continue",                   L_CONTINUE         },
    { "default",                    L_DEFAULT          },
    { "do",                         L_DO               },
    { "double",                     L_DOUBLE           },
    { "else",                       L_ELSE             },
    { "enum",                       L_ENUM             },
    { "extern",                     L_EXTERN           },
    { "float",                      L_FLOAT            },
    { "for",                        L_FOR              },
    { "goto",                       L_GOTO             },
    { "if",                         L_IF               },
    { "int",                        L_INT              },
    { "long",                       L_LONG             },
    { "register",                   L_REGISTER         },
    { "return",                     L_RETURN           },
    { "short",                      L_SHORT            },
    { "signed",                     L_SIGNED           },
    { "sizeof",                     L_SIZEOF           },
    { "static",                     L_STATIC           },
    { "struct",                     L_STRUCT           },
    { "switch",                     L_SWITCH           },
    { "typedef",                    L_TYPEDEF          },
    { "union",                      L_UNION            },
    { "unsigned",                   L_UNSIGNED         },
    { "void",                       L_VOID             },
    { "volatile",                   L_VOLATILE         },
    { "while",                      L_WHILE            },
    { "__inline",                   L_INLINE           },
    { "__cdecl",                    L_C                },
    { "__based",                    L_BASED            },
    { "__stdcall",                  L_STDCALL          },
    { "__declspec",                 L_DECLSPEC         },
    { "asm",                        L_ASM_0xb6         },
    { "catch",                      L_CATCH            },
    { "class",                      L_CLASS            },
    { "const_cast",                 L_CONSTCAST        },
    { "delete",                     L_DELETE           },
    { "dynamic_cast",               L_DYNCAST          },
    { "friend",                     L_FRIEND           },
    { "inline",                     L_INLINE           },
    { "new",                        L_NEW              },
    { "operator",                   L_OPERATOR         },
    { "private",                    L_PRIVATE          },
    { "protected",                  L_PROTECTED        },
    { "public",                     L_PUBLIC           },
    { "reinterpret_cast",           L_REINCAST         },
    { "static_cast",                L_STATCAST         },
    { "template",                   L_TEMPLATE         },
    { "this",                       L_THIS             },
    { "throw",                      L_THROW            },
    { "try",                        L_TRY_CXX          },
    { "typeid",                     L_POSTFIX_TYPEID   },
    { "virtual",                    L_VIRTUAL          },
    { "namespace",                  L_NAMESPACE        },
    { "using",                      L_USING            },
    { "__single_inheritance",       L_SI               },
    { "__multiple_inheritance",     L_MI               },
    { "__virtual_inheritance",      L_VI               },
    { "__novtordisp",               L_NOVTORDISP       },
    { "__resume",                   L_DISABLED         },
    { "__nounwind",                 L_DISABLED         },
    { "__syscall",                  L_DISABLED         },
    { "__near",                     L_DISABLED         },
    { "__far",                      L_DISABLED         },
    { "__far16",                    L_DISABLED         },
    { "__huge",                     L_DISABLED         },
    { "__fortran",                  L_DISABLED         },
    { "__export",                   L_DISABLED         },
    { "__interrupt",                L_DISABLED         },
    { "__loadds",                   L_DISABLED         },
    { "__saveregs",                 L_DISABLED         },
    { "__segment",                  L_DISABLED         },
    { "__segname",                  L_DISABLED         },
    { "__self",                     L_DISABLED         },
    { "__thiscall",                 L_THISCALL         },
    { "cdecl",                      L_C                },
    { "far",                        L_DISABLED         },
    { "fortran",                    L_DISABLED         },
    { "huge",                       L_DISABLED         },
    { "near",                       L_DISABLED         },
    { "pascal",                     L_PASCAL           },
    { "__pascal",                   L_PASCAL2          },
    { "__try",                      L_TRY              },
    { "__except",                   L_EXCEPT           },
    { "__finally",                  L_FINALLY          },
    { "__leave",                    L_LEAVE            },
    { "__asm",                      L_ASM              },
    { "__fastcall",                 L_FASTCALL         },
    { "__unaligned",                L_UNALIGNED        },
    { "__builtin_alignof",          L_BUILTINALIGNOF   },
    { "__sysapi",                   L_SYSAPI           },
    { "__builtin_isfloat",          L_BUILTIN_ISFLOAT  },
    { "__wchar_t",                  L_WCHAR_T          },
    { "__restrict",                 L_RESTRICT         },
    { "__int8",                     L_INT8             },
    { "__int16",                    L_INT16            },
    { "__int32",                    L_INT32            },
    { "__int64",                    L_INT64            },
    { "__int128",                   L_INT128           },
    { "wchar_t",                    L_WCHAR_T          },
    { "bool",                       L_DISABLED         },
    { "true",                       L_DISABLED         },
    { "false",                      L_DISABLED         },
    { "mutable",                    L_DISABLED         },
    { "explicit",                   L_DISABLED         },
    { "typename",                   L_DISABLED         },
    { 0 }
};

struct s_declspec_keys {
    const char *name;
    int field;
    int value;
    bool32 hasArgs;
};

// GLOBAL: MSVC5_C1 0x000005c0
// ?Declspec_Keys@@3PBUs_declspec_keys@@B
const s_declspec_keys Declspec_Keys[] = {
    { "dllimport", 6, 2, FALSE },
    { "dllexport", 7, 3, FALSE },
    { "inline", 3, 1, FALSE },
    { "naked", 4, 1, FALSE },
    { "thread", 5, 1, FALSE },
    { "allocate", 8, 1, TRUE },
    { 0 },
};

// GLOBAL: MSVC5_C1 0x0000087c
// ??_C@_06BHLC@arning?$AA@
// "arning"

// GLOBAL: MSVC5_C1 0x00000884
// ??_C@_07OMPP@tordisp?$AA@
// "tordisp"

// GLOBAL: MSVC5_C1 0x0000088c
// ??_C@_04DIKI@itle?$AA@
// "itle"

// GLOBAL: MSVC5_C1 0x00000894
// ??_C@_07JGLN@ame_seg?$AA@
// "ame_seg"

// GLOBAL: MSVC5_C1 0x0000089c
// ??_C@_09ELLG@earch_lib?$AA@
// "earch_lib"

// GLOBAL: MSVC5_C1 0x000008a8
// ??_C@_06ICAH@egment?$AA@
// "egment"

// GLOBAL: MSVC5_C1 0x000008b0
// ??_C@_08GKCL@etlocale?$AA@
// "etlocale"

// GLOBAL: MSVC5_C1 0x000008bc
// ??_C@_03CDKI@kip?$AA@
// "kip"

// GLOBAL: MSVC5_C1 0x000008c0
// ??_C@_07CKGL@kipping?$AA@
// "kipping"

// GLOBAL: MSVC5_C1 0x000008c8
// ??_C@_0BA@BAEH@tart_map_region?$AA@
// "tart_map_region"

// GLOBAL: MSVC5_C1 0x000008d8
// ??_C@_0P@NGBO@top_map_region?$AA@
// "top_map_region"

// GLOBAL: MSVC5_C1 0x000008e8
// ??_C@_0O@GJAF@tring_pooling?$AA@
// "tring_pooling"

// GLOBAL: MSVC5_C1 0x000008f8
// ??_C@_07EKJO@ubtitle?$AA@
// "ubtitle"

// GLOBAL: MSVC5_C1 0x00000900
// ??_C@_0M@JODP@witch_check?$AA@
// "witch_check"

// GLOBAL: MSVC5_C1 0x0000090c
// ??_C@_03INEA@ack?$AA@
// "ack"

// GLOBAL: MSVC5_C1 0x00000910
// ??_C@_03HMCA@age?$AA@
// "age"

// GLOBAL: MSVC5_C1 0x00000914
// ??_C@_07PLBC@agesize?$AA@
// "agesize"

// GLOBAL: MSVC5_C1 0x0000091c
// ??_C@_08DICG@arameter?$AA@
// "arameter"

// GLOBAL: MSVC5_C1 0x00000928
// ??_C@_03JBGB@lmf?$AA@
// "lmf"

// GLOBAL: MSVC5_C1 0x0000092c
// ??_C@_03MFNJ@lmn?$AA@
// "lmn"

// GLOBAL: MSVC5_C1 0x00000930
// ??_C@_0BD@DDJL@ointers_to_members?$AA@
// "ointers_to_members"

// GLOBAL: MSVC5_C1 0x00000944
// ??_C@_02PFKG@op?$AA@
// "op"

// GLOBAL: MSVC5_C1 0x00000948
// ??_C@_07FIMK@rocname?$AA@
// "rocname"

// GLOBAL: MSVC5_C1 0x00000950
// ??_C@_03HBGA@ush?$AA@
// "ush"

// GLOBAL: MSVC5_C1 0x00000954
// ??_C@_03IFO@nce?$AA@
// "nce"

// GLOBAL: MSVC5_C1 0x00000958
// ??_C@_07PJNN@ptimize?$AA@
// "ptimize"

// GLOBAL: MSVC5_C1 0x00000960
// ??_C@_06NCK@ptions?$AA@
// "ptions"

// GLOBAL: MSVC5_C1 0x00000968
// ??_C@_0N@OPEA@ative_caller?$AA@
// "ative_caller"

// GLOBAL: MSVC5_C1 0x00000978
// ??_C@_06EINJ@essage?$AA@
// "essage"

// GLOBAL: MSVC5_C1 0x00000980
// ??_C@_07LHBO@inesize?$AA@
// "inesize"

// GLOBAL: MSVC5_C1 0x00000988
// ??_C@_07IFCN@oop_opt?$AA@
// "oop_opt"

// GLOBAL: MSVC5_C1 0x00000990
// ??_C@_0BC@EJLL@mplementation_key?$AA@
// "mplementation_key"

// GLOBAL: MSVC5_C1 0x000009a4
// ??_C@_0N@OPHB@nclude_alias?$AA@
// "nclude_alias"

// GLOBAL: MSVC5_C1 0x000009b4
// ??_C@_07NPAI@nit_seg?$AA@
// "nit_seg"

// GLOBAL: MSVC5_C1 0x000009bc
// ??_C@_0M@DJMP@nline_depth?$AA@
// "nline_depth"

// GLOBAL: MSVC5_C1 0x000009c8
// ??_C@_0BA@NJKJ@nline_recursion?$AA@
// "nline_recursion"

// GLOBAL: MSVC5_C1 0x000009d8
// ??_C@_08BFIP@ntrinsic?$AA@
// "ntrinsic"

// GLOBAL: MSVC5_C1 0x000009e4
// ??_C@_06FKJF@drstop?$AA@
// "drstop"

// GLOBAL: MSVC5_C1 0x000009ec
// ??_C@_07CHHG@unction?$AA@
// "unction"

// GLOBAL: MSVC5_C1 0x000009f4
// ??_C@_07HEIL@ata_seg?$AA@
// "ata_seg"

// GLOBAL: MSVC5_C1 0x000009fc
// ??_C@_0N@LID@heck_pointer?$AA@
// "heck_pointer"

// GLOBAL: MSVC5_C1 0x00000a0c
// ??_C@_0L@OLCE@heck_stack?$AA@
// "heck_stack"

// GLOBAL: MSVC5_C1 0x00000a18
// ??_C@_07DNMM@ode_seg?$AA@
// "ode_seg"

// GLOBAL: MSVC5_C1 0x00000a20
// ??_C@_06EFCG@omment?$AA@
// "omment"

// GLOBAL: MSVC5_C1 0x00000a28
// ??_C@_08FFIB@omponent?$AA@
// "omponent"

// GLOBAL: MSVC5_C1 0x00000a34
// ??_C@_08LEIB@onst_seg?$AA@
// "onst_seg"

// GLOBAL: MSVC5_C1 0x00000a40
// ??_C@_06IHLN@ss_seg?$AA@
// "ss_seg"

// GLOBAL: MSVC5_C1 0x00000a48
// ??_C@_09NKOI@lloc_text?$AA@
// "lloc_text"

// GLOBAL: MSVC5_C1 0x00000a54
// ??_C@_0L@NCPG@uto_inline?$AA@
// "uto_inline"

// GLOBAL: MSVC5_C1 0x00000a60
// ??_C@_04LPDL@ndef?$AA@
// "ndef"

// GLOBAL: MSVC5_C1 0x00000a68
// ??_C@_05DGHO@ragma?$AA@
// "ragma"

// GLOBAL: MSVC5_C1 0x00000a70
// ??_C@_03EPGL@ine?$AA@
// "ine"

// GLOBAL: MSVC5_C1 0x00000a74
// ??_C@_04PPOM@dent?$AA@
// "dent"

// GLOBAL: MSVC5_C1 0x00000a7c
// ??_C@_01IFC@f?$AA@
// "f"

// GLOBAL: MSVC5_C1 0x00000a80
// ??_C@_04JFKL@fdef?$AA@
// "fdef"

// GLOBAL: MSVC5_C1 0x00000a88
// ??_C@_05HCBK@fndef?$AA@
// "fndef"

// GLOBAL: MSVC5_C1 0x00000a90
// ??_C@_05KCCO@mport?$AA@
// "mport"

// GLOBAL: MSVC5_C1 0x00000a98
// ??_C@_06IOKN@nclude?$AA@
// "nclude"

// GLOBAL: MSVC5_C1 0x00000aa0
// ??_C@_03MLML@lif?$AA@
// "lif"

// GLOBAL: MSVC5_C1 0x00000aa4
// ??_C@_03MGNK@lse?$AA@
// "lse"

// GLOBAL: MSVC5_C1 0x00000aa8
// ??_C@_04FAMF@ndif?$AA@
// "ndif"

// GLOBAL: MSVC5_C1 0x00000ab0
// ??_C@_04DPC@rror?$AA@
// "rror"

// GLOBAL: MSVC5_C1 0x00000ab8
// ??_C@_05EDAO@efine?$AA@
// "efine"

// GLOBAL: MSVC5_C1 0x00000ac0
// ??_C@_09CCMI@selectany?$AA@
// "selectany"

// GLOBAL: MSVC5_C1 0x00000acc
// ??_C@_06NEAL@thread?$AA@
// "thread"

// GLOBAL: MSVC5_C1 0x00000ad4
// ??_C@_05NIOE@naked?$AA@
// "naked"

// GLOBAL: MSVC5_C1 0x00000adc
// ??_C@_09JLFG@dllexport?$AA@
// "dllexport"

// GLOBAL: MSVC5_C1 0x00000ae8
// ??_C@_09ECDC@dllimport?$AA@
// "dllimport"

// GLOBAL: MSVC5_C1 0x00000af4
// ??_C@_05NAGO@false?$AA@
// "false"

// GLOBAL: MSVC5_C1 0x00000afc
// ??_C@_04NCCD@true?$AA@
// "true"

// GLOBAL: MSVC5_C1 0x00000b04
// ??_C@_04PPPK@bool?$AA@
// "bool"

// GLOBAL: MSVC5_C1 0x00000b0c
// ??_C@_06BDGI@not_eq?$AA@
// "not_eq"

// GLOBAL: MSVC5_C1 0x00000b14
// ??_C@_03OEEH@not?$AA@
// "not"

// GLOBAL: MSVC5_C1 0x00000b18
// ??_C@_05JCGE@compl?$AA@
// "compl"

// GLOBAL: MSVC5_C1 0x00000b20
// ??_C@_06OLEG@xor_eq?$AA@
// "xor_eq"

// GLOBAL: MSVC5_C1 0x00000b28
// ??_C@_03NGCI@xor?$AA@
// "xor"

// GLOBAL: MSVC5_C1 0x00000b2c
// ??_C@_05LCHG@bitor?$AA@
// "bitor"

// GLOBAL: MSVC5_C1 0x00000b34
// ??_C@_05MAEI@or_eq?$AA@
// "or_eq"

// GLOBAL: MSVC5_C1 0x00000b3c
// ??_C@_02KAII@or?$AA@
// "or"

// GLOBAL: MSVC5_C1 0x00000b40
// ??_C@_06BAFL@bitand?$AA@
// "bitand"

// GLOBAL: MSVC5_C1 0x00000b48
// ??_C@_06KDAN@and_eq?$AA@
// "and_eq"

// GLOBAL: MSVC5_C1 0x00000b50
// ??_C@_03HFEJ@and?$AA@
// "and"

// GLOBAL: MSVC5_C1 0x00000b54
// ??_C@_07EAPL@wchar_t?$AA@
// "wchar_t"

// GLOBAL: MSVC5_C1 0x00000b5c
// ??_C@_08NLKA@__int128?$AA@
// "__int128"

// GLOBAL: MSVC5_C1 0x00000b68
// ??_C@_07BGNA@__int64?$AA@
// "__int64"

// GLOBAL: MSVC5_C1 0x00000b70
// ??_C@_07KFKC@__int32?$AA@
// "__int32"

// GLOBAL: MSVC5_C1 0x00000b78
// ??_C@_07CCKL@__int16?$AA@
// "__int16"

// GLOBAL: MSVC5_C1 0x00000b80
// ??_C@_06LHNP@__int8?$AA@
// "__int8"

// GLOBAL: MSVC5_C1 0x00000b88
// ??_C@_07GMOI@__ptr64?$AA@
// "__ptr64"

// GLOBAL: MSVC5_C1 0x00000b90
// ??_C@_0L@CKEM@__restrict?$AA@
// "__restrict"

// GLOBAL: MSVC5_C1 0x00000b9c
// ??_C@_09JLDK@__wchar_t?$AA@
// "__wchar_t"

// GLOBAL: MSVC5_C1 0x00000ba8
// ??_C@_0BC@MALP@__builtin_isfloat?$AA@
// "__builtin_isfloat"

// GLOBAL: MSVC5_C1 0x00000bbc
// ??_C@_08BKOF@__sysapi?$AA@
// "__sysapi"

// GLOBAL: MSVC5_C1 0x00000bc8
// ??_C@_0BC@ODCE@__builtin_alignof?$AA@
// "__builtin_alignof"

// GLOBAL: MSVC5_C1 0x00000bdc
// ??_C@_0M@NPEN@__unaligned?$AA@
// "__unaligned"

// GLOBAL: MSVC5_C1 0x00000be8
// ??_C@_0L@PLEG@__fastcall?$AA@
// "__fastcall"

// GLOBAL: MSVC5_C1 0x00000bf4
// ??_C@_05KDMA@__asm?$AA@
// "__asm"

// GLOBAL: MSVC5_C1 0x00000bfc
// ??_C@_07EEKC@__leave?$AA@
// "__leave"

// GLOBAL: MSVC5_C1 0x00000c04
// ??_C@_09JHLE@__finally?$AA@
// "__finally"

// GLOBAL: MSVC5_C1 0x00000c10
// ??_C@_08HNHK@__except?$AA@
// "__except"

// GLOBAL: MSVC5_C1 0x00000c1c
// ??_C@_05INGA@__try?$AA@
// "__try"

// GLOBAL: MSVC5_C1 0x00000c24
// ??_C@_08HPJP@__pascal?$AA@
// "__pascal"

// GLOBAL: MSVC5_C1 0x00000c30
// ??_C@_06LOBJ@pascal?$AA@
// "pascal"

// GLOBAL: MSVC5_C1 0x00000c38
// ??_C@_04LEKL@near?$AA@
// "near"

// GLOBAL: MSVC5_C1 0x00000c40
// ??_C@_04MBEH@huge?$AA@
// "huge"

// GLOBAL: MSVC5_C1 0x00000c48
// ??_C@_07PAN@fortran?$AA@
// "fortran"

// GLOBAL: MSVC5_C1 0x00000c50
// ??_C@_03EJCL@far?$AA@
// "far"

// GLOBAL: MSVC5_C1 0x00000c54
// ??_C@_05BGOB@cdecl?$AA@
// "cdecl"

// GLOBAL: MSVC5_C1 0x00000c5c
// ??_C@_0L@PHD@__thiscall?$AA@
// "__thiscall"

// GLOBAL: MSVC5_C1 0x00000c68
// ??_C@_06JMMD@__self?$AA@
// "__self"

// GLOBAL: MSVC5_C1 0x00000c70
// ??_C@_09KLEK@__segname?$AA@
// "__segname"

// GLOBAL: MSVC5_C1 0x00000c7c
// ??_C@_09LEPO@__segment?$AA@
// "__segment"

// GLOBAL: MSVC5_C1 0x00000c88
// ??_C@_0L@GOME@__saveregs?$AA@
// "__saveregs"

// GLOBAL: MSVC5_C1 0x00000c94
// ??_C@_08FKCA@__loadds?$AA@
// "__loadds"

// GLOBAL: MSVC5_C1 0x00000ca0
// ??_C@_0M@GLIA@__interrupt?$AA@
// "__interrupt"

// GLOBAL: MSVC5_C1 0x00000cac
// ??_C@_08FOGA@__export?$AA@
// "__export"

// GLOBAL: MSVC5_C1 0x00000cb8
// ??_C@_09NEMM@__fortran?$AA@
// "__fortran"

// GLOBAL: MSVC5_C1 0x00000cc4
// ??_C@_06NMPM@__huge?$AA@
// "__huge"

// GLOBAL: MSVC5_C1 0x00000ccc
// ??_C@_07HPCC@__far16?$AA@
// "__far16"

// GLOBAL: MSVC5_C1 0x00000cd4
// ??_C@_05PCHA@__far?$AA@
// "__far"

// GLOBAL: MSVC5_C1 0x00000cdc
// ??_C@_06KJBA@__near?$AA@
// "__near"

// GLOBAL: MSVC5_C1 0x00000ce4
// ??_C@_09PKAG@__syscall?$AA@
// "__syscall"

// GLOBAL: MSVC5_C1 0x00000cf0
// ??_C@_0L@DOCG@__nounwind?$AA@
// "__nounwind"

// GLOBAL: MSVC5_C1 0x00000cfc
// ??_C@_08IIG@__resume?$AA@
// "__resume"

// GLOBAL: MSVC5_C1 0x00000d08
// ??_C@_08HGDG@__uuidof?$AA@
// "__uuidof"

// GLOBAL: MSVC5_C1 0x00000d14
// ??_C@_0N@GC@__novtordisp?$AA@
// "__novtordisp"

// GLOBAL: MSVC5_C1 0x00000d24
// ??_C@_0BG@EBKF@__virtual_inheritance?$AA@
// "__virtual_inheritance"

// GLOBAL: MSVC5_C1 0x00000d3c
// ??_C@_0BH@KHII@__multiple_inheritance?$AA@
// "__multiple_inheritance"

// GLOBAL: MSVC5_C1 0x00000d54
// ??_C@_0BF@MJKM@__single_inheritance?$AA@
// "__single_inheritance"

// GLOBAL: MSVC5_C1 0x00000d6c
// ??_C@_07HANI@virtual?$AA@
// "virtual"

// GLOBAL: MSVC5_C1 0x00000d74
// ??_C@_05PBEO@using?$AA@
// "using"

// GLOBAL: MSVC5_C1 0x00000d7c
// ??_C@_08CMEB@typename?$AA@
// "typename"

// GLOBAL: MSVC5_C1 0x00000d88
// ??_C@_06IJIL@typeid?$AA@
// "typeid"

// GLOBAL: MSVC5_C1 0x00000d90
// ??_C@_03DGDL@try?$AA@
// "try"

// GLOBAL: MSVC5_C1 0x00000d94
// ??_C@_05LJBC@throw?$AA@
// "throw"

// GLOBAL: MSVC5_C1 0x00000d9c
// ??_C@_04BEIE@this?$AA@
// "this"

// GLOBAL: MSVC5_C1 0x00000da4
// ??_C@_08JONF@template?$AA@
// "template"

// GLOBAL: MSVC5_C1 0x00000db0
// ??_C@_0M@OANN@static_cast?$AA@
// "static_cast"

// GLOBAL: MSVC5_C1 0x00000dbc
// ??_C@_0BB@BGMM@reinterpret_cast?$AA@
// "reinterpret_cast"

// GLOBAL: MSVC5_C1 0x00000dd0
// ??_C@_06NGHH@public?$AA@
// "public"

// GLOBAL: MSVC5_C1 0x00000dd8
// ??_C@_09IFOC@protected?$AA@
// "protected"

// GLOBAL: MSVC5_C1 0x00000de4
// ??_C@_07MGEE@private?$AA@
// "private"

// GLOBAL: MSVC5_C1 0x00000dec
// ??_C@_08KMNC@operator?$AA@
// "operator"

// GLOBAL: MSVC5_C1 0x00000df8
// ??_C@_03IDPP@new?$AA@
// "new"

// GLOBAL: MSVC5_C1 0x00000dfc
// ??_C@_09OIJB@namespace?$AA@
// "namespace"

// GLOBAL: MSVC5_C1 0x00000e08
// ??_C@_07ICIG@mutable?$AA@
// "mutable"

// GLOBAL: MSVC5_C1 0x00000e10
// ??_C@_06CGND@inline?$AA@
// "inline"

// GLOBAL: MSVC5_C1 0x00000e18
// ??_C@_06CCDK@friend?$AA@
// "friend"

// GLOBAL: MSVC5_C1 0x00000e20
// ??_C@_08GOMC@explicit?$AA@
// "explicit"

// GLOBAL: MSVC5_C1 0x00000e2c
// ??_C@_0N@HOF@dynamic_cast?$AA@
// "dynamic_cast"

// GLOBAL: MSVC5_C1 0x00000e3c
// ??_C@_06IDPA@delete?$AA@
// "delete"

// GLOBAL: MSVC5_C1 0x00000e44
// ??_C@_0L@GIFN@const_cast?$AA@
// "const_cast"

// GLOBAL: MSVC5_C1 0x00000e50
// ??_C@_05LGKP@class?$AA@
// "class"

// GLOBAL: MSVC5_C1 0x00000e58
// ??_C@_05HPNL@catch?$AA@
// "catch"

// GLOBAL: MSVC5_C1 0x00000e60
// ??_C@_03BIJL@asm?$AA@
// "asm"

// GLOBAL: MSVC5_C1 0x00000e64
// ??_C@_0L@MMO@__declspec?$AA@
// "__declspec"

// GLOBAL: MSVC5_C1 0x00000e70
// ??_C@_09PGII@__stdcall?$AA@
// "__stdcall"

// GLOBAL: MSVC5_C1 0x00000e7c
// ??_C@_07GOJJ@__based?$AA@
// "__based"

// GLOBAL: MSVC5_C1 0x00000e84
// ??_C@_07JAPM@__cdecl?$AA@
// "__cdecl"

// GLOBAL: MSVC5_C1 0x00000e8c
// ??_C@_08OHFF@__inline?$AA@
// "__inline"

// GLOBAL: MSVC5_C1 0x00000e98
// ??_C@_05NJDI@while?$AA@
// "while"

// GLOBAL: MSVC5_C1 0x00000ea0
// ??_C@_08CACH@volatile?$AA@
// "volatile"

// GLOBAL: MSVC5_C1 0x00000eac
// ??_C@_04BMNE@void?$AA@
// "void"

// GLOBAL: MSVC5_C1 0x00000eb4
// ??_C@_08EFFH@unsigned?$AA@
// "unsigned"

// GLOBAL: MSVC5_C1 0x00000ec0
// ??_C@_05NGGA@union?$AA@
// "union"

// GLOBAL: MSVC5_C1 0x00000ec8
// ??_C@_07GPII@typedef?$AA@
// "typedef"

// GLOBAL: MSVC5_C1 0x00000ed0
// ??_C@_06OPGE@switch?$AA@
// "switch"

// GLOBAL: MSVC5_C1 0x00000ed8
// ??_C@_06BKMO@struct?$AA@
// "struct"

// GLOBAL: MSVC5_C1 0x00000ee0
// ??_C@_06BGJL@static?$AA@
// "static"

// GLOBAL: MSVC5_C1 0x00000ee8
// ??_C@_06CBFL@sizeof?$AA@
// "sizeof"

// GLOBAL: MSVC5_C1 0x00000ef0
// ??_C@_06EFFB@signed?$AA@
// "signed"

// GLOBAL: MSVC5_C1 0x00000ef8
// ??_C@_05BODP@short?$AA@
// "short"

// GLOBAL: MSVC5_C1 0x00000f00
// ??_C@_06CGBH@return?$AA@
// "return"

// GLOBAL: MSVC5_C1 0x00000f08
// ??_C@_08DFJG@register?$AA@
// "register"

// GLOBAL: MSVC5_C1 0x00000f14
// ??_C@_04LHCN@long?$AA@
// "long"

// GLOBAL: MSVC5_C1 0x00000f1c
// ??_C@_03EMIM@int?$AA@
// "int"

// GLOBAL: MSVC5_C1 0x00000f20
// ??_C@_04FEFL@goto?$AA@
// "goto"

// GLOBAL: MSVC5_C1 0x00000f28
// ??_C@_03ILIA@for?$AA@
// "for"

// GLOBAL: MSVC5_C1 0x00000f2c
// ??_C@_05PIME@float?$AA@
// "float"

// GLOBAL: MSVC5_C1 0x00000f34
// ??_C@_06JGNA@extern?$AA@
// "extern"

// GLOBAL: MSVC5_C1 0x00000f3c
// ??_C@_04PGN@enum?$AA@
// "enum"

// GLOBAL: MSVC5_C1 0x00000f44
// ??_C@_04IIAH@else?$AA@
// "else"

// GLOBAL: MSVC5_C1 0x00000f4c
// ??_C@_06PJOP@double?$AA@
// "double"

// GLOBAL: MSVC5_C1 0x00000f54
// ??_C@_02NDCA@do?$AA@
// "do"

// GLOBAL: MSVC5_C1 0x00000f58
// ??_C@_07FMEP@default?$AA@
// "default"

// GLOBAL: MSVC5_C1 0x00000f60
// ??_C@_08HLGC@continue?$AA@
// "continue"

// GLOBAL: MSVC5_C1 0x00000f6c
// ??_C@_05KCGI@const?$AA@
// "const"

// GLOBAL: MSVC5_C1 0x00000f74
// ??_C@_04KENI@char?$AA@
// "char"

// GLOBAL: MSVC5_C1 0x00000f7c
// ??_C@_04NNBC@case?$AA@
// "case"

// GLOBAL: MSVC5_C1 0x00000f84
// ??_C@_05EELJ@break?$AA@
// "break"

// GLOBAL: MSVC5_C1 0x00000f8c
// ??_C@_04JOEF@auto?$AA@
// "auto"

// GLOBAL: MSVC5_C1 0x00000f94
// ??_C@_02BJOA@__?$AA@
// "__"

// FUNCTION: MSVC5_C1 0x00005d60
// ?mkKeywordIdent@@YAXPAD@Z
// FUNCTION: C1 0x0041b764
void mkKeywordIdent(const char *name)
{
    GetIdForKeyword(name);
    pCurId->attr.isKeyword = FALSE;
}

// FUNCTION: MSVC5_C1 0x00005d80
// ?mkKeywordObsolete@@YAXPAD@Z
// FUNCTION: C1 0x0041b7e3
void mkKeywordObsolete(const char *name)
{
    GetIdForKeyword(name);
    if (pCurId->attr.isKeyword) {
        pCurId->token = L_DISABLED;
        pCurId->action = 1;
    }
}

// FUNCTION: MSVC5_C1 0x00005db0
// ?mkKeywordCppOnly@@YAXPAD@Z
// FUNCTION: C1 0x0041b92c
void mkKeywordCppOnly(const char *name)
{
    GetIdForKeyword(name);
    if (pCurId->attr.isKeyword) {
      pCurId->token = L_DISABLED;
      pCurId->action = 2;
    }
}

// FUNCTION: MSVC5_C1 0x00005de0
// ?mkKeywordFutureUse@@YAXPAD@Z
// FUNCTION: C1 0x0041ba04
void mkKeywordFutureUse(const char *name)
{
    GetIdForKeyword(name);
    if (pCurId->attr.isKeyword) {
        pCurId->token = L_DISABLED;
        pCurId->action = 3;
    }
}

// FUNCTION: MSVC5_C1 0x00005e10
// ?mkKeywordNotThisProduct@@YAXPAD@Z
// FUNCTION: C1 0x0041c1c4
void mkKeywordNotThisProduct(const char *name)
{
    GetIdForKeyword(name);
    if (pCurId->attr.isKeyword) {
        pCurId->token = L_DISABLED;
        pCurId->action = 4;
    }
}

// FUNCTION: MSVC5_C1 0x00005e40
// ?mkKeywordExportSpecial@@YAXPAD@Z
// FUNCTION: C1 0x0041c146
void mkKeywordExportSpecial(const char *name)
{
    GetIdForKeyword(name);
    if (pCurId->attr.isKeyword) {
      pCurId->token = L_DISABLED;
      pCurId->action = 5;
    }
}

// FUNCTION: MSVC5_C1 0x00005e70
// ?mkKeywordNewCpp@@YAXPAD@Z
// FUNCTION: C1 0x0041c0f1
void mkKeywordNewCpp(const char *name)
{
    GetIdForKeyword(name);
    if (pCurId->attr.isKeyword) {
        pCurId->token = L_DISABLED;
        pCurId->action = 6;
    }
}

// FUNCTION: MSVC5_C1 0x00005ea0
// ?AddKeywordsToIdTable@@YAXXZ
// FUNCTION: 0x0041c031
void AddKeywordsToIdTable()
{
    size_t i;
    for (i = 0; Declspec_Keys[i].name != NULL; i++) {
        GetIdForKeyword(Declspec_Keys[i].name);
        pCurId->attr.isDeclSpecKey = TRUE;
        if (!pCurId->attr.isKeyword) {
            pCurId->token = i;
        }
    }
}

// FUNCTION: MSVC5_C1 0x00006520
// ?is_pkeyword@@YAEPAD@Z
// unsigned char __cdecl is_pkeyword(char *)

// FUNCTION: MSVC5_C1 0x000065c0
// ?is_pragma@@YAHPAD@Z
// int __cdecl is_pragma(char *)

// FUNCTION: MSVC5_C1 0x00006660
// ?InitKeywords@@YAXXZ
// FUNCTION: C1 0x0041bb78
void InitKeywords()
{
    size_t i;

    PchC.p_Extension = PchC.p_Extension || PchC.p_BigIntExtension;
    PchC.p_SizeOfBigInt = PchC.p_SizeOfBigInt / 8;
    if (PchC.p_SizeOfBigInt == 0) {
        PchC.p_SizeOfBigInt = 4;
    } else if (PchC.p_SizeOfBigInt < 4 || PchC.p_SizeOfBigInt > 8) {
        warning(1, 696, PchC.p_SizeOfBigInt * 8, 32);
        PchC.p_SizeOfBigInt = 4;
    } else if (PchC.p_SizeOfBigInt != 4 && PchC.p_SizeOfBigInt != 8) {
        warning(1, 696, PchC.p_SizeOfBigInt * 8, 32);
        PchC.p_SizeOfBigInt = 4;
    }
    for (i = 0; keytab[i].szKeyword != NULL; i++) {
        GetIdForKeyword(keytab[i].szKeyword);
        pCurId->attr.isKeyword = TRUE;
        pCurId->token = keytab[i].token;
    }
    mkKeywordIdent("asm");
    mkKeywordIdent("catch");
    mkKeywordIdent("class");
    mkKeywordIdent("const_cast");
    mkKeywordIdent("delete");
    mkKeywordIdent("dynamic_cast");
    mkKeywordIdent("friend");
    mkKeywordIdent("inline");
    mkKeywordIdent("new");
    mkKeywordIdent("operator");
    mkKeywordIdent("private");
    mkKeywordIdent("protected");
    mkKeywordIdent("public");
    mkKeywordIdent("reinterpret_cast");
    mkKeywordIdent("static_cast");
    mkKeywordIdent("template");
    mkKeywordIdent("this");
    mkKeywordIdent("throw");
    mkKeywordIdent("try");
    mkKeywordIdent("typeid");
    mkKeywordIdent("virtual");
    mkKeywordIdent("namespace");
    mkKeywordIdent("using");
    mkKeywordIdent("__interrupt");
    mkKeywordIdent("__loadds");
    mkKeywordIdent("__saveregs");
    mkKeywordIdent("__segment");
    mkKeywordIdent("__segname");
    mkKeywordIdent("__self");
    if (!PchC.p_Extension) {
        mkKeywordIdent("cdecl");
    }
    if (!gOption_Zf && !PchC.p_Extension) {
        mkKeywordIdent("far");
    }
    if (!gOption_Zf && !PchC.p_Extension) {
        mkKeywordIdent("fortran");
    }
    if (!gOption_Zf && !PchC.p_Extension) {
        mkKeywordIdent("huge");
    }
    if (!gOption_Zf && !PchC.p_Extension) {
        mkKeywordIdent("near");
    }
    if (!gOption_Zf && !PchC.p_Extension) {
        mkKeywordIdent("pascal");
    }
    mkKeywordIdent("wchar_t");
    mkKeywordIdent("bool");
    mkKeywordIdent("true");
    mkKeywordIdent("false");
    mkKeywordIdent("mutable");
    mkKeywordIdent("explicit");
    mkKeywordIdent("typename");
    mkKeywordFutureUse("namespace");
    mkKeywordFutureUse("using");
    mkKeywordCppOnly("__single_inheritance");
    mkKeywordCppOnly("__multiple_inheritance");
    mkKeywordCppOnly("__virtual_inheritance");
    mkKeywordCppOnly("__novtordisp");
    mkKeywordFutureUse("__resume");
    mkKeywordFutureUse("__nounwind");
    mkKeywordObsolete("__syscall");
    mkKeywordObsolete("__near");
    mkKeywordObsolete("__far");
    mkKeywordObsolete("__far16");
    mkKeywordObsolete("__huge");
    mkKeywordObsolete("__fortran");
    mkKeywordExportSpecial("__export");
    mkKeywordFutureUse("__thiscall");
    mkKeywordObsolete("far");
    mkKeywordObsolete("fortran");
    mkKeywordObsolete("huge");
    mkKeywordObsolete("near");
    mkKeywordObsolete("pascal");
    mkKeywordObsolete("__pascal");
    mkKeywordNotThisProduct("__unaligned");
    mkKeywordNotThisProduct("__builtin_alignof");
    mkKeywordNotThisProduct("__sysapi");
    mkKeywordNotThisProduct("__builtin_isfloat");
    mkKeywordNotThisProduct("__wchar_t");
    mkKeywordNotThisProduct("__restrict");
    if (PchC.p_SizeOfBigInt < 4) {
        mkKeywordNotThisProduct("__int8");
    }
    if (PchC.p_SizeOfBigInt < 4) {
        mkKeywordNotThisProduct("__int16");
    }
    if (PchC.p_SizeOfBigInt < 4) {
        mkKeywordNotThisProduct("__int32");
    }
    if (PchC.p_SizeOfBigInt < 8) {
        mkKeywordNotThisProduct("__int64");
    }
    if (PchC.p_SizeOfBigInt < 16) {
        mkKeywordNotThisProduct("__int128");
    }
    mkKeywordNewCpp("bool");
    mkKeywordNewCpp("true");
    mkKeywordNewCpp("false");
    mkKeywordNewCpp("mutable");
    mkKeywordNewCpp("explicit");
    mkKeywordNewCpp("typename");
    if (PchC.p_Extension || PchC.p_option_ZE) {
        for (i = 0; keytab[i].szKeyword != NULL; i++) {
            if (strncmp(keytab[i].szKeyword, "__", 2) == 0) {
                GetIdForKeyword(keytab[i].szKeyword);
                if (pCurId->attr.isKeyword) {
                    if (pCurId->token == L_DISABLED) {
                        int action = pCurId->action;
                        if (action == 1 || action == 5) {
                            GetIdForKeyword(&keytab[i].szKeyword[1]);
                            pCurId->attr.isKeyword = TRUE;
                            pCurId->token = L_DISABLED;
                            pCurId->action = action;
                        }
                    } else {
                        GetIdForKeyword(&keytab[i].szKeyword[1]);
                        pCurId->attr.isKeyword = TRUE;
                        pCurId->token = L_DISABLED;
                    }
                }
            }
        }
    }
    AddKeywordsToIdTable();
}
