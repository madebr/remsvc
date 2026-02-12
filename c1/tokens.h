#ifndef TOKENS_H
#define TOKENS_H

#include "token.h"

#include <stdint.h>

// ?Tokstrings_text@@3PBQBDB
// char const *const *Tokstrings_text

// ?Tokstrings_token@@3PBEB
// unsigned char const *Tokstrings_token

// ?Tokstrings_isHardToken@@3PBEB
extern const uint8_t Tokstrings_isHardToken[MAXTOKEN+1];

// ?Tokstrings_optype@@3PBIB
// unsigned int const *Tokstrings_optype

// ?Tokstrings_mvalue@@3PBEB
// unsigned char const *Tokstrings_mvalue

// ??_C@_0BE@KPIL@End?5of?5Token?5Stream?$AA@
// "End of Token Stream"

// ??_C@_0BB@GDGH@Disabled?5keyword?$AA@
// "Disabled keyword"

// ??_C@_0BG@LLNN@CompileTime?5directive?$AA@
// "CompileTime directive"

// ??_C@_0BA@MHKJ@?8?$DML_SUBSTREAM?$DO?8?$AA@
// "\'<L_SUBSTREAM>\'"

// ??_C@_0M@JJOI@?$DMposition?$DO?6?$AA@
// "<position>\n"

// ??_C@_0N@DDF@?$DML_PROPERTY?$DO?$AA@
// "<L_PROPERTY>"

// ??_C@_0BA@EOKO@?$DML_GENERICTYPE?$DO?$AA@
// "<L_GENERICTYPE>"

// ??_C@_0O@FLFP@?$DMtemplate?9id?$DO?$AA@
// "<template-id>"

// ??_C@_0P@HIIP@alignment?5cast?$AA@
// "alignment cast"

// ??_C@_0BE@BJOA@resolved?5identifier?$AA@
// "resolved identifier"

// ??_C@_0BH@OKHK@inline?5function?5header?$AA@
// "inline function header"

// ??_C@_0BD@CKKK@?8?$DML_TEMPLATEDECL?$DO?8?$AA@
// "\'<L_TEMPLATEDECL>\'"

// ??_C@_0BF@NMMJ@?8?$DML_TEMPLATEHEADER?$DO?8?$AA@
// "\'<L_TEMPLATEHEADER>\'"

// ??_C@_0O@GMLL@?8?$DML_FPSYM_T?$DO?8?$AA@
// "\'<L_FPSYM_T>\'"

// ??_C@_0L@BNEA@?8Class?5MF?8?$AA@
// "\'Class MF\'"

// ??_C@_0BB@CAPO@default?5argument?$AA@
// "default argument"

// ??_C@_0BD@EKHH@?8?$DML_EHSTATESLIST?$DO?8?$AA@
// "\'<L_EHSTATESLIST>\'"

// ??_C@_0BD@DOJN@?8?$DML_TEMPLATEDEFN?$DO?8?$AA@
// "\'<L_TEMPLATEDEFN>\'"

// ??_C@_0BB@HKDN@?8?$DML_DTORACTION?$DO?8?$AA@
// "\'<L_DTORACTION>\'"

// ??_C@_0P@DPMB@?8?$DML_POPSTATE?$DO?8?$AA@
// "\'<L_POPSTATE>\'"

// ??_C@_0BA@EECO@?8?$DML_PUSHSTATE?$DO?8?$AA@
// "\'<L_PUSHSTATE>\'"

// ??_C@_0M@KFJC@?8?$DML_ALIGN?$DO?8?$AA@
// "\'<L_ALIGN>\'"

// ??_C@_0M@JIBM@?8template?$DM?8?$AA@
// "\'template<\'"

// ??_C@_0BD@BBND@?8?$DML_TEMPLATEARGS?$DO?8?$AA@
// "\'<L_TEMPLATEARGS>\'"

// ??_C@_0CB@CNFD@List?5of?5keys?5in?5default?5arg?5tree@
// "List of keys in default arg tree"...

// ??_C@_0CI@NINA@List?5of?5destructors?5in?5default?5a@
// "List of destructors in default a"...

// ??_C@_0CI@OKMB@Base?1member?5initializer?5destruct@
// "Base/member initializer destruct"...

// ??_C@_0BG@ODLM@inheritance?9specifier?$AA@
// "inheritance-specifier"

