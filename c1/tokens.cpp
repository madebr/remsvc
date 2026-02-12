#include "tokens.h"

// GLOBAL: MSVC5_C1 0x00003a80
// ?Tokstrings_text@@3PBQBDB
// char const *const *Tokstrings_text

// GLOBAL: MSVC5_C1 0x00003e58
// ?Tokstrings_token@@3PBEB
// unsigned char const *Tokstrings_token

// GLOBAL: MSVC5_C1 0x00003f50
// ?Tokstrings_isHardToken@@3PBEB
const uint8_t Tokstrings_isHardToken[MAXTOKEN+1] = {
    0,  1,  1,  1,
    1,  1,  0,  0,
    0,  0,  0,  0,
    0,  0,  0,  1,
    1,  1,  1,  1,
    1,  1,  1,  1,
    1,  1,  1,  1,
    1,  1,  0,  1,
    1,  1,  1,  1,
    1,  0,  0,  0,
    0,  0,  0,  0,
    1,  1,  1,  0,
    1,  1,  1,  1,
    1,  0,  1,  1,
    1,  1,  1,  1,
    0,  1,  1,  1,
    1,  1,  1,  1,
    0,  1,  1,  1,
    1,  1,  1,  1,
    1,  1,  1,  1,
    1,  1,  1,  1,
    1,  1,  1,  1,
    1,  1,  1,  1,
    1,  1,  1,  1,
    1,  1,  1,  1,
    0,  1,  0,  0,
    0,  1,  1,  0,
    0,  1,  1,  0,
    1,  1,  1,  0,
    1,  0,  1,  0,
    1,  1,  0,  0,
    1,  1,  0,  0,
    1,  1,  1,  0,
    1,  1,  1,  0,
    1,  1,  0,  1,
    0,  1,  1,  1,
    1,  1,  1,  1,
    1,  0,  0,  1,
    0,  1,  1,  0,
    1,  0,  1,  0,
    0,  0,  0,  0,
    0,  0,  0,  0,
    0,  0,  0,  0,
    0,  0,  1,  1,
    1,  0,  0,  1,
    0,  1,  1,  1,
    1,  1,  1,  1,
    1,  0,  0,  1,
    1,  1,  0,  0,
    0,  1,  1,  1,
    1,  0,  0,  1,
    0,  0,  0,  0,
    0,  0,  1,  0,
    1,  0,  0,  1,
    1,  1,  1,  1,
    1,  1,  1,  1,
    0,  0,  0,  0,
    0,  0,  0,  0,
    0,  0,  1,  0,
    1,  0,  1,  1,
    1,  0,  0,  1,
    1,  1,  1,  0,
    0,  0,  0,  1,
    1,  0
};

// GLOBAL: MSVC5_C1 0x00004048
// ?Tokstrings_optype@@3PBIB
// unsigned int const *Tokstrings_optype

// GLOBAL: MSVC5_C1 0x00004420
// ?Tokstrings_mvalue@@3PBEB
// unsigned char const *Tokstrings_mvalue

// GLOBAL: MSVC5_C1 0x00004518
// ??_C@_0BE@KPIL@End?5of?5Token?5Stream?$AA@
// "End of Token Stream"

// GLOBAL: MSVC5_C1 0x0000452c
// ??_C@_0BB@GDGH@Disabled?5keyword?$AA@
// "Disabled keyword"

// GLOBAL: MSVC5_C1 0x00004540
// ??_C@_0BG@LLNN@CompileTime?5directive?$AA@
// "CompileTime directive"

// GLOBAL: MSVC5_C1 0x00004558
// ??_C@_0BA@MHKJ@?8?$DML_SUBSTREAM?$DO?8?$AA@
// "\'<L_SUBSTREAM>\'"

// GLOBAL: MSVC5_C1 0x00004568
// ??_C@_0M@JJOI@?$DMposition?$DO?6?$AA@
// "<position>\n"

// GLOBAL: MSVC5_C1 0x00004574
// ??_C@_0N@DDF@?$DML_PROPERTY?$DO?$AA@
// "<L_PROPERTY>"

// GLOBAL: MSVC5_C1 0x00004584
// ??_C@_0BA@EOKO@?$DML_GENERICTYPE?$DO?$AA@
// "<L_GENERICTYPE>"

// GLOBAL: MSVC5_C1 0x00004594
// ??_C@_0O@FLFP@?$DMtemplate?9id?$DO?$AA@
// "<template-id>"

// GLOBAL: MSVC5_C1 0x000045a4
// ??_C@_0P@HIIP@alignment?5cast?$AA@
// "alignment cast"

