#ifndef GLOBALS_H
#define GLOBALS_H

#include "c1_types.h"
#include "crc32.h"
#include "decomp.h"
#include "getflags.h"
#include "list.h"
#include "pdbmgr.h"

typedef struct {
    //uint LexIdentifier:1;
    //uint LexBaseClasses:1;
    //uint InAUDC:1;
    //uint ChooseTypeName:1;
    //uint InAnInitRegion:1;
    //uint ParsingExplicitDtor:1;
    //uint InAMemberFunction:1;
    //uint InlineParsing:1;
    //uint InLexerResolveIdentifier:1;
    //uint InComment:1;
    //uint InMacroActuals:1;
    //uint InInclude:1;
    //uint InIf:1;
    //uint OnPoundLine:1;
    //uint InFuncBody:1;
    //uint NeedEndData:1;
    //uint ClassKeyWasSeen:1;
    //uint CalculatingSkipToZeroOut:1;
    //uint ExpressionInit:1;
    //uint InAsm:1;
    //uint SkippedNewLine:1;
    //uint SkipFunction:1;
    //uint DefaultTypeUsed:1;
    //uint WithinFilter:1;
    //uint SpecialMemberFunctions:1;
    //uint LexFromTokenBuffer:1;
    //uint LexFillTokenBuffer:1;
    //uint LexFromDeclarationParser:1;
    //uint LexDeclarationOnly:1;
    //uint UserExplicitCast:1;
    //uint DefaultTypeIsForced:1;
    //uint UserSpecifiedUnaryAnd:1;
    //uint LexerInOperator:1;
    //uint NonCurlyLinkageSpec:1;
    //uint OldStyleFunction:1;
    //uint FinishedUserSource:1;
    //uint InBaseMemberInitList:1;
    //uint DisableYYerror:1;
    //uint ReturnStmtWasUsed:1;
    //uint InForcedInstantiation:1;
    //uint DoNotUpdateDefArgList:1;
    //uint CFlow_BuildingPendingUnwinds:1;
    //uint SilentCompile:1;
    //uint SkippingPCH:1;
    //uint InExplicitDtorCall:1;
    //uint NeedSbrEndBlk:1;
    //uint BrowserReferenceDisabled:1;
    //uint CansiSeenEnumDefn:1;
    //uint InitTypesLoaded:1;
    //uint ExternalDefinitionSeen:1;
    //uint CapturingTokenStream:1;
    //uint WrapTreesWithPushState:1;
    //uint LexIdentifierDisambig:1;
    //uint SuppressInitIl:1;
    //uint SkippingPersPchForHdrstop:1;
    //uint PreParsingClassTemplate:1;
    //uint PreParsingTemplateDecl:1;
    //uint SkipTemplateArguments:1;
    //uint ExpectingTemplateTemplateParameter:1;
    //uint ExpectError:1;
    //uint DoNotEncodeManagedness:1;
    //uint WorthlessAssumeExpression:1;
    //uint StoilingGlobalSymbols:1;
    //uint RecordInitExprTree:1;
    //uint FullExpressionSeen:1;
    //uint ParsingPMFForDelegate:1;
    //uint SuppressCXXPointerModOpt:1;
    //uint ParsingGenericArglist:1;
    //uint DeferConstraintChecks:1;
    //uint ProcessingMetaDataFile:1;
    //uint ParsingConstraints:1;
    //uint GatheringPragma:1;
    //uint InAttributeArglist:1;
    //uint ParsingAttributeBlock:1;
    //uint DeferTreeEmission:1;
    //uint ParsingInitTypes:1;
    //uint UserSpecifiedUnaryPercent:1;
    unsigned int field_0x0_bit0 : 1;
    unsigned int field_0x0_bit1 : 1;
    unsigned int field_0x0_bit2 : 1;
    unsigned int field_0x0_bit3 : 1;
    unsigned int field_0x0_bit4 : 1;
    unsigned int field_0x0_bit5 : 1;
    unsigned int field_0x0_bit6 : 1;
    unsigned int field_0x0_bit7 : 1;
    unsigned int field_0x0_bit8 : 1;
    unsigned int field_0x0_bit9 : 1;
    unsigned int field_0x0_bit10 : 1;
    unsigned int field_0x0_bit11 : 1;
    unsigned int field_0x0_bit12 : 1;
    unsigned int field_0x0_bit13 : 1;
    unsigned int field_0x0_bit14 : 1;
    unsigned int field_0x0_bit15 : 1;
    unsigned int field_0x0_bit16 : 1;
    unsigned int field_0x0_bit17 : 1;
    unsigned int field_0x0_bit18 : 1;
    unsigned int field_0x0_bit19 : 1;
    unsigned int field_0x0_bit20 : 1;
    unsigned int field_0x0_bit21 : 1;
    unsigned int field_0x0_bit22 : 1;
    unsigned int field_0x0_bit23 : 1;
    unsigned int field_0x0_bit24 : 1;
    unsigned int field_0x0_bit25 : 1;
    unsigned int field_0x0_bit26 : 1;
    unsigned int field_0x0_bit27 : 1;
    unsigned int field_0x0_bit28 : 1;
    unsigned int field_0x0_bit29 : 1;
    unsigned int field_0x0_bit30 : 1;
    unsigned int field_0x0_bit31 : 1;
    unsigned int field_0x4_bit0 : 1;
    unsigned int field_0x4_bit1 : 1;
    unsigned int field_0x4_bit2 : 1;
    unsigned int field_0x4_bit3 : 1;
    unsigned int field_0x4_bit4 : 1;
    unsigned int field_0x4_bit5 : 1;
    unsigned int field_0x4_bit6 : 1;
    unsigned int field_0x4_bit7 : 1;
    unsigned int field_0x4_bit8 : 1;
    unsigned int field_0x4_bit9 : 1;
    unsigned int field_0x4_bit10 : 1;
    unsigned int field_0x4_bit11 : 1;
    unsigned int field_0x4_bit12 : 1;
    unsigned int field_0x4_bit13 : 1;
    unsigned int field_0x4_bit14 : 1;
    unsigned int field_0x4_bit15 : 1;
    unsigned int field_0x4_bit16 : 1;
    unsigned int field_0x4_bit17 : 1;
    unsigned int field_0x4_bit18 : 1;
    unsigned int field_0x4_bit19 : 1;
    unsigned int field_0x4_bit20 : 1;
    unsigned int field_0x4_bit21 : 1;
    unsigned int field_0x4_bit22 : 1;
    unsigned int field_0x4_bit23 : 1;
    unsigned int field_0x4_bit24 : 1;
    unsigned int field_0x4_bit25 : 1;
    unsigned int field_0x4_bit26 : 1;
    unsigned int field_0x4_bit27 : 1;
    unsigned int field_0x4_bit28 : 1;
    unsigned int field_0x4_bit29 : 1;
    unsigned int field_0x4_bit30 : 1;
    unsigned int field_0x4_bit31 : 1;
    unsigned int field_0x8_bit0 : 1;
    unsigned int field_0x8_bit1 : 1;
    unsigned int field_0x8_bit2 : 1;
    unsigned int field_0x8_bit3 : 1;
    unsigned int field_0x8_bit4 : 1;
    unsigned int field_0x8_bit5 : 1;
    unsigned int field_0x8_bit6 : 1;
    unsigned int field_0x8_bit7 : 1;
    unsigned int field_0x8_bit8 : 1;
    unsigned int field_0x8_bit9 : 1;
    unsigned int field_0x8_bit10 : 1;
    unsigned int field_0x8_bit11 : 1;
    unsigned int field_0x8_bit12 : 1;
    unsigned int field_0x8_bit13 : 1;
    unsigned int field_0x8_bit14 : 1;
    unsigned int field_0x8_bit15 : 1;
    unsigned int field_0x8_bit16 : 1;
    unsigned int field_0x8_bit17 : 1;
    unsigned int field_0x8_bit18 : 1;
    unsigned int field_0x8_bit19 : 1;
    unsigned int field_0x8_bit20 : 1;
    unsigned int field_0x8_bit21 : 1;
    unsigned int field_0x8_bit22 : 1;
    unsigned int field_0x8_bit23 : 1;
    unsigned int field_0x8_bit24 : 1;
    unsigned int field_0x8_bit25 : 1;
    unsigned int field_0x8_bit26 : 1;
    unsigned int field_0x8_bit27 : 1;
    unsigned int field_0x8_bit28 : 1;
    unsigned int field_0x8_bit29 : 1;
    unsigned int field_0x8_bit30 : 1;
    unsigned int field_0x8_bit31 : 1;
} ParseFlags_t;

