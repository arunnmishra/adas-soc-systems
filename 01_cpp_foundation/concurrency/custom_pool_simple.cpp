#include <cstddef>
#include <cstdint>
#include <new>
#include <memory>
#include <iostream>
#include <string>

struct Node { 
    int data;
    Node* next;
}; // simple linked list node example

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
    void* allocate(){
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

template <typename T>
using ObjPtr = std::unique_ptr<T, NodeDeleter<T>>;

template<typename T, typename... Args>
ObjPtr<T> make_pool_object(FixedBlockPool& pool, Args&&... args)
{
    // allocate from pool
    void* mem = pool.allocate();
    if (!mem) return {nullptr, {&pool}};
    // construct object in allocated memory
    T* node = new (mem) T(std::forward<Args>(args)...);
    // return unique_ptr with NodeDeleter
    return ObjPtr<T>{node, NodeDeleter<T>{&pool}};
}

struct myCustomBlock    
{
    int id;
    std::string name;
    myCustomBlock(std::string v) : name(v) {
        std::cout << "Node constructed\n";
    }
    ~myCustomBlock() {
        std::cout << "Node destructed\n";
    }
    void display() { std::cout << "Block name: " << name << std::endl; }
    void setName(const std::string& newName) { name = newName; }
};


int main(void)
{
    constexpr size_t BLOCK_SIZE = sizeof(myCustomBlock);
    constexpr int BLOCK_COUNT = 20;
    alignas(myCustomBlock) uint8_t pool_mem[BLOCK_SIZE*BLOCK_COUNT];
    FixedBlockPool pool(pool_mem, BLOCK_SIZE, BLOCK_COUNT);
    
    ObjPtr<myCustomBlock> p1 = make_pool_object<myCustomBlock>(pool, "Block1");
    ObjPtr<myCustomBlock> p2 = make_pool_object<myCustomBlock>(pool, "Block2");
        // use p1, p2
     // p1, p2 go out of scope and are returned to the pool
    return 0;
}



/*
#include <iostream>
#include <memory>
#include <new>
#include <cstddef>
#include <algorithm>

struct Node {
    int value;
    Node(int v) : value(v) {
        std::cout << "Node constructed\n";
    }
    ~Node() {
        std::cout << "Node destructed\n";
    }
};

class FixedBlockPool {
    struct FreeNode { FreeNode* next; };

    FreeNode* free_list{nullptr};
    void*     memory{nullptr};
    size_t    block_size{0};
    size_t    block_count{0};

public:
    FixedBlockPool(void* mem, size_t blk_size, size_t blk_count)
        : memory(mem),
          block_size(std::max(blk_size, sizeof(FreeNode))),
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

struct NodeDeleter {
    FixedBlockPool* pool;

    void operator()(Node* p) const {
        if (!p) return;

        p->~Node();              // (1) destroy object
        pool->deallocate(p);     // (2) return memory to pool
    }
};

using NodePtr = std::unique_ptr<Node, NodeDeleter>;

NodePtr make_node(FixedBlockPool& pool, int value) {
    void* mem = pool.allocate();
    if (!mem) return {nullptr, NodeDeleter{&pool}};

    Node* obj = new (mem) Node(value);   // placement new
    return NodePtr(obj, NodeDeleter{&pool});
}

int main() {
    alignas(std::max_align_t)
    unsigned char buffer[4 * sizeof(Node)];

    FixedBlockPool pool(buffer, sizeof(Node), 4);

    {
        NodePtr n1 = make_node(pool, 10);
        NodePtr n2 = make_node(pool, 20);
    }   // automatic cleanup here

    return 0;
}


*/ 