// GLOBAL: MSVC5_C1 0x000045b4
// ??_C@_0BE@BJOA@resolved?5identifier?$AA@
// "resolved identifier"

// GLOBAL: MSVC5_C1 0x000045c8
// ??_C@_0BH@OKHK@inline?5function?5header?$AA@
// "inline function header"

// GLOBAL: MSVC5_C1 0x000045e0
// ??_C@_0BD@CKKK@?8?$DML_TEMPLATEDECL?$DO?8?$AA@
// "\'<L_TEMPLATEDECL>\'"

// GLOBAL: MSVC5_C1 0x000045f4
// ??_C@_0BF@NMMJ@?8?$DML_TEMPLATEHEADER?$DO?8?$AA@
// "\'<L_TEMPLATEHEADER>\'"

// GLOBAL: MSVC5_C1 0x0000460c
// ??_C@_0O@GMLL@?8?$DML_FPSYM_T?$DO?8?$AA@
// "\'<L_FPSYM_T>\'"

// GLOBAL: MSVC5_C1 0x0000461c
// ??_C@_0L@BNEA@?8Class?5MF?8?$AA@
// "\'Class MF\'"

// GLOBAL: MSVC5_C1 0x00004628
// ??_C@_0BB@CAPO@default?5argument?$AA@
// "default argument"

// GLOBAL: MSVC5_C1 0x0000463c
// ??_C@_0BD@EKHH@?8?$DML_EHSTATESLIST?$DO?8?$AA@
// "\'<L_EHSTATESLIST>\'"

// GLOBAL: MSVC5_C1 0x00004650
// ??_C@_0BD@DOJN@?8?$DML_TEMPLATEDEFN?$DO?8?$AA@
// "\'<L_TEMPLATEDEFN>\'"

// GLOBAL: MSVC5_C1 0x00004664
// ??_C@_0BB@HKDN@?8?$DML_DTORACTION?$DO?8?$AA@
// "\'<L_DTORACTION>\'"

// GLOBAL: MSVC5_C1 0x00004678
// ??_C@_0P@DPMB@?8?$DML_POPSTATE?$DO?8?$AA@
// "\'<L_POPSTATE>\'"

// GLOBAL: MSVC5_C1 0x00004688
// ??_C@_0BA@EECO@?8?$DML_PUSHSTATE?$DO?8?$AA@
// "\'<L_PUSHSTATE>\'"

// GLOBAL: MSVC5_C1 0x00004698
// ??_C@_0M@KFJC@?8?$DML_ALIGN?$DO?8?$AA@
// "\'<L_ALIGN>\'"

// GLOBAL: MSVC5_C1 0x000046a4
// ??_C@_0M@JIBM@?8template?$DM?8?$AA@
// "\'template<\'"

// GLOBAL: MSVC5_C1 0x000046b0
// ??_C@_0BD@BBND@?8?$DML_TEMPLATEARGS?$DO?8?$AA@
// "\'<L_TEMPLATEARGS>\'"

// GLOBAL: MSVC5_C1 0x000046c4
// ??_C@_0CB@CNFD@List?5of?5keys?5in?5default?5arg?5tree@
// "List of keys in default arg tree"...

// GLOBAL: MSVC5_C1 0x000046e8
// ??_C@_0CI@NINA@List?5of?5destructors?5in?5default?5a@
// "List of destructors in default a"...

// GLOBAL: MSVC5_C1 0x00004710
// ??_C@_0CI@OKMB@Base?1member?5initializer?5destruct@
// "Base/member initializer destruct"...

// GLOBAL: MSVC5_C1 0x00004738
// ??_C@_0BG@ODLM@inheritance?9specifier?$AA@
// "inheritance-specifier"

// GLOBAL: MSVC5_C1 0x00004750
// ??_C@_0BA@BIHP@?$DMconstant?5tree?$DO?$AA@
// "<constant tree>"

// GLOBAL: MSVC5_C1 0x00004760
// ??_C@_06DDGG@symbol?$AA@
// "symbol"

// GLOBAL: MSVC5_C1 0x00004768
// ??_C@_0M@KMC@?$DMend?5Parse?$DO?$AA@
// "<end Parse>"

// GLOBAL: MSVC5_C1 0x00004774
// ??_C@_0P@OLPM@const?1volatile?$AA@
// "const/volatile"

// GLOBAL: MSVC5_C1 0x00004784
// ??_C@_0L@PJNA@?4candidate?$AA@
// ".candidate"

