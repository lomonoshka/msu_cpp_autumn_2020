#include "test_runner.h"
#include "tests.cpp"

void RunTests() {
  TestRunner tr;
  RUN_TEST(tr, TestCtors);
  RUN_TEST(tr, TestMethods);
}

int main() {
  RunTests();
  return 0;
}