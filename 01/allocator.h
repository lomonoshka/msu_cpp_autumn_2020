#pragma once
#include <cstdlib>

class LinearAllocator
{
public:

  LinearAllocator();
  ~LinearAllocator();

  void makeAllocator(size_t max_size);
  char* alloc(size_t size);
  void reset();
  size_t capacity();
  size_t size();
  bool empty();
private:
  char* initial_ptr_;
  size_t capacity_;
  size_t size_;
};