typedef struct PchC_s {
    // int p_SizeOfBigInt;
    // bool p_Extension;
    // bool p_Cmd_conformForScope;
    // bool p_Cmd_conformNameDec;
    // bool p_BigIntExtension;
    // bool p_Jflag;
    // bool p_OptFlgBestPM;
    // bool p_OptFlgGenPM;
    // bool p_OptFlgPMSI;
    // bool p_OptFlgPMMI;
    // bool p_OptFlgPMVI;
    // int p_OptFlgVtorDisp;
    bool32 p_Symbolic_debug_holder;
    bool32 p_PchDFlag;
    // ushort p_ObjNamSize;
    // ushort p_SbrNamSize;
    // bool p_NoPoundLines;
    bool32 p_option_Bd;
    // bool p_fReproduceable;
    // bool p_Feedback;
    // bool p_Cmd_intrinsic;
    // bool p_Cmd_stack_check;
    // bool p_GpFlg;
    // int p_GpVal;
    // bool p_Cmd_cdecl;
    // bool p_Cmd_stdcall;
    // bool p_Cmd_fastcall;
    bool32 p_Cmd_Jd;
    // bool p_Cmd_ROStrPool;
    // bool p_ROStringPool;
    // bool p_CodeBasedStrings;
    // uint p_Cmd_processor;
    // bool p_SourceBrowser;
    // bool p_SourceBrowserExtended;
    // ulong p_SavePragStat;
    // bool p_ForceDataToThread;
    // bool p_Cmd_GS;
    // bool p_Cmd_Managed;
    // bool p_Cmd_ManagedOldSyntax_holder;
    // bool p_Cmd_ManagedNewSyntax_holder;
    // bool p_Cmd_Verifiable;
    // bool p_Cmd_PureMSIL_holder;
    // bool p_Cmd_SkipCorSystemDirectory;
    // bool p_Cmd_NoImplicitMSCorLib;
    // bool p_Cmd_NoPureCRT;
    // bool p_Cmd_NoPoundDefineWhitespaceKeyword;
    // bool p_Cmd_IDEIncludes;
    // bool p_Cmd_MinRebuild;
    // bool p_Stack_check;
    // bool p_Cmd_PMasMB;
    // bool p_Cmd_FpExcept;
    // bool p_Cmd_FpFast;
    // bool p_Cmd_FpStrict;
    // bool p_FenvAccess;
    // bool p_FpContract;
    // bool p_OptFlgSpeed;
    // bool p_OptFlgGlobCse;
    // bool p_OptFlgFrame;
    bool32 p_FUseTypeServer;
    char p_FdName[256];
    char p_szYlstring[256];
    // char p_szPchHeaderFile[778];
    // struct PDBSIG p_PchTPISig;
    // struct PDBSIG p_PchIDBSig;
    bool32 p_Cmd_C9IL;
    bool32 p_Cmd_fICC;
    // bool p_Cmd_fICCForceParseAll;
    // bool p_Cmd_fICCGLValidate;
    bool32 p_Cmd_fICCBrowse;
    // bool p_fWarnPort64;
    // bool p_fNoDefaultLib;
    // int p_Warn_level;
    // bool p_WarnAll;
    // uint p_CounterVar;
    // bool p_fLTCG;
    // bool p_fNewPTMAlign;
    // bool p_fNewReturnUDT;
    // bool p_fNewVxptrAlign;
    // bool p_fNewRiscFastcallDecoration;
    // bool p_fNewPtr64Decoration;
    // bool p_fNewUnalignedDecoration;
    // bool p_fNewConstDecoration;
    // bool p_fNewArrayDecoration;
    // bool p_fTlssupport;
    // int p_Cmd_pack_size;
    // int p_Cmd_Zm;
    // bool p_Cmd_ShowContinuationNumbers;
    // bool p_Cmd_Import_No_Registry;
    // bool p_Cmd_Import_No_Path;
    bool32 p_Cmd_splitPdbs;
} PchC_t;

