#include <cstddef>
#include <cstdint>
#include <new>
#include <memory>

struct Node { 
    int data;
    Node* next;
};

class FixedBlockPool {
    // raw memory + free list
    struct FreeNode {
        FreeNode* next;
    };

    void *mem;
    FreeNode *free_list{nullptr};
    size_t block_size{0};
    size_t block_count{0};

public:
FixedBlockPool(void* memory, size_t blk_size, size_t blk_count):mem{memory},block_size{blk_size},block_count{blk_count}
    {
        uint8_t* p = static_cast<uint8_t*>(memory);
        for(size_t i=0;i<block_count;++i){
            auto* node = reinterpret_cast<FreeNode*>(p);
            node->next = free_list;
            free_list = node;
            p += block_size;
        }
    };
    void* allocate(int chunks){
        if(!free_list)
            return nullptr;
        FreeNode* node = free_list;
        free_list = node->next;
        return node;

    }
    void deallocate(void* p){
        auto* node = static_cast<FreeNode*>(p);
        node->next = free_list;
        free_list = node;
    }
};

template<typename T>
struct NodeDeleter {
    FixedBlockPool* pool;
    void operator()(T* p) const {
        if (!p) return;
        p->~T();
        pool->deallocate(p);
    }
};

using ObjPtr = std::unique_ptr<T, NodeDeleter>;

ObjPtr make_pool_object(FixedBlockPool& pool, int number_of_chunks)
{
    // allocate from pool
    void* mem = pool.allocate(number_of_chunks);
    if (!mem) return {nullptr, {&pool}};
    // construct object in allocated memory
    T* node = new (mem) T(number_of_chunks);
    // return unique_ptr with NodeDeleter
    return ObjPtr{node, NodeDeleter{&pool}};
}

void main(void)
{
    constexpr size_t POOL_SIZE = 1024;
    alignas(std::max_align_t) uint8_t pool_mem[POOL_SIZE];
    FixedBlockPool pool(pool_mem, /*block_size=*/sizeof(T), /*block_count=*/POOL_SIZE / sizeof(T));
    {
        ObjPtr p1 = make_pool_object<T>(pool, 3);
        ObjPtr p2 = make_pool_object<T>(pool, 5);
        // use p1, p2
    } // p1, p2 go out of scope and are returned to the pool

}
