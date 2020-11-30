#include "test_runner.h"
#include "tests.cpp"
#include <iostream>

int main()
{
    TestRunner tr;
    RUN_TEST(tr, test_thread_pool);
    return 0;
}