typedef struct {
    // struct Symbol_t *p_AsmDollarSign;
    // struct Symbol_t *p_AsmLocalSize;
    // struct DefdFuncsCluster_t *p_DefdFuncsHead;
    // struct DefdFuncsCluster_t *p_DefdFuncsTail;
    // struct DictionaryNoMoveToFront<Symbol_t_*,long,DictionaryBucket<Symbol_t_*,long,&bool___fastcall_BucketEq<Symbol_t_*>(Symbol_t_*,Symbol_t_*),&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)>,&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)> *p_dictInitPchOffset;
    // struct DictionaryNoMoveToFront<Symbol_t_*,unsigned_long,DictionaryBucket<Symbol_t_*,unsigned_long,&bool___fastcall_BucketEq<Symbol_t_*>(Symbol_t_*,Symbol_t_*),&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)>,&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)> *p_dictExtraSize;
    // struct s_defn **p_Defn_level_0;
    // struct Type_t *p_Enum_head;
    // struct FlistEntry_t **p_Flist_table;
    // struct Id_t **p_IdTable;
    // struct IndirEntry_t **p_Indir_table;
    // struct s_StackOfPragmaItem_t *p_pPackStack;
    // struct s_StackOfPragmaItem_t *p_pConformStack;
    // struct s_StackOfPragmaItem_t *p_pManagedStack;
    // struct s_StackOfPragmaItem_t *p_pDataSegStack;
    // struct s_StackOfPragmaItem_t *p_pCodeSegStack;
    // struct s_StackOfPragmaItem_t *p_pBssSegStack;
    // struct s_StackOfPragmaItem_t *p_pConstSegStack;
    // struct s_StackOfPragmaItem_t *p_pFPMControlStack;
    // struct s_StackOfPragmaItem_t *p_pStrictGSCheckStack;
    // struct PragmaItem_t *p_pPragmaStackFreeSpace;
    // struct LifetimeStack *p_pLifetimeStackFreeSpace;
    // struct s_StringSubstitution_t *p_PIncludeAliasList;
    // struct s_list<void_*> *p_pchlistDefs;
    // struct s_list<void_*> *p_pchlistIncludes;
    // struct s_list<void_*> *p_pchlistAssemblyIncludes;
    // struct Type_t *p_Ret_type;
    // struct Symbol_t *p_Segment;
    // struct Type_t *p_ST_BTcchar;
    // struct Type_t *p_ST_BTcint;
    // struct Type_t *p_ST_BTcuchar;
    // struct Type_t *p_ST_BTcushort;
    // struct Type_t *p_ST_BTcwchar_t;
    // struct Type_t *p_ST_BTfloat;
    // struct Type_t *p_ST_BTdouble;
    // struct Type_t *p_ST_BTldouble;
    // struct Type_t *p_ST_BTint;
    // struct Type_t *p_ST_BTint64;
    // struct Type_t *p_ST_BTuint64;
    // struct Type_t *p_ST_BTarbint;
    // struct Type_t *p_ST_BTlong;
    // struct Type_t *p_ST_BTulong;
    // struct Type_t *p_ST_BTsegment;
    // struct Type_t *p_ST_BTshort;
    // struct Type_t *p_ST_BTushort;
    // struct Type_t *p_ST_BTchar;
    // struct Type_t *p_ST_BTuchar;
    // struct Type_t *p_ST_BTschar;
    // struct Type_t *p_ST_BTuint;
    // struct Type_t *p_ST_BTsize_t;
    // struct Type_t *p_ST_BTptrdiff_t;
    // struct Type_t *p_ST_BTundef;
    // struct Type_t *p_ST_BTvoid;
    // struct Type_t *p_ST_BTnullptr;
    // struct Type_t *p_ST_function;
    // struct Type_t *p_ST_pVoid;
    // struct Type_t *p_ST_BTindex_t;
    // struct Type_t *p_ST_BTUnknown;
    // struct Type_t *p_ST_BTEllipsis;
    // struct Symbol_t *p_pPureStub;
    // struct SymbolTableManager_t *p_pSymbolTableManager;
    // struct Type_t *p_pIndFunc[7][3];
    // struct CommentPragma_t *p_CommentPragmaList;
    // struct DictionaryNoMoveToFront<Symbol_t_*,unsigned_long,DictionaryBucket<Symbol_t_*,unsigned_long,&bool___fastcall_BucketEq<Symbol_t_*>(Symbol_t_*,Symbol_t_*),&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)>,&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)> *p_dictVarargFuncTokenCode;
    // struct DictionaryNoMoveToFront<Symbol_t_*,ComPlusMetaData_t_*,DictionaryBucket<Symbol_t_*,ComPlusMetaData_t_*,&bool___fastcall_BucketEq<Symbol_t_*>(Symbol_t_*,Symbol_t_*),&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)>,&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)> *p_dictComPlusMetaData;
    // struct s_dict_t *p_dictLocalsToGlobals;
    // struct DictionaryNoMoveToFront<Type_t_const_*,Symbol_t_*,DictionaryBucket<Type_t_const_*,Symbol_t_*,&bool___fastcall_BucketEq<Type_t_const_*>(Type_t_const_*,Type_t_const_*),&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)>,&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)> *p_dictTypeTokenSyms;
    // struct s_flist *p_pVoidList;
    // struct s_flist *p_pExplicitVoidList;
    // struct s_flist *p_pZeroParmList;
    // struct Symbol_t *p_AnonTextSegment;
    // struct Symbol_t *p_DefaultDataSegment;
    // struct Symbol_t *p_DefaultCodeSegment;
    // struct Symbol_t *p_DefaultFarDataSegment;
    // struct Token *p_HardTokenArray[427];
    // struct Token *p_defaultToken;
    // struct DepData *p_pMRDependencies;
    // struct Symbol_t *p_psym__LINE__Var;
    // struct ExtensibleDictionaryNoMoveToFront<unsigned_long,Symbol_t_*,DictionaryBucket<unsigned_long,Symbol_t_*,&bool___fastcall_BucketEq<unsigned_long>(unsigned_long,unsigned_long),&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)>,&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)> *p_SegmentInfoDictionary;
    // struct DictionaryNoMoveToFront<Symbol_t_const_*,Id_t_*,DictionaryBucket<Symbol_t_const_*,Id_t_*,&bool___fastcall_BucketEq<Symbol_t_const_*>(Symbol_t_const_*,Symbol_t_const_*),&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)>,&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)> *p_TextForDeprecatedDictionary;
    // struct s_list<void_*> *p_ListOfGUIDInits;
    unsigned char p_pWarningTable[1000];
    // struct set<WarningNumber,std::less<WarningNumber>,stl::STLAlloc_t<WarningNumber,0>_> *p_pUsedOnceWarnings;
    // struct SavedMacroList_t *p_pSavedMacros;
    // struct Symbol_t *p_pGlobalVoidFormalSymbol;
    // struct s_dict_t *p_AlignDictionary;
    // struct Symbol_t *p_pUnknownFunction;
    // struct DictionaryNoMoveToFront<unsigned_short,Id_t_*,DictionaryBucket<unsigned_short,Id_t_*,&bool___fastcall_BucketEq<unsigned_short>(unsigned_short,unsigned_short),&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)>,&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)> *p_NativeToManagedIdsDict;
    // struct ExtensibleDictionaryNoMoveToFront<Symbol_t_*,GlobalObjectLifetimeKind_t,DictionaryBucket<Symbol_t_*,GlobalObjectLifetimeKind_t,&bool___fastcall_BucketEq<Symbol_t_*>(Symbol_t_*,Symbol_t_*),&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)>,&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)> *p_dictGlobalObjectLifetime;
    // struct DictionaryNoMoveToFront<Id_t_*,Id_t_*,DictionaryBucket<Id_t_*,Id_t_*,&bool___fastcall_BucketEq<Id_t_*>(Id_t_*,Id_t_*),&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)>,&unsigned_int___fastcall_GenericHash(char_const_*,unsigned_int)> *p_pNormalizedFileName;
    // struct Id_t *p_PP_returnsudt;
    // struct Id_t *p_PP_Boolean;
    // struct Id_t *p_PP_Char;
    // struct Id_t *p_PP_SByte;
    // struct Id_t *p_PP_Byte;
    // struct Id_t *p_PP_Int16;
    // struct Id_t *p_PP_UInt16;
    // struct Id_t *p_PP_Int32;
    // struct Id_t *p_PP_UInt32;
    // struct Id_t *p_PP_Int64;
    // struct Id_t *p_PP_UInt64;
    // struct Id_t *p_PP_Single;
    // struct Id_t *p_PP_Double;
    // struct Id_t *p_PP_Void;
    // struct Id_t *p_PP_System;
    // struct Id_t *p_PP_TypedByRef;
    // struct Id_t *p_PP_IntPtr;
    // struct Id_t *p_PP_UIntPtr;
    // struct Id_t *p_PP_Array;
    // struct Id_t *p_PP_ArgIterator;
    // struct Id_t *p_PP_RuntimeArgumentHandle;
    // struct Id_t *p_PP_Type;
    // struct Id_t *p_PP_GetTypeFromHandle;
    // struct Id_t *p_PP_COMPlus_ctor;
    // struct Id_t *p_PP_IsCXXReferenceModifier;
    // struct Id_t *p_PP_IsCXXPointerModifier;
    // struct Id_t *p_PP_IsExplicitlyDereferenced;
    // struct Id_t *p_PP_IsConstModifier;
    // struct Id_t *p_PP_IsConst;
    // struct Id_t *p_PP_IsVolatileModifier;
    // struct Id_t *p_PP_IsVolatile;
    // struct Id_t *p_PP_IsLongModifier;
    // struct Id_t *p_PP_IsLong;
    // struct Id_t *p_PP_NoSignSpecifiedModifier;
    // struct Id_t *p_PP_IsSignUnspecifiedByte;
    // struct Id_t *p_PP_IsCopyConstructed;
    // struct Id_t *p_PP_DecoratedNameAttribute;
    // struct Id_t *p_PP_MiscellaneousBitsAttribute;
    // struct Id_t *p_PP_NativeCppClassAttribute;
    // struct Id_t *p_PP_RequiredAttribute;
    // struct Id_t *p_PP_DebugInfoInPDBAttribute;
    // struct Id_t *p_PP_CLSCompliantAttribute;
    // struct Id_t *p_PP_IsEnumModifier;
    // struct Id_t *p_PP_va_list;
    // struct Id_t *p_PP_MarshalWorkaround;
    // struct Id_t *p_PP_CompilerMarshalOverride;
    // struct Id_t *p_PP_BoxedModifier;
    // struct Id_t *p_PP_IsBoxed;
    // struct Id_t *p_PP_IntrinsicModifier;
    // struct Id_t *p_PP_IsJitIntrinsic;
    // struct Id_t *p_PP_CxxUdtReturnStyleModifier;
    // struct Id_t *p_PP_IsUdtReturn;
    // struct Id_t *p_PP_AllowMultiple;
    // struct Id_t *p_PP_Inherited;
    // struct Id_t *p_PP_ValidOn;
    // struct Id_t *p_PP_CppImplementationDetails;
    // struct Id_t *p_PP_CrtImplementationDetails;
    // struct Id_t *p_PP_alloca;
    // struct Id_t *p_PP_noop;
    // struct Id_t *p_PP_defined;
    // struct Id_t *p_PP_formal;
    // struct Id_t *p_PP_ellipsis;
    // struct Id_t *p_PP_cast;
    // struct Id_t *p_PP_main;
    // struct Id_t *p_PP_WinMain;
    // struct Id_t *p_PP_LibMain;
    // struct Id_t *p_PP_wmain;
    // struct Id_t *p_PP_wWinMain;
    // struct Id_t *p_PP_alignment;
    // struct Id_t *p_PP_unnamedTag;
    // struct Id_t *p_PP_unnamedSymbol;
    // struct Id_t *p_PP_UDCTemplate;
    // struct Id_t *p_PP_dollar;
    // struct Id_t *p_PP_drectve;
    // struct Id_t *p_PP_guard;
    // struct Id_t *p_PP_thread_guard;
    // struct Id_t *p_PP_setjmp;
    // struct Id_t *p_PP_setjmpex;
    // struct Id_t *p_PP_HRESULT;
    // struct Id_t *p_PP_wchar_t;
    // struct Id_t *p_PP_InternalPragmaState;
    // struct Id_t *p_PP_localsize;
    // struct Id_t *p_PP_va_alist;
    // struct Id_t *p_PP__LINE__Var;
    // struct Id_t *p_PP_size_t;
    // struct Id_t *p_PP_ptrdiff_t;
    // struct Id_t *p_PP__FUNCTION__;
    // struct Id_t *p_PP__FUNCDNAME__;
    // struct Id_t *p_PP__FUNCSIG__;
    // struct Id_t *p_PP__FSTREXP;
    // struct Id_t *p_PP__LPREFIX;
    // struct Id_t *p_PP__APREFIX;
    // struct Id_t *p_PP_m64;
    // struct Id_t *p_PP_m128;
    // struct Id_t *p_PP_vc_attributes;
    // struct Id_t *p_PP_vc_helper_attributes;
    // struct Id_t *p_PP_vc_atl_attributes;
    // struct Id_t *p_PP_Invoke;
    // struct Id_t *p_PP_BeginInvoke;
    // struct Id_t *p_PP_EndInvoke;
    // struct Id_t *p_PP_COMPlus_dtor;
    // struct Id_t *p_PP_XML_ctor;
    // struct Id_t *p_PP_XML_cctor;
    // struct Id_t *p_PP_op_Subscript;
    // struct Id_t *p_PP_LRBRACK;
    // struct Id_t *p_PP_op_FunctionCall;
    // struct Id_t *p_PP_op_Multiply;
    // struct Id_t *p_PP_op_PointerDereference;
    // struct Id_t *p_PP_delegate;
    // struct Id_t *p_PP_event;
    // struct Id_t *p_PP_gc;
    // struct Id_t *p_PP_property;
    // struct Id_t *p_PP_finally;
    // struct Id_t *p_PP_initonly;
    // struct Id_t *p_PP_internal;
    // struct Id_t *p_PP_literal;
    // struct Id_t *p_PP_ImageBase;
    // struct Id_t *p_idCtorSeg;
    // struct Symbol_t *p_pSym_vc_attributes;
    // struct Symbol_t *p_pSym_vc_helper_attributes;
    // struct Symbol_t *p_pSym_vc_atl_attributes;
    // struct set<std::pair<Symbol_t_*,unsigned_long>,std::less<std::pair<Symbol_t_*,unsigned_long>_>,stl::STLAlloc_t<std::pair<Symbol_t_*,unsigned_long>,0>_> *p_pExportedTypes;
    // struct map<long,long,std::less<long>,stl::STLAlloc_t<std::pair<long_const_,long>,0>_> *p_pDeclToDefTIMap;
    // struct list<Type_t_const_*,stl::STLAlloc_t<Type_t_const_*,0>_> *p_pDeferredPTMTypes;
    // struct set<long,std::less<long>,stl::STLAlloc_t<long,0>_> *p_pReferencedTIs;
    // struct TypeEntry_t **p_Type_table;
} pch_roots;

