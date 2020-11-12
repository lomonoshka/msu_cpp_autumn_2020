#include "Bigint.h"
#include "tests.h"
#include "test_runner.h"

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestWithBasicNumber);
    RUN_TEST(tr, TestWithPowerOfTwo);
    RUN_TEST(tr, TestFfp);
    return 0;
}
