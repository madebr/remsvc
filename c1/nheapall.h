#ifndef NHEAPALL_H
#define NHEAPALL_H

#include "c1_types.h"
#include "decomp.h"

#ifdef _WIN32
#include <windows.h>
#endif

// ??_7PCHHeap@@6B@
// const PCHHeap::`vftable'

// ??_7LocalPCHHeap@@6B@
// const LocalPCHHeap::`vftable'

// ?fMoveTheHeap@@3HA
// int fMoveTheHeap

// ?result@?1??CanOSDoMemoryMapCorrectly@@YAHXZ@4HA
// int `int __cdecl CanOSDoMemoryMapCorrectly(void)'::`2'::result

// ??_C@_0N@IBKN@?4?2nheapall?4c?$AA@
// ".\\nheapall.c"

// ??_B?1??CanOSDoMemoryMapCorrectly@@YAHXZ@51
// `int __cdecl CanOSDoMemoryMapCorrectly(void)'::`2'::`local static guard'{2}

// ??2HeapSet@@SAPAXIHPAVVirtualHeap@@@Z
// public: static void * __cdecl HeapSet::operator new(unsigned int, int, class VirtualHeap *)

// ??3HeapSet@@SAXPAX@Z
// public: static void __cdecl HeapSet::operator delete(void *)

// ??0HeapSet@@QAE@XZ
// public: __thiscall HeapSet::HeapSet(void)

// ??1HeapSet@@QAE@XZ
// public: __thiscall HeapSet::~HeapSet(void)

// ?Create@HeapSet@@QAEHJPAVVirtualHeap@@@Z
// public: int __thiscall HeapSet::Create(long, class VirtualHeap *)

// ?Create@HeapSet@@QAEHJPAE@Z
// public: int __thiscall HeapSet::Create(long, unsigned char *)

// ?GetBits@HeapSet@@QAEPAEXZ
// public: unsigned char * __thiscall HeapSet::GetBits(void)

// ?Destroy@HeapSet@@QAEXXZ
// public: void __thiscall HeapSet::Destroy(void)

// ?Add@HeapSet@@QAEXJ@Z
// public: void __thiscall HeapSet::Add(long)

// ?Contains@HeapSet@@QAEHJ@Z
// public: int __thiscall HeapSet::Contains(long)

// ?Remove@HeapSet@@QAEXJ@Z
// public: void __thiscall HeapSet::Remove(long)

// ?Clear@HeapSet@@QAEXXZ
// public: void __thiscall HeapSet::Clear(void)

// ?SearchForNext@HeapSet@@IAEHXZ
// protected: int __thiscall HeapSet::SearchForNext(void)

// ?First@HeapSet@@QAEHXZ
// public: int __thiscall HeapSet::First(void)

// ?Next@HeapSet@@QAEHXZ
// public: int __thiscall HeapSet::Next(void)

// ?Element@HeapSet@@QAEJXZ
// public: long __thiscall HeapSet::Element(void)

// ?FixupSet@HeapSet@@QAEXJ@Z
// public: void __thiscall HeapSet::FixupSet(long)

struct AllSAClasses {
    // ?Initialize@AllSAClasses@@SAXXZ
    // public: static void __cdecl AllSAClasses::Initialize(void)
    static void Initialize();

// ?Reinitialize@AllSAClasses@@SAXXZ
// public: static void __cdecl AllSAClasses::Reinitialize(void)
};

// ?GetCanOSDoMemoryMapCorrectly@@YAHXZ
// int __cdecl GetCanOSDoMemoryMapCorrectly(void)

// ?WhyIsHeapLow@@YAXXZ
// void __cdecl WhyIsHeapLow(void)

// FUNCTION: C1 0x0040c1af
size_t __fastcall MakeMultipleOf(size_t size, size_t increment);

class VirtualHeap {
public:
    struct HeapParameters {
        lifetime_e poolName;
        unsigned int maxSize;
        unsigned int allocIncrement;
        bool32 isSavedInPCH:1;
        bool32 field_0xc_bit1:1;
        bool32 field_0xc_bit2:1;
        bool32 field_0xc_bit3:1;
        bool32 field_0xc_bit4:1;
        bool32 field_0xc_bit5:1;
        // bool32 isRecyclable:1;
        // bool32 doStats:1;
        undefined4 field_0x10;
    };