typedef struct PchS_s {
    pch_roots rs;
    // int p_PchAllBiopsCount;
    // uint p_CurClusterNdx;
    // ulong p_curIlKey;
    // int p_UniqueIdCount;
    // long p_PrLimitsPosition;
    // long p_syAdjustment;
    // ulong p_TCounter;
    // int p_PchChksum;
    // ulong p_TypesOffset;
    // int p_PragmaVtorDisp;
    unsigned int p_warnP2Min;
    unsigned int p_warnP2Max;
    ParseFlags_t p_ParseFlags;
    // ulong p_PchTPIAge;
    // undefined;
    // bool p_FpExcept;
    // bool p_FpPrecise;
    // ulong p_PchIDBAge;
    // bool p_InclInjectedPchSym;
    // char p_PchSymName[779];
    // uchar p_CurSbrPatch;
    // struct PositionGenerator_t p_thePositionGenerator;
    // ulong p_CurVarargFuncCode;
    // struct AssemblyManager p_assemblyManager;
} PchS_t;

// ?g_hDLLHandle@@3PAXA
// void *g_hDLLHandle

// ?TPIMgr@@3VPDBManager_t@@A
extern PDBManager_t TPIMgr;

extern PDBManager_t SplitTPIMgr;

extern PDBManager_t *p_TPIMgr;