// ??_C@_0BA@BIHP@?$DMconstant?5tree?$DO?$AA@
// "<constant tree>"

// ??_C@_06DDGG@symbol?$AA@
// "symbol"

// ??_C@_0M@KMC@?$DMend?5Parse?$DO?$AA@
// "<end Parse>"

// ??_C@_0P@OLPM@const?1volatile?$AA@
// "const/volatile"

// ??_C@_0L@PJNA@?4candidate?$AA@
// ".candidate"

// ??_C@_08NHAM@modifier?$AA@
// "modifier"

// ??_C@_08MPDI@?$DMtag?$DO?3?3?$CK?$AA@
// "<tag>::*"

// ??_C@_08MGKK@?$DMptradd?$DO?$AA@
// "<ptradd>"

// ??_C@_08MGCI@?$DMthunkx?$DO?$AA@
// "<thunkx>"

// ??_C@_0BA@PIOE@?$DMallocate?5temp?$DO?$AA@
// "<allocate temp>"

// ??_C@_0O@CANM@?$DMconstructor?$DO?$AA@
// "<constructor>"

// ??_C@_0BD@CFGK@?$DMvirtual?5function?$DO?$AA@
// "<virtual function>"

// ??_C@_0BC@KOJF@?$DMmember?5function?$DO?$AA@
// "<member function>"

// ??_C@_0BE@GDJI@function?9style?5cast?$AA@
// "function-style cast"

// ??_C@_07EJHM@tag?3?3id?$AA@
// "tag::id"

// ??_C@_02NNPM@?3?3?$AA@
// "::"

// ??_C@_06NDDL@?4?$CK?$HM?9?$DO?$CK?$AA@
// ".*|->*"

// ??_C@_03OGAK@?9?$DO?$CK?$AA@
// "->*"

// ??_C@_02EEIP@?4?$CK?$AA@
// ".*"

// ??_C@_0BD@DGJF@?$DMaccess?5specifier?$DO?$AA@
// "<access specifier>"

// ??_C@_0BI@NCHF@user?9defined?5conversion?$AA@
// "user-defined conversion"

// ??_C@_0O@DBDK@operator?5?$DMop?$DO?$AA@
// "operator <op>"

// ??_C@_0BI@GBPL@internal?5compiler?5token?$AA@
// "internal compiler token"

// ??_C@_0BG@LCFB@struct?1union?5operator?$AA@
// "struct/union operator"

// ??_C@_0P@GAHO@shift?5operator?$AA@
// "shift operator"

// ??_C@_01FAJB@?$DL?$AA@
// ";"

// ??_C@_0BE@BEDG@relational?5operator?$AA@
// "relational operator"

// ??_C@_01KCD@?$HN?$AA@
// "}"

// ??_C@_01FIMD@?$FN?$AA@
// "]"

// ??_C@_0BD@MCIF@left?9side?5modifier?$AA@
// "left-side modifier"

// ??_C@_09BOII@intrinsic?$AA@
// "intrinsic"

// ??_C@_01PFFB@?$HL?$AA@
// "{"

// ??_C@_0N@BHDD@initializing?$AA@
// "initializing"

// ??_C@_0BD@CJGO@increment?5operator?$AA@
// "increment operator"

// ??_C@_08JJOG@function?$AA@
// "function"

// ??_C@_0BC@BAIH@equality?5operator?$AA@
// "equality operator"

// ??_C@_05BAMO@entry?$AA@
// "entry"

// ??_C@_0BC@IDL@division?5operator?$AA@
// "division operator"

// ??_C@_08BNAC@constant?$AA@
// "constant"

// ??_C@_09CIJM@type?5cast?$AA@
// "type cast"

// ??_C@_0BE@MBML@assignment?5operator?$AA@
// "assignment operator"

// ??_C@_08GOKM@argument?$AA@
// "argument"

// ??_C@_05ECKK@deseg?$AA@
// "deseg"

// ??_C@_02HHKA@?3?$DO?$AA@
// ":>"

// ??_C@_0BA@HCAL@based?5reference?$AA@
// "based reference"

// ??_C@_02KNEE@?$FO?$DN?$AA@
// "^="

// ??_C@_01KHHK@?$FO?$AA@
// "^"

// ??_C@_01PFJK@?$HO?$AA@
// "~"