    // ?Cmd_ScaleMemory@VirtualHeap@@2HA
    static int Cmd_ScaleMemory;

    // ?FigureHeapSize@VirtualHeap@@SAJPBUHeapParameters@1@@Z
    static long __fastcall FigureHeapSize(const HeapParameters *parameters);

    // ?FinishCreate@VirtualHeap@@QAEXXZ
    // public: void __thiscall VirtualHeap::FinishCreate(void)

    // ?Create@VirtualHeap@@QAEHPBUHeapParameters@1@PAX@Z
    // public: int __thiscall VirtualHeap::Create(struct VirtualHeap::HeapParameters const *, void *)
    bool32 Create(const HeapParameters *parameters, void *address);

    // ?Destroy@VirtualHeap@@QAEXXZ
    void Destroy();

    // ?HeapExtend@VirtualHeap@@QAEXXZ
    void HeapExtend(void);

    // ?Reset@VirtualHeap@@QAEXXZ
    void Reset();

    // ?GetAlignedPages@VirtualHeap@@QAEPAXIPAI@Z
    void * GetAlignedPages(size_t countPages, size_t *ptrFree);

    class SubAllocator {
    public:

        // ??0SubAllocator@VirtualHeap@@QAE@IW4lifetime_e@@@Z
        // public: __thiscall VirtualHeap::SubAllocator::SubAllocator(unsigned int, enum lifetime_e)

        // ??0SubAllocator@VirtualHeap@@QAE@IPAV1@@Z
        // public: __thiscall VirtualHeap::SubAllocator::SubAllocator(unsigned int, class VirtualHeap *)

        // ??0SubAllocator@VirtualHeap@@QAE@I@Z
        // public: __thiscall VirtualHeap::SubAllocator::SubAllocator(unsigned int)

        // ?Create@SubAllocator@VirtualHeap@@QAEXW4lifetime_e@@@Z
        void Create(lifetime_e);

        // ?Create@SubAllocator@VirtualHeap@@QAEXPAV2@@Z
        // public: void __thiscall VirtualHeap::SubAllocator::Create(class VirtualHeap *)

        // ?Clear@SubAllocator@VirtualHeap@@QAEXXZ
        // public: void __thiscall VirtualHeap::SubAllocator::Clear(void)

        void * Allocate(size_t size) {
            size = (size + 0x3) & ~0x3;
            if (FreeSize < size) {
                GetMemory(size);
            }
            void *result = fpFreeBlock;
            FreeSize -= size;
            fpFreeBlock = (void *)((uintptr_t)fpFreeBlock + size);
            return result;
        }

    private:
        // ?GetMemory@SubAllocator@VirtualHeap@@AAEXI@Z
        void GetMemory(size_t amount);

        void *fpFreeBlock;
        size_t FreeSize;
        size_t nPages;
        VirtualHeap *pHeap;
    };

    void * Allocate(size_t size) {
        void *result = fpFreeBlock;
        fpFreeBlock = (void *)((uintptr_t)fpFreeBlock + size);
        if (fpFreeBlock > fpFreeEnd) {
            HeapExtend();
        }
        return result;
    }

public:
    // ?Reallocate@VirtualHeap@@QAEPAXPAXII@Z
    // public: void * __thiscall VirtualHeap::Reallocate(void *, unsigned int, unsigned int)

private:
    void *fpFreeBlock;
    void *fpFreeEnd;
    void *fpBaseAddress;
    size_t lCurrentSize;
    const HeapParameters *pParameters;
    size_t lMaxSize;
    undefined4 field_0x18;
    undefined4 field_0x1c;
};

template <typename EntryType, unsigned Count=1>
class SAClass {
    static VirtualHeap::SubAllocator m_allocator;
public:
    static void Initialize(lifetime_e lifetime=M_LIFETIME0) {
        m_allocator.Create(lifetime);
    }
    static void *Allocate(size_t size) {
        return m_allocator.Allocate(size);
    }
    static EntryType *Allocate() {
        return static_cast<EntryType *>(m_allocator.Allocate(sizeof(EntryType)));
    }
};