// GLOBAL: MSVC5_C1 0x00004790
// ??_C@_08NHAM@modifier?$AA@
// "modifier"

// GLOBAL: MSVC5_C1 0x0000479c
// ??_C@_08MPDI@?$DMtag?$DO?3?3?$CK?$AA@
// "<tag>::*"

// GLOBAL: MSVC5_C1 0x000047a8
// ??_C@_08MGKK@?$DMptradd?$DO?$AA@
// "<ptradd>"

// GLOBAL: MSVC5_C1 0x000047b4
// ??_C@_08MGCI@?$DMthunkx?$DO?$AA@
// "<thunkx>"

// GLOBAL: MSVC5_C1 0x000047c0
// ??_C@_0BA@PIOE@?$DMallocate?5temp?$DO?$AA@
// "<allocate temp>"

// GLOBAL: MSVC5_C1 0x000047d0
// ??_C@_0O@CANM@?$DMconstructor?$DO?$AA@
// "<constructor>"

// GLOBAL: MSVC5_C1 0x000047e0
// ??_C@_0BD@CFGK@?$DMvirtual?5function?$DO?$AA@
// "<virtual function>"

// GLOBAL: MSVC5_C1 0x000047f4
// ??_C@_0BC@KOJF@?$DMmember?5function?$DO?$AA@
// "<member function>"

// GLOBAL: MSVC5_C1 0x00004808
// ??_C@_0BE@GDJI@function?9style?5cast?$AA@
// "function-style cast"

// GLOBAL: MSVC5_C1 0x0000481c
// ??_C@_07EJHM@tag?3?3id?$AA@
// "tag::id"

// GLOBAL: MSVC5_C1 0x00004824
// ??_C@_02NNPM@?3?3?$AA@
// "::"

// GLOBAL: MSVC5_C1 0x00004828
// ??_C@_06NDDL@?4?$CK?$HM?9?$DO?$CK?$AA@
// ".*|->*"

// GLOBAL: MSVC5_C1 0x00004830
// ??_C@_03OGAK@?9?$DO?$CK?$AA@
// "->*"

// GLOBAL: MSVC5_C1 0x00004834
// ??_C@_02EEIP@?4?$CK?$AA@
// ".*"

// GLOBAL: MSVC5_C1 0x00004838
// ??_C@_0BD@DGJF@?$DMaccess?5specifier?$DO?$AA@
// "<access specifier>"

// GLOBAL: MSVC5_C1 0x0000484c
// ??_C@_0BI@NCHF@user?9defined?5conversion?$AA@
// "user-defined conversion"

// GLOBAL: MSVC5_C1 0x00004864
// ??_C@_0O@DBDK@operator?5?$DMop?$DO?$AA@
// "operator <op>"

// GLOBAL: MSVC5_C1 0x00004874
// ??_C@_0BI@GBPL@internal?5compiler?5token?$AA@
// "internal compiler token"

// GLOBAL: MSVC5_C1 0x0000488c
// ??_C@_0BG@LCFB@struct?1union?5operator?$AA@
// "struct/union operator"

// GLOBAL: MSVC5_C1 0x000048a4
// ??_C@_0P@GAHO@shift?5operator?$AA@
// "shift operator"

// GLOBAL: MSVC5_C1 0x000048b4
// ??_C@_01FAJB@?$DL?$AA@
// ";"

// GLOBAL: MSVC5_C1 0x000048b8
// ??_C@_0BE@BEDG@relational?5operator?$AA@
// "relational operator"

// GLOBAL: MSVC5_C1 0x000048cc
// ??_C@_01KCD@?$HN?$AA@
// "}"

// GLOBAL: MSVC5_C1 0x000048d0
// ??_C@_01FIMD@?$FN?$AA@
// "]"

// GLOBAL: MSVC5_C1 0x000048d4
// ??_C@_0BD@MCIF@left?9side?5modifier?$AA@
// "left-side modifier"

// GLOBAL: MSVC5_C1 0x000048e8
// ??_C@_09BOII@intrinsic?$AA@
// "intrinsic"

// GLOBAL: MSVC5_C1 0x000048f4
// ??_C@_01PFFB@?$HL?$AA@
// "{"

// GLOBAL: MSVC5_C1 0x000048f8
// ??_C@_0N@BHDD@initializing?$AA@
// "initializing"

// GLOBAL: MSVC5_C1 0x00004908
// ??_C@_0BD@CJGO@increment?5operator?$AA@
// "increment operator"

// GLOBAL: MSVC5_C1 0x0000491c
// ??_C@_08JJOG@function?$AA@
// "function"

