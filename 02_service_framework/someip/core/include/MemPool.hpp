#pragma once
#include <cstddef>
#include <cstdint>
#include <new>

// Simple fixed-size block memory pool (arena allocator)
template<size_t BlockSize, size_t BlockCount>
class MemPool
{
    struct FreeNode { FreeNode* next; };

    alignas(std::max_align_t) uint8_t buffer[BlockSize * BlockCount];
    FreeNode* free_list{nullptr};

public:
    MemPool()
    {
        uint8_t* p = buffer;
        for (size_t i = 0; i < BlockCount; ++i)
        {
            auto* node = reinterpret_cast<FreeNode*>(p);
            node->next = free_list;
            free_list = node;
            p += BlockSize;
        }
    }

    void* allocate()
    {
        if (!free_list) return nullptr;
        FreeNode* node = free_list;
        free_list = node->next;
        return node;
    }

    void deallocate(void* p)
    {
        auto* node = static_cast<FreeNode*>(p);
        node->next = free_list;
        free_list = node;
    }
};