// ??_C@_02CNAK@?$DO?$DO?$AA@
// ">>"

// ??_C@_03MNMO@?$DO?$DO?$DN?$AA@
// ">>="

// ??_C@_01PKMN@?$DP?$AA@
// "?"

// ??_C@_02HMFM@?9?$DO?$AA@
// "->"

// ??_C@_02PEBK@?$CL?$DN?$AA@
// "+="

// ??_C@_01PJOB@?$CL?$AA@
// "+"

// ??_C@_01PJCK@?4?$AA@
// "."

// ??_C@_02FKBE@?$HM?$HM?$AA@
// "||"

// ??_C@_02FFED@?$HM?$DN?$AA@
// "|="

// ??_C@_01KALE@?$HM?$AA@
// "|"

// ??_C@_02GMBL@?$CB?$DN?$AA@
// "!="

// ??_C@_02OCLA@?$CK?$DN?$AA@
// "*="

// ??_C@_02DGLB@?$CF?$DN?$AA@
// "%="

// ??_C@_01FCCL@?$CF?$AA@
// "%"

// ??_C@_02IDOF@?9?$DN?$AA@
// "-="

// ??_C@_01GJD@?9?$AA@
// "-"

// ??_C@_02PPOG@?$DM?$DN?$AA@
// "<="

// ??_C@_02FFHB@?$DM?$DM?$AA@
// "<<"

// ??_C@_03EELG@?$DM?$DM?$DN?$AA@
// "<<="

// ??_C@_01KHLB@?$FL?$AA@
// "["

// ??_C@_02KCBI@?$CL?$CL?$AA@
// "++"

// ??_C@_02NCLD@?$DO?$DN?$AA@
// ">="

// ??_C@_01PIHH@?$CB?$AA@
// "!"

// ??_C@_02OJEM@?$DN?$DN?$AA@
// "=="

// ??_C@_02KOLA@?1?$DN?$AA@
// "/="

// ??_C@_01FDLN@?1?$AA@
// "/"

// ??_C@_02CKJF@?9?9?$AA@
// "--"

// ??_C@_01PKAG@?3?$AA@
// ":"

// ??_C@_09OEAF@bit?5field?$AA@
// "bit field"

// ??_C@_01KPOD@?$DN?$AA@
// "="

// ??_C@_02NEO@?$CG?$DN?$AA@
// "&="

// ??_C@_02PDP@?$CG?$CG?$AA@
// "&&"

// ??_C@_01KNJC@?$CG?$AA@
// "&"

// ??_C@_0BL@MDGP@hidden?5udt?5return?5argument?$AA@
// "hidden udt return argument"

// ??_C@_0L@IHLI@asm?5string?$AA@
// "asm string"

// ??_C@_0BH@GKEH@inline?5trap?5definition?$AA@
// "inline trap definition"

// ??_C@_0BE@PIMP@right?9side?5modifier?$AA@
// "right-side modifier"

// ??_C@_04PIKN@type?$AA@
// "type"

// ??_C@_0L@DMLB@enum?5?$FLtag?$FN?$AA@
// "enum [tag]"

// ??_C@_0N@OHIO@?$DMclass?9head?$DO?$AA@
// "<class-head>"

// ??_C@_0BD@FJFD@?$DMstorage?5modifier?$DO?$AA@
// "<storage modifier>"

// ??_C@_0BA@GFDN@?$DMstorage?5class?$DO?$AA@
// "<storage class>"

// ??_C@_06LLCF@?$DMtype?$DO?$AA@
// "<type>"

// ??_C@_0M@BAG@?$DMtype?5name?$DO?$AA@
// "<type name>"

// ??_C@_06EMNG@string?$AA@
// "string"

// ??_C@_0L@MJMK@identifier?$AA@
// "identifier"

// ??_C@_0M@BPOL@end?5of?5file?$AA@
// "end of file"

// ??_C@_0BD@GPGA@PCH?5creation?5point?$AA@
// "PCH creation point"

// ??_C@_0CB@DPGH@?$CDline?5directive?5for?5PCH?5creation@
// "#line directive for PCH creation"...

// ??_C@_0BA@IEIF@?$CDpragma?5hdrstop?$AA@
// "#pragma hdrstop"

// ??_C@_07JKAE@newline?$AA@
// "newline"

#endif /* TOKENS_H */
