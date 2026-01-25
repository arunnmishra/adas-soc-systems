#include <cstddef>
#include <cstdint>
#include <new>

class FixedBlockPool {      
    struct FreeNode { FreeNode* next; };

    FreeNode* free_list;
    void*     pool_mem;
    size_t    block_size;
    size_t    block_count;

public:
    FixedBlockPool(void* memory, size_t blk_size, size_t blk_count)
        : free_list(nullptr),
          pool_mem(memory),
          block_size(blk_size),
          block_count(blk_count)
    {
        uint8_t* p = static_cast<uint8_t*>(memory);
        for (size_t i = 0; i < block_count; ++i) {
            auto* node = reinterpret_cast<FreeNode*>(p);
            node->next = free_list;
            free_list  = node;
            p += block_size;
        }
    }

    void* allocate() {
        if (!free_list) return nullptr;
        FreeNode* node = free_list;
        free_list = node->next;
        return node;
    }

    void deallocate(void* p) {
        auto* node = static_cast<FreeNode*>(p);
        node->next = free_list;
        free_list  = node;
    }
};


template<typename T>
struct PoolDeleter {
    FixedBlockPool* pool;

    void operator()(T* p) const {
        if (!p) return;
        p->~T();               // explicit destructor
        pool->deallocate(p);  // return block
    }
};

#include <memory>

template<typename T, typename... Args>
std::unique_ptr<T, PoolDeleter<T>>
make_pool_object(FixedBlockPool& pool, Args&&... args)
{
    void* mem = pool.allocate();
    if (!mem) return {nullptr, {&pool}};

    T* obj = new (mem) T(std::forward<Args>(args)...);

    return std::unique_ptr<T, PoolDeleter<T>>(
        obj,
        PoolDeleter<T>{&pool}
    );
}

#include <iostream>

struct Msg {
    int id;
    int padding;
    Msg(int i) : id(i) {
        std::cout << "Msg constructed\n";
    }
    ~Msg() {
        std::cout << "Msg destructed\n";
    }
};

int main() {
    alignas(Msg) uint8_t buffer[10 * sizeof(Msg)];

    FixedBlockPool pool(buffer, sizeof(Msg), 10);

    auto m1 = make_pool_object<Msg>(pool, 42);
    auto m2 = make_pool_object<Msg>(pool, 100);

    // RAII:
    // - m1 / m2 go out of scope
    // - destructor called
    // - memory returned to pool
    }