// ?fSkipPDBOpen@@3HA
// int fSkipPDBOpen

// ?pIDBMgr@@3PAVPDBManager_t@@A
// class PDBManager_t *pIDBMgr

// ?IDBMgr@@3VPDBManager_t@@A
// class PDBManager_t IDBMgr

// ?fClosePDB@@3HA
// int fClosePDB

// ?PchS@@3UPchS_t@@A
extern PchS_t PchS;

// ?PchC@@3UPchC_t@@A
extern PchC_t PchC;

// ?MemoryStatsLevel@@3HA
// int MemoryStatsLevel

// ?PchUFlag@@3HA
extern bool32 PchUFlag;

// ?PchUFile@@3PAEA
extern char *PchUFile;

// ?PchCFlag@@3HA
extern bool32 PchCFlag;

// ?PchCFile@@3PAEA
extern char *PchCFile;

// ?PchXFlag@@3HA
// int PchXFlag

// ?PchXFile@@3PAEA
// unsigned char *PchXFile

// ?szCmd_Ylstring@@3PADA
extern const char *szCmd_Ylstring;

// ?PchPFile@@3PAEA
// unsigned char *PchPFile

// ?PchFinalFileName@@3PAEA
// unsigned char *PchFinalFileName

// ?PchCreateFlag@@3HA
// int PchCreateFlag

