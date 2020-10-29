#include "tests.cpp"

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConstuctor);
  RUN_TEST(tr, TestOperators);
  RUN_TEST(tr, TestIndex);
}
