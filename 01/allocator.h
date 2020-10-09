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

private:
  char* initial_ptr;
  size_t capacity;
  size_t size;
};
