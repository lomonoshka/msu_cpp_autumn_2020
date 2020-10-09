#include "allocator.h"
#include <iostream>

LinearAllocator::LinearAllocator():
initial_ptr(nullptr), capacity(0), size(0)
{
}

void LinearAllocator::makeAllocator(size_t max_size) {
  if(initial_ptr != nullptr) {
    std::realloc(initial_ptr, max_size);
  } else {
    initial_ptr = std::static_cast(char *)std::malloc(max_size * sizeof(char));
    capacity = max_size;
    size = capacity;
  }
}

char* LinearAllocator::alloc(size_t size_) {
  if(size < size_) {
    return nullptr;
  } else {
    size_t ptr_shift = capacity - size;
    size -= size_;
    cur_ptr += size;
    return ptr + ptr_shift;
  }
}

void LinearAllocator::reset() {
  cur_ptr = initial_ptr;
  free_memory = total_memory;
}

LinearAllocator::~LinearAllocator() {
  std::free(initial_ptr);
}