// GLOBAL: MSVC5_C1 0x00004928
// ??_C@_0BC@BAIH@equality?5operator?$AA@
// "equality operator"

// GLOBAL: MSVC5_C1 0x0000493c
// ??_C@_05BAMO@entry?$AA@
// "entry"

// GLOBAL: MSVC5_C1 0x00004944
// ??_C@_0BC@IDL@division?5operator?$AA@
// "division operator"

// GLOBAL: MSVC5_C1 0x00004958
// ??_C@_08BNAC@constant?$AA@
// "constant"

// GLOBAL: MSVC5_C1 0x00004964
// ??_C@_09CIJM@type?5cast?$AA@
// "type cast"

// GLOBAL: MSVC5_C1 0x00004970
// ??_C@_0BE@MBML@assignment?5operator?$AA@
// "assignment operator"

// GLOBAL: MSVC5_C1 0x00004984
// ??_C@_08GOKM@argument?$AA@
// "argument"

// GLOBAL: MSVC5_C1 0x00004990
// ??_C@_05ECKK@deseg?$AA@
// "deseg"

// GLOBAL: MSVC5_C1 0x00004998
// ??_C@_02HHKA@?3?$DO?$AA@
// ":>"

// GLOBAL: MSVC5_C1 0x0000499c
// ??_C@_0BA@HCAL@based?5reference?$AA@
// "based reference"

// GLOBAL: MSVC5_C1 0x000049ac
// ??_C@_02KNEE@?$FO?$DN?$AA@
// "^="

// GLOBAL: MSVC5_C1 0x000049b0
// ??_C@_01KHHK@?$FO?$AA@
// "^"

// GLOBAL: MSVC5_C1 0x000049b4
// ??_C@_01PFJK@?$HO?$AA@
// "~"

// GLOBAL: MSVC5_C1 0x000049b8
// ??_C@_02CNAK@?$DO?$DO?$AA@
// ">>"

// GLOBAL: MSVC5_C1 0x000049bc
// ??_C@_03MNMO@?$DO?$DO?$DN?$AA@
// ">>="

// GLOBAL: MSVC5_C1 0x000049c0
// ??_C@_01PKMN@?$DP?$AA@
// "?"

// GLOBAL: MSVC5_C1 0x000049c4
// ??_C@_02HMFM@?9?$DO?$AA@
// "->"

// GLOBAL: MSVC5_C1 0x000049c8
// ??_C@_02PEBK@?$CL?$DN?$AA@
// "+="

// GLOBAL: MSVC5_C1 0x000049cc
// ??_C@_01PJOB@?$CL?$AA@
// "+"

// GLOBAL: MSVC5_C1 0x000049d0
// ??_C@_01PJCK@?4?$AA@
// "."

// GLOBAL: MSVC5_C1 0x000049d4
// ??_C@_02FKBE@?$HM?$HM?$AA@
// "||"

// GLOBAL: MSVC5_C1 0x000049d8
// ??_C@_02FFED@?$HM?$DN?$AA@
// "|="

// GLOBAL: MSVC5_C1 0x000049dc
// ??_C@_01KALE@?$HM?$AA@
// "|"

// GLOBAL: MSVC5_C1 0x000049e0
// ??_C@_02GMBL@?$CB?$DN?$AA@
// "!="

// GLOBAL: MSVC5_C1 0x000049e4
// ??_C@_02OCLA@?$CK?$DN?$AA@
// "*="

// GLOBAL: MSVC5_C1 0x000049e8
// ??_C@_02DGLB@?$CF?$DN?$AA@
// "%="

// GLOBAL: MSVC5_C1 0x000049ec
// ??_C@_01FCCL@?$CF?$AA@
// "%"

// GLOBAL: MSVC5_C1 0x000049f0
// ??_C@_02IDOF@?9?$DN?$AA@
// "-="

// GLOBAL: MSVC5_C1 0x000049f4
// ??_C@_01GJD@?9?$AA@
// "-"

// GLOBAL: MSVC5_C1 0x000049f8
// ??_C@_02PPOG@?$DM?$DN?$AA@
// "<="

// GLOBAL: MSVC5_C1 0x000049fc
// ??_C@_02FFHB@?$DM?$DM?$AA@
// "<<"

// GLOBAL: MSVC5_C1 0x00004a00
// ??_C@_03EELG@?$DM?$DM?$DN?$AA@
// "<<="

// GLOBAL: MSVC5_C1 0x00004a04
// ??_C@_01KHLB@?$FL?$AA@
// "["

// GLOBAL: MSVC5_C1 0x00004a08
// ??_C@_02KCBI@?$CL?$CL?$AA@
// "++"