struct GeneralAllocator_t{};
struct SymbolAllocator_t{};
struct TypeEntry_t{};
struct IndirEntry_t{};
struct FlistEntry_t{};
struct Assoc_t{};
struct Id_t;
struct s_defn{};
struct Token;

// VTABLE: C1 0x00457f70
class PCHHeap {
public:
    // ?SaveDescriptor@PCHHeap@@UAEXPAX@Z
    // public: virtual void __thiscall PCHHeap::SaveDescriptor(void *)

    // ?CopyHeap@PCHHeap@@SAPAV1@PBV1@PAVPCHHeapManager@@@Z
    // public: static class PCHHeap * __cdecl PCHHeap::CopyHeap(class PCHHeap const *, class PCHHeapManager *)

    // ?LoadDescriptor@PCHHeap@@SAPAV1@PAXPAVPCHHeapManager@@@Z
    // public: static class PCHHeap * __cdecl PCHHeap::LoadDescriptor(void *, class PCHHeapManager *)

    virtual void UnLoad() = 0;

    undefined4 GetStatus() const {
        return m_status;
    }
protected:
    // ??0PCHHeap@@IAE@W4Mode_e@0@PAVPCHHeapManager@@@Z
    // protected: __thiscall PCHHeap::PCHHeap(enum PCHHeap::Mode_e, class PCHHeapManager *)

    undefined field_0x4[0xc - 0x4];
    undefined4 m_status;
};

// VTABLE: C1 0x00457fb8
class LocalPCHHeap : public PCHHeap {
    // ??0LocalPCHHeap@@QAE@PAVVirtualHeap@@PAVPCHHeapManager@@@Z
    // public: __thiscall LocalPCHHeap::LocalPCHHeap(class VirtualHeap *, class PCHHeapManager *)

    // ??0LocalPCHHeap@@IAE@ABV0@PAVPCHHeapManager@@@Z
    // protected: __thiscall LocalPCHHeap::LocalPCHHeap(class LocalPCHHeap const &, class PCHHeapManager *)

    // ??0LocalPCHHeap@@IAE@PAXW4Mode_e@PCHHeap@@PAVPCHHeapManager@@@Z
    // protected: __thiscall LocalPCHHeap::LocalPCHHeap(void *, enum PCHHeap::Mode_e, class PCHHeapManager *)

    // ?MapAtAddress@LocalPCHHeap@@UAE?AW4Status_e@PCHHeap@@PAXH0@Z
    // public: virtual enum PCHHeap::Status_e __thiscall LocalPCHHeap::MapAtAddress(void *, int, void *)

    // ?LoadAtAddress@LocalPCHHeap@@UAE?AW4Status_e@PCHHeap@@PAX@Z
    // public: virtual enum PCHHeap::Status_e __thiscall LocalPCHHeap::LoadAtAddress(void *)

    // ?LoadAnywhere@LocalPCHHeap@@UAE?AW4Status_e@PCHHeap@@PAX0@Z
    // public: virtual enum PCHHeap::Status_e __thiscall LocalPCHHeap::LoadAnywhere(void *, void *)

    // ?ReadHeap@LocalPCHHeap@@IAEXPAX@Z
    // protected: void __thiscall LocalPCHHeap::ReadHeap(void *)

    // ?WriteHeap@LocalPCHHeap@@IAEXPAX@Z
    // protected: void __thiscall LocalPCHHeap::WriteHeap(void *)

    // ?MoveTheHeap@LocalPCHHeap@@IAEXXZ
    // protected: void __thiscall LocalPCHHeap::MoveTheHeap(void)

    // ?UnLoad@LocalPCHHeap@@UAEXXZ
    void UnLoad() override;

    // ?SaveNewHeap@LocalPCHHeap@@UAEXPAX@Z
    // public: virtual void __thiscall LocalPCHHeap::SaveNewHeap(void *)

    // ?SaveFixedHeap@LocalPCHHeap@@UAEXPAX@Z
    // public: virtual void __thiscall LocalPCHHeap::SaveFixedHeap(void *)

