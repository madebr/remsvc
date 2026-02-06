#include "initmain.h"

#include "decomp.h"

// GLOBAL: MSVC5_C1 0x000013e0
// ?Unknown@@3PADA
// char *Unknown

// GLOBAL: MSVC5_C1 0x000013e4
// ?C7CompatCVInfo@@3HA
// int C7CompatCVInfo

// GLOBAL: MSVC5_C1 0x00003034
// ??_C@_01FDHG@?$CK?$AA@
// "*"

// GLOBAL: MSVC5_C1 0x00003038
// ??_C@_0M@JFCE@?9Bshow_incl?$AA@
// "-Bshow_incl"

// GLOBAL: MSVC5_C1 0x00003044
// ??_C@_0M@IGPH@?9NoEHForNew?$AA@
// "-NoEHForNew"

// GLOBAL: MSVC5_C1 0x00003050
// ??_C@_0M@JPHG@?9SplitPdbs?9?$AA@
// "-SplitPdbs-"

// GLOBAL: MSVC5_C1 0x0000305c
// ??_C@_0L@OFCA@?9SplitPdbs?$AA@
// "-SplitPdbs"

// GLOBAL: MSVC5_C1 0x00003068
// ??_C@_05ONCA@?9C9IL?$AA@
// "-C9IL"

// GLOBAL: MSVC5_C1 0x00003070
// ??_C@_06OELC@?9BMOVE?$AA@
// "-BMOVE"

// GLOBAL: MSVC5_C1 0x00003078
// ??_C@_03KOIF@?9G?$CD?$AA@
// "-G#"

// GLOBAL: MSVC5_C1 0x0000307c
// ??_C@_03PCGP@?9GM?$AA@
// "-GM"

// GLOBAL: MSVC5_C1 0x00003080
// ??_C@_09KOFP@?9noexpinl?$AA@
// "-noexpinl"

// GLOBAL: MSVC5_C1 0x0000308c
// ??_C@_08MBHL@?9BNOPPCH?$AA@
// "-BNOPPCH"

// GLOBAL: MSVC5_C1 0x00003098
// ??_C@_04JFNE@?9Yl?$CK?$AA@
// "-Yl*"

// GLOBAL: MSVC5_C1 0x000030a0
// ??_C@_03PDNG@?9YX?$AA@
// "-YX"

// GLOBAL: MSVC5_C1 0x000030a4
// ??_C@_04HAIF@?9YX?$CK?$AA@
// "-YX*"

// GLOBAL: MSVC5_C1 0x000030ac
// ??_C@_04OBBC@?9Fp?$CD?$AA@
// "-Fp#"

// GLOBAL: MSVC5_C1 0x000030b4
// ??_C@_03PGKC@?9Yd?$AA@
// "-Yd"

// GLOBAL: MSVC5_C1 0x000030b8
// ??_C@_03KDEH@?9Yc?$AA@
// "-Yc"

// GLOBAL: MSVC5_C1 0x000030bc
// ??_C@_04EBNF@?9Yc?$CK?$AA@
// "-Yc*"

// GLOBAL: MSVC5_C1 0x000030c4
// ??_C@_03PFEF@?9Yu?$AA@
// "-Yu"

// GLOBAL: MSVC5_C1 0x000030c8
// ??_C@_04FMID@?9Yu?$CK?$AA@
// "-Yu*"

// GLOBAL: MSVC5_C1 0x000030d0
// ??_C@_0N@JJKJ@?9debugBreak?$CF?$AA@
// "-debugBreak%"

// GLOBAL: MSVC5_C1 0x000030e0
// ??_C@_03BGPH@?9Oy?$AA@
// "-Oy"

// GLOBAL: MSVC5_C1 0x000030e4
// ??_C@_03BHKK@?9Ov?$AA@
// "-Ov"

// GLOBAL: MSVC5_C1 0x000030e8
// ??_C@_03ECEP@?9Oq?$AA@
// "-Oq"

// GLOBAL: MSVC5_C1 0x000030ec
// ??_C@_03LNDN@?9Ow?$AA@
// "-Ow"

// GLOBAL: MSVC5_C1 0x000030f0
// ??_C@_03ECIE@?9Ot?$AA@
// "-Ot"

// GLOBAL: MSVC5_C1 0x000030f4
// ??_C@_03BHGB@?9Os?$AA@
// "-Os"

// GLOBAL: MSVC5_C1 0x000030f8
// ??_C@_03OINI@?9Op?$AA@
// "-Op"

// GLOBAL: MSVC5_C1 0x000030fc
// ??_C@_03BEEN@?9Og?$AA@
// "-Og"

// GLOBAL: MSVC5_C1 0x00003100
// ??_C@_03LPIH@?9Oi?$AA@
// "-Oi"

// GLOBAL: MSVC5_C1 0x00003104
// ??_C@_04GEEN@?9Ob?$CD?$AA@
// "-Ob#"

// GLOBAL: MSVC5_C1 0x0000310c
// ??_C@_03OLDP@?9Oa?$AA@
// "-Oa"

// GLOBAL: MSVC5_C1 0x00003110
// ??_C@_09CAAJ@?9cbstring?$AA@
// "-cbstring"

