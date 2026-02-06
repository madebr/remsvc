#include "nheapall.h"

#include "decomp.h"
#include "error.h"
#include "main.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#endif

// GLOBAL: MSVC5_C1 0x00000538
// ??_7PCHHeap@@6B@
// const PCHHeap::`vftable'

// GLOBAL: MSVC5_C1 0x00000578
// ??_7LocalPCHHeap@@6B@
// const LocalPCHHeap::`vftable'

// GLOBAL: MSVC5_C1 0x0000197c
// ?fMoveTheHeap@@3HA
// int fMoveTheHeap

// GLOBAL: MSVC5_C1 0x00001980
// ?Cmd_ScaleMemory@VirtualHeap@@2HA
// GLOBAL: C1 0x0045cb2c
int VirtualHeap::Cmd_ScaleMemory = 100;

// GLOBAL: MSVC5_C1 0x00001984
// ?result@?1??CanOSDoMemoryMapCorrectly@@YAHXZ@4HA
// int `int __cdecl CanOSDoMemoryMapCorrectly(void)'::`2'::result

// GLOBAL: MSVC5_C1 0x00005a7c
// ??_C@_0N@IBKN@?4?2nheapall?4c?$AA@
// ".\\nheapall.c"

// GLOBAL: MSVC5_C1 0x00008f88
// ?ThePCH@HeapManager@@2VPCHHeapManager@@A
// public: static class PCHHeapManager HeapManager::ThePCH

// GLOBAL: MSVC5_C1 0x00008fd0
// ?ActiveHeaps@HeapManager@@2PAVVirtualHeap@@A
// GLOBAL: C1 0x0046a378
VirtualHeap HeapManager::ActiveHeaps[M_LIFEMAX];

// GLOBAL: C1 0x00457ec0
const VirtualHeap::HeapParameters HeapManager::TheHeapParameters[M_LIFEMAX] = {
    { M_LIFETIME0, 50 * 1024 * 1024, 64 * 1024, 1, 0, 0, 0, 0, 1, 1, },
    { M_LIFETIME1, 10 * 1024 * 1024, 32 * 1024, 0, 0, 0, 0, 1, 0, 4, },
    { M_LIFETIME2, 10 * 1024 * 1024, 32 * 1024, 0, 0, 0, 1, 1, 0, 4, },
    { M_LIFETIME3,  5 * 1024 * 1024, 16 * 1024, 0, 0, 0, 1, 1, 0, 4, },
    { M_LIFETIME4,  5 * 1024 * 1024, 32 * 1024, 0, 0, 0, 1, 1, 0, 4, },
    { M_LIFETIME5,  5 * 1024 * 1024, 32 * 1024, 0, 0, 0, 1, 1, 0, 4, }
};

// GLOBAL: MSVC5_C1 0x00009090
// ?m_hMap@HeapManager@@0PAXA
// private: static void *HeapManager::m_hMap

// GLOBAL: MSVC5_C1 0x00009094
// ??_B?1??CanOSDoMemoryMapCorrectly@@YAHXZ@51
// `int __cdecl CanOSDoMemoryMapCorrectly(void)'::`2'::`local static guard'{2}

// FUNCTION: MSVC5_C1 0x000458e0
// ??2HeapSet@@SAPAXIHPAVVirtualHeap@@@Z
// public: static void * __cdecl HeapSet::operator new(unsigned int, int, class VirtualHeap *)

// FUNCTION: MSVC5_C1 0x00045930
// ??3HeapSet@@SAXPAX@Z
// public: static void __cdecl HeapSet::operator delete(void *)

// FUNCTION: MSVC5_C1 0x00045950
// ??0HeapSet@@QAE@XZ
// public: __thiscall HeapSet::HeapSet(void)

// FUNCTION: MSVC5_C1 0x00045970
// ??1HeapSet@@QAE@XZ
// public: __thiscall HeapSet::~HeapSet(void)