// ?PchFileCreated@@3HA
// int PchFileCreated

// ?PchMustCreate@@3HA
// int PchMustCreate

// ?PchFileNameFromCmdLine@@3HA
// int PchFileNameFromCmdLine

// ?fPersistentPch@@3HA
extern bool32 fPersistentPch;

// ?PchReuseCVTypes@@3HA
// int PchReuseCVTypes

// ?CurFuncInPch@@3HA
// int CurFuncInPch

// ?CurFuncSkipped@@3HA
// int CurFuncSkipped

// ?Debug@@3PADA
// char *Debug

// ?NVStr@@3PADA
// char *NVStr

// ?ParentEsu@@3PAVSymbol_t@@A
// class Symbol_t *ParentEsu

// ?Nsilent_errors@@3HA
// int Nsilent_errors

// ?Nsilent_warnings@@3HA
// int Nsilent_warnings

// ?Prep_ifstack@@3HA
// int Prep_ifstack

// ?OutFil@@3PADA
// char *OutFil

// ?szPDBName@@3PADA
extern const char *szPDBName;

// ?StunDepth@@3HA
// int StunDepth

// ?Warn_level@@3HA
// int Warn_level

// ?InlineDepth@@3FA
// short InlineDepth

// ?InlineRecursion@@3FA
// short InlineRecursion

// ?PragmaAutoInline@@3HA
// int PragmaAutoInline

// ?AutoInline@@3HA
// int AutoInline

// ?ExplicitComdat@@3HA
// int ExplicitComdat

// ?NoExpansion@@3HA
// int NoExpansion

// ?Enum_val@@3_JA
// __int64 Enum_val

// ?LexicalIndex@@3GA
// unsigned short LexicalIndex

// ?pStringBuffer@@3PAEA
// unsigned char *pStringBuffer

// ?Path_chars@@3PADA
// char *Path_chars

// ?Basename@@3PADA
// char *Basename

// ?Cmd_pack_size@@3HA
// int Cmd_pack_size

// ?iTryBlockLevel@@3HA
// int iTryBlockLevel

// ?iExceptBlockLevel@@3HA
// int iExceptBlockLevel

// ?iFinallyBlockLevel@@3HA
// int iFinallyBlockLevel

// ?SizeofDepth@@3HA
// int SizeofDepth

// ?zgDepth@@3HA
// int zgDepth

// ?Hold_I_DATA@@3PAVSymbol_t@@A
// class Symbol_t *Hold_I_DATA

// ?Cmd_NoExportInlines@@3HA
// int Cmd_NoExportInlines

// ?Realt_const0@@3Us_realt@@A
// struct s_realt Realt_const0

// ?pMRMgr@@3PAVMRMgr_t@@A
// class MRMgr_t *pMRMgr

// ?ExecutionState@@3W4CompilerExecutionState_t@@A
extern CompilerExecutionState_t ExecutionState;

// ?JDateVer@@3PBDB
// char const *JDateVer

// ?Copyright@@3PBDB
// char const *Copyright

// ?C1Str@@3PBDB
// char const *C1Str

// ?Cdecl_str@@3PBDB
// char const *Cdecl_str

// ?Pascal_str@@3PBDB
// char const *Pascal_str

// ?PPelse_str@@3PBDB
// char const *PPelse_str

// ?PPendif_str@@3PBDB
// char const *PPendif_str

// ?PPifel_str@@3PBDB
// char const *PPifel_str

// ?PPdefine_str@@3PBDB
// char const *PPdefine_str

// ?PPundef_str@@3PBDB
// char const *PPundef_str

// ?PPerror_str@@3PBDB
// char const *PPerror_str

// ?PPinclude_str@@3PBDB
// char const *PPinclude_str

// ?PPifdef_str@@3PBDB
// char const *PPifdef_str

// ?PPifndef_str@@3PBDB
// char const *PPifndef_str

// ?PPline_str@@3PBDB
// char const *PPline_str

// ?PPpragma_str@@3PBDB
// char const *PPpragma_str

// ?Near_str@@3PBDB
// char const *Near_str

// ?Far_str@@3PBDB
// char const *Far_str

// ?Far16_str@@3PBDB
// char const *Far16_str

// ?Syscall_str@@3PBDB
// char const *Syscall_str

// ?Asm_str@@3PBDB
// char const *Asm_str

// ?xlateECerr@@3PBHB
// int const *xlateECerr

// ??_C@_03IGI@?2?3?1?$AA@
// "\\:/"

// ??_C@_08CNLK@vc50?4pdb?$AA@
// "vc50.pdb"

// ?TagIsInCurrentBlock@@3HA
// int TagIsInCurrentBlock

// ?Dump_tables@@3HA
// int Dump_tables