// GLOBAL: MSVC5_C1 0x0000311c
// ??_C@_03FJGO@?9GF?$AA@
// "-GF"

// GLOBAL: MSVC5_C1 0x00003120
// ??_C@_03LIO@?9Gf?$AA@
// "-Gf"

// GLOBAL: MSVC5_C1 0x00003124
// ??_C@_04KBJF@?9Fo?$CK?$AA@
// "-Fo*"

// GLOBAL: MSVC5_C1 0x0000312c
// ??_C@_04NBBB@?9Fd?$CD?$AA@
// "-Fd#"

// GLOBAL: MSVC5_C1 0x00003134
// ??_C@_04BJBF@?9FR?$CD?$AA@
// "-FR#"

// GLOBAL: MSVC5_C1 0x0000313c
// ??_C@_04MMEH@?9Fr?$CD?$AA@
// "-Fr#"

// GLOBAL: MSVC5_C1 0x00003144
// ??_C@_04NDAK@?9NV?$CD?$AA@
// "-NV#"

// GLOBAL: MSVC5_C1 0x0000314c
// ??_C@_03BKOK@?9FD?$AA@
// "-FD"

// GLOBAL: MSVC5_C1 0x00003150
// ??_C@_05JBM@?9GFR?9?$AA@
// "-GFR-"

// GLOBAL: MSVC5_C1 0x00003158
// ??_C@_04IPMH@?9GFR?$AA@
// "-GFR"

// GLOBAL: MSVC5_C1 0x00003160
// ??_C@_03FIDD@?9GI?$AA@
// "-GI"

// GLOBAL: MSVC5_C1 0x00003164
// ??_C@_03KND@?9Gi?$AA@
// "-Gi"

// GLOBAL: MSVC5_C1 0x00003168
// ??_C@_03FMBK@?9Gz?$AA@
// "-Gz"

// GLOBAL: MSVC5_C1 0x0000316c
// ??_C@_03FOKA@?9Gd?$AA@
// "-Gd"

// GLOBAL: MSVC5_C1 0x00003170
// ??_C@_03IKC@?9Gr?$AA@
// "-Gr"

// GLOBAL: MSVC5_C1 0x00003174
// ??_C@_03LEF@?9Gc?$AA@
// "-Gc"

// GLOBAL: MSVC5_C1 0x00003178
// ??_C@_03KCDF@?9Gs?$AA@
// "-Gs"

// GLOBAL: MSVC5_C1 0x0000317c
// ??_C@_03NCIG@?9V?$CD?$AA@
// "-V#"

// GLOBAL: MSVC5_C1 0x00003180
// ??_C@_03GALP@?9xc?$AA@
// "-xc"

// GLOBAL: MSVC5_C1 0x00003184
// ??_C@_04FNKB@?9il$?$AA@
// "-il$"

// GLOBAL: MSVC5_C1 0x0000318c
// ??_C@_04EIKK@?9ef?$CD?$AA@
// "-ef#"

// GLOBAL: MSVC5_C1 0x00003194
// ??_C@_03MDFH@?9Z?$CK?$AA@
// "-Z*"

// GLOBAL: MSVC5_C1 0x00003198
// ??_C@_04HEBG@?9ZB?$CK?$AA@
// "-ZB*"

// GLOBAL: MSVC5_C1 0x000031a0
// ??_C@_03GAMP@?9ZB?$AA@
// "-ZB"

// GLOBAL: MSVC5_C1 0x000031a4
// ??_C@_04NAIL@?9ZBe?$AA@
// "-ZBe"

// GLOBAL: MSVC5_C1 0x000031ac
// ??_C@_04BIJH@?9Zp?$CD?$AA@
// "-Zp#"

// GLOBAL: MSVC5_C1 0x000031b4
// ??_C@_03MOHB@?9Zp?$AA@
// "-Zp"

// GLOBAL: MSVC5_C1 0x000031b8
// ??_C@_03MECM@?9W?$CD?$AA@
// "-W#"

// GLOBAL: MSVC5_C1 0x000031bc
// ??_C@_03DBHN@?9WX?$AA@
// "-WX"

// GLOBAL: MSVC5_C1 0x000031c0
// ??_C@_03JEEB@?9MD?$AA@
// "-MD"

// GLOBAL: MSVC5_C1 0x000031c4
// ??_C@_03DNDB@?9MT?$AA@
// "-MT"

// GLOBAL: MSVC5_C1 0x000031c8
// ??_C@_07FIMM@?9Brepro?$AA@
// "-Brepro"

// GLOBAL: MSVC5_C1 0x000031d0
// ??_C@_04ILGK@?9Zm?$CD?$AA@
// "-Zm#"

// GLOBAL: MSVC5_C1 0x000031d8
// ??_C@_04DKLF@?9Bm?$CD?$AA@
// "-Bm#"

// GLOBAL: MSVC5_C1 0x000031e0
// ??_C@_04OFEI@?9Bu?$CD?$AA@
// "-Bu#"

