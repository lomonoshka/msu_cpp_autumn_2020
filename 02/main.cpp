#include "parser.h"
#include "tests.h"
#include "test_runner.h"

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIsInteger);
  RUN_TEST(tr, TestParser);
  return 0;
}