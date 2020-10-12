#include "tests.h"

void TestOnCreate() {
    {
        const size_t capacity = 10;
        LinearAllocator al;
        al.makeAllocator(capacity);
        ASSERT(!al.empty() && al.capacity() == capacity && al.size() == capacity);
    }

    {
        const size_t capacity1 = 10, capacity2 = 15;
        LinearAllocator al;
        al.makeAllocator(capacity1);
        al.makeAllocator(capacity2);
        ASSERT(!al.empty() && al.capacity() == capacity2 && al.size() == capacity2);
    }

    {
        const size_t capacity1 = 15, capacity2 = 10;
        LinearAllocator al;
        al.makeAllocator(capacity1);
        al.makeAllocator(capacity2);
        ASSERT(!al.empty() && al.capacity() == capacity2 && al.size() == capacity2);
    }
}

void TestAlloc() {
    {
        const size_t capacity = 10;
        size_t size = capacity;
        LinearAllocator al;
        al.makeAllocator(capacity);
        char* ptr1 = al.alloc(5);
        size -= 5;
        ASSERT(ptr1 != nullptr && al.capacity() == capacity && al.size() == size)
        char* ptr2 = al.alloc(6);
        ASSERT(ptr2 == nullptr && al.capacity() == capacity && al.size() == size)
        char* ptr3 = al.alloc(4);
        size -= 4;
        ASSERT(ptr3 != nullptr && al.capacity() == capacity && al.size() == size)
        
    }

    {
        const size_t capacity = 10;
        size_t size = capacity;
        LinearAllocator al;
        al.makeAllocator(capacity);
        char* ptr1 = al.alloc(0);
        ASSERT(al.capacity() == capacity && al.size() == size);
    }
}

void TestReset() {
    const size_t capacity = 10;
    size_t size = capacity;
    LinearAllocator al;
    al.makeAllocator(capacity);
    char* ptr1 = al.alloc(5);
    al.reset();
    ASSERT(al.capacity() == capacity && al.size() == size);
}