// ?XformedFormalListType@@3W4FormalListKind_e@GTBFormalList@@A
// enum GTBFormalList::FormalListKind_e XformedFormalListType

// ?fReusePersistPch@@3HA
// int fReusePersistPch

// ?m_allocator@?$SAClass@UFlistEntry_t@@$00@@0USubAllocator@VirtualHeap@@A
// private: static struct VirtualHeap::SubAllocator SAClass<struct FlistEntry_t, 1>::m_allocator

// ?NParseErrors@@3HA
// int NParseErrors

// ?ilsEEAttrib@@3VILSink@@A
// class ILSink ilsEEAttrib

// ?ilsGSym@@3VILSink@@A
// class ILSink ilsGSym

// ?Optimize_state@@3HA
// int Optimize_state

// ?Inteltypes@@3HA
// int Inteltypes

// ?Cons_case@@3PAUs_tree@@A
// struct s_tree *Cons_case

// ?m_allocator@?$SAClass@VToken@@$00@@0USubAllocator@VirtualHeap@@A
// private: static struct VirtualHeap::SubAllocator SAClass<class Token, 1>::m_allocator

// ?ZnFlag@@3HA
// int ZnFlag

// ?Break@@3PAUs_stack@@A
// struct s_stack *Break

// ?szIlModName@@3PBDB
// char const *szIlModName

// ?CurrFormalList@@3PAVDLSymbolList_t@@A
// class DLSymbolList_t *CurrFormalList

// ?Default@@3PAUs_stack@@A
// struct s_stack *Default

// ?m_allocator@?$SAClass@UIndirEntry_t@@$00@@0USubAllocator@VirtualHeap@@A
// private: static struct VirtualHeap::SubAllocator SAClass<struct IndirEntry_t, 1>::m_allocator

// ?ilsDB@@3VILSink@@A
// class ILSink ilsDB

// ?listIncludes@@3PAUlist@@A
extern list<void *> *listIncludes;

// ?ParenDepth@@3HA
// int ParenDepth

// ?Input_file@@3PADA
extern const char *Input_file;

// ?RecursiveParseFlags@@3PAUs_RecursiveParseFlags@@A
// struct s_RecursiveParseFlags *RecursiveParseFlags

// ?TypesForThisDepth@@3PAUs_declspec@@A
// struct s_declspec *TypesForThisDepth

// ?CurrentTimeStamp@@3PADA
// char *CurrentTimeStamp

// ?ilsRGL@@3VILSink@@A
// class ILSink ilsRGL

// ?Continue@@3PAUs_stack@@A
// struct s_stack *Continue

// ?ilsInitStrings@@3VILSink@@A
// class ILSink ilsInitStrings

// ?ilsExp@@3VILSink@@A
// class ILSink ilsExp

// ?ZfExtension@@3HA
// int ZfExtension

// ?m_allocator@?$SAClass@Us_defn@@$00@@0USubAllocator@VirtualHeap@@A
// private: static struct VirtualHeap::SubAllocator SAClass<struct s_defn, 1>::m_allocator

// ?TmpTypePool@@3PAVType_t@@A
// class Type_t *TmpTypePool

// ?Version@@3PADA
// char *Version

// ?m_allocator@?$SAClass@UId_t@@$00@@0USubAllocator@VirtualHeap@@A
// private: static struct VirtualHeap::SubAllocator SAClass<struct Id_t, 1>::m_allocator

// ?C_value@@3Tu_value@@A
// union u_value C_value

// ?Reg_vars@@3PAUs_stack@@A
// struct s_stack *Reg_vars

// ?Asm_align@@3FA
// short Asm_align

// ?listForcedIncludes@@3PAUlist@@A
extern list<void *> *listForcedIncludes;

// ?ShowIncludes@@3HA
// int ShowIncludes

// ?ilsLSym@@3VILSink@@A
// class ILSink ilsLSym

// ?InternalUnaryTree_ivBasedInfo@@3Tu_ivalue@@A
// union u_ivalue InternalUnaryTree_ivBasedInfo

// ?listDefs@@3PAUlist@@A
extern list<void *> *listDefs;

// ?SymbolLevel@@3EA
// unsigned char SymbolLevel

// ?Lex_level@@3EA
// unsigned char Lex_level

// ?CurFuncStartLineNumber@@3JA
// long CurFuncStartLineNumber

// ?Optimize_string@@3PAEA
// unsigned char *Optimize_string

// ?Out_funcdef@@3HA
extern bool32 Out_funcdef;

// ?EnumTag@@3PAVSymbol_t@@A
// class Symbol_t *EnumTag

// ?SwitchLabel@@3PAVSymbol_t@@A
// class Symbol_t *SwitchLabel

// ?m_allocator@?$SAClass@UAssoc_t@@$00@@0USubAllocator@VirtualHeap@@A
// private: static struct VirtualHeap::SubAllocator SAClass<struct Assoc_t, 1>::m_allocator

// ?QnamedTypeForThisDepth@@3PAPAVSymbol_t@@A
// class Symbol_t **QnamedTypeForThisDepth

// ?InstantiateFunc@@3HA
// int InstantiateFunc

// ?StdoutFile@@3PADA
// char *StdoutFile

// ?Macro_depth@@3HA
// int Macro_depth

// ?iterForcedIncludes@@3UlistIter_t@@A
// struct listIter_t iterForcedIncludes

// ?CurrentTime@@3PADA
// char *CurrentTime

// ?FormalListDepth@@3HA
// int FormalListDepth

// ?I_Eoutput@@3PAU_iobuf@@A
// struct _iobuf *I_Eoutput

// ?m_allocator@?$SAClass@VGeneralAllocator_t@@$00@@0USubAllocator@VirtualHeap@@A
// private: static struct VirtualHeap::SubAllocator SAClass<class GeneralAllocator_t, 1>::m_allocator

// ?Case@@3PAUs_stack@@A
// struct s_stack *Case

