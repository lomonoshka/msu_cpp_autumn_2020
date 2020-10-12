#include "allocator.h"
#include "test_runner.h"
#include "tests.h"
#include <cstdlib>

using namespace std;

void TestAll() {
    TestRunner tr;
    RUN_TEST(tr, TestOnCreate);
    RUN_TEST(tr, TestAlloc);
    RUN_TEST(tr, TestReset);  
}
int main()
{
    TestAll();
    return 0;
}
