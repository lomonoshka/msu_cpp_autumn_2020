#include "matrix.h"
#include "test_runner.h"

int main() {
  array<int> a({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  a += 2;
  array<int> v(a);
  std::cout << v[0] << std::endl;
  for(int i = 0; i < 10; ++i) {
    std::cout << a[i] << " ";
  }
}