// GLOBAL: MSVC5_C1 0x00004a0c
// ??_C@_02NCLD@?$DO?$DN?$AA@
// ">="

// GLOBAL: MSVC5_C1 0x00004a10
// ??_C@_01PIHH@?$CB?$AA@
// "!"

// GLOBAL: MSVC5_C1 0x00004a14
// ??_C@_02OJEM@?$DN?$DN?$AA@
// "=="

// GLOBAL: MSVC5_C1 0x00004a18
// ??_C@_02KOLA@?1?$DN?$AA@
// "/="

// GLOBAL: MSVC5_C1 0x00004a1c
// ??_C@_01FDLN@?1?$AA@
// "/"

// GLOBAL: MSVC5_C1 0x00004a20
// ??_C@_02CKJF@?9?9?$AA@
// "--"

// GLOBAL: MSVC5_C1 0x00004a24
// ??_C@_01PKAG@?3?$AA@
// ":"

// GLOBAL: MSVC5_C1 0x00004a28
// ??_C@_09OEAF@bit?5field?$AA@
// "bit field"

// GLOBAL: MSVC5_C1 0x00004a34
// ??_C@_01KPOD@?$DN?$AA@
// "="

// GLOBAL: MSVC5_C1 0x00004a38
// ??_C@_02NEO@?$CG?$DN?$AA@
// "&="

// GLOBAL: MSVC5_C1 0x00004a3c
// ??_C@_02PDP@?$CG?$CG?$AA@
// "&&"

// GLOBAL: MSVC5_C1 0x00004a40
// ??_C@_01KNJC@?$CG?$AA@
// "&"

// GLOBAL: MSVC5_C1 0x00004a44
// ??_C@_0BL@MDGP@hidden?5udt?5return?5argument?$AA@
// "hidden udt return argument"

// GLOBAL: MSVC5_C1 0x00004a60
// ??_C@_0L@IHLI@asm?5string?$AA@
// "asm string"

// GLOBAL: MSVC5_C1 0x00004a6c
// ??_C@_0BH@GKEH@inline?5trap?5definition?$AA@
// "inline trap definition"

// GLOBAL: MSVC5_C1 0x00004a84
// ??_C@_0BE@PIMP@right?9side?5modifier?$AA@
// "right-side modifier"

// GLOBAL: MSVC5_C1 0x00004a98
// ??_C@_04PIKN@type?$AA@
// "type"

// GLOBAL: MSVC5_C1 0x00004aa0
// ??_C@_0L@DMLB@enum?5?$FLtag?$FN?$AA@
// "enum [tag]"

// GLOBAL: MSVC5_C1 0x00004aac
// ??_C@_0N@OHIO@?$DMclass?9head?$DO?$AA@
// "<class-head>"

// GLOBAL: MSVC5_C1 0x00004abc
// ??_C@_0BD@FJFD@?$DMstorage?5modifier?$DO?$AA@
// "<storage modifier>"

// GLOBAL: MSVC5_C1 0x00004ad0
// ??_C@_0BA@GFDN@?$DMstorage?5class?$DO?$AA@
// "<storage class>"

// GLOBAL: MSVC5_C1 0x00004ae0
// ??_C@_06LLCF@?$DMtype?$DO?$AA@
// "<type>"

// GLOBAL: MSVC5_C1 0x00004ae8
// ??_C@_0M@BAG@?$DMtype?5name?$DO?$AA@
// "<type name>"

// GLOBAL: MSVC5_C1 0x00004af4
// ??_C@_06EMNG@string?$AA@
// "string"

// GLOBAL: MSVC5_C1 0x00004afc
// ??_C@_0L@MJMK@identifier?$AA@
// "identifier"

// GLOBAL: MSVC5_C1 0x00004b08
// ??_C@_0M@BPOL@end?5of?5file?$AA@
// "end of file"

// GLOBAL: MSVC5_C1 0x00004b14
// ??_C@_0BD@GPGA@PCH?5creation?5point?$AA@
// "PCH creation point"

// GLOBAL: MSVC5_C1 0x00004b28
// ??_C@_0CB@DPGH@?$CDline?5directive?5for?5PCH?5creation@
// "#line directive for PCH creation"...

// GLOBAL: MSVC5_C1 0x00004b4c
// ??_C@_0BA@IEIF@?$CDpragma?5hdrstop?$AA@
// "#pragma hdrstop"

// GLOBAL: MSVC5_C1 0x00004b5c
// ??_C@_07JKAE@newline?$AA@
// "newline"