// ?Current_function@@3PAVSymbol_t@@A
// class Symbol_t *Current_function

// ?StrNoInCurFunc@@3IA
// unsigned int StrNoInCurFunc

// ?SourceBrowserNam@@3PADA
// char *SourceBrowserNam

// ?BadInternalClassErrors@@3HA
// int BadInternalClassErrors

// ?crc32ClCmd@@3VCRC32@@A
extern CRC32 crc32ClCmd;

// ?SourceBrowserExt@@3PADA
// char *SourceBrowserExt

// ?ilsInit@@3VILSink@@A
// class ILSink ilsInit

// ?fGenPersistPch@@3HA
// int fGenPersistPch

// ?Cmd_inlineparsing@@3HA
// int Cmd_inlineparsing

// ?Prep@@3HA
extern bool32 Prep;

// ?SourceBrowserNamFlg@@3PADA
// char *SourceBrowserNamFlg

// ?Current_char@@3PAEA
// unsigned char *Current_char

// ?CurFuncSyOff@@3JA
// long CurFuncSyOff

// ?Reuse_1@@3PAEA
// unsigned char *Reuse_1

// ?pSigMgr@@3PAUFESigMgr@@A
// struct FESigMgr *pSigMgr

// ?CurrentDate@@3PADA
// char *CurrentDate

// ?PchOldUFlag@@3HA
// int PchOldUFlag

// ?TmpTypeIndex@@3HA
// int TmpTypeIndex

// ?Exit_label@@3PAUs_tree@@A
// struct s_tree *Exit_label

// ?PchOldUFile@@3PAEA
// unsigned char *PchOldUFile

// ?CurFuncNumFormals@@3IA
// unsigned int CurFuncNumFormals

// ?AsmString@@3PAEA
// unsigned char *AsmString

// ?Test@@3PAUs_stack@@A
// struct s_stack *Test

// ?CurFuncNumExNodes@@3KA
// unsigned long CurFuncNumExNodes

// ?Cflag@@3HA
// int Cflag

// ?I_stdoutfp@@3PAU_iobuf@@A
// struct _iobuf *I_stdoutfp

// ?I_sbrfp@@3PAU_iobuf@@A
// struct _iobuf *I_sbrfp

// ?Nerrors@@3HA
extern int Nerrors;

// ?BdFlg@@3HA
// int BdFlg

// ?m_allocator@?$SAClass@UTypeEntry_t@@$00@@0USubAllocator@VirtualHeap@@A
// private: static struct VirtualHeap::SubAllocator SAClass<struct TypeEntry_t, 1>::m_allocator

// ?CurrFormalListType@@3W4FormalListKind_e@GTBFormalList@@A
// enum GTBFormalList::FormalListKind_e CurrFormalListType

// ?BlockScope@@3EA
// unsigned char BlockScope

// ?Start@@3PAUs_stack@@A
// struct s_stack *Start

// ?Loopi_stack@@3PAUs_stack@@A
// struct s_stack *Loopi_stack

// ?Cross_compile@@3HA
// int Cross_compile

// ?Processor@@3HA
// int Processor

// ?XformedFormalList@@3PAVDLSymbolList_t@@A
// class DLSymbolList_t *XformedFormalList

// ?I_pchfp@@3PAU_iobuf@@A
// struct _iobuf *I_pchfp

// ?Stack_depth@@3HA
// int Stack_depth

// ?m_allocator@?$SAClass@VSymbolAllocator_t@@$00@@0USubAllocator@VirtualHeap@@A
// private: static struct VirtualHeap::SubAllocator SAClass<class SymbolAllocator_t, 1>::m_allocator

// ?WarnIsError@@3HA
// int WarnIsError

// ?pSymBitTemp@@3PAVSymbol_t@@A
// class Symbol_t *pSymBitTemp

// ?Leave@@3PAUs_stack@@A
// struct s_stack *Leave

// ?pIPM@@3PAUIncrParseMgr@@A
// struct IncrParseMgr *pIPM

// ?CurrentDateTime@@3PADA
// char *CurrentDateTime

// ?Nologo@@3HA
// int Nologo

// ?Asm_opt@@3HA
// int Asm_opt

// ?Cmd_ShowBehaviorChanges@@3HA
// int Cmd_ShowBehaviorChanges

// ?FATFlg@@3HA
// int FATFlg

// ?CurFuncExOff@@3JA
// long CurFuncExOff

// ?gNoToken@@3VToken@@A
// class Token gNoToken

// ?StringBuffer@@3PAEA
// unsigned char *StringBuffer

// ?MF_inlinefunc@@3PAUs_memfile@@A
// struct s_memfile *MF_inlinefunc

// _$E33

// _$E30

// _$E32

// _$E31

// _$E38

// _$E35

// _$E37

// _$E36

// _$E43

// _$E40

// _$E42

// _$E41

// _$E48

// _$E45

// _$E47

// _$E46

// _$E53

// _$E50

// _$E52

// _$E51

// _$E58

// _$E55

// _$E57

// _$E56

// _$E63

// _$E60

// _$E62

// _$E61

// _$E68

// _$E65

// _$E67

// _$E66

// _$E71

// _$E70

// _$E74

// _$E73

// _$E77

// _$E76

// _$E80

// _$E79

// _$E85

// _$E82

// _$E84

// _$E83

// _$E90

// _$E87

// _$E89

// _$E88

// _$E93

// _$E92

// _$E96

// _$E95

// _$E99

// _$E98

// _$E102

// _$E101

// _$E105

// _$E104

// _$E108

// _$E107

// _$E111

// _$E110

// _$E114

// _$E113

// _$E117

// _$E116

extern s_cmd_line_warning_t CmdLineWarningList[];

extern cmdtab_s cmdtab[];

extern bool32 p_Embed_debug;

extern const char *gYl_arg_path;

extern const char *gYX_arg_path;

extern bool32 gOption_YX;

#endif /* GLOBALS_H */