    // ?SaveDescriptor@LocalPCHHeap@@UAEXPAX@Z
    // public: virtual void __thiscall LocalPCHHeap::SaveDescriptor(void *)

    // ?SaveBlankDescriptor@LocalPCHHeap@@SAXPAXPAE@Z
    // public: static void __cdecl LocalPCHHeap::SaveBlankDescriptor(void *, unsigned char *)

    // ?SkipBlankDescriptor@LocalPCHHeap@@SAXPAXPAE@Z
    // public: static void __cdecl LocalPCHHeap::SkipBlankDescriptor(void *, unsigned char *)

    // ?PrepareRelocation@LocalPCHHeap@@IAEXXZ
    // protected: void __thiscall LocalPCHHeap::PrepareRelocation(void)

    // ?PrepareFindPointers@LocalPCHHeap@@UAEXPAVVirtualHeap@@@Z
    // public: virtual void __thiscall LocalPCHHeap::PrepareFindPointers(class VirtualHeap *)

    // ?PrepareFixup@LocalPCHHeap@@UAEHPAV1@@Z
    // public: virtual int __thiscall LocalPCHHeap::PrepareFixup(class LocalPCHHeap *)

    // ?Fixup@LocalPCHHeap@@UAEXPAVPCHHeapManager@@@Z
    // public: virtual void __thiscall LocalPCHHeap::Fixup(class PCHHeapManager *)
};

// ?AddHeap@PCHHeapLocator@@QAEXPAVLocalPCHHeap@@PAXI@Z
// public: void __thiscall PCHHeapLocator::AddHeap(class LocalPCHHeap *, void *, unsigned int)

// SIZE: 0x44
class PCHHeapManager {
public:
    // ??0PCHHeapManager@@QAE@XZ
    // public: __thiscall PCHHeapManager::PCHHeapManager(void)

    // ?Create@PCHHeapManager@@QAEXH@Z
    // public: void __thiscall PCHHeapManager::Create(int)

    // ?Create@PCHHeapManager@@QAEXABV1@H@Z
    // public: void __thiscall PCHHeapManager::Create(class PCHHeapManager const &, int)

    // ?Create@PCHHeapManager@@QAEXPAEK@Z
    // public: void __thiscall PCHHeapManager::Create(unsigned char *, unsigned long)

    // ?Destroy@PCHHeapManager@@QAEXXZ
    void Destroy();

    // ?AddHeap@PCHHeapManager@@QAEXPAVVirtualHeap@@@Z
    // public: void __thiscall PCHHeapManager::AddHeap(class VirtualHeap *)

    // ?WriteToPCH@PCHHeapManager@@QAEXPAEK@Z
    // public: void __thiscall PCHHeapManager::WriteToPCH(unsigned char *, unsigned long)

    // ?LoadFromPCH@PCHHeapManager@@QAEHXZ
    // public: int __thiscall PCHHeapManager::LoadFromPCH(void)
    // ?UpdatePCH@PCHHeapManager@@QAEXXZ
    // public: void __thiscall PCHHeapManager::UpdatePCH(void)

    // ?FoundPointerInHeap@PCHHeapManager@@QAEHPAPAX@Z
    // public: int __thiscall PCHHeapManager::FoundPointerInHeap(void **)

    // ?AdjustPointerIntoHeap@PCHHeapManager@@QAEHPAPAX@Z
    // public: int __thiscall PCHHeapManager::AdjustPointerIntoHeap(void **)

private:
    // ?WritePCHHeader@PCHHeapManager@@AAEXXZ
    // private: void __thiscall PCHHeapManager::WritePCHHeader(void)

    // ?MakeMemoryMap@PCHHeapManager@@AAEPAXKPAPAX@Z
    // private: void * __thiscall PCHHeapManager::MakeMemoryMap(unsigned long, void **)

    // ?RelocateHeaps@PCHHeapManager@@AAEXH@Z
    // private: void __thiscall PCHHeapManager::RelocateHeaps(int)

    // ?MakePCHHeapLocator@PCHHeapManager@@AAEPAVPCHHeapLocator@@P8PCHHeap@@BEPAXXZ@Z
    // private: class PCHHeapLocator * __thiscall PCHHeapManager::MakePCHHeapLocator(void * (__thiscall PCHHeap::*)(void) const)