// GLOBAL: MSVC5_C1 0x000031e8
// ??_C@_04GGDJ@?9Bd?$CF?$AA@
// "-Bd%"

// GLOBAL: MSVC5_C1 0x000031f0
// ??_C@_03KHPE@?9Jd?$AA@
// "-Jd"

// GLOBAL: MSVC5_C1 0x000031f4
// ??_C@_02IIFA@?9J?$AA@
// "-J"

// GLOBAL: MSVC5_C1 0x000031f8
// ??_C@_02CEFE@?9f?$AA@
// "-f"

// GLOBAL: MSVC5_C1 0x000031fc
// ??_C@_04CIEF@?9Fi?$CD?$AA@
// "-Fi#"

// GLOBAL: MSVC5_C1 0x00003204
// ??_C@_03CCDJ@?9EP?$AA@
// "-EP"

// GLOBAL: MSVC5_C1 0x00003208
// ??_C@_04PNBH@?9FI?$CD?$AA@
// "-FI#"

// GLOBAL: MSVC5_C1 0x00003210
// ??_C@_03GMCO@?9I?$CD?$AA@
// "-I#"

// GLOBAL: MSVC5_C1 0x00003214
// ??_C@_02IJAN@?9E?$AA@
// "-E"

// GLOBAL: MSVC5_C1 0x00003218
// ??_C@_03JFHK@?9D?$CD?$AA@
// "-D#"

// GLOBAL: MSVC5_C1 0x0000321c
// ??_C@_02HGHP@?9C?$AA@
// "-C"

// GLOBAL: MSVC5_C1 0x00003220
// ??_C@_03NFCA@?9pf?$AA@
// "-pf"

// GLOBAL: MSVC5_C1 0x00003224
// ??_C@_04DPIM@?9pc?$CD?$AA@
// "-pc#"

// GLOBAL: MSVC5_C1 0x0000322c
// ??_C@_04EDPG@?9FAT?$AA@
// "-FAT"

// GLOBAL: MSVC5_C1 0x00003234
// ??_C@_07BCFD@?9nologo?$AA@
// "-nologo"

// GLOBAL: MSVC5_C1 0x0000323c
// ??_C@_02FCBJ@?$EA$?$AA@
// "@$"

// GLOBAL: MSVC5_C1 0x00003240
// ??_C@_03NLLK@?4?4?2?$AA@
// "..\\"

// GLOBAL: MSVC5_C1 0x00003244
// ??_C@_01FKHJ@C?$AA@
// "C"

// GLOBAL: MSVC5_C1 0x00003248
// ?specWarnings@?1??InitSpecialWarnings@@YAXXZ@4PBUsWarn@@B
// struct sWarn const *`void __cdecl InitSpecialWarnings(void)'::`2'::specWarnings

// GLOBAL: MSVC5_C1 0x000032a0
// ??_C@_0O@MECB@MSC_CMD_FLAGS?$AA@
// "MSC_CMD_FLAGS"

// GLOBAL: MSVC5_C1 0x000032b0
// ??_C@_02MMAH@rt?$AA@
// "rt"

// GLOBAL: MSVC5_C1 0x00005c4c
// ?Cmd_DebugBreak@@3HA
// int Cmd_DebugBreak

// GLOBAL: MSVC5_C1 0x00005c50
// ?Argc@@3HA
// GLOBAL: C1 0x00467040
int Argc = 0;

// GLOBAL: MSVC5_C1 0x00005c54
// ?Argv@@3PAPADA
// GLOBAL: C1 0x00467044
char **Argv;

// GLOBAL: MSVC5_C1 0x00005c58
// ?DummyArg@@3PADA
// char *DummyArg

// FUNCTION: MSVC5_C1 0x00020b40
// ?nextword@@YAPADXZ
// char * __cdecl nextword(void)

// FUNCTION: MSVC5_C1 0x00020b70
// ?SzCanonFilename@canonFullPathHelperClass@@CAPADPAD@Z
// private: static char * __cdecl canonFullPathHelperClass::SzCanonFilename(char *)

// FUNCTION: MSVC5_C1 0x00020bc0
// ?SzCanonFullPath@@YAPADPADPBDI@Z
// char * __cdecl SzCanonFullPath(char *, char const *, unsigned int)

// FUNCTION: MSVC5_C1 0x00020d40
// ?szRelToPdb@@YAPADPBD@Z
// char * __cdecl szRelToPdb(char const *)

// FUNCTION: MSVC5_C1 0x00020df0
// ?relPath@@YAPADPAD00J@Z
// char * __cdecl relPath(char *, char *, char *, long)
// static

// FUNCTION: MSVC5_C1 0x00020ef0
// ?szStreamName@@YAPADPAD0@Z
// char * __cdecl szStreamName(char *, char *)

// FUNCTION: MSVC5_C1 0x00020f70
// ?init_main1@@YAXHPAPAD@Z
// C1: FUNCTION 0x0041b4b2
void init_main1(int argc, char **argv)
{
    NOT_IMPLEMENTED();
}

// FUNCTION: MSVC5_C1 0x00021420
// ?InitCanonCharMap@@YAXXZ
// void __cdecl InitCanonCharMap(void)
// static

