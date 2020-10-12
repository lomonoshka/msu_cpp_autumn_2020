#include "allocator.h"
#include <iostream>

LinearAllocator::LinearAllocator():
initial_ptr_(nullptr), capacity_(0), size_(0)
{
}

size_t LinearAllocator::capacity() {
  return capacity_;
}

size_t LinearAllocator::size() {
  return size_;
}

bool LinearAllocator::empty() {
  return initial_ptr_ == nullptr;
}

void LinearAllocator::makeAllocator(size_t capacity) {
  if(initial_ptr_ != nullptr) {
    initial_ptr_ = static_cast<char*>(std::realloc(initial_ptr_, capacity));
  } else {
    initial_ptr_ = static_cast<char*>(std::malloc(capacity * sizeof(char)));
  }
  capacity_ = capacity;
  size_ = capacity_;
}

char* LinearAllocator::alloc(size_t size) {
  if(size_ < size) {
    return nullptr;
  } else {
    size_t ptr_shift = capacity_ - size_;
    size_ -= size;
    return initial_ptr_ + ptr_shift;
  }
}

void LinearAllocator::reset() {
  size_ = capacity_;
}

LinearAllocator::~LinearAllocator() {
  std::free(initial_ptr_);
}