    size_t m_nHeaps;
    undefined m_field_0x4[4];
    PCHHeap **m_theHeaps;
    undefined m_field_0xc[4];
    char *m_field_0x10;
    undefined m_field_0x14[4];
#ifdef _WIN32
    HANDLE m_field_0x18;
    HANDLE m_field_0x1c;
    HANDLE m_field_0x20;
    HANDLE m_field_0x24;
    HANDLE m_field_0x28;
    HANDLE m_field_0x2c;
    HANDLE m_field_0x30;
#endif
    undefined m_field_0x34[0x44-0x34];
};

// _$E31

// _$E30

// SIZE: 0x44
class HeapManager {
public:
    // ?InitGlobalHeaps@HeapManager@@SAXXZ
    // public: static void __cdecl HeapManager::InitGlobalHeaps(void)
    static void InitGlobalHeaps();

    // ?ActiveHeaps@HeapManager@@2PAVVirtualHeap@@A
    // public: static class VirtualHeap *HeapManager::ActiveHeaps
    static VirtualHeap ActiveHeaps[M_LIFEMAX];

    static void *Allocate(size_t size, lifetime_e lifetime) {
        return ActiveHeaps[lifetime].Allocate(size);
    }
    template<typename Type>
    static Type *Allocate(lifetime_e lifetime) {
        return static_cast<Type *>(Allocate(sizeof(Type), lifetime));
    }

    static void Destroy() {
        size_t i;

        ThePCH.Destroy();
        for (i = 0; i < arraysize(ActiveHeaps); i++) {
            ActiveHeaps[i].Destroy();
        }
    }

private:
    // ?InitPCHLifeHeaps@HeapManager@@CAXXZ
    // private: static void __cdecl HeapManager::InitPCHLifeHeaps(void)
    static void InitPCHLifeHeaps();

    // ?DestroyPCHLifeHeaps@HeapManager@@CAXXZ
    // private: static void __cdecl HeapManager::DestroyPCHLifeHeaps(void)

    // ?ReleaseAllHeaps@HeapManager@@SAXXZ
    // public: static void __cdecl HeapManager::ReleaseAllHeaps(void)

    // ?CreatePCH@HeapManager@@SAXPAEK@Z
    // public: static void __cdecl HeapManager::CreatePCH(unsigned char *, unsigned long)

    // ?LoadPCH@HeapManager@@SAHPAEK@Z
    // public: static int __cdecl HeapManager::LoadPCH(unsigned char *, unsigned long)

    // ?ThePCH@HeapManager@@2VPCHHeapManager@@A
    static PCHHeapManager ThePCH;

    // ?m_hMap@HeapManager@@0PAXA
    // private: static void *HeapManager::m_hMap

    static const VirtualHeap::HeapParameters TheHeapParameters[M_LIFEMAX];
};

// ?QueryLocalHeap@LocalPCHHeap@@UAEPAV1@XZ
// public: virtual class LocalPCHHeap * __thiscall LocalPCHHeap::QueryLocalHeap(void)

// ?GetSavedAddress@LocalPCHHeap@@UBEPAXXZ
// public: virtual void * __thiscall LocalPCHHeap::GetSavedAddress(void) const

// ?GetLoadAddress@LocalPCHHeap@@UBEPAXXZ
// public: virtual void * __thiscall LocalPCHHeap::GetLoadAddress(void) const

// ?GetExactSize@LocalPCHHeap@@UBEIXZ
// public: virtual unsigned int __thiscall LocalPCHHeap::GetExactSize(void) const

// ?GetLoadPriority@LocalPCHHeap@@UBE?AW4LoadPriority_e@@XZ
// public: virtual enum LoadPriority_e __thiscall LocalPCHHeap::GetLoadPriority(void) const

// ??_9@$BDA@AE
// [thunk]: __thiscall `vcall'{48, {flat}}

// ??_9@$BDE@AE
// [thunk]: __thiscall `vcall'{52, {flat}}

#endif /* NHEAPALL_H */