// FUNCTION: MSVC5_C1 0x00045980
// ?Create@HeapSet@@QAEHJPAVVirtualHeap@@@Z
// public: int __thiscall HeapSet::Create(long, class VirtualHeap *)

// FUNCTION: MSVC5_C1 0x00045a30
// ?Create@HeapSet@@QAEHJPAE@Z
// public: int __thiscall HeapSet::Create(long, unsigned char *)

// FUNCTION: MSVC5_C1 0x00045a60
// ?GetBits@HeapSet@@QAEPAEXZ
// public: unsigned char * __thiscall HeapSet::GetBits(void)

// FUNCTION: MSVC5_C1 0x00045a70
// ?Destroy@HeapSet@@QAEXXZ
// public: void __thiscall HeapSet::Destroy(void)

// FUNCTION: MSVC5_C1 0x00045ab0
// ?Add@HeapSet@@QAEXJ@Z
// public: void __thiscall HeapSet::Add(long)

// FUNCTION: MSVC5_C1 0x00045ad0
// ?Contains@HeapSet@@QAEHJ@Z
// public: int __thiscall HeapSet::Contains(long)

// FUNCTION: MSVC5_C1 0x00045b00
// ?Remove@HeapSet@@QAEXJ@Z
// public: void __thiscall HeapSet::Remove(long)

// FUNCTION: MSVC5_C1 0x00045b30
// ?Clear@HeapSet@@QAEXXZ
// public: void __thiscall HeapSet::Clear(void)

// FUNCTION: MSVC5_C1 0x00045b50
// ?SearchForNext@HeapSet@@IAEHXZ
// protected: int __thiscall HeapSet::SearchForNext(void)

// FUNCTION: MSVC5_C1 0x00045bc0
// ?First@HeapSet@@QAEHXZ
// public: int __thiscall HeapSet::First(void)

// FUNCTION: MSVC5_C1 0x00045be0
// ?Next@HeapSet@@QAEHXZ
// public: int __thiscall HeapSet::Next(void)

// FUNCTION: MSVC5_C1 0x00045c30
// ?Element@HeapSet@@QAEJXZ
// public: long __thiscall HeapSet::Element(void)

// FUNCTION: MSVC5_C1 0x00045c40
// ?FixupSet@HeapSet@@QAEXJ@Z
// public: void __thiscall HeapSet::FixupSet(long)

// FUNCTION: MSVC5_C1 0x00045c60
// ?Initialize@AllSAClasses@@SAXXZ
// FUNCTION: C1 0x0041a3b4
void AllSAClasses::Initialize()
{
  SAClass<GeneralAllocator_t>::Initialize();
  SAClass<SymbolAllocator_t>::Initialize();
  SAClass<TypeEntry_t>::Initialize();
  SAClass<IndirEntry_t>::Initialize();
  SAClass<FlistEntry_t>::Initialize();
  SAClass<Assoc_t,1 >::Initialize();
  SAClass<Id_t>::Initialize();
  SAClass<s_defn>::Initialize();
  SAClass<Token>::Initialize();
}

// FUNCTION: MSVC5_C1 0x00045cd0
// ?Reinitialize@AllSAClasses@@SAXXZ
// public: static void __cdecl AllSAClasses::Reinitialize(void)

// FUNCTION: MSVC5_C1 0x00045da0
// ?GetCanOSDoMemoryMapCorrectly@@YAHXZ
// int __cdecl GetCanOSDoMemoryMapCorrectly(void)

// FUNCTION: MSVC5_C1 0x00045db0
// ?FigureHeapSize@VirtualHeap@@SAJPBUHeapParameters@1@@Z
// FUNCTION: C1 0x0041a383
long __fastcall VirtualHeap::FigureHeapSize(const VirtualHeap::HeapParameters *parameters) {
    size_t size = (size_t)((float)parameters->maxSize * (float)Cmd_ScaleMemory / 100.f);
    size = MakeMultipleOf(size, parameters->allocIncrement);
    if (size == 0) {
        size = parameters->allocIncrement;
    }
    return size;
}

