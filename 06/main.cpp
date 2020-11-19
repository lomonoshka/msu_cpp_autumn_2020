#include <iostream>
#include "format.h"
#include "test_runner.h"
#include "tests.cpp"

int main()
{
    TestRunner tr;
    RUN_TEST(tr, test_format);
    return 0;
}
