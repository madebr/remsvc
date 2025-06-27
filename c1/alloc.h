#pragma once

#include "decomp.h"

#include <stdint.h>
#include <windows.h>

typedef struct tPCH_chunk_info {
    undefined4 field_0x0;   // offet 0x00
    uint32_t maxSize;       // offet 0x04
    uint32_t itemSize;      // offet 0x08
    uint32_t flags;         // offet 0x0c
    undefined4 field_0x10;  // offet 0x10
} tPCH_chunk_info;

class tPCH_chunk {
public:
    BOOL Initialize(tPCH_chunk_info *chunk_info, void *startAddress);
    void *AllocatePages(size_t count_pages, size_t *actualSize);
    void Reset();

    inline void *Allocate(size_t size) {
        void *result = (void *)m_mem_commited_next_free;
        m_mem_commited_next_free += (size + sizeof(uintptr_t) - 1) & ~(sizeof(uintptr_t) - 1);
        if (m_mem_commited_end < m_mem_commited_next_free) {
            IncreaseCommitedMemoryBlock();
        }
        return result;
    }
private:
    void IncreaseCommitedMemoryBlock();

    uintptr_t m_mem_commited_next_free;     // offset 0x00
    uintptr_t m_mem_commited_end;           // offset 0x04
    uintptr_t m_address;                    // offset 0x08
    size_t m_commited_size;                 // offset 0x0c
    tPCH_chunk_info *m_chunk_info;          // offset 0x10
    undefined4 m_maxSize;                   // offset 0x14
    undefined4 m_field_0x18;                // offset 0x18
    undefined4 m_field_0x1c;                // offset 0x1c
};

class tPCH_allocated_chunk {
public:
    tPCH_allocated_chunk(uint32_t minSize=1);

    inline void *Allocate(size_t size) {
        size = (size + sizeof(void *) - 1) & ~(sizeof(void *) - 1);
        if (m_mem_left < size) {
            IncreaseHeapByAtLeast(size);
        }
        void *result = m_ptr_free;
        m_mem_left -= size;
        m_ptr_free = (void *)((uintptr_t)m_ptr_free + size);
        return result;
    }

    void SelectChunk(int chunk_id);
    void IncreaseHeapByAtLeast(size_t size);
private:
    void *m_ptr_free;       // offset 0x0
    size_t m_mem_left;      // offset 0x4
    size_t m_min_size;      // offset 0x8
    tPCH_chunk *m_chunk;    // offset 0xc
};