// FUNCTION: MSVC5_C1 0x00045de0
// ?FinishCreate@VirtualHeap@@QAEXXZ
// public: void __thiscall VirtualHeap::FinishCreate(void)

// FUNCTION: MSVC5_C1 0x00045e00
// ?Create@VirtualHeap@@QAEHPBUHeapParameters@1@PAX@Z
// FUNCTION: C1 0x0041a2f3
bool32 VirtualHeap::Create(const VirtualHeap::HeapParameters *parameters, void *address)
{
    pParameters = parameters;
    lMaxSize = FigureHeapSize(parameters);
#ifdef _WIN32
    fpBaseAddress = VirtualAlloc(address, lMaxSize, MEM_RESERVE, PAGE_READWRITE);
#else
    fpBaseAddress = mmap(address, lMaxSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
    if (fpBaseAddress == NULL) {
        return FALSE;
    }
    field_0x1c = 0;
    Reset();
    return TRUE;
}

// FUNCTION: MSVC5_C1 0x00045e60
// ?Destroy@VirtualHeap@@QAEXXZ
// public: void __thiscall VirtualHeap::Destroy(void)

// FUNCTION: MSVC5_C1 0x00045f30
// ?WhyIsHeapLow@@YAXXZ
// void __cdecl WhyIsHeapLow(void)

// FUNCTION: C1 0x0040c1af
size_t __fastcall MakeMultipleOf(size_t size, size_t increment)
{
    size_t result;

    result = (size / increment) * increment;
    if (size % increment > 0) {
        result += increment;
    }
    return result;
}

// FUNCTION: MSVC5_C1 0x00045f50
// ?HeapExtend@VirtualHeap@@QAEXXZ
// GLOBAL: C1 0x0040c1cf
void VirtualHeap::HeapExtend() {
    if ((uintptr_t)fpFreeBlock - (uintptr_t)fpBaseAddress > lMaxSize) {
        fatal_varargs(C1076);
    }
    size_t size = MakeMultipleOf((uintptr_t)fpFreeBlock - (uintptr_t)fpFreeEnd, pParameters->allocIncrement);
    bool success;
#ifdef _WIN32
    success = VirtualAlloc(fpFreeEnd, size, MEM_COMMIT, PAGE_READWRITE) != NULL;
#else
    success = mmap(fpFreeEnd, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)  != MAP_FAILED;;
#endif
    if (!success) {
        fatal_varargs(C1060);
    }
    fpFreeEnd = (void *)((uintptr_t)fpFreeEnd + size);
    lCurrentSize += size;
}

// FUNCTION: MSVC5_C1 0x00045fc0
// ?Reset@VirtualHeap@@QAEXXZ
// FUNCTION: C1 0x0041a372
void VirtualHeap::Reset()
{
    lCurrentSize = 0;
    fpFreeBlock = fpBaseAddress;
    fpFreeEnd = fpBaseAddress;
    field_0x18 = 0;
}

// FUNCTION: MSVC5_C1 0x00045ff0
// ?GetAlignedPages@VirtualHeap@@QAEPAXIPAI@Z
// FUNCTION: C1 0x0040c3bd
void * VirtualHeap::GetAlignedPages(size_t countPages, size_t *ptrFree)
{
    void *result = fpFreeBlock;
    *ptrFree = (uintptr_t)fpBaseAddress + MakeMultipleOf((uintptr_t)result - (uintptr_t)fpBaseAddress + countPages * systemInfo.dwPageSize, systemInfo.dwPageSize) - (uintptr_t)fpFreeBlock;
    fpFreeBlock = (void *)((uintptr_t)fpFreeBlock + *ptrFree);
    if (fpFreeBlock > fpFreeEnd) {
        HeapExtend();
    }
    return result;
}

// FUNCTION: MSVC5_C1 0x00046040
// ??0SubAllocator@VirtualHeap@@QAE@IW4lifetime_e@@@Z
// public: __thiscall VirtualHeap::SubAllocator::SubAllocator(unsigned int, enum lifetime_e)

// FUNCTION: MSVC5_C1 0x00046080
// ??0SubAllocator@VirtualHeap@@QAE@IPAV1@@Z
// public: __thiscall VirtualHeap::SubAllocator::SubAllocator(unsigned int, class VirtualHeap *)

// FUNCTION: MSVC5_C1 0x000460b0
// ??0SubAllocator@VirtualHeap@@QAE@I@Z
// public: __thiscall VirtualHeap::SubAllocator::SubAllocator(unsigned int)

// FUNCTION: MSVC5_C1 0x000460d0
// ?Create@SubAllocator@VirtualHeap@@QAEXW4lifetime_e@@@Z
// FUNCTION: 0x0041a29e
void VirtualHeap::SubAllocator::Create(lifetime_e lifetime) {

    pHeap = &HeapManager::ActiveHeaps[lifetime];
    GetMemory(1);
}

// FUNCTION: MSVC5_C1 0x000460f0
// ?Create@SubAllocator@VirtualHeap@@QAEXPAV2@@Z
// public: void __thiscall VirtualHeap::SubAllocator::Create(class VirtualHeap *)

// FUNCTION: MSVC5_C1 0x00046110
// ?Clear@SubAllocator@VirtualHeap@@QAEXXZ
// public: void __thiscall VirtualHeap::SubAllocator::Clear(void)

// FUNCTION: MSVC5_C1 0x00046120
// ?GetMemory@SubAllocator@VirtualHeap@@AAEXI@Z
// FUNCTION: C1 0x0040c390
void VirtualHeap::SubAllocator::GetMemory(size_t amount)
{
    size_t count_pages = (amount - 1) / systemInfo.dwPageSize + 1;
    if (count_pages <= nPages) {
        count_pages = nPages;
    }
    fpFreeBlock = pHeap->GetAlignedPages(count_pages, &FreeSize);
}

// FUNCTION: MSVC5_C1 0x00046150
// ?Reallocate@VirtualHeap@@QAEPAXPAXII@Z
// public: void * __thiscall VirtualHeap::Reallocate(void *, unsigned int, unsigned int)

// FUNCTION: MSVC5_C1 0x00046190
// ??0PCHHeap@@IAE@W4Mode_e@0@PAVPCHHeapManager@@@Z
// protected: __thiscall PCHHeap::PCHHeap(enum PCHHeap::Mode_e, class PCHHeapManager *)

// FUNCTION: MSVC5_C1 0x000461c0
// ?SaveDescriptor@PCHHeap@@UAEXPAX@Z
// public: virtual void __thiscall PCHHeap::SaveDescriptor(void *)

// FUNCTION: MSVC5_C1 0x00046270
// ?CopyHeap@PCHHeap@@SAPAV1@PBV1@PAVPCHHeapManager@@@Z
// public: static class PCHHeap * __cdecl PCHHeap::CopyHeap(class PCHHeap const *, class PCHHeapManager *)

// FUNCTION: MSVC5_C1 0x000462c0
// ?LoadDescriptor@PCHHeap@@SAPAV1@PAXPAVPCHHeapManager@@@Z
// public: static class PCHHeap * __cdecl PCHHeap::LoadDescriptor(void *, class PCHHeapManager *)

// FUNCTION: MSVC5_C1 0x000463d0
// ??0LocalPCHHeap@@QAE@PAVVirtualHeap@@PAVPCHHeapManager@@@Z
// public: __thiscall LocalPCHHeap::LocalPCHHeap(class VirtualHeap *, class PCHHeapManager *)

// FUNCTION: MSVC5_C1 0x000464a0
// ??0LocalPCHHeap@@IAE@ABV0@PAVPCHHeapManager@@@Z
// protected: __thiscall LocalPCHHeap::LocalPCHHeap(class LocalPCHHeap const &, class PCHHeapManager *)

// FUNCTION: MSVC5_C1 0x000464f0
// ??0LocalPCHHeap@@IAE@PAXW4Mode_e@PCHHeap@@PAVPCHHeapManager@@@Z
// protected: __thiscall LocalPCHHeap::LocalPCHHeap(void *, enum PCHHeap::Mode_e, class PCHHeapManager *)

// FUNCTION: MSVC5_C1 0x00046620
// ?MapAtAddress@LocalPCHHeap@@UAE?AW4Status_e@PCHHeap@@PAXH0@Z
// public: virtual enum PCHHeap::Status_e __thiscall LocalPCHHeap::MapAtAddress(void *, int, void *)

// FUNCTION: MSVC5_C1 0x000466b0
// ?LoadAtAddress@LocalPCHHeap@@UAE?AW4Status_e@PCHHeap@@PAX@Z
// public: virtual enum PCHHeap::Status_e __thiscall LocalPCHHeap::LoadAtAddress(void *)

// FUNCTION: MSVC5_C1 0x00046760
// ?LoadAnywhere@LocalPCHHeap@@UAE?AW4Status_e@PCHHeap@@PAX0@Z
// public: virtual enum PCHHeap::Status_e __thiscall LocalPCHHeap::LoadAnywhere(void *, void *)

// FUNCTION: MSVC5_C1 0x000467f0
// ?ReadHeap@LocalPCHHeap@@IAEXPAX@Z
// protected: void __thiscall LocalPCHHeap::ReadHeap(void *)

// FUNCTION: MSVC5_C1 0x00046880
// ?WriteHeap@LocalPCHHeap@@IAEXPAX@Z
// protected: void __thiscall LocalPCHHeap::WriteHeap(void *)

// FUNCTION: MSVC5_C1 0x00046900
// ?MoveTheHeap@LocalPCHHeap@@IAEXXZ
// protected: void __thiscall LocalPCHHeap::MoveTheHeap(void)

// FUNCTION: MSVC5_C1 0x000469a0
// ?UnLoad@LocalPCHHeap@@UAEXXZ
// public: virtual void __thiscall LocalPCHHeap::UnLoad(void)

// FUNCTION: MSVC5_C1 0x00046a20
// ?SaveNewHeap@LocalPCHHeap@@UAEXPAX@Z
// public: virtual void __thiscall LocalPCHHeap::SaveNewHeap(void *)

// FUNCTION: MSVC5_C1 0x00046aa0
// ?SaveFixedHeap@LocalPCHHeap@@UAEXPAX@Z
// public: virtual void __thiscall LocalPCHHeap::SaveFixedHeap(void *)

// FUNCTION: MSVC5_C1 0x00046b00
// ?SaveDescriptor@LocalPCHHeap@@UAEXPAX@Z
// public: virtual void __thiscall LocalPCHHeap::SaveDescriptor(void *)

// FUNCTION: MSVC5_C1 0x00046c00
// ?SaveBlankDescriptor@LocalPCHHeap@@SAXPAXPAE@Z
// public: static void __cdecl LocalPCHHeap::SaveBlankDescriptor(void *, unsigned char *)

// FUNCTION: MSVC5_C1 0x00046c20
// ?SkipBlankDescriptor@LocalPCHHeap@@SAXPAXPAE@Z
// public: static void __cdecl LocalPCHHeap::SkipBlankDescriptor(void *, unsigned char *)

// FUNCTION: MSVC5_C1 0x00046c50
// ?PrepareRelocation@LocalPCHHeap@@IAEXXZ
// protected: void __thiscall LocalPCHHeap::PrepareRelocation(void)

// FUNCTION: MSVC5_C1 0x00046c70
// ?PrepareFindPointers@LocalPCHHeap@@UAEXPAVVirtualHeap@@@Z
// public: virtual void __thiscall LocalPCHHeap::PrepareFindPointers(class VirtualHeap *)

// FUNCTION: MSVC5_C1 0x00046cd0
// ?PrepareFixup@LocalPCHHeap@@UAEHPAV1@@Z
// public: virtual int __thiscall LocalPCHHeap::PrepareFixup(class LocalPCHHeap *)

// FUNCTION: MSVC5_C1 0x00046d40
// ?Fixup@LocalPCHHeap@@UAEXPAVPCHHeapManager@@@Z
// public: virtual void __thiscall LocalPCHHeap::Fixup(class PCHHeapManager *)

// FUNCTION: MSVC5_C1 0x00046d80
// ?AddHeap@PCHHeapLocator@@QAEXPAVLocalPCHHeap@@PAXI@Z
// public: void __thiscall PCHHeapLocator::AddHeap(class LocalPCHHeap *, void *, unsigned int)

// FUNCTION: MSVC5_C1 0x00046db0
// ??0PCHHeapManager@@QAE@XZ
// public: __thiscall PCHHeapManager::PCHHeapManager(void)

// FUNCTION: MSVC5_C1 0x00046dd0
// ?Create@PCHHeapManager@@QAEXH@Z
// public: void __thiscall PCHHeapManager::Create(int)

// FUNCTION: MSVC5_C1 0x00046e20
// ?Create@PCHHeapManager@@QAEXABV1@H@Z
// public: void __thiscall PCHHeapManager::Create(class PCHHeapManager const &, int)

// FUNCTION: MSVC5_C1 0x00046ea0
// ?Create@PCHHeapManager@@QAEXPAEK@Z
// public: void __thiscall PCHHeapManager::Create(unsigned char *, unsigned long)

// FUNCTION: MSVC5_C1 0x00047070
// ?Destroy@PCHHeapManager@@QAEXXZ
// public: void __thiscall PCHHeapManager::Destroy(void)

// FUNCTION: MSVC5_C1 0x00047110
// ?AddHeap@PCHHeapManager@@QAEXPAVVirtualHeap@@@Z
// public: void __thiscall PCHHeapManager::AddHeap(class VirtualHeap *)

// FUNCTION: MSVC5_C1 0x00047170
// ?WriteToPCH@PCHHeapManager@@QAEXPAEK@Z
// public: void __thiscall PCHHeapManager::WriteToPCH(unsigned char *, unsigned long)

// FUNCTION: MSVC5_C1 0x00047200
// ?WritePCHHeader@PCHHeapManager@@AAEXXZ
// private: void __thiscall PCHHeapManager::WritePCHHeader(void)

// FUNCTION: MSVC5_C1 0x00047360
// ?MakeMemoryMap@PCHHeapManager@@AAEPAXKPAPAX@Z
// private: void * __thiscall PCHHeapManager::MakeMemoryMap(unsigned long, void **)

// FUNCTION: MSVC5_C1 0x000473a0
// ?LoadFromPCH@PCHHeapManager@@QAEHXZ
// public: int __thiscall PCHHeapManager::LoadFromPCH(void)

// FUNCTION: MSVC5_C1 0x00047550
// ?RelocateHeaps@PCHHeapManager@@AAEXH@Z
// private: void __thiscall PCHHeapManager::RelocateHeaps(int)

// FUNCTION: MSVC5_C1 0x000476a0
// ?MakePCHHeapLocator@PCHHeapManager@@AAEPAVPCHHeapLocator@@P8PCHHeap@@BEPAXXZ@Z
// private: class PCHHeapLocator * __thiscall PCHHeapManager::MakePCHHeapLocator(void * (__thiscall PCHHeap::*)(void) const)

// FUNCTION: MSVC5_C1 0x00047720
// ?UpdatePCH@PCHHeapManager@@QAEXXZ
// public: void __thiscall PCHHeapManager::UpdatePCH(void)

// FUNCTION: MSVC5_C1 0x00047850
// ?FoundPointerInHeap@PCHHeapManager@@QAEHPAPAX@Z
// public: int __thiscall PCHHeapManager::FoundPointerInHeap(void **)

// FUNCTION: MSVC5_C1 0x000478b0
// ?AdjustPointerIntoHeap@PCHHeapManager@@QAEHPAPAX@Z
// public: int __thiscall PCHHeapManager::AdjustPointerIntoHeap(void **)

// FUNCTION: MSVC5_C1 0x000478f0
// _$E31
// static

// FUNCTION: MSVC5_C1 0x00047900
// _$E30
// static

// FUNCTION: MSVC5_C1 0x00047910
// ?InitGlobalHeaps@HeapManager@@SAXXZ
// FUNCTION: C1 0x00419264
void HeapManager::InitGlobalHeaps()
{
    int i;

    InitPCHLifeHeaps();
    for (i = 0; i < arraysize(ActiveHeaps); i++) {
        if (!TheHeapParameters[i].isSavedInPCH) {
            if (!ActiveHeaps[i].Create(&TheHeapParameters[i], NULL)) {
                fatal_varargs(C1060);
            }
        }
    }
    AllSAClasses::Initialize();
}

// FUNCTION: MSVC5_C1 0x00047960
// ?InitPCHLifeHeaps@HeapManager@@CAXXZ
// FUNCTION: C1 0x004192ab
void HeapManager::InitPCHLifeHeaps()
{
    int i;

    for (i = 0; i < arraysize(ActiveHeaps); i++) {
        if (!ActiveHeaps[i].Create(&TheHeapParameters[i], NULL)) {
            fatal_varargs(C1060);
        }
    }
}

// FUNCTION: MSVC5_C1 0x000479a0
// ?DestroyPCHLifeHeaps@HeapManager@@CAXXZ
// private: static void __cdecl HeapManager::DestroyPCHLifeHeaps(void)

// FUNCTION: MSVC5_C1 0x000479f0
// ?ReleaseAllHeaps@HeapManager@@SAXXZ
// public: static void __cdecl HeapManager::ReleaseAllHeaps(void)

// FUNCTION: MSVC5_C1 0x00047a20
// ?CreatePCH@HeapManager@@SAXPAEK@Z
// public: static void __cdecl HeapManager::CreatePCH(unsigned char *, unsigned long)

// FUNCTION: MSVC5_C1 0x00047ab0
// ?LoadPCH@HeapManager@@SAHPAEK@Z
// public: static int __cdecl HeapManager::LoadPCH(unsigned char *, unsigned long)

// FUNCTION: MSVC5_C1 0x00047ae0
// ?QueryLocalHeap@LocalPCHHeap@@UAEPAV1@XZ
// public: virtual class LocalPCHHeap * __thiscall LocalPCHHeap::QueryLocalHeap(void)

// FUNCTION: MSVC5_C1 0x00047af0
// ?GetSavedAddress@LocalPCHHeap@@UBEPAXXZ
// public: virtual void * __thiscall LocalPCHHeap::GetSavedAddress(void) const

// FUNCTION: MSVC5_C1 0x00047b00
// ?GetLoadAddress@LocalPCHHeap@@UBEPAXXZ
// public: virtual void * __thiscall LocalPCHHeap::GetLoadAddress(void) const

// FUNCTION: MSVC5_C1 0x00047b10
// ?GetExactSize@LocalPCHHeap@@UBEIXZ
// public: virtual unsigned int __thiscall LocalPCHHeap::GetExactSize(void) const

// FUNCTION: MSVC5_C1 0x00047b20
// ?GetLoadPriority@LocalPCHHeap@@UBE?AW4LoadPriority_e@@XZ
// public: virtual enum LoadPriority_e __thiscall LocalPCHHeap::GetLoadPriority(void) const

// FUNCTION: MSVC5_C1 0x00047b30
// ??_9@$BDA@AE
// [thunk]: __thiscall `vcall'{48, {flat}}

// FUNCTION: MSVC5_C1 0x00047b40
// ??_9@$BDE@AE
// [thunk]: __thiscall `vcall'{52, {flat}}

